# General Behaviour
The Gateway starts and loads all the registered devices attached to statues.

Lora nodes send a JSON string like the following one
`{'dev_id' : 'dev_00', 'profile_id' : 'hugo'}`

The Gateway receives the message and looks for the existance of the device.

If the device is found, then the Gateway assigns it the requested profile.

Data are forwarded to the cloud.

TODO : the audio track title corresponding to the profile is forwarded to the device so it can play the file.


***

## Requirements
- [paho-mqtt](https://pypi.org/project/paho-mqtt/)
- [IOT-LAB](https://www.iot-lab.info) account
- TheThingsNetwork ([TTN](https://console.thethingsnetwork.org)) account
- [RIOT OS](https://riot-os.org/)
- [Gateway file](https://github.com/PanK0/TalkingChalks/tree/master/Demo/Gateway) knowledge
- [LoRa file](https://github.com/PanK0/TalkingChalks/tree/master/Demo/LoRa) knowledge
- azure-iot-device [Python module]

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

And this is a kind of the message arriving to the cloud: 

[![database-received-data.png](https://i.postimg.cc/nzCmWL1D/database-received-data.png)](https://postimg.cc/bDfdDpWy)

[Here](https://youtu.be/xRKr4TnVqlI) is the tech demo.
## End User product [Draft]
[Here](https://youtu.be/Zwez2I6sRho) you can find a short video of how an user should see the system.

In the video the LoRa Board is physically simulated by a smartphone and two smartbands are physically simulated by two distinct NFC tags. Also the statue is simulated by an action figure of the famous pokèmon Squirtle.

It's possible to see that, when the user passes his smartband [NFC tag] next to the board [Smartphone], the corresponding audio guide is activated. Audio guides are different because the two simulated users have choosen different profiles.

***

## Directory Example and specifications
Here is an example on how the directory tree can be:

[![dirtree.png](https://i.postimg.cc/jj5jTsHZ/dirtree.png)](https://postimg.cc/MnCwbJrQ)

You can find the `main.c` file in the [/LoRa](https://github.com/PanK0/TalkingChalks/tree/master/Demo/LoRa) folder.

You can find the `Gateway.py` and the `devices.txt` file in the [/Gateway](https://github.com/PanK0/TalkingChalks/tree/master/Demo/Gateway) folder.
