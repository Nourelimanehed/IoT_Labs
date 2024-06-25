void setup() {
  pinMode(10, INPUT_PULLUP);
  // Enable the internal pull-up resistor
  Serial.begin(9600);
  // Start serial communication at 9600 baud
}

void loop() {
  int buttonState = digitalRead(10);
  // Read the button state

  if (buttonState == LOW) {
    // Button is pressed
    Serial.println('1');
    // Send a message to the second Arduino
  } else {
    // Button is released
    Serial.println('0');
    // Send a message to the second Arduino
  }
}
