import paho.mqtt.client as paho                         # mqtt library
import os
import json
import time
import random
from azure.iot.device import Message, IoTHubDeviceClient
from datetime import datetime
import configparser
from tkinter import *                                   # painting
from random import seed, randint, choice
import scriptDatabase


'''
#######################################
BEGIN THE THINGS NETWORK
Variables to interact with TTN
'''

# Communication with TheThingsNetwork
ttn_host = 'eu.thethings.network'                                       # Host for TheThingsNetwork
ttn_port = 1883                                                         # TTN service Port
ttn_topic = '+/devices/+/up'                                            # TTN topic
ttn_user = 'talkingchalks'                                              # TTN Application's name
ttn_key = 'ttn-account-v2.irz9S0BWYo_ydlT-PddsRSza7epCz6ScAfSP--qhdMM'  # TTN Application's Access Key

'''
END THE THINGS NETWORK
#######################################
'''

'''
#######################################
BEGIN DEVICE CLASS
'''
class Device :

    def __init__(self, name, device_id, hub_client) :
        self.name = name
        self.device_id = device_id
        self.assigned_profile = 'default'
        self.hub_client = hub_client
        self.timestamp = 0

    def __str__(self) :
        return ("Device Name : " + self.name + ", Device ID : " + self.device_id + ", Connected : " + str(self.hub_client.connected))

'''
END DEVICE CLASS
#######################################
'''

'''
#######################################
BEGIN PAINTING
'''

# Stuffs
WIDTH = 900
HEIGHT = 600
HUGO = 'Hugo'
MARIA = 'Maria'
ETTORE = 'Ettore'
categories = [HUGO, MARIA, ETTORE]

yel_range = ('#ffff00', '#ffff4d', '#ffff99')
red_range = ('#ff0000', '#ff4d4d', '#ff9999')
blu_range = ('#0000ff', '#4d4dff', '#8080ff')


master = Tk()
c = Canvas(master, width=WIDTH, height=HEIGHT)
c.pack()

def random_coord(width,height):
    seed(1)
    w = randint(0,width)
    h = randint(0,height)
    return w,h

# category : user profile from {HUGO, MARIA, ETTORE}
# c : canvas in where to painting
# hr : heartrate, used for the radius
# width=0 : border of the geometric shape
def add_circle(c, category, hr, w, h):
    global yel_range, red_range, blu_range

    if (category == HUGO):
        colour = choice(yel_range)      # yellow
    elif(category == MARIA):
        colour = choice(red_range)      # red
    elif (category == ETTORE):
        colour = choice(blu_range)      # blue
    c.create_oval(w, h, w+hr, h+hr, width=0, fill=colour)

def paint_message(devices, categories) :
    dev = choice(devices)
    prof = choice(categories)
    hr = randint(50, 120)
    if (prof == HUGO) : prof = "Hugo"
    elif (prof == MARIA) : prof = "Maria"
    elif (prof == ETTORE) : prof = "Ettore"
    print("\n*********************************************")
    print ("Profile assigned")
    print ("A message has been received")
    print ("Sender Device : " + dev.device_id)
    print ("Device Name : " + dev.name )
    print ("Profile : " + prof)
    print ("Heart rate : " + str(hr))
    print("*********************************************\n")

    add_circle(c, prof, hr, randint(0, WIDTH), randint(0, HEIGHT))


# received_message :
# {'dev_id' : 'dev_00', 'profile_id' : 'Hugo', 'temp' : '36', 'hrate' : '72', 'timestamp' : '123'}
def print_circle(received_message) :
    global c
    cat = received_message['profile_id']
    hr = int(received_message['hrate'])
    add_circle(c, cat, hr, randint(0, WIDTH), randint(0, HEIGHT))

'''
END PAINTING
#######################################
'''

'''
#######################################
BEGIN CLIENT SETTINGS
Settings for the client: callbacks, functions and variables for the gateway client
'''

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
            hucli = IoTHubDeviceClient.create_from_connection_string(attributes[2], websockets=True)
            hucli.connect()
            devices.append(Device(attributes[0], attributes[1], hucli) )
    return devices

# Function for getting a device from a list of devices given the device_id
def get_device(device_id, devices) :
    for element in devices :
        if (element.device_id == device_id) :
            #print ("Device found!")
            return element
    print ("No device with ID " + device_id + " found.")

# Function to assign a given profile to a device given the device id and a device list
def assign_profile(device_id, profile, timestamp, devices) :
    for element in devices :
        if (element.device_id == device_id) :
            element.assigned_profile = profile
            element.timestamp = timestamp
            print ("Profile assigned")


# Callback for connection
def on_connect(client, userdata, flags, rc) :           # connect callback for datarec in TTN
    print ("Connected with result code " + str(rc))

# Callback for subscription
def on_subscribe(client, userdata, mid, granted_qos) :
    print ("Subscribed")

# Callback for message event
def on_message(client, userdata, message) :

    #print (message.payload)

    global devices
    generic_payload = json.loads(message.payload)           # dict
    payload_dict = generic_payload['payload_fields']        # dict
    received_message = json.loads(payload_dict['string'])   # dict

    sender_device = get_device(received_message['dev_id'], devices)
    if (received_message['timestamp'] != sender_device.timestamp) :

        print("\n*********************************************")

        assign_profile(sender_device.device_id, received_message['profile_id'], received_message['timestamp'], devices)


        print ("A message has been received")
        print ("Sender Device : " + received_message['dev_id'])
        print ("Device Name : " + sender_device.name )
        print ("Profile Required : " + received_message['profile_id'] + ", assigned : " + sender_device.assigned_profile)

        msg = {'profile_id':received_message['profile_id']}
        hub_msg = json.dumps(msg)
        (sender_device.hub_client).send_message(hub_msg)
        print("Profile forwarded to the hub")

        received_message['id'] = received_message['timestamp']
        scriptDatabase.add_to_db(received_message)

        print("*********************************************\n")

# Setting up Data Receiver from TTN
client = paho.Client("Gateway")                        # create client for data receiver from TTN
client.on_message = on_message                         # define what to do when a message is received
client.username_pw_set(ttn_user, password=ttn_key)     # access with the right credentials
client.on_subscribe = on_subscribe                     # event handler
client.connect(ttn_host, ttn_port, keepalive=60)       # establish connection
client.subscribe(ttn_topic, qos=1)

'''
END CLIENT SETTINGS
#######################################
'''

'''
#######################################
BEGIN MAIN
'''

if __name__ == "__main__" :

    devices = upload_devices()
    for element in devices :
        print (element)

    if (input("Type <demo> to start the demo ") == "demo") :
        #
        while (input() == "") :
            paint_message(devices, categories)
    else :
        try :
            client.loop_forever()

        except KeyboardInterrupt :
            print('Disconnecting')
            client.disconnect()
            for element in devices :
                element.hub_client.disconnect()

'''
END MAIN
#######################################
'''
