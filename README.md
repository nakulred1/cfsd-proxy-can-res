# cfsd-proxy-cangw-res
cfsd proxy CAN RES&Data logger getway

Get opendlv standard message and forward to CAN Messages

This version is for the communicate with the Remote Emergency System(RES) and Datalogger (Haven't been implemented yet)

messages:



The mapping info of messages can be found at CAN Mapping.md

lynx-v0.1.0.odvd is the message set for talking to CAN should only be used in these CAN getway microservice.

lynxres19gw.dbc is the CAN database file which is a reference for decoding and encoding the CAN message.

lynxres19gw.dbc.map is the mapping setting file for the microservice knowing how to map the messsages.

Messege : opendlv::proxy::SwitchStateReading:

| senderstamp | Message Name | Value | Meaning                        |
| ----------- | ------------ | ----- | ------------------------------ |
| 1408        | resEStop     | 0     | emergency Stop triggered       |
|             |              | 128   | Not triggered                  |
| 1409        | resQuality   | 0-100 | show the quality of connection |
| 1407        | resStatus    | 0     | Off                            |
|             |              | 1     | On                             |
| 1410        | resButtons   | 1     | 0                              |
|             |              | 5     | 0+go                           |
|             |              | 3     | 1                              |
|             |              | 7     | 1+go                           |

run the microservice:

```
docker run --rm -ti --net=host --privileged cfsd-proxy-cangw-res:v0.0.1 --cid=111 --can=can0 --verbose
```

generate the dbc map file:

```
docker run --rm -ti -v $PWD/src/:/in -w /in dbc2odvd:v0.0.0 generateHeaderOnly.sh lynxres19gw.dbc lynx-v0.1.0.odvd
```

get the code snippet:

```
docker run --rm -ti -v $PWD/src/:/in -w /in dbc2odvd:v0.0.0 generateMappingCodeSnippet.awk lynxres19gw.dbc.map
```

Setting the CAN:

```
sudo ip link set can0 up type can bitrate 1000000
sudo ifconfig can0 up
```

watch the CAN message:

```
candump can0
```