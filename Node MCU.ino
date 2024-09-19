#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ThingSpeak.h>

const char* ssid = "abcd";   // Your Network SSID
const char* password = "12345678";       // Your Network Password


WiFiClient client;

unsigned long myChannelNumber = 2611668; //Your Channel Number (Without Brackets)
const char * myWriteAPIKey = "M869556TKZ28PXFK"; //Your Write API Key


#include <TinyGPS++.h>
#include <SoftwareSerial.h>//Library used to create software serial port                                  
                  // library used to enable i2c port 

int Number_of_SATS;       // Variable used to store number of satellite  
float latitude;         // variable to store latitude
float longitude;       // variable to store longitude                                 
TinyGPSPlus gps;         // create oject gps to class TinyGPSPLUS
SoftwareSerial serial2(D7, D8);  // create software serial "serial2" tx pin of gps to pin11 and rx to pin 10

#include <Wire.h>
#include "MAX30100_PulseOximeter.h"

#define REPORTING_PERIOD_MS     1000

PulseOximeter pox;

   
    int sensorValue1;
    int sensorValue2;
    int sensorValue3;
  
 float sensorValue4;

uint32_t tsLastReport = 0;
        float heartBeat;
        int spo2;


void onBeatDetected()
{
    Serial.println("Beat!");
}

void setup(){

   Serial.begin(115200);
   serial2.begin(9600);
  WiFi.begin(ssid, password);
  ThingSpeak.begin(client);

   Serial.print("Initializing pulse oximeter..");


    if (!pox.begin()) {
        Serial.println("FAILED");
        for(;;);
    } else {
        Serial.println("SUCCESS");
    }

    pox.setOnBeatDetectedCallback(onBeatDetected);
 }  


void loop(){

  getGPS();
  
   pox.update();

    if (millis() - tsLastReport > REPORTING_PERIOD_MS) {
getGPS();
        Serial.print(pox.getHeartRate());
      Serial.print(",");
        Serial.print(pox.getSpO2());
      Serial.println(",");
      Serial.println(" ");
   
     Serial.print(sensorValue1);
          Serial.print(",");
     Serial.print(sensorValue2);
           Serial.print(",");
      Serial.print(sensorValue3);
            Serial.print(",");
     Serial.println(sensorValue4);

           Serial.print(latitude);
            Serial.print(",");

                  Serial.print(longitude);
            Serial.println(",");

  ThingSpeak.writeField(myChannelNumber, 1,pox.getHeartRate(), myWriteAPIKey); //Update in ThingSpeak
  ThingSpeak.writeField(myChannelNumber, 2,pox.getSpO2(), myWriteAPIKey); //Update in ThingSpeak
    ThingSpeak.writeField(myChannelNumber, 3,sensorValue1, myWriteAPIKey); //Update in ThingSpeak
        ThingSpeak.writeField(myChannelNumber, 4,sensorValue2, myWriteAPIKey); //Update in ThingSpeak
            ThingSpeak.writeField(myChannelNumber, 5,sensorValue4, myWriteAPIKey); //Update in ThingSpeak
                ThingSpeak.writeField(myChannelNumber, 6,sensorValue3, myWriteAPIKey); //Update in ThingSpeak
                    ThingSpeak.writeField(myChannelNumber, 7,longitude, myWriteAPIKey); //Update in ThingSpeak
                        ThingSpeak.writeField(myChannelNumber, 8,latitude, myWriteAPIKey); //Update in 


    tsLastReport = millis();

    }
  
 if ( serial2.available()) {
    String data = serial2.readStringUntil('\n');   // x data (2,0.5,37)
    int firstSeparatorIndex = data.indexOf(",");
    int secondSeparatorIndex = data.indexOf(",", firstSeparatorIndex + 1);
    int thirdindex =data.indexOf(",",secondSeparatorIndex +1);
    int fourthindex =data.indexOf(",",thirdindex + 1);

   
    sensorValue1 = data.substring(0, firstSeparatorIndex).toInt();
     sensorValue2 = data.substring(firstSeparatorIndex + 1, secondSeparatorIndex).toInt();
    sensorValue3 = data.substring(secondSeparatorIndex + 1,thirdindex).toInt();
  
  sensorValue4 = data.substring(thirdindex+1,fourthindex).toInt();
   




  }
}

void getGPS()                                                 // Get Latest GPS coordinates
{

  while (Serial.available() > 0)             //check for gps data available in serial port
  {
    gps.encode(Serial.read());
  }                 // encode the gps data into latitude and longitude 

latitude =gps.location.lat(); //fe tch latitude and store 
longitude =gps.location.lng(); // fetch longitude and store 

}
