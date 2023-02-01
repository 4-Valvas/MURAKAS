#include <SPI.h>
#include <LoRa.h>

void setup() {
  Serial.begin(115200);       // Initialize serial
  while (!Serial);

  Serial.println("Serial connections - ONLINE");
  Serial.println("Initializing LoRa reciver");
  
  if (!LoRa.begin(866E6)) {             // Initialize LoRa radio at 866 MHz
    Serial.println("LoRa initialization failed. Check your connections. LoRa - OFFLINE");
    while (true);                       // If failed, do nothing
  }
  Serial.println("LoRa initialization succeeded.");
  Serial.println("Waiting packets");
}

void loop() {

  int packetSize = LoRa.parsePacket();  // try to parse packet
  if (packetSize) {
    Serial.print("Received packet '");  // received a packet
    
    while (LoRa.available()) {          // read packet
      Serial.print((char)LoRa.read());
    }
    Serial.print("' with RSSI ");       // print RSSI of packet
    Serial.println(LoRa.packetRssi());
  }
}
