# TalkingChalks

## The second judgement
<img src="pics/more_iot.jpg" width="250px">

In the first delivery professors had doubts about the use of smartbands for our application, because the choice seemed not well motivated and evaluated.
In the second delivery we presented our well done evaluation work, showing our results on user preferences and needs during a tour in a museum: smart band resulted to be a winning choice, satisfying the majority of people with the simplicity, the immediacy of use and the contained costs for enjoying the tour.
Finally, in the second judgement, professors liked how we defended our work according to their comments. However they suggested us to add some extra features to make the project more attrative in terms of IOT.

For this reason we wanted to enlarge our focus on the user and so we took inspiration from [this](https://mapping-museum-experience.com/wp-content/uploads/2019/04/Physiological-Correlates.pdf) paper: laboratory research has indicated that artworks may elicit emotional and physiological responses and we tried too collect this kind of data! The dimensions “Aesthetic Quality”, “Surprise/Humor”, “Dominance”  and “Curatorial Quality” were associated with cardiac measures (heart rate variability,heart rate level).
We decided to add this functionality to the smartband to let it collect also the heart rate of the person who wears it. It can be used as an indicator to understand if he liked the artwork or not and later by the curators to build more specific tours.

Moreover the scalability we have planned will let to implement more smart features as you can see in the specific section.

Finally, we also we paid attention to the comments the professors gave to other teams and even if they said nothing to us, we evaluated to create a simple web interface to let the curators visualize the dedicated data of devices and statues: it is just a simple and unpretentious web view, but this is the curse of IOT and not the one of Web Application Development, so we decided to focus more on the IOT aspect.

## Changes
* New functionality! Heart reate sensing.
* Visitor's painting completed.
* System full functionalities developed. 
* Detailed cost evaluation of the prototype. 
* Web interface for curators.

## Our work up to now
We finally built a working prototype of the whole system that you can see [here](https://youtu.be/zbf5zkPk7X0): again audio playback is simulated with "on-screen" text, but now we managed to push visitor's data to the database and figured out how to really do crowdsensing with them.

As exposed in previus delivery we noticed that our project lacked interactivity so we decided to make visitors part of the museum's art. A new abstract painting is generated everyday by the users while activating the sensors with the smartbands.

<img src="pics/circle.gif">

Moreover, smartband now has the ability to read heart rate of the visitor. The heart rate pick of the last few seconds will be sent to the gateway when the NFC tag of a statue is scanned and this will help curators to understand if the statue is appreciated or not. This idea is validated thanks to [this](https://mapping-museum-experience.com/wp-content/uploads/2019/04/Physiological-Correlates.pdf) paper. In addition heart rate is also used to give different sizes to the visitor's "personal" painting circles.

The complete code to make TalkingChalks alive is available in the [/Demo](https://github.com/PanK0/TalkingChalks/tree/master/Demo) section, and also a simple tutorial and the description of the software are provided.

We have made a cost evaulation so that the museum curators know more about TalkingChalks and its costs. We have decided to estimate the cost per unit, so that the curators of each museum can decide where to place each unit. It's strongly recommended to not to place sensors on each statue, because the speakers of a statue can interpose with the ones of another statue.

## Possible Future Implementations
The keypoint of our project as explained multiple times is the scalability: smartband can be used for multiple purposes thanks to its easyness of use. Thanks to this we think that a new "future-feature" could be the possibility to let the band vibrate when the visitors are too close to the statue (safety of the object) or too close to each others (safety for the person). 

Moreover, many others visitor's profile can be implemented to diversify more the journey into the museum.

## What we have not evaluated
An important part of the project that could not evaluate is product evaluation both by us and by the users. Unfortunately we don't own a programmable smartband and we have no access to the Sapienza museum right now, so we could not test our product and we could not collect users feedbacks on it. 

## Blog post
[Here](https://www.hackster.io/348161/talking-chalks-d497bc) is a blog post that presents our work.
