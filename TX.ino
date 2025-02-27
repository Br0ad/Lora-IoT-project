#include <SPI.h>
#include <RH_RF95.h>
#include "DHT.h"

// LoRa Pin Definitions for Feather RP2040 RFM95
#define RFM95_CS   16
#define RFM95_INT  21
#define RFM95_RST  17

// LoRa Frequency
#define RF95_FREQ 915.0

// DHT11 Sensor Pin and Type
#define DHTPIN 10
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

// LoRa Radio Driver
RH_RF95 rf95(RFM95_CS, RFM95_INT);

void setup() {
  pinMode(RFM95_RST, OUTPUT);
  digitalWrite(RFM95_RST, HIGH);

  Serial.begin(115200);
  while (!Serial) delay(1);
  delay(100);
  
  Serial.println("Initializing LoRa...");
  
  // Reset LoRa Module
  digitalWrite(RFM95_RST, LOW);
  delay(10);
  digitalWrite(RFM95_RST, HIGH);
  delay(10);

  // Initialize LoRa
  if (!rf95.init()) {
    Serial.println("LoRa init failed");
    while (1);
  }
  Serial.println("LoRa init OK!");

  // Set Frequency
  if (!rf95.setFrequency(RF95_FREQ)) {
    Serial.println("setFrequency failed");
    while (1);
  }
  Serial.print("Set Freq to: "); Serial.println(RF95_FREQ);

  // Set Power
  rf95.setTxPower(23, false);

  // Initialize DHT Sensor
  dht.begin();
}

void loop() {
  delay(2000); // Wait before reading sensor

  // Read DHT11 Sensor
  float humidity = dht.readHumidity();
  float tempC = dht.readTemperature();
  float tempF = dht.readTemperature(true);

  // Check if readings are valid
  if (isnan(humidity) || isnan(tempC) || isnan(tempF)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  // Compute Heat Index
  float heatIndexC = dht.computeHeatIndex(tempC, humidity, false);
  float heatIndexF = dht.computeHeatIndex(tempF, humidity);

  // Create Message String
  char message[50];
  snprintf(message, sizeof(message), "H:%.1f%% T:%.1fC %.1fF HI:%.1fC %.1fF", humidity, tempC, tempF, heatIndexC, heatIndexF);

  // Print to Serial
  Serial.println("Sending LoRa Message...");
  Serial.println(message);

  // Send Message via LoRa (with Correct Length)
  rf95.send((uint8_t *)message, strlen(message) + 1);

  // Wait for Transmission Completion
  rf95.waitPacketSent();
  Serial.println("Message Sent!");
}
