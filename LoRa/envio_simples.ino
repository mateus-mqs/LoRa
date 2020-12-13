#include <SPI.h>
#include <LoRa.h>
const int csPin = 10;
const int resetPin = 9;
const int irqPin = 2; 
String InputString;

void setup() {
  Serial.begin(9600);
  while (!Serial);

  Serial.println("LoRa Sender");
  LoRa.setPins(csPin, resetPin, irqPin);
  if (!LoRa.begin(915E6)) {
    Serial.println("Starting LoRa failed!");
    while (1);
  }
}

void loop() {
  if(Serial.readString() == 0 && LoRa.receive() == 0){
    return;
  }
  else if(Serial.readString() == 1 && LoRa.receive() == 0){
    
   manda(); 
  }
  else if(Serial.readString() == 0 && LoRa.receive() == 1){
    //receive
  }
  else{
    return;
  }
 
}

void manda(){
   while(Serial.available()) {
    InputString = Serial.readString();
    LoRa.beginPacket();
    LoRa.print(InputString);
    LoRa.endPacket();
    Serial.print("Mateus: ");
    Serial.println(InputString);
   }
}

void recebe(){
  int packetSize = LoRa.parsePacket();
  if (packetSize) {
    Serial.print("João: ");
    while (LoRa.available()) {
      Serial.print((char)LoRa.read());
    }
  }
}
