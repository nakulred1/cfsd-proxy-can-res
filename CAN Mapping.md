### This is the mapping for CAN 1 RES & Datalogger at bitrate 1M (Mapping Datalogging is not implemented yet.)

CAN Mapping : lynxres19gw.dbc | lynx-v0.1.0.odvd

|   CAN message    | CAN signal  | Lynx message                      | msg signal | sensor/req/log | unit |
| :--------------: | :---------: | --------------------------------- | :--------: | :------------: | :--: |
|  PDO_RES_Status  | RES_Status  | opendlv.proxyCANReading.RESStatus | resStatus  |     sensor     |      |
|                  | RES_E_Stop  |                                   |  resEStop  |     sensor     |      |
|                  | RES_Quality |                                   | resQuality |     sensor     |      |
|                  | RES_Buttons |                                   | resButtons |     sensor     |      |
| NMT_Node_Control | Node_State  | opendlv.proxyCANWriting.NMT       | nodeState  |      req       |      |
|                  |   Node_Id   |                                   |   nodeId   |      req       |      |
|                  |             |                                   |            |                |      |
|                  |             |                                   |            |                |      |

Lynx Message <-> OpenDLV message:  lynx-v0.1.0.odvd | opendlv-standard-message-set-v0.9.7.odvd

|          OpenDLV message           | sender stamp | Lynx message                      | msg signal | sensor/req/log | unit |
| :--------------------------------: | :----------: | --------------------------------- | :--------: | :------------: | :--: |
| opendlv::proxy::SwitchStateReading |     1407     | opendlv.proxyCANReading.RESStatus | resStatus  |     sensor     |      |
|                                    |     1408     |                                   |  resEStop  |     sensor     |      |
|                                    |     1409     |                                   | resQuality |     sensor     |      |
|                                    |     1410     |                                   | resButtons |     sensor     |      |
| opendlv::proxy::SwitchStateReading |     1499     | opendlv.proxyCANWriting.NMT*[1]   | nodeState  |      req       |  1   |
|                                    |              |                                   |   nodeId   |      req       |  0   |

*[1] according to the rule: DE7.4.8 The receiver is booted up and sends a message to signalize its initialization (NMT message with CAN-ID 0x700 + Node-ID and a single data byte 0x00). A CAN/CANopen master device must set the receiver to operational mode (NMT message CAN-ID = 0x000, byte 1 = 0x01 (requested state), byte 2 = addressed Node-ID or 0x00 for all). 