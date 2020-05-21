# 2<sup>nd</sup> Delivery Recap

## The first judgement
Our first delivery was a bit confusionary so we tried to make it more focused and streamlined. 

<img src="https://i.kym-cdn.com/photos/images/newsfeed/001/838/935/07d.jpg" alt="alt text" width="250px">

## Changes
We moved our focus to the most important component of the project: the user.
Our second survey is based on questions about visitor's attitude with wearables to define better the possible use of the smartband.

## Our work up to now
The first prototype of the system has been built: basic connection across the edge board (iot-lab), the gateway (python script) and the cloud (Azure).
Audio playback is simulated printing different string on device terminal.

## Future-Features
We noticed that our project lacked interactivity so we decided to make visitors part of the museum's art. Using visitor's interactions with the statues we plan to create a digital modern art paiting. Stay tuned.




##### Metrics evaluation
| Metrics | Status |Solution/Result |
| ------------- |---| :-----|
| `Accessibility` | ✅ | Battery-powered that can last up to 2 years, they can be placed on any surface, accessible from the mobile app |
| `Radius` | ⚠️ |
| `Accuracy` | ⚠️ |
| `Precision` | ⚠️ |
| `Complexity` | ✅ | The architecture is very simple to install and to develop thanks to STM32 community specifications |
| `Robustness` | ⚠️ |
| `Scalability` | ⚠️ |
| `Cost` | ⚠️ | Cost of sensors + Cost of Google Cloud Platform |
| `Security` | ✅ | Beacons transmit output signals, there is no intrinsic safety risk in the transmission |
| `Failure detection` | ✅ | Being the statues close to each other, will be beacons (named guards) that monitor the other neighbors and report faults via the Google Cloud |