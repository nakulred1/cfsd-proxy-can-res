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
#include "lynxres19gw.hpp"

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
        std::cerr << "Usage:   " << argv[0] << " --cid=<OD4 session> [--id=ID] --can=<name of the CAN device> [--verbose]" << std::endl;
        std::cerr << "         --cid:    CID of the OD4Session to send and receive messages" << std::endl;
        std::cerr << "         --id:     ID to use as senderStamp for sending" << std::endl;
        std::cerr << "Example: " << argv[0] << " --cid=111 --can=can1 --verbose" << std::endl;
    }
    else {
        const std::string CANDEVICE{commandlineArguments["can"]};
        const uint32_t ID{(commandlineArguments["id"].size() != 0) ? static_cast<uint32_t>(std::stoi(commandlineArguments["id"])) : 0};
        const bool VERBOSE{commandlineArguments.count("verbose") != 0};


        // Interface to a running OpenDaVINCI session; here, you can send and receive messages.
        cluon::OD4Session od4{static_cast<uint16_t>(std::stoi(commandlineArguments["cid"]))};
        // Delegate to convert incoming CAN frames into ODVD messages that are broadcast into the OD4Session.
        auto decode = [&od4, VERBOSE, ID](cluon::data::TimeStamp ts, uint16_t canFrameID, uint8_t *src, uint8_t len) {
            if ( (nullptr == src) || (0 == len) ) return;
            if (LYNXRES19GW_PDO_RES_STATUS_FRAME_ID == canFrameID) {
                lynxres19gw_pdo_res_status_t tmp;
                if (0 == lynxres19gw_pdo_res_status_unpack(&tmp, src, len)) {
                    opendlv::proxyCANReading::RESStatus msg;
                    msg.resButtons(lynxres19gw_pdo_res_status_res_buttons_decode(tmp.res_buttons));
                    msg.resEStop(lynxres19gw_pdo_res_status_res_e_stop_decode(tmp.res_e_stop));
                    msg.resQuality(lynxres19gw_pdo_res_status_res_quality_decode(tmp.res_quality));
                    msg.resStatus(lynxres19gw_pdo_res_status_res_status_decode(tmp.res_status));
                    // The following block is automatically added to demonstrate how to display the received values.
                    {
                        std::stringstream sstr;
                        msg.accept([](uint32_t, const std::string &, const std::string &) {},
                                [&sstr](uint32_t, std::string &&, std::string &&n, auto v) { sstr << n << " = " << v << '\n'; },
                                []() {});
                        std::cout << sstr.str() << std::endl;
                    }
                    
                    opendlv::proxy::SwitchStateReading msgRESBtn;
                    msgRESBtn.state(msg.resButtons());
                    od4.send(msgRESBtn,ts,1410);

                    opendlv::proxy::SwitchStateReading msgResQuality;
                    msgResQuality.state(msg.resQuality());
                    od4.send(msgResQuality,ts,1409);

                    opendlv::proxy::SwitchStateReading msgResEStop;
                    msgResEStop.state(msg.resEStop());
                    od4.send(msgResEStop,ts,1408);

                    opendlv::proxy::SwitchStateReading msgResStatus;
                    msgResStatus.state(msg.resStatus());
                    od4.send(msgResStatus,ts,1407);
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
        
// Encode Vehicle State
/*
        {
            lynxres19gw_nmt_node_control_t tmp;
            memset(&tmp, 0, sizeof(tmp));
            // The following msg would have to be passed to this encoder externally.
            opendlv::proxyCANWriting::NMT msg;
            tmp.node_state = lynxres19gw_nmt_node_control_node_state_encode(msg.nodeState());
            tmp.node_id = lynxres19gw_nmt_node_control_node_id_encode(msg.nodeId());
            // The following statement packs the encoded values into a CAN frame.
            int size = lynxres19gw_nmt_node_control_pack(dst, &tmp, len);
            return size;
        }
*/
/********** sample of encode *************
        auto onTorqueRequestSetPoint =[&socketCAN](cluon::data::Envelope &&env){
            opendlv::proxy::TorqueRequestSetPoint msg = cluon::extractMessage<opendlv::proxy::TorqueRequestSetPoint>(std::move(env));;
            // Message to encode: LYNX19GW_AS_TORQUE_REQ_FRAME_ID
            lynx19gw_as_torque_req_t tmp;
            memset(&tmp, 0, sizeof(tmp));
            // The following msg would have to be passed to this encoder externally.
            tmp.torque_set_point_left = lynx19gw_as_torque_req_torque_set_point_left_encode(msg.torqueLeft());
            tmp.torque_set_point_right = lynx19gw_as_torque_req_torque_set_point_right_encode(msg.torqueRight());
            //The following statement packs the encoded values into a CAN frame.
            std::clog << "Received msg Torque: Left: " << tmp.torque_set_point_left << " Right: "<< tmp.torque_set_point_right <<std::endl;
            uint8_t buffer[8];
            int len = lynx19gw_as_torque_req_pack(buffer, &tmp, 8);
            if ( (0 < len) && (-1 < socketCAN) ) {
#ifdef __linux__
                struct can_frame frame;
                frame.can_id = LYNX19GW_AS_TORQUE_REQ_FRAME_ID;
                frame.can_dlc = len;
                memcpy(frame.data, buffer, 8);
                int32_t nbytes = ::write(socketCAN, &frame, sizeof(struct can_frame));
                if (!(0 < nbytes)) {
                    std::clog << "[SocketCANDevice] Writing ID = " << frame.can_id << ", LEN = " << +frame.can_dlc << ", strerror(" << errno << "): '" << strerror(errno) << "'" << std::endl;
                }
#endif
            }
        };

        od4.dataTrigger(opendlv::proxy::TorqueRequestSetPoint::ID(), onTorqueRequestSetPoint);
**************/
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

