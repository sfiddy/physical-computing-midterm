# Midterm IoT Project

Name: Stephanie Fiddy 

Date: October 12th 2017

## Project: Weather Wear
![Logo](/images/logo.png)

### Conceptual Description

/// Replace with a description of the ***critical / conceptual dimensions of your project***, with specific reference to the key issues it engages.  These should intersect with the issues that have been explored in the readings and discussions during the first half of class:  eWaste, data security/ownership in relation to corporate cloud infrastructures; critical making; surveillance and privacy, etc. ** *How does your project engage with these issues beyond mere instrumentality?* ** ///

### Form

The purpose of this enclosure is to introduce a service that camouflages into the user’s daily lives. Our devices need to be placed outdoors to provide the user with accurate temperature and soil moisture data. With this in mind, we have decided to hook our devices on a flower pot that could be placed in the user’s desired area (in our case, we would place it on the main quad in west campus). The flower pot provides the user with the portability and freedom of placing it in their desired area and moving it as needed. Our enclosures hook the devices on the edges of the pot providing easy installation and can be moved to other flower pots. 

The temperature monitoring device has a small opening in the bottom exposing the RHT03 temperature/humidity sensor to the open. The enclosure is *mostly* waterproof to protect the machinery inside. A 9V battery (which is also contained within the enclosure) powers the devices and therefore a computer is not needed to use the weather wear service. 


**Finished Enclosure:**

![Finished Enclosure](/images/enclosure.jpg)

**Electronics Exposed:**

![Enclosure with electronics exposed](/images/exposed.jpg)

### Technical Details
The “sweater weather” device communicates with the soil moisture device via Particle’s event cloud system. “Sweater Weather” is subscribed to 3 different events from the soil moisture device:

```
Particle.subscribe("Sandals", sandalsHandler, "320039001751353432393433");
Particle.subscribe("Rainboots", rainbootsHandler, "320039001751353432393433");
Particle.subscribe("Sneakers", sneakersHandler, "320039001751353432393433");
```
When either of the 3 events above (“Sandals”, “Rainboots”, or “Sneakers”) is triggered, the title of the event name is displayed in an LCD widget within the Blynk app. For instance, when the “Sandals” event is triggered, the string “Sandals” is displayed within the LCD Widget. All event handlers follow the same format as the snippet below:

```
void sandalsHandler(const char *event, const char *data)
{
    shoesInstruct.clear();
    delay(2500);
    shoesInstruct.print(0,0, "Sandals");
    Serial.print("Sandals \n");
}
```

Please refer to [photon.ino](photon.ino) for the full code. 

**Wiring Diagram**

![Wiring Diagram](/images/fritzing.jpg)
