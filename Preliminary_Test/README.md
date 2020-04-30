# Preliminary Tests
Following the official [IOT-LAB tutorial](https://www.iot-lab.info/tutorials/riot-ttn/).

Clone this repository in the terminal and then, after cloning RIOT, copy the file _main.c_ in the appropriate folder:

```
cp TalkingChalks/Preliminary_Test/main.c RIOT/tests/pkg_semtech-loramac
```

Run the gateway on your pc. You'll need paho-mqtt.
Then set up the lora nodes and run

```
loramac start
```
## Some pictures of the expected output
[![test1.png](https://i.postimg.cc/90GwyNcG/test1.png)](https://postimg.cc/Wq14v8F3)

[![test2.png](https://i.postimg.cc/T2mb8hnp/test2.png)](https://postimg.cc/BtSbHSY0)

[![test3.png](https://i.postimg.cc/0QSzqHML/test3.png)](https://postimg.cc/2bzkQGxw)

[![test4.png](https://i.postimg.cc/3NHdrC2W/test4.png)](https://postimg.cc/8Jt1tvKV)
