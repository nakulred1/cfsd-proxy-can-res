CAN Mapping

|    CAN message    |       CAN signal       |    OpenDLV message    | sensor/request/log |    unit    |
| :---------------: | :--------------------: | :-------------------: | :----------------: | :--------: |
| AS_Torque_Req*[1] | Torque_Set_Point_Right |  TorqueRequest.Left   |        req         |  0~24cNm   |
|                   | Torque_Set_Point_Left  |  TorqueRequest.Right  |        req         |    cNm     |
|  NR_DL_Sensors_1  |     Wheel_Speed_RR     | WheelSpeedRear.Right  |       sensor       |    Km/h    |
|                   |     Wheel_Speed_RL     |  WheelSpeedRear.Left  |       sensor       |    Km/h    |
|  NF_NR_Sensors_2  |     Wheel_Speed_FR     | WheelSpeedFront.Right |       sensor       |    Km/h    |
|                   |     Wheel_Speed_FL     | WheelSpeedFront.Left  |       sensor       |    Km/h    |
|  NF_NR_Sensors_1  |         Brake          |   Brake.BreakRatio    |       sensor       |     %      |
|   DL_AS_Status    |       AS_Mission       |   AsMission.Mission   |       sensor       |    0-8     |
|                   |      Brake_Front       |                       |                    |     %      |
|                   |       Brake_Rear       |                       |                    |     %      |
| NF_DL_Buttons_RTD |     Redy_To_Drive      |    Ready_To_Drive     |    ??Request??     | 0=off 1=on |
|                   |                        |                       |                    |            |
|                   |                        |                       |                    |            |

*[1]math equation: from speed to torque see: opendlv-logic-action-motion-cfsd

