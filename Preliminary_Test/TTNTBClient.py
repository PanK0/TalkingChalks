import paho.mqtt.client as paho                         # mqtt library
import os
import json
import time
import random
from datetime import datetime

# Communication with TheThingsNetwork
ttn_host = 'eu.thethings.network'                                       # Host for TheThingsNetwork
ttn_port = 1883                                                         # TTN service Port
ttn_topic = '+/devices/+/up'                                            # TTN topic
ttn_user = 'iotappan'                                                   # TTN Application's name
ttn_key = 'ttn-account-v2.myG4JDRyLI_p3ylliDwH72pX7bkdRBRL8-fmWpJ0jio'  # TTN Application's Access Key
ttn_dev_e = 'iotappan-dev-e'                                            # device E name
ttn_dev_f = 'iotappan-dev-f'                                            # device F name

# Payload variables
payload_E = ""
payload_F = ""

def on_connect(client, userdata, flags, rc) :           # connect callback for datarec in TTN
    print ("Connected with result code " + str(rc))

def on_subscribe(client, userdata, mid, granted_qos) :
    print ("Subscribed")

def on_message(client, userdata, message) :
    #print("Received message '" + str(message.payload) + "' on topic '" + message.topic)
    generic_payload = json.loads(message.payload)       # Capturing the message arrived on TTN Topic
    #print(generic_payload['dev_id'] )

    if (generic_payload['dev_id'] == ttn_dev_e) :
        pippo = generic_payload['payload_fields']
        global payload_E
        payload_E = pippo['string']
    elif (generic_payload['dev_id'] == ttn_dev_f) :
        pippo = generic_payload['payload_fields']
        global payload_F
        payload_F = pippo['string']
    else : print("LOOOOL")

# Setting up Data Receiver from TTN
datarec = paho.Client("DataRec")                        # create client for data receiver from TTN
datarec.on_message = on_message                         # define what to do when a message is received
datarec.username_pw_set(ttn_user, password=ttn_key)     # access with the right credentials
datarec.on_subscribe = on_subscribe                     # event handler
datarec.connect(ttn_host, ttn_port, keepalive=60)       # establish connection
datarec.subscribe(ttn_topic, qos=1)


# Start loooooooooop
datarec.loop_start()

# Starting up our rsmb
while (True) :

    while (payload_E == "" and payload_F == "") :
        pass

    # Nike of Samotracia statue
    if (payload_E != "") :
        print ("Nike of Samotracia statue is speaking!")
        print ("Using profile : " + payload_E)
        print ("BLA BLA BLA BLA BLA BLA BLA BLA BLA BLA BLA")

    print ("\n")

    # President Mattarels statue
    if (payload_F != "") :
        print ("President Mattarels status is speaking!  ** Must change the name for legal reasons")
        print ("Using profile : " + payload_F)
        print ("Fratelli d'Italia, l'Italia s'è desta! E dell'elmo di Scipio s'è cinta la testa.")
        print ("Dov'è la Vittoria? Le porga la chioma! Che schiava di Roma Iddio la creò.")

    print ("\n")

    # Reset payload variables
    payload_E = ""
    payload_F = ""
