/*
 * Copyright (C) 2019  Christian Berger
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "cluon-complete.hpp"
#include "opendlv-standard-message-set.hpp"
#include "lynx19gw.hpp"

#include <sys/ioctl.h>
#include <sys/socket.h>
#include <sys/select.h>

#ifdef __linux__
    #include <linux/if.h>
    #include <linux/can.h>
#endif

#include <unistd.h>

#include <cerrno>
#include <cstdint>
#include <cstring>

#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>

int32_t main(int32_t argc, char **argv) {
    int32_t retCode{1};
    auto commandlineArguments = cluon::getCommandlineArguments(argc, argv);
    if ( (0 == commandlineArguments.count("cid")) ) {
        std::cerr << argv[0] << " translates messages from CAN to ODVD messages and vice versa." << std::endl;
        std::cerr << "Usage:   " << argv[0] << " --cid=<OD4 session> [--id=ID] --can=<name of the CAN device> [--enablethrottle] [--enablebrake] [--enablesteering] [--verbose]" << std::endl;
        std::cerr << "         --cid:    CID of the OD4Session to send and receive messages" << std::endl;
        std::cerr << "         --id:     ID to use as senderStamp for sending" << std::endl;
        std::cerr << "Example: " << argv[0] << " --cid=111 --can=can0 --enablethrottle --enablebrake --enablesteering --verbose" << std::endl;
    }
    else {
        const std::string CANDEVICE{commandlineArguments["can"]};
        const uint32_t ID{(commandlineArguments["id"].size() != 0) ? static_cast<uint32_t>(std::stoi(commandlineArguments["id"])) : 0};
        const bool VERBOSE{commandlineArguments.count("verbose") != 0};

        const bool ENABLED_ACTUATION_THROTTLE{commandlineArguments.count("enablethrottle") != 0};
        const bool ENABLED_ACTUATION_BRAKE{commandlineArguments.count("enablebrake") != 0};
        const bool ENABLED_ACTUATION_STEERING{commandlineArguments.count("enablesteering") != 0};

        // Interface to a running OpenDaVINCI session; here, you can send and receive messages.
        cluon::OD4Session od4{static_cast<uint16_t>(std::stoi(commandlineArguments["cid"]))};

        // Delegate to convert incoming CAN frames into ODVD messages that are broadcast into the OD4Session.
        auto decode = [&od4, VERBOSE, ID](cluon::data::TimeStamp ts, uint16_t canFrameID, uint8_t *src, uint8_t len) {
            if ( (nullptr == src) || (0 == len) ) return;

            if (LYNX19GW_DL_AS_STATUS_FRAME_ID == canFrameID) {
                lynx19gw_dl_as_status_t tmp;
                if (0 == lynx19gw_dl_as_status_unpack(&tmp, src, len)) {
                    opendlv::proxy::AsStatus msg;
                    msg.asMission(lynx19gw_dl_as_status_as_mission_decode(tmp.as_mission));
                    // The following block is automatically added to demonstrate how to display the received values.
                    {
                        std::stringstream sstr;
                        msg.accept([](uint32_t, const std::string &, const std::string &) {},
                                [&sstr](uint32_t, std::string &&, std::string &&n, auto v) { sstr << n << " = " << v << '\n'; },
                                []() {});
                        std::cout << sstr.str() << std::endl;
                    }
                }
            }
            
            if (LYNX19GW_NF_NR_SENSORS_1_FRAME_ID == canFrameID) {
                lynx19gw_nf_nr_sensors_1_t tmp;
                if (0 == lynx19gw_nf_nr_sensors_1_unpack(&tmp, src, len)) {
                    opendlv::proxy::TorqueReading msg;
                    msg.torque(lynx19gw_nf_nr_sensors_1_throttle_decode(tmp.throttle));
                    // The following block is automatically added to demonstrate how to display the received values.
                    {
                        std::stringstream sstr;
                        msg.accept([](uint32_t, const std::string &, const std::string &) {},
                                [&sstr](uint32_t, std::string &&, std::string &&n, auto v) { sstr << n << " = " << v << '\n'; },
                                []() {});
                        std::cout << sstr.str() << std::endl;
                    }
                }
            }
            
        };

#ifdef __linux__
        struct sockaddr_can address;
#endif
        int socketCAN;

        std::cerr << "[opendlv-device-cangw-lynx] Opening " << CANDEVICE << "... ";
#ifdef __linux__
        // Create socket for SocketCAN.
        socketCAN = socket(PF_CAN, SOCK_RAW, CAN_RAW);
        if (socketCAN < 0) {
            std::cerr << "failed." << std::endl; 

            std::cerr << "[opendlv-device-cangw-lynx] Error while creating socket: " << strerror(errno) << std::endl;
        }

        // Try opening the given CAN device node.
        struct ifreq ifr;
        memset(&ifr, 0, sizeof(ifr));
        strcpy(ifr.ifr_name, CANDEVICE.c_str());
        if (0 != ioctl(socketCAN, SIOCGIFINDEX, &ifr)) {
            std::cerr << "failed." << std::endl;

            std::cerr << "[opendlv-device-cangw-lynx] Error while getting index for " << CANDEVICE << ": " << strerror(errno) << std::endl;
            return retCode;
        }

        // Setup address and port.
        memset(&address, 0, sizeof(address));
        address.can_family = AF_CAN;
        address.can_ifindex = ifr.ifr_ifindex;

        if (bind(socketCAN, reinterpret_cast<struct sockaddr *>(&address), sizeof(address)) < 0) {
            std::cerr << "failed." << std::endl;

            std::cerr << "[opendlv-device-cangw-lynx] Error while binding socket: " << strerror(errno) << std::endl;
            return retCode;
        }
        std::cerr << "done." << std::endl;
#else
        std::cerr << "failed (SocketCAN not available on this platform). " << std::endl;
        return retCode;
#endif

        // Delegate for handling incoming opendlv.proxy.ActuationRequest.
        auto onActuationRequest = [&socketCAN, ENABLED_ACTUATION_BRAKE, ENABLED_ACTUATION_THROTTLE, ENABLED_ACTUATION_STEERING](cluon::data::Envelope &&env){
            opendlv::proxy::ActuationRequest ar = cluon::extractMessage<opendlv::proxy::ActuationRequest>(std::move(env));

            const float acceleration{ar.acceleration()};
            if (acceleration < 0.0f) {
                // opendlv::proxy::lynx::BrakeRequest brakeRequest;
                // brakeRequest.enableRequest(ENABLED_ACTUATION_BRAKE && isValid);

                // const float max_deceleration{2.0f};
                // if (acceleration < -max_deceleration) {
                //     if (ENABLED_ACTUATION_BRAKE && isValid) {
                //       std::clog << "[opendlv-device-cangw-lynx] WARNING: Deceleration was limited to " 
                //         << max_deceleration << ". This should never happen, and "
                //         << "may be a safety violating behaviour!" 
                //         << std::endl;
                //     }
                //     brakeRequest.brake(-max_deceleration);
                // }
                // else {
                //     brakeRequest.brake(acceleration);
                // }

                {
//                     lynx19gw_brake_request_t tmp;
//                     tmp.brake_request = lynx19gw_brake_request_brake_request_encode(brakeRequest.brake());
//                     tmp.enable_brake_request = lynx19gw_brake_request_enable_brake_request_encode(brakeRequest.enableRequest());

//                     // The following statement packs the encoded values into a CAN frame.
//                     uint8_t buffer[8];
//                     int len = lynx19gw_brake_request_pack(buffer, &tmp, 8);
//                     if ( (0 < len) && (-1 < socketCAN) ) {
// #ifdef __linux__
//                         struct can_frame frame;
//                         frame.can_id = lynx19gw_BRAKE_REQUEST_FRAME_ID;
//                         frame.can_dlc = len;
//                         memcpy(frame.data, buffer, 8);
//                         int32_t nbytes = ::write(socketCAN, &frame, sizeof(struct can_frame));
//                         if (!(0 < nbytes)) {
//                             std::clog << "[SocketCANDevice] Writing ID = " << frame.can_id << ", LEN = " << +frame.can_dlc << ", strerror(" << errno << "): '" << strerror(errno) << "'" << std::endl;
//                         }
// #endif
//                     }
                }
            }
            else {
                // opendlv::proxy::lynx::AccelerationRequest accelerationRequest;
                // accelerationRequest.enableRequest(ENABLED_ACTUATION_THROTTLE && isValid);
                // accelerationRequest.accelerationPedalPosition(acceleration);

                {
//                     lynx19gw_acceleration_request_t tmp;
//                     tmp.acceleration_request_pedal = lynx19gw_acceleration_request_acceleration_request_pedal_encode(accelerationRequest.accelerationPedalPosition());
//                     tmp.enable_acc_request = lynx19gw_acceleration_request_enable_acc_request_encode(accelerationRequest.enableRequest());

//                     // The following statement packs the encoded values into a CAN frame.
//                     uint8_t buffer[8];
//                     int len = lynx19gw_acceleration_request_pack(buffer, &tmp, 8);
//                     if ( (0 < len) && (-1 < socketCAN) ) {
// #ifdef __linux__
//                         struct can_frame frame;
//                         frame.can_id = lynx19gw_ACCELERATION_REQUEST_FRAME_ID;
//                         frame.can_dlc = len;
//                         memcpy(frame.data, buffer, 8);
//                         int32_t nbytes = ::write(socketCAN, &frame, sizeof(struct can_frame));
//                         if (!(0 < nbytes)) {
//                             std::clog << "[SocketCANDevice] Writing ID = " << frame.can_id << ", LEN = " << +frame.can_dlc << ", strerror(" << errno << "): '" << strerror(errno) << "'" << std::endl;
//                         }
// #endif
//                     }
                }
            }

            // opendlv::proxy::lynx::SteeringRequest steeringRequest;
            // steeringRequest.enableRequest(ENABLED_ACTUATION_STEERING && isValid);
            // steeringRequest.steeringRoadWheelAngle(ar.steering());
            // // Must be 33.535 to disable deltatorque.
            // steeringRequest.steeringDeltaTorque(33.535);

            {
                // // Message to encode: LYNX19GW_AS_DL_SENSORS_FRAME_ID
                // {
                //     lynx19gw_as_dl_sensors_t tmp;
                //     memset(&tmp, 0, sizeof(tmp));
                //     // The following msg would have to be passed to this encoder externally.
                //     opendlv::proxy::SwitchStateRequest msg;
                //     tmp.as_state = lynx19gw_as_dl_sensors_as_state_encode(msg.state());
                //     // The following statement packs the encoded values into a CAN frame.
                //     int size = lynx19gw_as_dl_sensors_pack(dst, &tmp, len);
                //     return size;
                // }


//                 lynx19gw_steer_request_t tmp;
//                 tmp.steer_req_delta_trq = lynx19gw_steer_request_steer_req_delta_trq_encode(steeringRequest.steeringDeltaTorque());
//                 tmp.steer_req_rwa = lynx19gw_steer_request_steer_req_rwa_encode(steeringRequest.steeringRoadWheelAngle());
//                 tmp.enable_steer_req = lynx19gw_steer_request_enable_steer_req_encode(steeringRequest.enableRequest());

//                 // The following statement packs the encoded values into a CAN frame.
//                 uint8_t buffer[8];
//                 int len = lynx19gw_steer_request_pack(buffer, &tmp, 8);
//                 if ( (0 < len) && (-1 < socketCAN) ) {
// #ifdef __linux__
//                     struct can_frame frame;
//                     frame.can_id = lynx19gw_STEER_REQUEST_FRAME_ID;
//                     frame.can_dlc = len;
//                     memcpy(frame.data, buffer, 8);
//                     int32_t nbytes = ::write(socketCAN, &frame, sizeof(struct can_frame));
//                     if (!(0 < nbytes)) {
//                         std::clog << "[SocketCANDevice] Writing ID = " << frame.can_id << ", LEN = " << +frame.can_dlc << ", strerror(" << errno << "): '" << strerror(errno) << "'" << std::endl;
//                     }
// #endif
//                 }
            }
        };

        // Register our lambda for the message identifier for opendlv::proxy::lynx::AccelerationRequest.
        od4.dataTrigger(opendlv::proxy::ActuationRequest::ID(), onActuationRequest);

        struct can_frame frame;
        fd_set rfds;
        struct timeval timeout;
        struct timeval socketTimeStamp;
        int32_t nbytes = 0;

        while (od4.isRunning() && socketCAN > -1) {
#ifdef __linux__
            timeout.tv_sec = 1;
            timeout.tv_usec = 0;

            FD_ZERO(&rfds);
            FD_SET(socketCAN, &rfds);

            select(socketCAN + 1, &rfds, NULL, NULL, &timeout);

            if (FD_ISSET(socketCAN, &rfds)) {
                nbytes = read(socketCAN, &frame, sizeof(struct can_frame));
                if ( (nbytes > 0) && (nbytes == sizeof(struct can_frame)) ) {
                    // Get receiving time stamp.
                    if (0 != ioctl(socketCAN, SIOCGSTAMP, &socketTimeStamp)) {
                        // In case the ioctl failed, use traditional vsariant.
                        cluon::data::TimeStamp now{cluon::time::now()};
                        socketTimeStamp.tv_sec = now.seconds();
                        socketTimeStamp.tv_usec = now.microseconds();
                    }
                    cluon::data::TimeStamp sampleTimeStamp;
                    sampleTimeStamp.seconds(socketTimeStamp.tv_sec)
                                   .microseconds(socketTimeStamp.tv_usec);
                    decode(sampleTimeStamp, frame.can_id, frame.data, frame.can_dlc);
                }
            }
#endif
        }

        std::clog << "[opendlv-device-cangw-lynx] Closing " << CANDEVICE << "... ";
        if (socketCAN > -1) {
            close(socketCAN);
        }
        std::clog << "done." << std::endl;

        retCode = 0;
    }
    return retCode;
}

