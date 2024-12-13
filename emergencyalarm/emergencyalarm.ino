#include <Arduino.h>
#include <SoftwareSerial.h>

SoftwareSerial mySerial(10, 11);

boolean messagesent = false;
#define PIR_PIN 3
#define BUZZER_PIN 2
#define MIC_PIN A3

int pirState = LOW;
int micState = LOW;
const char* phoneNumber = "+639062254061"; // Enter the phone number you want to alert

void setup() {
  mySerial.begin(9600);
  Serial.begin(9600);
  pinMode(PIR_PIN, INPUT);
  pinMode(MIC_PIN, INPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  Serial.println("ATE0");
  delay(1000);
  mySerial.println("AT+CMGF=1\r"); // Set GSM to SMS mode
  delay(100);
  
  // Calibration time of 2 seconds
  Serial.println("Calibrating...");
  delay(2000);
  Serial.println("Calibration done.");
}

void loop() {
  pirState = digitalRead(PIR_PIN);
  micState = digitalRead(MIC_PIN);

  if (pirState == HIGH || micState == HIGH) {
    Serial.println("Emergency! Someone needs help in room 202");
    Serial.print("PIR State: ");
    Serial.println(pirState);
    Serial.print("MIC State: ");
    Serial.println(micState);
    sendSMS(); // Send alert SMS
    digitalWrite(BUZZER_PIN, HIGH);
    delay(3000);
  } else {
    digitalWrite(BUZZER_PIN, LOW);
  }
}

void sendSMS() {
  Serial.println("Sending SMS...");
  mySerial.println("AT+CMGF=1"); // Set GSM to SMS mode
  delay(100);
  mySerial.print("AT+CMGS=\"");
  mySerial.print(phoneNumber);
  mySerial.println("\"");
  delay(100);
  mySerial.println("Emergency! Someone needs help in room 102"); // The SMS text
  delay(100);
  mySerial.println((char)26); // ASCII code of CTRL+Z to send the SMS
  delay(100);
  Serial.println("SMS sent.");
}
