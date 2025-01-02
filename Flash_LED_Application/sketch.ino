#define led 13 // LED connected to digital pin 13

void setup() {
  pinMode(led, OUTPUT); // sets the digital pin as output
}

void loop() {
  digitalWrite(led, HIGH); // sets the LED on
  delay(1000); // waits for a second
  digitalWrite(led, LOW); // sets the LED off
  delay(1000); // waits for a second
}