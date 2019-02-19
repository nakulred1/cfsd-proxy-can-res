# cfsd-proxy-cangw
cfsd proxy CAN getway

Mapping the CAN messages to Opendlv messages




run the microservice:

```
docker run cfsd-proxy-cangw:v0.0.0 --cid=111 --can=can0 --enablethrottle --enablebrake --enablesteering --verbose
```


generate the dbc map file:

```
docker run --rm -ti -v $PWD/src/:/in -w /in dbc2odvd:v0.0.0 generateHeaderOnly.sh lynx19gw.dbc lynx.odvd
```

get the code Snippet:

```
docker run --rm -ti -v $PWD/src/:/in -w /in dbc2odvd:v0.0.0 generateMappingCodeSnippet.awk lynx19gw.dbc.map
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