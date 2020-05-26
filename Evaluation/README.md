# Evaluation
## Survey
**First survey**

**Objectives:**
* analyse the habits of museum visitors and divide them in different categories;
* use of the competitors;
* possible difficulties that occur when bringing children to the museum;
* detect if people would like TalkingChalks and why not.

[Italian version](https://forms.gle/jZ4fBaXa6VDhBdABA) and [English one](https://forms.gle/cDC3gm15HeV4toPn9).

### Second survery

**Objectives:**
* identify the weakenesses of the competitors;
* use of the smartphone during the museum tour;
* preferred device(s) to activate TalkingChalks;
* what the museum tours lack in order to add it in a future release;
* detect if people would like and use TalkingChalks and why not.

[Italian](https://forms.gle/VDwkLs2pHf6RFf8VA) and [English](https://forms.gle/q8f3F8phV47RapQr8) versions.

### Results

**Audio guide issues:**
* You can use it only one at time / isolation
* Cost
* Quality of information provided
* Too long lasting descriptions

**Guided tours issues:**
* Cost
* Being bonded by the timing of the whole group
* Difficult to follow if there are too many people

**Info taken from internet issues:**
* Costantly checking on the phone
* Many researches required
* Source reliability
* Smartphone and internet connection required

**Use of the smartphone during the museum tour**
* People use their smartphone to take pictures during the tour
* Majority of people don't want to use it to look for information, etc.
* Causes isolation

**Preferred device to activate TalkingChalks**
* **Smartband**
  * easy-to-use
  * smartphone not required
  * no isolation 
  * no distraction given by the smartphone
  * possible issues: queues to pick it up and leave it after the tour, igienic problems due to pandemic

* **QR code**
  * need the personal smartphone
  * more igienic to use
  * distraction given by the smartphone

* **App**
  * need the personal smartphone
  * more igienic to use
  * distraction given by the smartphone
  * Main issue: to download an app that will be used only once.

## Objective
* Provide customized information on the tour 
* Info are propagated through speakers, in order to not isolate people
* Full immersion on the tour, but not too long descriptions
* **Simplicity** easy-to-use and ready-to-use
* Everyone can use it, even elder people, because no smartphone and no internet connectiont are required
* **Source reliability** because info are given by the museum 
* **Usability** response with the audio is quick
* **Scalability**

## Technical evaluation

### LoRaWAN STM Board

### Smartband
* Easy-to-use and ready-to-use
* No isolation
* Possible issues: recharge the batteries
* **Security**: it doesn't access to sensitive data of the users

### The Things Network

### Hi-Fi System
* Wired speakers connected to the LoRaWAN board 
* We don't need as many speakers as statues

### Cloud
* Azure by Microsoft offers many out-of-the-box services that can be easily interconnected
* We are currently using Azure IoT Hub and Azure Database
* If we want to extend our project, we can use other Azure services
* **Azure IoT Hub**
 * With our current subscription and with a standard plan, we can handle a maximum of 400000 messages per day.
 * The subscription is not free and only the first two devices are free. You can calculate your medium cost [here](https://azure.microsoft.com/it-it/pricing/calculator/)
 * **Database**
  * Always reachable
  * No sensitive data stored
  * Museum curators can use these data to find out which are the most visited artworks
