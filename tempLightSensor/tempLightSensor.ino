#include <SPI.h>
#include <Ethernet.h>

#define DEBUG_TO_SERIAL 0
#define AREF_VOLTAGE 3.3

String server_id = "sensor.server.domain";

int tempPin = A0;
int tempReading;
int photocellPin = A1;
int photocellReading;

byte mac[] = {
  0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };

EthernetServer server(80);

void setup(void) {
  Serial.begin(9600);
  
  analogReference(EXTERNAL);
  
  if (Ethernet.begin(mac) == 0) {
    Serial.println("Failed to configure Ethernet using DHCP");
    // no point in carrying on, so do nothing forevermore:
    for(;;)
      ;
  }
  
  server.begin();  
  
  Serial.print("Server started at address: ");
  for (byte thisByte = 0; thisByte < 4; thisByte++) {
    // print the value of each byte of the IP address:
    Serial.print(Ethernet.localIP()[thisByte], DEC);
    Serial.print("."); 
  }
  Serial.println();

}

void loop(void) {
  EthernetClient client = server.available();
  if (client) {
      boolean currentLineIsBlank = true;
      while (client.connected()) {
           if (client.available()) {
               char c = client.read();
               if (c == '\n' && currentLineIsBlank) {
                   photocellReading = analogRead(photocellPin);
                   tempReading = analogRead(tempPin);

                   float tempVoltage = tempReading * AREF_VOLTAGE / 1024.0;
                   float tempC = (tempVoltage - 0.5) * 100 ;

                   #if DEBUG_TO_SERIAL
                     Serial.print("Light = ");
                     Serial.println(photocellReading);
                     Serial.print("Raw temp = ");
                     Serial.print(tempReading);
                     Serial.print(" - ");
                     Serial.print(tempVoltage);
                     Serial.println(" volts");
                     Serial.print("Temp = ");
                     Serial.print(tempC);
                     Serial.println(" degrees C");
                   #endif

                   client.println("HTTP/1.1 200 OK");
                   client.println("Content-Type: application/json");
                   client.println("Connnection: close");
                   client.println();
                   client.print("{\"sensors\":{\"id\":\"" + server_id + "\",\"temp\":{\"raw\":\"");
                   client.print(tempReading);
                   client.print("\",\"volts\":\"");
                   client.print(tempVoltage);
                   client.print("\",\"celsius\":\"");
                   client.print(tempC);
                   client.print("\" },\"light\":\"");
                   client.print(photocellReading);
                   client.println("\"}}");
                   break;
               }
               if (c == '\n') {
                   currentLineIsBlank = true;
               }
               else if (c != '\r') {
                   currentLineIsBlank = false;
               }
           }
      }
      delay(1);
      client.stop();
  }
}
