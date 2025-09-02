#include <SoftwareSerial.h>

SoftwareSerial SIM900(10, 11); // RX, TX

const int gasSensorPin = A0;       // MQ-7 sensor
const int gasThreshold = 300;

bool alertSent = false;
bool callDone = false;
unsigned long alertTime = 0;
unsigned long callDelay = 10000;   // Wait 10 seconds after SMS
unsigned long callDuration = 40000; // Ring 40 seconds

void setup() {
  Serial.begin(9600);
  SIM900.begin(9600);
  pinMode(gasSensorPin, INPUT);

  Serial.println("Initializing SIM900...");

  SIM900.println("AT");
  delay(1000);

  SIM900.println("AT+CMGF=1"); // SMS Text mode
  delay(1000);

  Serial.println("Ready.");
}

void sendSMS(const char* number) {
  SIM900.print("AT+CMGS=\"");
  SIM900.print(number);
  SIM900.println("\"");
  delay(1000);
  SIM900.println("There is a gas leak detect in your house, Please check immediatly !!!");
  delay(500);
  SIM900.write(26); // Ctrl+Z
  Serial.print("SMS Sent to ");
  Serial.println(number);
  delay(5000); // Wait to ensure SMS sent
}

void makeCall(const char* number) {
  SIM900.print("ATD");
  SIM900.print(number);
  SIM900.println(";");
  Serial.print("Calling ");
  Serial.println(number);
  delay(callDuration); // Ring for 40 seconds
  SIM900.println("ATH");
  Serial.println("Call ended.");
  delay(3000); // Small pause before next call
}

void loop() {
  int gasValue = analogRead(gasSensorPin);
  Serial.print("Gas Sensor Value: ");
  Serial.println(gasValue);

  if (gasValue > gasThreshold && !alertSent) {
    Serial.println("Gas Leakage Detected!");

    sendSMS("+94703757210");
    sendSMS("+94714114003");

    alertSent = true;
    alertTime = millis();
  }

  if (alertSent && !callDone && millis() - alertTime >= callDelay) {
    makeCall("+94703757210");
    makeCall("+94714114003");

    // Set to true to avoid repeating call
    callDone = true;
  }

  delay(1000); // Slight delay between loops
}
