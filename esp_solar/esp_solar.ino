
#include <WiFi.h>
#include "ThingSpeak.h"

const char* ssid = "Kshitij's Oneplus";   // your network SSID (name) 
const char* password = "kshitij18";   // your network password

WiFiClient  client;

unsigned long myChannelNumber = 2334777;
const char * myWriteAPIKey = "IY3I6QSP921R4G8Z";

// Timer variables
unsigned long lastTime = 0;
unsigned long timerDelay = 30000;
float current,voltage;
int x;
void setup() {
  Serial.begin(9600);  //Initialize serial
  //initBME();
  
  WiFi.mode(WIFI_STA);   
  
  ThingSpeak.begin(client);  // Initialize ThingSpeak
}

void loop() {
  if ((millis() - lastTime) > timerDelay) {
    
    // Connect or reconnect to WiFi
    if(WiFi.status() != WL_CONNECTED){
      Serial.print("Attempting to connect");
      while(WiFi.status() != WL_CONNECTED){
        WiFi.begin(ssid, password); 
        delay(5000);     
      } 
      Serial.println("\nConnected.");
    }
    //int current = analogRead(A5);
    int voltage = analogRead(A4);
    x=ThingSpeak.writeField(myChannelNumber, 1, voltage, myWriteAPIKey);

    //uncomment if you want to get temperature in Fahrenheit
    //int x = ThingSpeak.writeField(myChannelNumber, 1, temperatureF, myWriteAPIKey);
    if(x == 200){
      Serial.println("Channel update successful.");
    }
    else{
      Serial.println("Problem updating channel. HTTP error code " + String(x));
    }
    delay(15000);

    lastTime = millis();
  }
}