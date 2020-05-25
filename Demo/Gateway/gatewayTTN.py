import paho.mqtt.client as mqtt                     # mqtt library
import os
import json
import time
import random
from azure.iot.device import Message, IoTHubDeviceClient
from datetime import datetime
import configparser

'''
#######################################
BEGIN DEVICE CLASS
'''
class Device :

    def __init__(self, name, device_id) :
        self.name = name
        self.device_id = device_id
        self.assigned_profile = 'default'

    def __str__(self) :
        return ("Device Name : " + self.name + ", Device ID : " + self.device_id)

# Variables for devices
filename = 'devices.txt'
devices = [None] * 0

# Function for uploading devices : creates an empty list and then appends the devices from the file
def upload_devices() :
    devices = [None] * 0
    with open(filename) as devfile :
        lines = [line.rstrip() for line in devfile]
        for element in lines :
            attributes = element.split(" ")
            devices.append(Device(attributes[0], attributes[1]))
    return devices

# Function for getting a device from a list of devices given the device_id
def get_device(device_id, devices) :
    for element in devices :
        if (element.device_id == device_id) :
            print ("Device found!")
            return element
    print ("No device with ID " + device_id + " found.")

# Function to assign a given profile to a device given the device id and a device list
def assign_profile(device_id, profile, devices) :
    for element in devices :
        if (element.device_id == device_id) :
            element.assigned_profile = profile
            print ("Profile assigned")

#connect to TTN and subscribe to the topic of the devices
def on_connect(client, userdata, flags, rc) :          
    print ("Gateway connected with result code " + str(rc))
    client.subscribe('+/devices/+/up')

#disconnect from TTN
def on_disconnect(client,userdata,rd):
	print("Gateway disconnected")

# Callback for message event
def on_message(client, userdata, message) :
    print("\n*********************************************")
    #print (message.payload)

    global devices
    generic_payload = json.loads(message.payload) # dict

    payload_dict = generic_payload['payload_fields'] #dict

    received_message = json.loads(payload_dict['string']) #dict

    dev_id = received_message['dev_id']

    sender_device = get_device(dev_id, devices)
    assign_profile(sender_device.device_id, received_message['profile_id'], devices)

    print ("A message has been received")
    print ("Sender Device : " + received_message['dev_id'])
    print ("Device Name : " + sender_device.name )
    print ("Profile Required : " + received_message['profile_id'] + ", assigned : " + sender_device.assigned_profile)

    msg = {'profile_id':received_message['profile_id']}
    msg = json.dumps(msg)

    if (dev_id == config['HUB']['Device0']):
		hub_client0.send_message(msg)
    elif (dev_id == config['HUB']['Device1']):
		hub_client1.send_message(msg)
    elif (dev_id == config['HUB']['Device2']):
		hub_client2.send_message(msg)
    print("Message forwarded to the hub")

    print("*********************************************\n")


if __name__=="__main__":
    #load the configuration file
    config = configparser.ConfigParser()
    config.read('TTNconfigurations.ini')

    #connect to the hub
    hub_client0 = IoTHubDeviceClient.create_from_connection_string(config['HUB']['ConnectionString0'],websockets=True)
    hub_client0.connect()
    hub_client1 = IoTHubDeviceClient.create_from_connection_string(config['HUB']['ConnectionString1'],websockets=True)
    hub_client1.connect()
    hub_client2 = IoTHubDeviceClient.create_from_connection_string(config['HUB']['ConnectionString2'],websockets=True)
    hub_client2.connect()

    # Setting up Data Receiver from TTN
    client = mqtt.Client("Gateway")                        # create client for data receiver from TTN
    client.on_connect = on_connect
    client.on_message = on_message                         # define what to do when a message is received
    client.username_pw_set(config['TTN']['AppID'],config['TTN']['AccessKey'])
    client.connect(config['TTN']['Server'],int(config['TTN']['Port']),60)

    devices = upload_devices()
    for element in devices :
        print(element)

    try:
        client.loop_forever()

    except KeyboardInterrupt:
        print('disconnect')
        client.disconnect()
        hub_client0.disconnect()
        hub_client1.disconnect()
        hub_client2.disconnect()