# Architecture

![](pics/architecture.png)

## Video Presentation
Take a look at the video presentation @ https://youtu.be/5a8aUJ3mY7I

## General
The project is presented in a semi-simulated environment using the [iot-lab.info](https://www.iot-lab.info/) real testbed facility and [RIOT-OS](https://riot-os.org/) to provide a portable and functional application, in this way the whole system is easy replicable and ready to be used.
<br/>The general idea is as follows:

Each visitor is provided with a smartband different for every typology of user that is visiting the museum. Profiles are essential to let the application know the language of the user and the level of detail for the presentation of the artifacts.

Once a visitor with a smartband steps next to a statue, a sensor recognizes the user profile and sends the information to the Cloud through the gateway using [LoRa](https://en.wikipedia.org/wiki/LoRa#LoRaWAN) technology.

The gateway forwards data to the Cloud and sends the material to reproduce to an HiFi System incorporated in the statue, so the user can hear the customized description.

When in the Cloud, data can be stored into a database and they will be ready to be analyzed.

# LoRaWAN STM Board
[LoRaWAN](https://lora-alliance.org/about-lorawan): Long Range Wide Area Network is a communication protocol with high efficiency peculiarities. LoRaWAN is based on low power consumption and a wide communication range belonging to a technologies category named LPWAN - Low Power Wide Area Network, useful in terms of sensors to use the least energy as possible.
With [iot-lab.info](https://www.iot-lab.info/) in our project we are going to use [B-L072Z-LRWAN1 LoRa Kit](https://www.st.com/en/evaluation-tools/b-l072z-lrwan1.html) programmable using [RIOT-OS](https://riot-os.org/).
The B-L072Z-LRWAN1 LoRa®/SigfoxTM Discovery kit is a development tool to learn and develop solutions based
on LoRa®, SigfoxTM, and FSK/OOK technologies. This Discovery kit features the all-in-one CMWX1ZZABZ-091
open module by Murata. The module is powered by an STM32L072CZ microcontroller and SX1276 transceiver.
The transceiver features the LoRa® long-range modem, providing ultra-long-range spread-spectrum
communication and high interference immunity, minimizing current consumption. Since CMWX1ZZABZ-091 is an
open module, the user has access to all STM32L072CZ peripherals such as ADC, 16-bit timer, LP-UART, I2C,
SPI, and USB 2.0 FS (supporting BCD and LPM).
The B-L072Z-LRWAN1 Discovery kit includes an ST-LINK/V2-1 embedded debug tool interface, LEDs, push-
buttons, antenna, ArduinoTM Uno V3 connectors and USB OTG connector in Micro-B format.
The LoRaWANTM stack supports Class A, Class B, and Class C. It is available in the I-CUBE-LRWAN firmware
package. Several examples, including an AT-command stack, are available to help users set up a complete
LoRaWANTM node.
The SigfoxTM stack is RC1, RC2, RC3c, and RC4 compliant. It is available in the X-CUBE-SFOX Expansion
Package. Several examples, including an AT-command modem, are also available to help users set up a
complete SigfoxTM node.

![](pics/board.png)

Each board based on STM Nucleo system has a beacon/nfc sensor able to identify a smartband's profile and it is also equipped with an Hi-Fi System.

# Smartband
The smartband is the key point of the entire system because it stores the premade user profiles. It also contains a beacon sensor to be identified by the board. The profile ID is sent to the LoRaWAN board and an appropirate guide track will be reproduced. The main role of the smartband is to activate the sensor near the statue, but we have decided to exploit the data that all the smartbands collect and use also heart rate in our project. Heart rate is also sent to the hub and stored in the database with all the other data in order to catch the level of appreciation of the user while looking at the statue.

Smartband has been chosen to activate TalkingChalks because it is easy-to-use, ready-to-use, doesn't cause isolation and it doesn't access to sensitive data of the users.

# The Things Network
[The Things Network](https://www.thethingsnetwork.org/) provides a set of open tools and a global, open network to build an IoT application at low cost.
In our project it is used to register our devices to the network and to let them communicate with the gateway.

# TTN/MQTT Gateway
The Gateway is responsible of the forwarding of the incoming data from The Things Network to the Cloud.

Once running, the Gateway launches a client that subscribes to the TTN's broker at the topic _+/devices/+/up_ using as username the name of the TTN Application and as password the Applocation Access Key.

Data are received from the boards as a json string, then the emitting board is identified by its ID and the payloads are so forwarded using MQTT protocol.

# Hi-Fi System
Simple speakers connected to the LoRaWAN board, the main role of these instruments is to reproduce the requested audio track that explains the statue. They can be connected to the electric system or powered by batteries. We don't need as many speakers as artworks in the museum and volume must be not too loud in order to not interpose with the audio description of other statues.

# Cloud
Azure IoT Hub by Microsoft is a managed service hosted in the cloud that acts as a central message hub for bidirectional communication between the IoT application and the device it manages.

It has a lot of functionalities for all the types of applications, in our project we will use it as MQTT broker to receive messages sent by the devices through the Gateway and store the data in CosmoDB, which is an integrated service.
With a free subscription and with a standard plan, we can handle a maximum of 8000 messages per day.

# Database
Azure CosmoDB is a multi-model database service for any scale. It guarantees a global distribution, high-availability and low latency. Messages that arrive at the hub are stored here, so that museum curators can access the data and know which are the most visited statues and the typologies of users.
