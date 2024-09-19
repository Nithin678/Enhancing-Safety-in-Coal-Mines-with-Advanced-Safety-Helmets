![WhatsApp Image 2024-08-06 at 4 43 37 PM](https://github.com/user-attachments/assets/73b9b743-da46-4d9a-8b14-1e1d252133de)
The system starts with several sensors: a heart rate and SpO2 sensor that measures the user's heart rate and blood oxygen level; an air quality sensor that measures overall air quality; a carbon monoxide sensor that detects potentially dangerous levels of carbon monoxide; a DHT11 sensor that measures ambient temperature and humidity; and a GPS module that provides accurate location data. In addition, a panic button is included to allow users to directly signal emergency situations.All these components are connected to an Arduino microcontroller which acts as the central hub of the system. The Arduino collects the raw data from each sensor and processes it into a format suitable for transmission. The inclusion of a panic button allows the Arduino to instantly recognize and prioritize emergency signals. Once the data is compiled and processed, it is sent to the NodeMCU, a microcontroller with built-in Wi-Fi capabilities.
Essentially, this system provides a seamless flow of data from multiple sensors through the Arduino and NodeMCU to the server, facilitating end-to-end monitoring and emergency control. It shows how the integration of hardware and wireless communication can be used to improve health and environmental safety.




