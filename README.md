# Midterm IoT Project

Name: Stephanie Fiddy 

Date: October 12th 2017

## Project: Weather Wear
![Logo](/images/logo.png)

### Conceptual Description

Weather Wear emphasizes society’s reliance on technology in our everyday decision making process and how those decisions can be unknowingly monitored. It addresses the problem of data ownership and dispersion that often remains unnoticed by these silent devices that we use in our everyday lives. Weather Wear’s enclosure camouflages into our environment to remain unnoticed by the user. Unknown to the user, when the app displays its recommendation on whether to wear a sweater and what type of shoe to use is emailed to the developers.
This discreet form of data collection demonstrates how the simplest device can be exploited for data collection. Our model sends an email to weatherwear.data@gmail.com on what the user wore based on the recommendations from the Blynk app.  
In addition, Weather Wear demonstrates how the introduction of a new service can affect the way we carry out our day to day tasks. It automates a personal, intimate decision on what we wear. ITS and smartphone compatibility facilitates the creation of the habit of using the app. With time, the user may feel the need to refer to the app to decide what to wear instead of doing it themselves. 


### Form

The purpose of this enclosure is to introduce a service that camouflages into the user’s daily lives. Our devices need to be placed outdoors to provide the user with accurate temperature and soil moisture data. With this in mind, we have decided to hook our devices on a flower pot that could be placed in the user’s desired area (in our case, we would place it on the main quad in west campus). The flower pot provides the user with the portability and freedom of placing it in their desired area and moving it as needed. Our enclosures hook the devices on the edges of the pot providing easy installation and can be moved to other flower pots. 

The temperature monitoring device has a small opening in the bottom exposing the RHT03 temperature/humidity sensor to the open. The enclosure is *mostly* waterproof to protect the machinery inside. A 9V battery (which is also contained within the enclosure) powers the devices and therefore a computer is not needed to use the weather wear service. 


**Finished Enclosure:**

![Finished Enclosure](/images/enclosure.jpg)

**Electronics Exposed:**

![Enclosure with electronics exposed](/images/exposed.jpg)

### Technical Details

#### Sweater Weather Device
The “Sweater Weather” device uses the [Sparkfun RHT03 Humidity and Temperature Sensor](https://www.sparkfun.com/products/10167) to read the temperature of the desired location. Through the Blynk app, the user specifies the temperature at which he/she usually wear sweaters and is then prompted on whether the user should wear a sweater that day given the current temperature. 

![Blynk Demo for Sweater Weather](/images/blynk-demo.png)
#### Device Communication
The “sweater weather” device uses a two-way communication system to transfer data between my device and the soil moisture device. They communicate with each other using the Particle’s event cloud system. My device publishes either 2 of the following events depending on the pertinent sweater value: 
```
Particle.publish("sweater");
Particle.publish("nosweater");
```

“Sweater Weather” is subscribed to 3 different events from the soil moisture device:
```
Particle.subscribe("Sandals", sandalsHandler, "320039001751353432393433");
Particle.subscribe("Rainboots", rainbootsHandler, "320039001751353432393433");
Particle.subscribe("Sneakers", sneakersHandler, "320039001751353432393433");
```
When either of the 3 events above (“Sandals”, “Rainboots”, or “Sneakers”) is triggered, the title of the event name is displayed in an LCD widget within the Blynk app. For instance, when the “Sandals” event is triggered, the string “Sandals” is displayed within the LCD Widget. All handlers follow the same format as the snippet below:

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
