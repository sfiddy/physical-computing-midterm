// This #include statement was automatically added by the Particle IDE.
#include <blynk.h>

// This #include statement was automatically added by the Particle IDE.
#include <SparkFunRHT03.h>



//////////////////////
// RHT03 DEFINITIONS //
/////////////////////
const int RHT03_DATA_PIN = D3;          // RHT03 Data Pin
const int TEMP_LABELED_VALUE_PIN = V2;  // Labeled Value Pin in Blynk
const int USER_TEMP_INPUT = V3;         // User entered temperature
RHT03 rht;                              // RHT03 Object

////////////////////////
// BLYNK DEFINITIONS //
///////////////////////
char auth[] = "98f495e9e02d45a88e80fc93d5b44cbc";


//////////////////////
// I/O DEFINITIONS //
/////////////////////
WidgetLCD sweaterWeatherText(V1);
WidgetLCD sweaterInstruct(V4);
WidgetLCD shoesInstruct(V5);
// WidgetTerminal terminal(V6);



// Grabs user's temp threshold input 
int userTempInput = 0;
int prevUserTempInput = 0;
// int terminalInput = 0;
BLYNK_CONNECTED() { Blynk.syncVirtual(V3); }
BLYNK_WRITE(V3) { userTempInput = param.asInt(); }
// BLYNK_WRITE(V6){ terminalInput = param.asInt(); }


// Runs redboard
void setup() {
    
    Serial.begin(9600);
    rht.begin(RHT03_DATA_PIN);                  // Initializes the RHT03 sensor
    
    // Particle Subscription to receive shoetype events
    Particle.subscribe("Sandals", sandalsHandler, "320039001751353432393433");
    Particle.subscribe("Rainboots", rainbootsHandler, "320039001751353432393433");
    Particle.subscribe("Sneakers", sneakersHandler, "320039001751353432393433");
    
    Blynk.begin(auth);                  // Connects to my Blynk app
    displayText();                      // Displays sweater weather text question to user 
    
    
    
}

void loop() {
    
    Blynk.run();                        // Runs Blynk App
    
    if(userTempInput != prevUserTempInput)
    {
        Serial.print("User Temp input changed from: ");
        Serial.print(prevUserTempInput);
        Serial.print(" to ");
        Serial.print(userTempInput);
        Serial.print("\n");
        prevUserTempInput = userTempInput;
    }

    int update = rht.update();        // update = 1 when successful, 0 otherwise.
    if (update == 1) {
        float tempF = rht.tempF();           // Set temp = updated temperature in Farenheits
        float humidity = rht.humidity();    // Set humidty = updated humidity levels
        
        // Displays Updated values in Blynk app
        Blynk.virtualWrite(V0, tempF);
        sweaterWeather(tempF);           // Instructs the user on whether to wear a sweater or not
    }
    else {
        delay(1000);                    // If no update, then delay 1 second
    }
    
    delay(1500);                        // Delays next update to prevent spamming

}

void sandalsHandler(const char *event, const char *data)
{
    shoesInstruct.clear();
    delay(2500);
    shoesInstruct.print(0,0, "Sandals");
    Serial.print("Sandals \n");
}

void rainbootsHandler(const char *event, const char *data)
{
    shoesInstruct.clear();
    delay(2500);
    shoesInstruct.print(0,0, "Rainboots");
    Serial.print("Rainboots \n");
}

void sneakersHandler(const char *event, const char *data)
{
    shoesInstruct.clear();
    delay(2500);
    shoesInstruct.print(0,0, "Sneakers");
    Serial.print("Sneakers \n");
}


// Displays input instruction for user
// and displays user's input
void displayText()
{
    sweaterWeatherText.clear();
    sweaterWeatherText.print(0,0,"Sweater weather");
    sweaterWeatherText.print(0,1,"temp(F)?");
}

void sweaterWeather(int temp) 
{
    Blynk.virtualWrite(V2, userTempInput);
    sweaterInstruct.clear();
    if(userTempInput < temp)
    {
        Particle.publish("sweater");
        Serial.print("published sweater event \n");
        sweaterInstruct.print(0,0, "sweater");
        Blynk.email("weatherwear.data@gmail.com", "User Clothing Data", "The user wore a Sweater");
    }
    else 
    {
        Particle.publish("nosweater");
        Serial.print("published no sweater event \n");
        sweaterInstruct.print(0,0, "no sweater");
        Blynk.email("weatherwear.data@gmail.com", "User Clothing Data", "The user did not wear a Sweater");
    }
}
