#include <SPI.h>
#include <LoRa.h>


#include <OneWire.h>
#include <DallasTemperature.h>

#define ONE_WIRE_BUS 7                  // OneWire data port


OneWire oneWire(ONE_WIRE_BUS);          // Set up OneWire
DallasTemperature sensors(&oneWire);    // Set up DallasTemperature

const int csPin = 10;                   // LoRa radio chip select
const int resetPin = 5;                 // LoRa radio reset
const int irqPin = 2;                   // Change for your board; must be a hardware interrupt pin

float temperaturePIN7;                  // Variable for temperature measurements
float temperaturePIN8;


void setup() {
  Serial.begin(115200);                 // Initialize serial
  while (!Serial);
  Serial.println("Serial connections - ONLINE");
  Serial.println("Initializing LoRa sender");

  // Override the default CS, reset, and IRQ pins (optional)
  LoRa.setPins(csPin, resetPin, irqPin);// Set CS, reset, IRQ pin

  if (!LoRa.begin(866E6)) {             // Initialize LoRa radio at 866 MHz
    Serial.println("LoRa initialization failed. Check your connections. LoRa - OFFLINE");
    while (true);                       // If failed, do nothing
  }
  Serial.println("LoRa initialization succeeded.");
}

void loop() {
  read_temp();                          // Read data from sensors 
  
  Serial.println("Sending packet with LoRa");
  LoRa.beginPacket();                   // Sending data with LoRa
  LoRa.print(temperaturePIN7);
  LoRa.endPacket();
  Serial.println("Packet sent");
  
  LoRa.sleep();                         // Putting LoRa module in sleep mode
 
  delay(8000);
}

void read_temp(){                       // Void for reading data from different sensors
  sensors.requestTemperatures();
  Serial.println(sensors.getTempCByIndex(0));
  temperaturePIN7 = sensors.getTempCByIndex(0); //For fahrenheit: sensors.getTempFByIndex(0)
}
