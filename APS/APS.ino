#include <SPI.h>
#include <MFRC522.h>
#include <ESP32Servo.h>

#define SS_PIN 21
#define RST_PIN 22
#define SENSORMASUK 14
#define LEDMASUKR 15
#define LEDMASUKG 2
#define Parkir1 26
#define LEDP1 17
#define Parkir2 25
#define LEDP2 16
#define pinServos 32

int isObstacle = HIGH;
int stateParkir1 = HIGH;
int stateParkir2 = HIGH;
bool isFull = false;

 
MFRC522 rfid(SS_PIN, RST_PIN); // Instance of the class

MFRC522::MIFARE_Key key; 

// Init array that will store new NUID 
byte nuidPICC[4];

Servo myservo;

void setup() { 
  Serial.begin(9600);
  SPI.begin(); // Init SPI bus
  rfid.PCD_Init(); // Init MFRC522 
  delay(4000);

  myservo.attach(pinServos);
  myservo.write(0);

  pinMode(SENSORMASUK, INPUT);
  pinMode(Parkir1, INPUT);
  pinMode(Parkir2, INPUT);
  pinMode(SENSORMASUK, INPUT);
  pinMode(LEDMASUKG, OUTPUT);
  pinMode(LEDMASUKR, OUTPUT);
  digitalWrite(LEDMASUKG, LOW);
  digitalWrite(LEDMASUKR, LOW);
  pinMode(LEDP1, OUTPUT);
  pinMode(LEDP2, OUTPUT);
  digitalWrite(LEDP1, LOW);
  digitalWrite(LEDP2, LOW);


  for (byte i = 0; i < 6; i++) {
    key.keyByte[i] = 0xFF;
  }

  Serial.println(F("This code scan the MIFARE Classsic NUID."));
  Serial.print(F("Using the following key:"));
  printHex(key.keyByte, MFRC522::MF_KEY_SIZE);
}

bool going = false;

void loop() {

  stateParkir1 = digitalRead(Parkir1);
  stateParkir2 = digitalRead(Parkir2);

  if(stateParkir1 == LOW && stateParkir2 == LOW){
    isFull = true;
  }
  
  else{
    isFull = false;
  }

  if(going){
    return;
  }

  if(stateParkir1 == LOW){
    digitalWrite(LEDP1, HIGH);
  }
  else{
    digitalWrite(LEDP1, LOW);
  }

  if(stateParkir2 == LOW){
    digitalWrite(LEDP2, HIGH);
  }
  else{
    digitalWrite(LEDP2, LOW);
  }

  if(isFull){
    digitalWrite(LEDMASUKR, HIGH);
    return;
  }
  else{
    digitalWrite(LEDMASUKR, LOW);
  }

  // Reset the loop if no new card present on the sensor/reader. This saves the entire process when idle.
  if ( ! rfid.PICC_IsNewCardPresent())
    return;

  // Verify if the NUID has been readed
  if ( ! rfid.PICC_ReadCardSerial())
    return;

  going = true;
  digitalWrite(LEDMASUKR, HIGH);
  delay(1500);
  Serial.print(F("PICC type: "));
  MFRC522::PICC_Type piccType = rfid.PICC_GetType(rfid.uid.sak);
  Serial.println(rfid.PICC_GetTypeName(piccType));

  // Check is the PICC of Classic MIFARE type
  if (piccType != MFRC522::PICC_TYPE_MIFARE_MINI &&  
    piccType != MFRC522::PICC_TYPE_MIFARE_1K &&
    piccType != MFRC522::PICC_TYPE_MIFARE_4K) {
    Serial.println(F("Your tag is not of type MIFARE Classic."));
    return;
  }

  if (rfid.uid.uidByte[0] != nuidPICC[0] || 
    rfid.uid.uidByte[1] != nuidPICC[1] || 
    rfid.uid.uidByte[2] != nuidPICC[2] || 
    rfid.uid.uidByte[3] != nuidPICC[3] ) {
    Serial.println(F("A new card has been detected."));

    // Store NUID into nuidPICC array
    for (byte i = 0; i < 4; i++) {
      nuidPICC[i] = rfid.uid.uidByte[i];
    }
   
    Serial.println(F("The NUID tag is:"));
    Serial.print(F("In hex: "));
    printHex(rfid.uid.uidByte, rfid.uid.size);
    Serial.println();
    Serial.print(F("In dec: "));
    printDec(rfid.uid.uidByte, rfid.uid.size);
    Serial.println();
  }

  else {
    Serial.println(F("Card read previously."));
  }

  if(going){
    myservo.write(90);
    Serial.print("Waiting Car passing");
    while(1){
      isObstacle = digitalRead(SENSORMASUK);
      if (isObstacle == HIGH) {
        Serial.print("waiting...\n");
        digitalWrite(LEDMASUKR, LOW);
        digitalWrite(LEDMASUKG, HIGH);
      }
      else{
        digitalWrite(LEDMASUKR, HIGH);
        digitalWrite(LEDMASUKG, LOW);

        delay(3000);
        
        going=false;
        Serial.print("anjay lewat");
        break;
      }
    }
    myservo.write(0);
    delay(1500);
    digitalWrite(LEDMASUKR, LOW);
  }

  // Halt PICC
  rfid.PICC_HaltA();

  // Stop encryption on PCD
  rfid.PCD_StopCrypto1();
}


/**
 * Helper routine to dump a byte array as hex values to Serial. 
 */
void printHex(byte *buffer, byte bufferSize) {
  for (byte i = 0; i < bufferSize; i++) {
    Serial.print(buffer[i] < 0x10 ? " 0" : " ");
    Serial.print(buffer[i], HEX);
  }
}

/**
 * Helper routine to dump a byte array as dec values to Serial.
 */
void printDec(byte *buffer, byte bufferSize) {
  for (byte i = 0; i < bufferSize; i++) {
    Serial.print(' ');
    Serial.print(buffer[i], DEC);
  }
}
