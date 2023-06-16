#include <RCSwitch.h>
#define ID 33
RCSwitch mySwitch = RCSwitch();

void setup() {
  Serial.begin(9600);
  // Transmitter is connected to Arduino Pin #0
  mySwitch.enableTransmit(0);
  pinMode(LED_BUILTIN, OUTPUT);
  // Optional set protocol (default is 1, will work for most outlets)
  // mySwitch.setProtocol(2);
  // Optional set number of transmission repetitions.
  // mySwitch.setRepeatTransmit(15);
  // Optional set pulse length.
  // mySwitch.setPulseLength(320);
}

void loop() {
  /* Same switch as above, but using decimal code */

  digitalWrite(LED_BUILTIN, LOW);
  delay(1000);                      // Wait for a second
  digitalWrite(LED_BUILTIN, HIGH);  // Turn the LED off by making the voltage HIGH
  delay(2000);                      // Wait for two seconds (to demonstrate the active low LED)
  mySwitch.send(ID, 24);
  Serial.println("sent!");

  delay(2000);
}