CAN Mapping

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
|                  |             |                                   |            |                |      |
|                  |             |                                   |            |                |      |
|                  |             |                                   |            |                |      |
|                  |             |                                   |            |                |      |
|                  |             |                                   |            |                |      |
|                  |             |                                   |            |                |      |
|                  |             |                                   |            |                |      |
|                  |             |                                   |            |                |      |
|                  |             |                                   |            |                |      |
|                  |             |                                   |            |                |      |
|                  |             |                                   |            |                |      |
|                  |             |                                   |            |                |      |
|                  |             |                                   |            |                |      |

*[1] math equation: from speed to torque see: opendlv-logic-action-motion-cfsd

*[2] The Brake Front reading = brake pedal Ratio

*[3] The Brake Rare reading read Data type not confirmed



Lynx Message to OpenDLV message



|          OpenDLV message           | sender stamp | Lynx message                      | msg signal | sensor/req/log | unit |
| :--------------------------------: | :----------: | --------------------------------- | :--------: | :------------: | :--: |
| opendlv::proxy::SwitchStateReading |     1407     | opendlv.proxyCANReading.RESStatus | resStatus  |     sensor     |      |
|                                    |     1408     |                                   |  resEStop  |     sensor     |      |
|                                    |     1409     |                                   | resQuality |     sensor     |      |
|                                    |     1410     |                                   | resButtons |     sensor     |      |
|                                    |              |                                   |            |                |      |
|                                    |              |                                   |            |                |      |
|                                    |              |                                   |            |                |      |
|                                    |              |                                   |            |                |      |
|                                    |              |                                   |            |                |      |
|                                    |              |                                   |            |                |      |
|                                    |              |                                   |            |                |      |
|                                    |              |                                   |            |                |      |
|                                    |              |                                   |            |                |      |
|                                    |              |                                   |            |                |      |
|                                    |              |                                   |            |                |      |
|                                    |              |                                   |            |                |      |
|                                    |              |                                   |            |                |      |
|                                    |              |                                   |            |                |      |
|                                    |              |                                   |            |                |      |
|                                    |              |                                   |            |                |      |
|                                    |              |                                   |            |                |      |

Sending time trigger:

```
auto atFrequency{[&ps3controller, &ANGLECONVERSION, &VERBOSE, &od4, &od4pwm]() -> bool
    {
      
      return true;
    }};
        

    od4.timeTrigger(FREQ, atFrequency);
```

