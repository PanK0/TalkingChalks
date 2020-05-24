# General Behaviour
The Gateway starts and loads all the registered devices attached to statues.

Lora nodes send a JSON string like the following one
`{'dev_id' : 'dev_00', 'profile_id' : 'hugo'}`

The Gateway receives the message and looks for the existance of the device.

If the device is found, then the Gateway assigns it the requested profile.

TODO : the audio track title corresponding to the profile is forwarded to the device so it can play the file.

TODO : data are forwarded to the cloud.

***

## Requirements
- [paho-mqtt](https://pypi.org/project/paho-mqtt/)
- [IOT-LAB](https://www.iot-lab.info) account
- TheThingsNetwork ([TTN](https://console.thethingsnetwork.org)) account
- [RIOT OS](https://riot-os.org/)
- [Gateway file](https://github.com/PanK0/TalkingChalks/tree/master/Demo/Gateway) knowledge
- [LoRa file](https://github.com/PanK0/TalkingChalks/tree/master/Demo/LoRa) knowledge

***
## How To test

### Gateway
- Run the `Gateway.py` giving `python Gateway.py` on your local machine

### LoRa
On [IOT-LAB](https://www.iot-lab.info) follow [this tutorial](https://www.iot-lab.info/tutorials/riot-ttn/) with some exceptions:
- at point (2), when you submit the experiment, change -l 1 with -l 3 in order to reserve two lorawan boards
- at point (4), after cloning RIOT, copy the file [main.c](https://github.com/PanK0/TalkingChalks/blob/master/Demo/LoRa/main.c) in the RIOT/tests/pkg_semtech-loramac folder
- at point (7) execute the command once per board
- at point (8) do the operations per each board
- instead of following point (10) just give the command `loramac set dev_id`, where `dev_id` is the ID of the device you have choosen between `dev_00`, `dev_01`, `dev_02`
- instead of following point (12) just give the command `loramac start`

## Output
The output should be like:

[![pic2.png](https://i.postimg.cc/c4gz3fFW/pic2.png)](https://postimg.cc/Cz0JTnyr)

***

## Directory Example and specifications
Here is an example on how the directory tree can be:

[![dirtree.png](https://i.postimg.cc/jj5jTsHZ/dirtree.png)](https://postimg.cc/MnCwbJrQ)

You can find the `main.c` file in the [/LoRa](https://github.com/PanK0/TalkingChalks/tree/master/Demo/LoRa) folder.

You can find the `Gateway.py` and the `devices.txt` file in the [/Gateway](https://github.com/PanK0/TalkingChalks/tree/master/Demo/Gateway) folder.
