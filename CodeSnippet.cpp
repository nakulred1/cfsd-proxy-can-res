inline int encode(uint8_t *dst, uint8_t len);
int encode(uint8_t *dst, uint8_t len) {
    if ( (nullptr == dst) || (0 == len) ) return 0;
    // TODO: Provide logic to check what messages to actually encode; the code in the
    //       following is mainly template code for illustration.
 
    // Message to encode: LYNX19GW_DATALOGGER_CONFIG_FRAME_ID
    {
        lynx19gw_datalogger_config_t tmp;
        memset(&tmp, 0, sizeof(tmp));
        (void)tmp;
        // No mapping defined for lynx19gw_datalogger_config
    }
    // Message to encode: LYNX19GW_NR_DL_TV_OUT_1_FRAME_ID
    {
        lynx19gw_nr_dl_tv_out_1_t tmp;
        memset(&tmp, 0, sizeof(tmp));
        (void)tmp;
        // No mapping defined for lynx19gw_nr_dl_tv_out_1
    }
    // Message to encode: LYNX19GW_NR_DL_SENSORS_1_FRAME_ID
    {
        lynx19gw_nr_dl_sensors_1_t tmp;
        memset(&tmp, 0, sizeof(tmp));
        // The following msg would have to be passed to this encoder externally.
        opendlv::proxyCANReading::WheelSpeedRare msg;
        tmp.wheel_speed_rl = lynx19gw_nr_dl_sensors_1_wheel_speed_rl_encode(msg.wheelRareLeft());
        tmp.wheel_speed_rr = lynx19gw_nr_dl_sensors_1_wheel_speed_rr_encode(msg.wheelRareRight());
        // The following statement packs the encoded values into a CAN frame.
        int size = lynx19gw_nr_dl_sensors_1_pack(dst, &tmp, len);
        return size;
    }
    // Message to encode: LYNX19GW_NF_DL_HARTBEAT_FRAME_ID
    {
        lynx19gw_nf_dl_hartbeat_t tmp;
        memset(&tmp, 0, sizeof(tmp));
        (void)tmp;
        // No mapping defined for lynx19gw_nf_dl_hartbeat
    }
    // Message to encode: LYNX19GW_PEL_PDO_2_TX_FRAME_ID
    {
        lynx19gw_pel_pdo_2_tx_t tmp;
        memset(&tmp, 0, sizeof(tmp));
        (void)tmp;
        // No mapping defined for lynx19gw_pel_pdo_2_tx
    }
    // Message to encode: LYNX19GW_NR_DL_TV_OUT_2_FRAME_ID
    {
        lynx19gw_nr_dl_tv_out_2_t tmp;
        memset(&tmp, 0, sizeof(tmp));
        (void)tmp;
        // No mapping defined for lynx19gw_nr_dl_tv_out_2
    }
    // Message to encode: LYNX19GW_DL_AS_STATUS_FRAME_ID
    {
        lynx19gw_dl_as_status_t tmp;
        memset(&tmp, 0, sizeof(tmp));
        // The following msg would have to be passed to this encoder externally.
        opendlv::proxyCANReading::AsStatus msg;
        tmp.as_mission = lynx19gw_dl_as_status_as_mission_encode(msg.asMission());
        tmp.brake_front = lynx19gw_dl_as_status_brake_front_encode(msg.brakeFront());
        tmp.brake_rear = lynx19gw_dl_as_status_brake_rear_encode(msg.brakeRear());
        tmp.dl_status = lynx19gw_dl_as_status_dl_status_encode(msg.dlStatus());
        tmp.acc_so_c = lynx19gw_dl_as_status_acc_so_c_encode(msg.accSoC());
        // The following statement packs the encoded values into a CAN frame.
        int size = lynx19gw_dl_as_status_pack(dst, &tmp, len);
        return size;
    }
    // Message to encode: LYNX19GW_NR_DL_TV_OUT_3_NEW_FRAME_ID
    {
        lynx19gw_nr_dl_tv_out_3_new_t tmp;
        memset(&tmp, 0, sizeof(tmp));
        (void)tmp;
        // No mapping defined for lynx19gw_nr_dl_tv_out_3_new
    }
    // Message to encode: LYNX19GW_NR_DL_SENSORS_4_NEW_FRAME_ID
    {
        lynx19gw_nr_dl_sensors_4_new_t tmp;
        memset(&tmp, 0, sizeof(tmp));
        (void)tmp;
        // No mapping defined for lynx19gw_nr_dl_sensors_4_new
    }
    // Message to encode: LYNX19GW_NF_NR_SENSORS_1_FRAME_ID
    {
        lynx19gw_nf_nr_sensors_1_t tmp;
        memset(&tmp, 0, sizeof(tmp));
        (void)tmp;
        // No mapping defined for lynx19gw_nf_nr_sensors_1
    }
    // Message to encode: LYNX19GW_NR_DL_SENSORS_2_FRAME_ID
    {
        lynx19gw_nr_dl_sensors_2_t tmp;
        memset(&tmp, 0, sizeof(tmp));
        (void)tmp;
        // No mapping defined for lynx19gw_nr_dl_sensors_2
    }
    // Message to encode: LYNX19GW_AS_TORQUE_REQ_FRAME_ID
    {
        lynx19gw_as_torque_req_t tmp;
        memset(&tmp, 0, sizeof(tmp));
        // The following msg would have to be passed to this encoder externally.
        opendlv::proxyCANWriting::ASTorque msg;
        tmp.torque_set_point_left = lynx19gw_as_torque_req_torque_set_point_left_encode(msg.torqueLeft());
        tmp.torque_set_point_right = lynx19gw_as_torque_req_torque_set_point_right_encode(msg.torqueRight());
        // The following statement packs the encoded values into a CAN frame.
        int size = lynx19gw_as_torque_req_pack(dst, &tmp, len);
        return size;
    }
    // Message to encode: LYNX19GW_NF_NR_SENSORS_2_FRAME_ID
    {
        lynx19gw_nf_nr_sensors_2_t tmp;
        memset(&tmp, 0, sizeof(tmp));
        // The following msg would have to be passed to this encoder externally.
        opendlv::proxyCANReading::WheelSpeedFront msg;
        tmp.wheel_speed_fl = lynx19gw_nf_nr_sensors_2_wheel_speed_fl_encode(msg.wheelFrontLeft());
        tmp.wheel_speed_fr = lynx19gw_nf_nr_sensors_2_wheel_speed_fr_encode(msg.wheelFrontRight());
        // The following statement packs the encoded values into a CAN frame.
        int size = lynx19gw_nf_nr_sensors_2_pack(dst, &tmp, len);
        return size;
    }
    // Message to encode: LYNX19GW_NR_DL_SENSORS_3_FRAME_ID
    {
        lynx19gw_nr_dl_sensors_3_t tmp;
        memset(&tmp, 0, sizeof(tmp));
        (void)tmp;
        // No mapping defined for lynx19gw_nr_dl_sensors_3
    }
    // Message to encode: LYNX19GW_BMS_CLIENT_CELL_VOLTAGES_FRAME_ID
    {
        lynx19gw_bms_client_cell_voltages_t tmp;
        memset(&tmp, 0, sizeof(tmp));
        (void)tmp;
        // No mapping defined for lynx19gw_bms_client_cell_voltages
    }
    // Message to encode: LYNX19GW_PER_PDO_2_TX_FRAME_ID
    {
        lynx19gw_per_pdo_2_tx_t tmp;
        memset(&tmp, 0, sizeof(tmp));
        (void)tmp;
        // No mapping defined for lynx19gw_per_pdo_2_tx
    }
    // Message to encode: LYNX19GW_DL_NR_TV_CONF_1_FRAME_ID
    {
        lynx19gw_dl_nr_tv_conf_1_t tmp;
        memset(&tmp, 0, sizeof(tmp));
        (void)tmp;
        // No mapping defined for lynx19gw_dl_nr_tv_conf_1
    }
    // Message to encode: LYNX19GW_NR_PEL_PDO_1_RX_FRAME_ID
    {
        lynx19gw_nr_pel_pdo_1_rx_t tmp;
        memset(&tmp, 0, sizeof(tmp));
        (void)tmp;
        // No mapping defined for lynx19gw_nr_pel_pdo_1_rx
    }
    // Message to encode: LYNX19GW_BMS_DL_DATA_FRAME_ID
    {
        lynx19gw_bms_dl_data_t tmp;
        memset(&tmp, 0, sizeof(tmp));
        (void)tmp;
        // No mapping defined for lynx19gw_bms_dl_data
    }
    // Message to encode: LYNX19GW_DL_NR_TV_CONF_2_FRAME_ID
    {
        lynx19gw_dl_nr_tv_conf_2_t tmp;
        memset(&tmp, 0, sizeof(tmp));
        (void)tmp;
        // No mapping defined for lynx19gw_dl_nr_tv_conf_2
    }
    // Message to encode: LYNX19GW_CLIENT_BMS_DATA_FRAME_ID
    {
        lynx19gw_client_bms_data_t tmp;
        memset(&tmp, 0, sizeof(tmp));
        (void)tmp;
        // No mapping defined for lynx19gw_client_bms_data
    }
    // Message to encode: LYNX19GW_NF_DL_BUTTONS_RTD_FRAME_ID
    {
        lynx19gw_nf_dl_buttons_rtd_t tmp;
        memset(&tmp, 0, sizeof(tmp));
        (void)tmp;
        // No mapping defined for lynx19gw_nf_dl_buttons_rtd
    }
    // Message to encode: LYNX19GW_NR_PER_PDO_1_RX_FRAME_ID
    {
        lynx19gw_nr_per_pdo_1_rx_t tmp;
        memset(&tmp, 0, sizeof(tmp));
        (void)tmp;
        // No mapping defined for lynx19gw_nr_per_pdo_1_rx
    }
    // Message to encode: LYNX19GW_BMS_DL_HARTBEAT_FRAME_ID
    {
        lynx19gw_bms_dl_hartbeat_t tmp;
        memset(&tmp, 0, sizeof(tmp));
        (void)tmp;
        // No mapping defined for lynx19gw_bms_dl_hartbeat
    }
    // Message to encode: LYNX19GW_BMS_CLIENT_CELL_TEMPERATURES_FRAME_ID
    {
        lynx19gw_bms_client_cell_temperatures_t tmp;
        memset(&tmp, 0, sizeof(tmp));
        (void)tmp;
        // No mapping defined for lynx19gw_bms_client_cell_temperatures
    }
    // Message to encode: LYNX19GW_NR_PER_PDO_2_RX_FRAME_ID
    {
        lynx19gw_nr_per_pdo_2_rx_t tmp;
        memset(&tmp, 0, sizeof(tmp));
        (void)tmp;
        // No mapping defined for lynx19gw_nr_per_pdo_2_rx
    }
    // Message to encode: LYNX19GW_NR_PEL_PDO_2_RX_FRAME_ID
    {
        lynx19gw_nr_pel_pdo_2_rx_t tmp;
        memset(&tmp, 0, sizeof(tmp));
        (void)tmp;
        // No mapping defined for lynx19gw_nr_pel_pdo_2_rx
    }
    // Message to encode: LYNX19GW_PER_PDO_1_TX_FRAME_ID
    {
        lynx19gw_per_pdo_1_tx_t tmp;
        memset(&tmp, 0, sizeof(tmp));
        (void)tmp;
        // No mapping defined for lynx19gw_per_pdo_1_tx
    }
    // Message to encode: LYNX19GW_AS_DL_SENSORS_FRAME_ID
    {
        lynx19gw_as_dl_sensors_t tmp;
        memset(&tmp, 0, sizeof(tmp));
        // The following msg would have to be passed to this encoder externally.
        opendlv::proxyCANWriting::ASStatus msg;
        tmp.as_state = lynx19gw_as_dl_sensors_as_state_encode(msg.asState());
        tmp.steering_position = lynx19gw_as_dl_sensors_steering_position_encode(msg.steeringPosition());
        tmp.rack_position = lynx19gw_as_dl_sensors_rack_position_encode(msg.rackPosition());
        tmp.pressure_ebs_act = lynx19gw_as_dl_sensors_pressure_ebs_act_encode(msg.pressureEBSAct());
        tmp.pressure_ebs_line = lynx19gw_as_dl_sensors_pressure_ebs_line_encode(msg.pressureEBSLine());
        tmp.pressure_service = lynx19gw_as_dl_sensors_pressure_service_encode(msg.pressureService());
        tmp.pressure_regulator = lynx19gw_as_dl_sensors_pressure_regulator_encode(msg.pressureRegulator());
        tmp.as_rtd = lynx19gw_as_dl_sensors_as_rtd_encode(msg.asRedyToDrive());
        // The following statement packs the encoded values into a CAN frame.
        int size = lynx19gw_as_dl_sensors_pack(dst, &tmp, len);
        return size;
    }
    // Message to encode: LYNX19GW_NR_DL_HARTBEAT_FRAME_ID
    {
        lynx19gw_nr_dl_hartbeat_t tmp;
        memset(&tmp, 0, sizeof(tmp));
        (void)tmp;
        // No mapping defined for lynx19gw_nr_dl_hartbeat
    }
    // Message to encode: LYNX19GW_PEL_PDO_1_TX_FRAME_ID
    {
        lynx19gw_pel_pdo_1_tx_t tmp;
        memset(&tmp, 0, sizeof(tmp));
        (void)tmp;
        // No mapping defined for lynx19gw_pel_pdo_1_tx
    }
}
inline void decode(uint16_t canFrameID, uint8_t *src, uint8_t len);
void decode(uint16_t canFrameID, uint8_t *src, uint8_t len) {
    if ( (nullptr == src) || (0 == len) ) return;
    if (LYNX19GW_DATALOGGER_CONFIG_FRAME_ID == canFrameID) {
        lynx19gw_datalogger_config_t tmp;
        if (0 == lynx19gw_datalogger_config_unpack(&tmp, src, len)) {
            // No mapping defined for lynx19gw_datalogger_config
        }
    }
    else if (LYNX19GW_NR_DL_TV_OUT_1_FRAME_ID == canFrameID) {
        lynx19gw_nr_dl_tv_out_1_t tmp;
        if (0 == lynx19gw_nr_dl_tv_out_1_unpack(&tmp, src, len)) {
            // No mapping defined for lynx19gw_nr_dl_tv_out_1
        }
    }
    else if (LYNX19GW_NR_DL_SENSORS_1_FRAME_ID == canFrameID) {
        lynx19gw_nr_dl_sensors_1_t tmp;
        if (0 == lynx19gw_nr_dl_sensors_1_unpack(&tmp, src, len)) {
            opendlv::proxyCANReading::WheelSpeedRare msg;
            msg.wheelRareLeft(lynx19gw_nr_dl_sensors_1_wheel_speed_rl_decode(tmp.wheel_speed_rl));
            msg.wheelRareRight(lynx19gw_nr_dl_sensors_1_wheel_speed_rr_decode(tmp.wheel_speed_rr));
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
    else if (LYNX19GW_NF_DL_HARTBEAT_FRAME_ID == canFrameID) {
        lynx19gw_nf_dl_hartbeat_t tmp;
        if (0 == lynx19gw_nf_dl_hartbeat_unpack(&tmp, src, len)) {
            // No mapping defined for lynx19gw_nf_dl_hartbeat
        }
    }
    else if (LYNX19GW_PEL_PDO_2_TX_FRAME_ID == canFrameID) {
        lynx19gw_pel_pdo_2_tx_t tmp;
        if (0 == lynx19gw_pel_pdo_2_tx_unpack(&tmp, src, len)) {
            // No mapping defined for lynx19gw_pel_pdo_2_tx
        }
    }
    else if (LYNX19GW_NR_DL_TV_OUT_2_FRAME_ID == canFrameID) {
        lynx19gw_nr_dl_tv_out_2_t tmp;
        if (0 == lynx19gw_nr_dl_tv_out_2_unpack(&tmp, src, len)) {
            // No mapping defined for lynx19gw_nr_dl_tv_out_2
        }
    }
    else if (LYNX19GW_DL_AS_STATUS_FRAME_ID == canFrameID) {
        lynx19gw_dl_as_status_t tmp;
        if (0 == lynx19gw_dl_as_status_unpack(&tmp, src, len)) {
            opendlv::proxyCANReading::AsStatus msg;
            msg.asMission(lynx19gw_dl_as_status_as_mission_decode(tmp.as_mission));
            msg.brakeFront(lynx19gw_dl_as_status_brake_front_decode(tmp.brake_front));
            msg.brakeRear(lynx19gw_dl_as_status_brake_rear_decode(tmp.brake_rear));
            msg.dlStatus(lynx19gw_dl_as_status_dl_status_decode(tmp.dl_status));
            msg.accSoC(lynx19gw_dl_as_status_acc_so_c_decode(tmp.acc_so_c));
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
    else if (LYNX19GW_NR_DL_TV_OUT_3_NEW_FRAME_ID == canFrameID) {
        lynx19gw_nr_dl_tv_out_3_new_t tmp;
        if (0 == lynx19gw_nr_dl_tv_out_3_new_unpack(&tmp, src, len)) {
            // No mapping defined for lynx19gw_nr_dl_tv_out_3_new
        }
    }
    else if (LYNX19GW_NR_DL_SENSORS_4_NEW_FRAME_ID == canFrameID) {
        lynx19gw_nr_dl_sensors_4_new_t tmp;
        if (0 == lynx19gw_nr_dl_sensors_4_new_unpack(&tmp, src, len)) {
            // No mapping defined for lynx19gw_nr_dl_sensors_4_new
        }
    }
    else if (LYNX19GW_NF_NR_SENSORS_1_FRAME_ID == canFrameID) {
        lynx19gw_nf_nr_sensors_1_t tmp;
        if (0 == lynx19gw_nf_nr_sensors_1_unpack(&tmp, src, len)) {
            // No mapping defined for lynx19gw_nf_nr_sensors_1
        }
    }
    else if (LYNX19GW_NR_DL_SENSORS_2_FRAME_ID == canFrameID) {
        lynx19gw_nr_dl_sensors_2_t tmp;
        if (0 == lynx19gw_nr_dl_sensors_2_unpack(&tmp, src, len)) {
            // No mapping defined for lynx19gw_nr_dl_sensors_2
        }
    }
    else if (LYNX19GW_AS_TORQUE_REQ_FRAME_ID == canFrameID) {
        lynx19gw_as_torque_req_t tmp;
        if (0 == lynx19gw_as_torque_req_unpack(&tmp, src, len)) {
            opendlv::proxyCANWriting::ASTorque msg;
            msg.torqueLeft(lynx19gw_as_torque_req_torque_set_point_left_decode(tmp.torque_set_point_left));
            msg.torqueRight(lynx19gw_as_torque_req_torque_set_point_right_decode(tmp.torque_set_point_right));
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
    else if (LYNX19GW_NF_NR_SENSORS_2_FRAME_ID == canFrameID) {
        lynx19gw_nf_nr_sensors_2_t tmp;
        if (0 == lynx19gw_nf_nr_sensors_2_unpack(&tmp, src, len)) {
            opendlv::proxyCANReading::WheelSpeedFront msg;
            msg.wheelFrontLeft(lynx19gw_nf_nr_sensors_2_wheel_speed_fl_decode(tmp.wheel_speed_fl));
            msg.wheelFrontRight(lynx19gw_nf_nr_sensors_2_wheel_speed_fr_decode(tmp.wheel_speed_fr));
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
    else if (LYNX19GW_NR_DL_SENSORS_3_FRAME_ID == canFrameID) {
        lynx19gw_nr_dl_sensors_3_t tmp;
        if (0 == lynx19gw_nr_dl_sensors_3_unpack(&tmp, src, len)) {
            // No mapping defined for lynx19gw_nr_dl_sensors_3
        }
    }
    else if (LYNX19GW_BMS_CLIENT_CELL_VOLTAGES_FRAME_ID == canFrameID) {
        lynx19gw_bms_client_cell_voltages_t tmp;
        if (0 == lynx19gw_bms_client_cell_voltages_unpack(&tmp, src, len)) {
            // No mapping defined for lynx19gw_bms_client_cell_voltages
        }
    }
    else if (LYNX19GW_PER_PDO_2_TX_FRAME_ID == canFrameID) {
        lynx19gw_per_pdo_2_tx_t tmp;
        if (0 == lynx19gw_per_pdo_2_tx_unpack(&tmp, src, len)) {
            // No mapping defined for lynx19gw_per_pdo_2_tx
        }
    }
    else if (LYNX19GW_DL_NR_TV_CONF_1_FRAME_ID == canFrameID) {
        lynx19gw_dl_nr_tv_conf_1_t tmp;
        if (0 == lynx19gw_dl_nr_tv_conf_1_unpack(&tmp, src, len)) {
            // No mapping defined for lynx19gw_dl_nr_tv_conf_1
        }
    }
    else if (LYNX19GW_NR_PEL_PDO_1_RX_FRAME_ID == canFrameID) {
        lynx19gw_nr_pel_pdo_1_rx_t tmp;
        if (0 == lynx19gw_nr_pel_pdo_1_rx_unpack(&tmp, src, len)) {
            // No mapping defined for lynx19gw_nr_pel_pdo_1_rx
        }
    }
    else if (LYNX19GW_BMS_DL_DATA_FRAME_ID == canFrameID) {
        lynx19gw_bms_dl_data_t tmp;
        if (0 == lynx19gw_bms_dl_data_unpack(&tmp, src, len)) {
            // No mapping defined for lynx19gw_bms_dl_data
        }
    }
    else if (LYNX19GW_DL_NR_TV_CONF_2_FRAME_ID == canFrameID) {
        lynx19gw_dl_nr_tv_conf_2_t tmp;
        if (0 == lynx19gw_dl_nr_tv_conf_2_unpack(&tmp, src, len)) {
            // No mapping defined for lynx19gw_dl_nr_tv_conf_2
        }
    }
    else if (LYNX19GW_CLIENT_BMS_DATA_FRAME_ID == canFrameID) {
        lynx19gw_client_bms_data_t tmp;
        if (0 == lynx19gw_client_bms_data_unpack(&tmp, src, len)) {
            // No mapping defined for lynx19gw_client_bms_data
        }
    }
    else if (LYNX19GW_NF_DL_BUTTONS_RTD_FRAME_ID == canFrameID) {
        lynx19gw_nf_dl_buttons_rtd_t tmp;
        if (0 == lynx19gw_nf_dl_buttons_rtd_unpack(&tmp, src, len)) {
            // No mapping defined for lynx19gw_nf_dl_buttons_rtd
        }
    }
    else if (LYNX19GW_NR_PER_PDO_1_RX_FRAME_ID == canFrameID) {
        lynx19gw_nr_per_pdo_1_rx_t tmp;
        if (0 == lynx19gw_nr_per_pdo_1_rx_unpack(&tmp, src, len)) {
            // No mapping defined for lynx19gw_nr_per_pdo_1_rx
        }
    }
    else if (LYNX19GW_BMS_DL_HARTBEAT_FRAME_ID == canFrameID) {
        lynx19gw_bms_dl_hartbeat_t tmp;
        if (0 == lynx19gw_bms_dl_hartbeat_unpack(&tmp, src, len)) {
            // No mapping defined for lynx19gw_bms_dl_hartbeat
        }
    }
    else if (LYNX19GW_BMS_CLIENT_CELL_TEMPERATURES_FRAME_ID == canFrameID) {
        lynx19gw_bms_client_cell_temperatures_t tmp;
        if (0 == lynx19gw_bms_client_cell_temperatures_unpack(&tmp, src, len)) {
            // No mapping defined for lynx19gw_bms_client_cell_temperatures
        }
    }
    else if (LYNX19GW_NR_PER_PDO_2_RX_FRAME_ID == canFrameID) {
        lynx19gw_nr_per_pdo_2_rx_t tmp;
        if (0 == lynx19gw_nr_per_pdo_2_rx_unpack(&tmp, src, len)) {
            // No mapping defined for lynx19gw_nr_per_pdo_2_rx
        }
    }
    else if (LYNX19GW_NR_PEL_PDO_2_RX_FRAME_ID == canFrameID) {
        lynx19gw_nr_pel_pdo_2_rx_t tmp;
        if (0 == lynx19gw_nr_pel_pdo_2_rx_unpack(&tmp, src, len)) {
            // No mapping defined for lynx19gw_nr_pel_pdo_2_rx
        }
    }
    else if (LYNX19GW_PER_PDO_1_TX_FRAME_ID == canFrameID) {
        lynx19gw_per_pdo_1_tx_t tmp;
        if (0 == lynx19gw_per_pdo_1_tx_unpack(&tmp, src, len)) {
            // No mapping defined for lynx19gw_per_pdo_1_tx
        }
    }
    else if (LYNX19GW_AS_DL_SENSORS_FRAME_ID == canFrameID) {
        lynx19gw_as_dl_sensors_t tmp;
        if (0 == lynx19gw_as_dl_sensors_unpack(&tmp, src, len)) {
            opendlv::proxyCANWriting::ASStatus msg;
            msg.asState(lynx19gw_as_dl_sensors_as_state_decode(tmp.as_state));
            msg.steeringPosition(lynx19gw_as_dl_sensors_steering_position_decode(tmp.steering_position));
            msg.rackPosition(lynx19gw_as_dl_sensors_rack_position_decode(tmp.rack_position));
            msg.pressureEBSAct(lynx19gw_as_dl_sensors_pressure_ebs_act_decode(tmp.pressure_ebs_act));
            msg.pressureEBSLine(lynx19gw_as_dl_sensors_pressure_ebs_line_decode(tmp.pressure_ebs_line));
            msg.pressureService(lynx19gw_as_dl_sensors_pressure_service_decode(tmp.pressure_service));
            msg.pressureRegulator(lynx19gw_as_dl_sensors_pressure_regulator_decode(tmp.pressure_regulator));
            msg.asRedyToDrive(lynx19gw_as_dl_sensors_as_rtd_decode(tmp.as_rtd));
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
    else if (LYNX19GW_NR_DL_HARTBEAT_FRAME_ID == canFrameID) {
        lynx19gw_nr_dl_hartbeat_t tmp;
        if (0 == lynx19gw_nr_dl_hartbeat_unpack(&tmp, src, len)) {
            // No mapping defined for lynx19gw_nr_dl_hartbeat
        }
    }
    else if (LYNX19GW_PEL_PDO_1_TX_FRAME_ID == canFrameID) {
        lynx19gw_pel_pdo_1_tx_t tmp;
        if (0 == lynx19gw_pel_pdo_1_tx_unpack(&tmp, src, len)) {
            // No mapping defined for lynx19gw_pel_pdo_1_tx
        }
    }
}
