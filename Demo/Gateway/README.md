# Gateway

## Requirements
- [paho-mqtt](https://pypi.org/project/paho-mqtt/)
- azure-iot-device [python module]

***

## TTN Stuffs
- `ttn_host = 'eu.thethings.network' `, standard TTN host for MQTT communication
- `ttn_port = 1883`, TTN service port
- `ttn_topic = '+/devices/+/up'`, TTN topic on which data are published
- `ttn_user = APP_NAME`, TTN Application's name
- `ttn_key = APP_KEY`, TTN App's Access Key

***

## Device
A Device has fields `name`, `device_id`, `hub_client`, `assigned_profile`.
All the devices are stored in a .txt file, one device per file, in the following format:
`<name> <device_id> <hub_client string>`
where

**name** = name of the statue where the device is attached

**device_id** = device ID on TTN

**hub_client** = connection string for the hub

When the gateway starts, all registered devices are loaded and connected to the hub by the function `upload_devices()`.

***

## on_message()
Callback, called when a message arrives.
The `message` field is an object of class **message** with members: [*topic*, *payload*, *qos*].
We are interested in **payload**.
- `message.payload` is a string. We want lora boards sending the payload formatted in a JSON string, so we can transform it into a dictionary.
After some transformations we obtain `received_message`, that is a dictionnary, and in the dictionary are:
	- `dev_id` , that is the device id. It's useful to recognise the board who sent the request for the profile identification.
	- `profile_id` , that is the profile who requested the service.
	- Example string:
	`{'dev_id' : 'dev_00', 'profile_id' : 'Hugo'}`
- `message.topic` contains the topic in where the message arrives.

**What happens when a message arrives?** When a message arrives it is transformed into a `received_message` dictionnary.

Then, through the `get_device()` function, there is a security check on the device to verify if it is a registered device and then the requested profile is assigned to the device through the `assign_profile()` function.

At the end, the message is forwarded to the cloud.

NB : the effective assignation has to be done. For now the profile is assigned only locally.

***

## Client
- `client = paho.Client(CLIENTNAME)` , where CLIENTMANE is a casual name to identify the Gateway Client that is subscribing `ttn_topic`
- `client.on_message = on_message` , on_message() callback to run when a message arrives on the topic
- `client.username_pw_set(ttn_user, password=ttn_key)` , to access with TTN Application credentials
- `client.connect(ttn_host, ttn_port, keepalive=60)` , to establish the connection with TTN
