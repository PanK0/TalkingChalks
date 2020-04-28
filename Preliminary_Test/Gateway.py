import paho.mqtt.client as paho                         # mqtt library
import os
import json
import time
import random
from datetime import datetime

# Default texts
maria = "Maria"
hugo = "Hugo"
ettore = "Ettore"

nike_maria = "Ehi ciao! Sono la Nike di Samotracia! Vuoi giocare con me?"
nike_hugo = """The Winged Victory of Samothrace, also called the Nike of Samothrace,
            (Greek: Νίκη της Σαμοθράκης Niki tis Samothrakis) is a marble Hellenistic sculpture of Nike
            (the Greek goddess of victory), that was created in about the 2nd century BC. Since 1884,
            it has been prominently displayed at the Louvre and is one of the most celebrated
            sculptures in the world. H. W. Janson described it as the greatest masterpiece of
            Hellenistic sculpture"""
nike_ettore = """La Nike di Samotracia venne scolpita a Rodi in epoca ellenistica per
            commemorare la vittoria della lega delio-attica nella battaglia dell'Eurimedonte,
            in cui il re siriano Antioco III combatté contro un'alleanza tra Roma, Pergamo,
            Rodi e Samotracia. """

matt_maria = "Ciao! Io sono il Sommo Presidente Mattarels, e domani mi studierai sui libri di scuola."
matt_hugo = """ Il Canto degli Italiani is a canto written by Goffredo Mameli and set to music by Michele Novaro
                in 1847[2], and is the current national anthem of Italy. It is best known among Italians as the Inno di Mameli
                 ("Mameli's Hymn"), after the author of the lyrics, or Fratelli d'Italia ("Brothers of Italy"), from its opening
                 line. The piece, a 4/4 in B-flat major, consists of six strophes and a refrain that is sung at the end of each strophe.
                 The sixth group of verses, which is almost never performed, recalls the text of the first strophe.    """
matt_ettore = """ Fratelli d'Italia, l'Italia s'è desta! E dell'elmo di Scipio s'è cinta la testa.
                Dov'è la Vittoria? - le porga la chioma - che schiava di Roma Iddio la creò. """

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

    # Nike of Samothrace statue
    if (payload_E != "") :
        print ("Nike of Samothrace statue is speaking!")
        print ("Using " + payload_E)
        text = json.loads(payload_E)
        if (text['Profile'] == maria) :
            print (nike_maria)
        elif (text['Profile'] == hugo) :
            print (nike_hugo)
        else :
            print (nike_ettore)

    print ("\n")

    # President Mattarels statue
    if (payload_F != "") :
        print ("President Mattarels statue is speaking!  ** Must change the name for legal reasons")
        print ("Using " + payload_F)
        text = json.loads(payload_F)
        if (text['Profile'] == maria) :
            print (matt_maria)
        elif (text['Profile'] == hugo) :
            print (matt_hugo)
        else :
            print (matt_ettore)

    print ("\n")

    # Reset payload variables
    payload_E = ""
    payload_F = ""
