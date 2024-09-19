#include <DHT.h>
#define DHTPIN 7    // Pin connected to the DHT11 sensor
#define DHTTYPE DHT11 // Type of DHT sensor
DHT dht(DHTPIN, DHTTYPE);






void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

 dht.begin();

 

}

void loop() {
  // put your main code here, to run repeatedly:


int humidity = dht.readHumidity();
int temperature = dht.readTemperature();

      // Check if any errors occurred while reading the sensor
      if (isnan(humidity) || isnan(temperature)) {
        Serial.println("Failed to read data from DHT11 sensor");
        return;
      }

        // Print the temperature and humidity to the serial monitor

      Serial.print(temperature);
Serial.print(",");
      Serial.print(humidity);
      Serial.print(",");

int airQuality = analogRead(A1);
int mq7 = analogRead(A0);

      Serial.print(airQuality);
Serial.print(",");
      Serial.print(mq7);
      Serial.println(",");
       
  





}
