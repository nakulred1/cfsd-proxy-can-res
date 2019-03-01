CAN Mapping

|    CAN message    |       CAN signal       | Lynx message                            |    msg signal     | sensor/req/log |      unit       |
| :---------------: | :--------------------: | --------------------------------------- | :---------------: | :------------: | :-------------: |
| AS_Torque_Req*[1] | Torque_Set_Point_Right | opendlv.proxyCANWriting.ASTorque        |    torqueRight    |      req       |     0~24cNm     |
|                   | Torque_Set_Point_Left  |                                         |    torqueLeft     |      req       |       cNm       |
|  NR_DL_Sensors_1  |     Wheel_Speed_RR     | opendlv.proxyCANReading.WheelSpeedRare  |  wheelRareRight   |     sensor     |      Km/h       |
|                   |     Wheel_Speed_RL     |                                         |   wheelRareLeft   |     sensor     |      Km/h       |
|  NF_NR_Sensors_2  |     Wheel_Speed_FR     | opendlv.proxyCANReading.WheelSpeedFront |  wheelFrontRight  |     sensor     |      Km/h       |
|                   |     Wheel_Speed_FL     |                                         |  wheelFrontLeft   |     sensor     |      Km/h       |
|  NF_NR_Sensors_1  |         Brake          | opendlv.proxyCANReading.PedalRatio      |       brake       |     sensor     |        %        |
|                   |        Throttle        |                                         |     throttle      |     sensor     |        %        |
|   DL_AS_Status    |         accSoC         | opendlv.proxyCANReading.AsStatus        |      accSoC       |     sensor     | State of Charge |
|                   |    Brake_Front*[2]     |                                         |    brakeFront     |     sensor     |        %        |
|                   |     Brake_Rear*[3]     |                                         |     brakeRear     |     sensor     |        ?        |
|                   |       DL_Status        |                                         |     dlStatus      |     sensor     |       0/1       |
|                   |       AS_Mission       |                                         |     asMission     |     sensor     |       0-8       |
|   AS_DL_Sensors   |         AS_RTD         | opendlv.proxyCANWriting.ASStatus        |   asRedyToDrive   |      log       |       1/0       |
|                   |   Steering_Position    |                                         | steeringPosition  |      log       |       mm        |
|                   |     Rack_Position      |                                         |   rackPosition    |      log       |       mm        |
|                   |    Pressure_Service    |                                         |  pressureService  |      log       |       bar       |
|                   |   Pressure_Regulator   |                                         | pressureRegulator |      log       |       bar       |
|                   |   Pressure_EBS_Line    |                                         |  pressureEBSLine  |      log       |       bar       |
|                   |    Pressure_EBS_Act    |                                         |  pressureEBSAct   |      log       |       bar       |
|                   |        AS_State        |                                         |      asState      |      log       |     states      |

*[1] math equation: from speed to torque see: opendlv-logic-action-motion-cfsd

*[2] The Brake Front reading = brake pedal Ratio

*[3] The Brake Rare reading read Data type not confirmed



Lynx Message to OpenDLV message



|            OpenDLV message            | sender stamp | Lynx message                            |    msg signal     | sensor/req/log |      unit       |
| :-----------------------------------: | :----------: | --------------------------------------- | :---------------: | :------------: | :-------------: |
|     opendlv::proxy::TorqueRequest     |     1501     | opendlv.proxyCANWriting.ASTorque        |    torqueRight    |      req       |     0~24cNm     |
|                                       |     1500     |                                         |    torqueLeft     |      req       |       cNm       |
|                                       |              | opendlv.proxyCANReading.WheelSpeedRare  |  wheelRareRight   |     sensor     |      Km/h       |
|                                       |              |                                         |   wheelRareLeft   |     sensor     |      Km/h       |
|                                       |              | opendlv.proxyCANReading.WheelSpeedFront |  wheelFrontRight  |     sensor     |      Km/h       |
|                                       |              |                                         |  wheelFrontLeft   |     sensor     |      Km/h       |
|                                       |              | opendlv.proxyCANReading.PedalRatio      |       brake       |     sensor     |        %        |
|                                       |              |                                         |     throttle      |     sensor     |        %        |
|                                       |              | opendlv.proxyCANReading.AsStatus        |      accSoC       |     sensor     | State of Charge |
|                                       |              |                                         |    brakeFront     |     sensor     |        %        |
|                                       |              |                                         |     brakeRear     |     sensor     |        ?        |
|                                       |              |                                         |     dlStatus      |     sensor     |       0/1       |
|                                       |              |                                         |     asMission     |     sensor     |       0-8       |
|  opendlv::proxy::SwitchStateReading   |     1404     | opendlv.proxyCANWriting.ASStatus        |   asRedyToDrive   |      log       |       1/0       |
| opendlv::proxy::GroundSteeringReading |     1200     |                                         | steeringPosition  |      log       |       mm        |
|                                       |     1206     |                                         |   rackPosition    |      log       |       mm        |
|    opendlv::proxy::PressureReading    |     1202     |                                         |  pressureService  |      log       |       bar       |
|                                       |     1205     |                                         | pressureRegulator |      log       |       bar       |
|                                       |     1201     |                                         |  pressureEBSLine  |      log       |       bar       |
|                                       |     1203     |                                         |  pressureEBSAct   |      log       |       bar       |
|  opendlv::proxy::SwitchStateReading   |     1401     |                                         |      asState      |      log       |     states      |

