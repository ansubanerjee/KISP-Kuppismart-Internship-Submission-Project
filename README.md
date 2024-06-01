<h1># KISP-Kuppismart-Internship-Submission-Project</h1>
<h3>My Submission Project for Kuppismart Internship Interview </h3>

Meet KISP, It utilizes an ESP32 Module, Connected to a SIM900A for communication, which feeds in data from the BME280 Temperature, Pressure, Humidity sensor, BH1750 Light Sensor, MQ2 Gas Sensor. Coded using Embedded C Arduino Code.

<h2>
  Libraries Used:
</h2>
<h4>
  SoftwareSerial
  MQ2 (custom library [https://github.com/rolan37/MQ-2-Sensor-Interfaced-with-Arduino/blob/main/MQ-2-sensor-library-master.zip])
  Wire
  BME280-Adafruit
  BH1750
</h4>

<h2>
  Primary Functions:
  Monitors the following attributes; Temperature, Pressure, Humidity, Smoke and Light of a system. Feeds this data to Thingspeak dashboard for monitoring, also has set values which act as a threshold for emergency, once the sensor crosses set value, it sends SMS to my phone number +91 8754322576 and alerts me of the same.
</h2>

Pin Connction:

https://www.flux.ai/omom/rear-indigo-point-of-view-gun?editor=schematic

MQ2 pin not added since the component was not available. The connection however I have listed below

BME280:
VCC	3.3V
GND	GND
SDA	GPIO 21 (SDA)
SCL	GPIO 22 (SCL)

BH1750:
VCC	3.3V
GND	GND
SDA	GPIO 21 (SDA)
SCL	GPIO 22 (SCL)

MQ2:
VCC	3.3V
GND	GND
AOUT	A0

SIM900A	VCC	5V:
VCC	5V 
GND	GND
TXD	GPIO 16 (RX2)
RXD	GPIO 17 (TX2)
