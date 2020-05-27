# Evaluation
## TalkingChalks objectives
* Provide customized information on the tour for every typology of user
* Full immersion on the tour
* **Simplicity**: easy-to-use and ready-to-use
* Everyone can use it, even elder people, because no smartphone and no internet connectiont are required
* **Source reliability**: info are provided by the museum 
* **Scalability**

## Survey
**First survey**
[Italian version](https://forms.gle/jZ4fBaXa6VDhBdABA) and [English one](https://forms.gle/cDC3gm15HeV4toPn9).

**Objectives:**
* analyse the habits of museum visitors and divide them in different categories;
* use of the competitors;
* possible difficulties that occur when bringing children to the museum;
* detect if people would like TalkingChalks and why not.

**Results:**
* people prefer audio guides because they are easy-to-use and they can visit the museum on their own
* bringing children to the museum is easy, but not keep them focused on the visit and provide them info

### Second survery
[Italian](https://forms.gle/VDwkLs2pHf6RFf8VA) and [English](https://forms.gle/q8f3F8phV47RapQr8) versions.

**Objectives:**
* identify the weakenesses of the competitors;
* use of the smartphone during the museum tour;
* preferred device(s) to activate TalkingChalks;
* what the museum tours lack in order to add it in a future release;
* detect if people would like and use TalkingChalks and why not.

### Results

**Audio guide drawbacks:**
* You can use it only one at time / isolation
* Cost
* Quality of information provided
* Too long lasting descriptions

**Guided tours drawbacks:**
* Cost
* Have to conform to the timing of the whole group
* Difficult to follow if there are too many people

**Info taken from internet drawbacks:**
* Repeatedly checking on the phone
* Many researches required
* Source reliability
* Smartphone and internet connection required

**Use of the smartphone during the museum tour:**
* People use their smartphone to take pictures during the tour
* Majority of people doesn't want to use it to look for information, etc.
* Causes isolation

**Preferred devices to activate TalkingChalks:**
* **Smartband**
  * easy-to-use
  * smartphone not required
  * no isolation 
  * no distraction given by the smartphone
  * possible drawbacks: queues to pick it up and leave it after the tour, igienic problems due to pandemic

* **QR code**
  * needs the personal smartphone
  * more igienic to use
  * distraction given by the smartphone

* **App**
  * need the personal smartphone
  * more igienic to use
  * distraction given by the smartphone
  * Main drawbacks: to download an app that will be used only once.

## Technical evaluation

### LoRaWAN STM Board
* Low power consumption
* Wide communication range

### Smartband
* Easy-to-use and ready-to-use
* No isolation
* **Security**: no access to sensitive data of the users

### Hi-Fi System
* Wired speakers connected to the LoRaWAN board 
* We don't need as many speakers as statues
* Volume not too loud in order to not interpose with the audio description of other statues

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

## Demo
We have built a demo using IoT-Lab, TheThingsNetwork and Azure IoT Hub. The Gateway starts and loads all the registered devices attached to statues..When Lora nodes send a JSON string like {'dev_id' : 'dev_00', 'profile_id' : 'hugo'}, the gateway receives it and looks for the device. If the device is found, then the Gateway assigns the requested profile to it and data are forwarded to the hub. During this simulation we have not used speakers: the description of the statue is just a string.

## End user product
We have also built a end user product 

   
## FAQ

#### What is TalkingChalks?
TalkingChalks is an IoT system that can be used in a museum. It can help visitors during the tour providing information about the museum, the statues and the story behind them.

#### How does it work?
TalkingChalks works with special smartbands. They can activate sensors placed in specific points and an audio description of the statue will be played out loud. The audio description changes according to the typology of the smartbands that is activating it. The sensors are activated by smartbands and not by people in proximity because the museum is a noisy environment full of students who study and have classes. Moreover counting how many times sensors have been activated by the smartbands, we can have an overview on the most visited statues of the collection.

#### Why is TalkingChalks different?
TalkingChalks’ innovation is that the tour is more interactive and fun, especially for children. Plus, students from classical studies and from theatre courses could contribute to our project providing the correct information in the best way.

#### Does it answer the needs of the user?
TalkingChalks uses different smartbands to meet everyone’s needs. There is a smartband for people passionate about arts so that they can have detailed descriptions, a smartband for people who are not really interested and want to know the basic information. There is also a smartband for teachers or parents who are visiting the museum with children, so that they can have information in a simplified way. 

#### Why a smartband?
TaklingChalks works with a smartband so that everyone can use it. It is mainly thought for children and elder people, which don’t usually have smartphones or an internet connection.
