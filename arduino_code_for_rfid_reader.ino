/*
 * 
 * All the resources for this project: https://www.hackster.io/Aritro
 * Modified by Aritro Mukherjee
 * 
 * 
 */
#include <SPI.h>
#include <MFRC522.h>

#define SS_PIN 10
#define RST_PIN 9
MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522 instance.

int RedLedPin = 8;
int GreenLedPin = 7;
int BlueLedPin = 6;


void setup() 
{
  pinMode(RedLedPin, OUTPUT);
  pinMode(GreenLedPin, OUTPUT);
  pinMode(BlueLedPin, OUTPUT);
  
  Serial.begin(9600);   // Initiate a serial communication
  SPI.begin();      // Initiate  SPI bus
  mfrc522.PCD_Init();   // Initiate MFRC522
  Serial.println("tap your card or tag to the reader...");
  Serial.println();
  digitalWrite(BlueLedPin, HIGH);

}
void loop() 
{
  // Look for new cards
  if ( ! mfrc522.PICC_IsNewCardPresent()) 
  {
    return;
  }
  // Select one of the cards
  if ( ! mfrc522.PICC_ReadCardSerial()) 
  {
    return;
  }
  //Show UID on serial monitor
  Serial.print("UID tag :");
  String content= "";
  byte letter;
  for (byte i = 0; i < mfrc522.uid.size; i++) 
  {
     Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
     Serial.print(mfrc522.uid.uidByte[i], HEX);
     content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
     content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  Serial.println();
  Serial.print("Message : ");
  content.toUpperCase();
  if (content.substring(1) == "63 6E A0 59") //change here the UID of the card/cards that you want to give access
  {
    Serial.println("Authorized access");
    Serial.println();
    digitalWrite(BlueLedPin, LOW);
    digitalWrite(GreenLedPin, HIGH);
    tone(2, 440, 40);
    delay(3000);
    digitalWrite(GreenLedPin, LOW);
    digitalWrite(BlueLedPin, HIGH);
  }
 
 else   {
    Serial.println(" Access denied");
    Serial.println();
    digitalWrite(BlueLedPin, LOW);
    digitalWrite(RedLedPin, HIGH);
    tone(2, 200, 40);
    delay(60);
    tone(2, 200, 40);
    delay(60);
    tone(2, 200, 40);
    delay(3000);
    digitalWrite(RedLedPin, LOW);
    digitalWrite(BlueLedPin, HIGH);
  }
} 
