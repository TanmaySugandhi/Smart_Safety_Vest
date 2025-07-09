#define BLYNK_TEMPLATE_ID "TMPL3T6gQDCT3"
#define BLYNK_TEMPLATE_NAME "SCB"
#define BLYNK_AUTH_TOKEN "wiNDgCTL8OOFD-NOD3V2zn-SvVhdsBmQ"

#define BLYNK_PRINT Serial

#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>
#include <DHT.h>
#include <Wire.h>
#include <TinyGPSPlus.h>
#include <PulseSensorPlayground.h>

// WiFi credentials
char ssid[] = "Error";
char pass[] = "idontknow";

// DHT Sensor setup
#define DHTPIN 33
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

// Pulse sensor setup
const int PulseSensorPin = 32;
PulseSensorPlayground pulseSensor;
int myBPM = 0;

// ADXL335 Sensor setup
const int xPin = 26;
const int yPin = 35;
const int zPin = 27;
const float sensitivity = 0.300;       // Sensitivity for ADXL335 (V/g)
const float zero_g_voltage = 1.65;     // Zero-g voltage

// NEO-6M GPS setup using HardwareSerial
TinyGPSPlus gps;
HardwareSerial gpsSerial(1); // UART1

// MQ7 setup
#define MQ7PIN 34

// Blynk timer
BlynkTimer timer;

void setup() {
  Serial.begin(115200);

  // Initialize WiFi and Blynk
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);

  // Initialize DHT sensor
  dht.begin();

  // Configure pulse sensor
  pulseSensor.analogInput(PulseSensorPin);
  pulseSensor.setThreshold(550);
  if (pulseSensor.begin()) {
    Serial.println("Pulse Sensor started");
  } else {
    Serial.println("Failed to start Pulse Sensor.");
  }

  // Initialize GPS on UART1, RX=16, TX=17
  gpsSerial.begin(9600, SERIAL_8N1, 16, 17);
}

void loop() {
  Blynk.run();
  timer.run();

  float dhtValue = dht11Values();
  String adxlValue = adxl335Values();
  float mq7Value = mq7Values();
  float pulseVal = pulseValue();
  String neo6Val = neo6Value();

  // Send data to Blynk
  Blynk.virtualWrite(V0, dhtValue);
  Blynk.virtualWrite(V1, adxlValue);
  Blynk.virtualWrite(V2, mq7Value);
  Blynk.virtualWrite(V3, pulseVal);
  Blynk.virtualWrite(V4, neo6Val);

  // Debug prints
  Serial.println(adxlValue);
  Serial.println(dhtValue);
  Serial.println(mq7Value);
  Serial.println(pulseVal);
  Serial.println(neo6Val);
  Serial.println("===========");

  delay(1000); // Optional: Replace with timer for cleaner code
}

float dht11Values() {
  float temperature = dht.readTemperature();
  if (isnan(temperature)) {
    Serial.println("Failed to read from DHT sensor!");
    return 0;
  }
  return temperature;
}

String adxl335Values() {
  int xReading = analogRead(xPin);
  int yReading = analogRead(yPin);
  int zReading = analogRead(zPin);

  float xVoltage = xReading * (3.3 / 4095.0);
  float yVoltage = yReading * (3.3 / 4095.0);
  float zVoltage = zReading * (3.3 / 4095.0);

  // Convert voltage to acceleration (g)
  float xAccel = (xVoltage - zero_g_voltage) / sensitivity;
  float yAccel = (yVoltage - zero_g_voltage) / sensitivity;
  float zAccel = (zVoltage - zero_g_voltage) / sensitivity;

  return createOutputString(xAccel, yAccel, zAccel);
}

float mq7Values() {
  return analogRead(MQ7PIN);
}

float pulseValue() {
  myBPM = pulseSensor.getBeatsPerMinute();
  if (pulseSensor.sawStartOfBeat()) {
    return myBPM / 2.0; // Divided by 2 as per your logic
  }
  return 0; // Return 0 if no beat detected
}

String neo6Value() {
  String gpsData = "";

  while (gpsSerial.available() > 0) {
    gps.encode(gpsSerial.read());
  }

  if (gps.location.isUpdated()) {
    gpsData += "Lat: " + String(gps.location.lat(), 6);
    gpsData += ", Lon: " + String(gps.location.lng(), 6);
    gpsData += ", Alt: " + String(gps.altitude.meters()) + "m";
    gpsData += ", Speed: " + String(gps.speed.kmph()) + "km/h";
    gpsData += ", Sat: " + String(gps.satellites.value());
  } else {
    gpsData = "No GPS data available";
  }

  return gpsData;
}

String createOutputString(float xAccel, float yAccel, float zAccel) {
  String direction;

  if (xAccel > 0.5) {
    direction = "Right";
  } else if (xAccel < -0.5) {
    direction = "Left";
  } else if (yAccel > 0.5) {
    direction = "Forward";
  } else if (yAccel < -0.5) {
    direction = "Backward";
  } else if (zAccel > 0.5) {
    direction = "Up";
  } else if (zAccel < -0.5) {
    direction = "Down";
  } else {
    direction = "Stable";
  }

  return "X: " + String(xAccel, 2) + " g, " +
         "Y: " + String(yAccel, 2) + " g, " +
         "Z: " + String(zAccel, 2) + " g, " +
         "Direction: " + direction;
}
