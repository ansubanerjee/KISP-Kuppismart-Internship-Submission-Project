<h1># KISP-Kuppismart-Internship-Submission-Project</h1>
<h3>My Submission Project for Kuppismart Internship Interview </h3>

Meet KISP, It utilizes an ESP32 Module, Connected to a SIM900A for communication, which feeds in data from the BME280 Temperature, Pressure, Humidity sensor, BH1750 Light Sensor, MQ2 Gas Sensor. Coded using Embedded C Arduino Code.

<h2>
  Libraries Used:
</h2>
<h4>
  SoftwareSerial <br>
  MQ2 (custom library [https://github.com/rolan37/MQ-2-Sensor-Interfaced-with-Arduino/blob/main/MQ-2-sensor-library-master.zip]) <br>
  Wire <br>
  BME280-Adafruit <br>
  BH1750 <br>
</h4>

<h2>
  Primary Functions:
  Monitors the following attributes; Temperature, Pressure, Humidity, Smoke and Light of a system. Feeds this data to Thingspeak dashboard for monitoring, also has set values which act as a threshold for emergency, once the sensor crosses set value, it sends SMS to my phone number +91 8754322576 and alerts me of the same.
</h2>

Pin Connction:

https://www.flux.ai/omom/rear-indigo-point-of-view-gun?editor=schematic

MQ2 pin not added since the component was not available. The connection however I have listed below

BME280: <br>
VCC	3.3V <br>
GND	GND <br>
SDA	GPIO 21 (SDA) <br>
SCL	GPIO 22 (SCL) <br>

BH1750: <br>
VCC	3.3V <br>
GND	GND <br>
SDA	GPIO 21 (SDA) <br>
SCL	GPIO 22 (SCL)

MQ2: <br>
VCC	3.3V <br>
GND	GND <br>
AOUT	A0 <br>

SIM900A	VCC	5V: <br>
VCC	5V <br>
GND	GND <br>
TXD	GPIO 16 (RX2) <br>
RXD	GPIO 17 (TX2) <br>
