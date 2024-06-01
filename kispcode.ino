// SUBMISSION OF ANSU BANERJEE, VIT UNIVERSITY, Email: workansubanerjee@gmail.com
// Utilizes ESP32 Microcontroller, SIM900A, BME280, BH1750, MQ2

// Packages Included:
#include <SoftwareSerial.h>
#include <MQ2.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>
#include <BH1750.h>

// Constants:
SoftwareSerial gprsSerial(12, 13);  // RX, TX pins for SIM900A
BH1750 lightMeter;
Adafruit_BME280 bme;
const int smokeSensorPin = A0;
unsigned long delayTime;
MQ2 mq2(smokeSensorPin);

void setup() {
  Serial.begin(9600);
  Wire.begin();
  Serial.println("Systems Test");

  bool status1;
  bool status2; 
  
  status1 = bme.begin(0x76);
  status2 = lightMeter.begin();
  mq2.begin();
  
  if (!status1) {
    Serial.println("BME280 Sensor Not found");
    while (1);
  }
  if (!status2) {
    Serial.println("BH1750 Sensor Not found");
    while (1);
  }

  Serial.println("-- Default Test --");
  delayTime = 300000;

  Serial.println();
}

void ShowSerialData() {
  while (gprsSerial.available() != 0) {
    Serial.write(gprsSerial.read());
  }
  delay(5000);
}

// SENDING ALERTS ON MOBILE USING SIM900A
void alertSystem(float temperature, float pressure, float humidity, float smoke, float light) {
  float alertTemperature = 50.0;
  float alertPressure = 990.0; 
  float alertHumidity = 90.0;
  float alertSmoke = 130000.0;
  float alertLight = 400.0; 

  Serial.println("Wait for initialization");
  gprsSerial.println("AT+CMGF=1");
  delay(1000);
  gprsSerial.println("AT+CMGS=\"+918754322576\"\r");
  delay(1000);
  
  if (temperature > alertTemperature) {
    gprsSerial.println("ALERT Current Temperature of System: ");
    gprsSerial.println(temperature);
    gprsSerial.println("System Monitoring Required");
  }
  if (pressure > alertPressure) {
    gprsSerial.println("ALERT Current Pressure of System: ");
    gprsSerial.println(pressure);
    gprsSerial.println("System Monitoring Required");
  }
  if (humidity > alertHumidity) {
    gprsSerial.println("ALERT Current Humidity of System: ");
    gprsSerial.println(humidity);
    gprsSerial.println("System Monitoring Required");
  }
  if (smoke > alertSmoke) {
    gprsSerial.println("ALERT Current Smoke of System: ");
    gprsSerial.println(smoke);
    gprsSerial.println("System Monitoring Required");
  }
  if (light < alertLight) {
    gprsSerial.println("ALERT Current Light of System: ");
    gprsSerial.println(light);
    gprsSerial.println("System Monitoring Required");
  }
  
  gprsSerial.println((char)26);
  delay(1000);
}

void loop() {
  // Declaration of all Sensor Data to be fed into the SIM900A
  float temperature = bme.readTemperature();
  delay(100);
  float pressure = bme.readPressure() / 100.0;
  delay(100);
  float humidity = bme.readHumidity();
  delay(100);
  float smoke = (mq2.readSmoke() * 100.0) / 1000000.0;
  delay(100);
  float light = lightMeter.readLightLevel();
  delay(100);

  // Setting up the GPRS Module
  if (gprsSerial.available()) {
    Serial.write(gprsSerial.read());
  }
  gprsSerial.println("AT");
  delay(1000);
  gprsSerial.println("AT+CPIN?");
  delay(1000);
  gprsSerial.println("AT+CREG?");
  delay(1000);
  gprsSerial.println("AT+CGATT?");
  delay(1000);
  gprsSerial.println("AT+CIPSHUT");
  delay(1000);
  gprsSerial.println("AT+CIPSTATUS");
  delay(2000);
  gprsSerial.println("AT+CIPMUX=0");
  delay(2000);
  
  ShowSerialData();
  
  gprsSerial.println("AT+CSTT=\"airtelgprs.com\"");
  delay(1000);
  ShowSerialData();
  
  gprsSerial.println("AT+CIICR");
  delay(3000);
  ShowSerialData();
  
  gprsSerial.println("AT+CIFSR");
  delay(2000);
  ShowSerialData();
  
  gprsSerial.println("AT+CIPSPRT=0");
  delay(3000);
  ShowSerialData();
  
  gprsSerial.println("AT+CIPSTART=\"TCP\",\"api.thingspeak.com\",\"80\"");
  delay(6000);
  ShowSerialData();
  
  gprsSerial.println("AT+CIPSEND");
  delay(4000);
  ShowSerialData();

  String str = "GET https://api.thingspeak.com/update?api_key=Z7X0QZUZTVCP81YM&field1=" + String(temperature) + "&field2=" + String(humidity) + "&field3=" + String(pressure) + "&field4=" + String(smoke) + "&field5=" + String(light);
  Serial.println(str);
  gprsSerial.println(str);

  delay(4000);
  ShowSerialData();
  gprsSerial.println((char)26);
  delay(5000);
  gprsSerial.println();
  ShowSerialData();
 
  gprsSerial.println("AT+CIPSHUT");
  delay(100);
  ShowSerialData();
  
  alertSystem(temperature, pressure, humidity, smoke, light);
}
