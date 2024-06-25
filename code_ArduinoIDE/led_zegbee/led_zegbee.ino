char Signal;
const int LEDpin = 10; // Assign the LED pin number

void setup() {
  pinMode(LEDpin, OUTPUT); // Set the digital pin connected to the LED as output
  Serial.begin(9600); // Start serial communication at 9600 baud
}

void loop() {
  Signal = Serial.read(); // Read the incoming signal

  if (Signal == '1') {
    digitalWrite(LEDpin, HIGH); // Turn on the LED
  } else if (Signal == '0') {
    digitalWrite(LEDpin, LOW); // Turn off the LED
  }
}
