# LoRaWAN_Station
In this assignment we will built on-top of the cloud-based and edge-based components developed in the first and second assignments. Now we will replace the MQTT protocol and the short-range wireless medium with LoRaWAN and TheThingsNetwork. In this assignment you need to develop a new RIOT-OS application that will be executed on the B-L072Z-LRWAN1 LoRa kit. You will use TheThingsNetwork to interconnect the sensor devices with the cloud infrastructure via the MQTT protocol.

Using RIOT-OS develop an application that represents a virtual environmental station that generates periodically a set of random values for 5 different sensors:

    temperature (-50 ... 50 Celsius)
    humidity (0 ... 100%)
    wind direction (0 ... 360 degrees)
    wind intensity (0 ... 100 m/s)
    rain height (0 ... 50 mm / h)

The virtual environmental station uses a unique ID (identity) to publish these random values on TheThingsNetwork via LoRaWAN.

Refs @ http://ichatz.me/Site/InternetOfThings2020-Assignment3

## Requirements
- pahp-mqtt @ https://pypi.org/project/paho-mqtt/
- Mosquitto @ https://mosquitto.org/
- TheThingsNetwork @ https://www.thethingsnetwork.org/
- IOT-LAB @ https://www.iot-lab.info/

In order to make the whole thing work see the requirements @ [MAIN PROJECT PAGE](https://github.com/PanK0/iot-project#requirements)

It's also important to go on your TTN *console* > *application* > *Payload Formats* and add the following javascript code to the _decoder_ section:

```
function Decoder(bytes, port) {
  var result = "";
  for (var byte in bytes) {
    result += String.fromCharCode(bytes[byte]);
  }
  return {"string": result};
}
```

## TTNTBClient.py
The client receives data from the devices on the TheThingsNetwork and forwards the telemetry to Thingsboard.

Remember to set the variables _ACCESS\_TOKEN\_C_ and _ACCESS\_TOKEN\_D_ to your Thingsboard's devices tokens.

Also remember to change the _ttn\_user, ttn\_key, ttn\_dev\_e, ttn\_dev\_f_ with your devices parameters.

This file will run on your *local machine*.

## main.c
- Copy the file main.c in the _RIOT/tests/pkg\_semtech-loramac_ folder

The file emulates two environmental stations sending data on the choosen topics formatted in a JSON script.

This file will be compiled in your IOT-LAB RIOT instance and the resulting _.elf_ file will be flashed on two lorawan boards.

You can easily follow the dedicated [TUTORIAL ON IOT-LAB](https://www.iot-lab.info/tutorials/riot-ttn/) keeping in mind that:
- at point (2), when you submit the experiment, change _-l 1_ with _-l 2_ in order to reserve two lorawan boards
- at point (7) execute the command once per board
- at point (8) do the operations per each board

Note that IOT-LAB uses the code of the 2019.01 release of [RIOT](https://github.com/RIOT-OS/RIOT).

## Directory Example
Here is an example on how the directory tree can be:

[![dirtree.png](https://i.postimg.cc/K8wgtkL4/dirtree.png)](https://postimg.cc/rDGmkpfL)

## Tutorial
[FULL TUTORIAL HERE](https://www.hackster.io/panicik/iot-assignment-3-0191b5)
