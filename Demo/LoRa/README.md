 
# Generic LoRa Board

## Notes
The original code given by RIOT OS has been modified to fit our demo purposes.

It has been choosen to leave that code almost unchanged to for better testing the devices.

Essential code for demo has been added in the appropriated parts. Everything is explained in the following document.

## Requirements
- [IOT-LAB](https://www.iot-lab.info) account
- TheThingsNetwork ([TTN](https://console.thethingsnetwork.org)) account
- [RIOT OS](https://riot-os.org/)

**Note for developers**: It's also important to go on your TTN *console* > *application* > *Payload Formats* and add the following javascript code to the *decoder* section:
```
function Decoder(bytes, port) {
  var result = "";
  for (var byte in bytes) {
    result += String.fromCharCode(bytes[byte]);
  }
  return {"string": result};
}
```

***

## Static Information
In this section are stored informations useful for demo purposes.

Here is possible to store data from the three testing devices for a quick setting.

***

## Emulation functions
Useful functions and variables for demo purposes.

Here it's possible to generate a random user profile approaching to the selected board.

***

## Get (almost unchanged)
In this section are present the get commands to give to the board for getting the wanted informations. This part has been left almost unchanged from the original code.

***

## Set
In this section are present the set commands to give to the board for setting the wanted informations.

Setting commands have been added to speed up the board setting process using default TTN devices.

Once launched, type `loramac set dev_**`, where in place of ** put the device number. (ex: `loramac set dev_01` to set the board as the device 01)

***

## Start
`start` command added for starting the simulation: when the command is given, the board with `dev_id` starts sending a random generated payload from the `get_random_payload()` function.

Type `loramac start` to start the loop for sending data.


After sending, the board sleeps for a random number of seconds. This sleep is useful for demo purposes because simulates a track playing in the corresponding node. In a real life situation the start command is given by a device approaching to the board requesting the audio reproduction.

The payload has the following shape: `{'dev_id' : 'dev_00', 'profile_id' : 'Hugo', 'hrate' : '72', 'timestamp' : '123'}`. This stands for "An User with profile 'Hugo' is visiting the 'Penelope Statue' that is equipped with the device 'dev_00' ".

***

## NFC Simulation
A command to simulate the NFC contact between the board and the smart band has been added. 

Type `loramac NFC` to send a message from the device. 
