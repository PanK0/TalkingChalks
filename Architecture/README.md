# Architecture

## General
Due to the quarantine circumstances that made it impossible for us to put our hands on the real boards, the project is presented in a semi-simulated environment using the [iot-lab.info](https://www.iot-lab.info/) real testbed facility and [RIOT-OS](https://riot-os.org/) to provide a portable and functional application: in this way the whole system is easy replicable and ready to be used.
The general idea is as follows:

A bracelet is provided to the users with a premade internal general profile to identify what kind of user is visiting the museum. Profiles are essential to let the application know the language of the user and the level of detail for the presentation of the artifacts.


Once a user with a bracelet steps next to a statue a sensor recognizes the user profile and, using [LoRa](https://en.wikipedia.org/wiki/LoRa#LoRaWAN) technology, sends the information to the Cloud through the gateway.

The gateway forwards data to the Cloud and sends the material to reproduce to an HiFi System incorporated in the statue, so the user can hear the personalized description.

When in the Cloud, data can be stored into a database and they will be ready to be analyzed.

## LoRaWAN Boards
[LoRaWAN](https://lora-alliance.org/about-lorawan): Long Range Wide Area Network is a communication protocol with high efficiency peculiarities. LoRaWAN is based on low power consumption and a wide communication range belonging to a technologies category named LPWAN - Low Power Wide Area Network, useful in terms of sensors to use the least energy as possible.
With [iot-lab.info](https://www.iot-lab.info/) in our project we are going to use [B-L072Z-LRWAN1 LoRa Kit](https://www.st.com/en/evaluation-tools/b-l072z-lrwan1.html) programmable using [RIOT-OS](https://riot-os.org/).

## Bracelet 
TODO

## The Things Network
[The Things Network](https://www.thethingsnetwork.org/) provides a set of open tools and a global, open network to build an IoT application at low cost.
In our project it is used to register our devices to the network and to let them communicate with the gateway.

## TTN/MQTT Gateway
TODO

## Hi-Fi System
TODO

## Cloud
TODO

# Database
TODO
