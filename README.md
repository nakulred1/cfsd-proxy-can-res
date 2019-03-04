# cfsd-proxy-cangw
cfsd proxy CAN getway

Mapping the CAN messages to Opendlv messages

run the microservice:

```
docker run --rm -ti --net=host --privileged cfsd-proxy-cangw-res:v0.0.0 --cid=111 --can=can0 --verbose
```


generate the dbc map file:

```
docker run --rm -ti -v $PWD/src/:/in -w /in dbc2odvd:v0.0.0 generateHeaderOnly.sh lynxres19gw.dbc lynx-v0.1.0.odvd
```

get the code Snippet:

```
docker run --rm -ti -v $PWD/src/:/in -w /in dbc2odvd:v0.0.0 generateMappingCodeSnippet.awk lynxres19gw.dbc.map
```

Setting the CAN:

```
sudo ip link set can0 up type can bitrate 500000
sudo ifconfig can0 up
```

watch the CAN message:

```
candump can0
```