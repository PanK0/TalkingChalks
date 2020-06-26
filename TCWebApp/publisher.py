import os
from azure.iot.device import Message, IoTHubDeviceClient
import random
import time
import json

profiles = ["Hugo","Ettore","Maria"]
devs = ["dev_00","dev_01","dev_02"]

def publish_message():
    """
    It publishes messages to the IoT hub every 4 seconds.
    """
    con0 = "HostName=TalkingChalkz.azure-devices.net;DeviceId=dev_00;SharedAccessKey=UJ/C3PxH8S/dx/+uY6BuBEuBzyfKoPhk/btkGgG1y2c="
    client0 = IoTHubDeviceClient.create_from_connection_string(con0,websockets=True)
    
    con1 = "HostName=TalkingChalkz.azure-devices.net;DeviceId=dev_01;SharedAccessKey=3lE82lIMlEoJg1zvN9J8FFUxBxEeKNi+kJ1ZUad3igQ="
    client1 = IoTHubDeviceClient.create_from_connection_string(con1,websockets=True)

    con2 = "HostName=TalkingChalkz.azure-devices.net;DeviceId=dev_02;SharedAccessKey=5mbx9W1uxKd/aK6pDEKQuHaOcMkMkKwBqPRj/Ri051w="
    client2 = IoTHubDeviceClient.create_from_connection_string(con2,websockets=True)

    # Connect the device client
    client0.connect()
    client1.connect()
    client2.connect()

    while(True):
        try:
            dev = random.choice(devs)
            profile = random.choice(profiles)
            #Generating the message to send
            msg = {'dev_id' : dev, 'profile_id' : profile, 'hrate' : '72', 'timestamp' : '123'}
            message = json.dumps(msg)
            
            # Send the message
            print("Sending message...")
            if (dev=="dev_00"):
                client0.send_message(message)
            elif(dev=="dev_01"):
                client1.send_message(message)
            elif(dev=="dev_02"):
                client2.send_message(message)
            print("Message successfully sent!")
            print(message)
            time.sleep(4)
        
        except KeyboardInterrupt:
            print("IoTHubClient stopped")
            return
        
        except:
            print("Unexpected error")
            time.sleep(4)

    # finally, disconnect
    client0.disconnect()
    client1.disconnect()
    client2.disconnect()

if __name__ == "__main__":
    publish_message()