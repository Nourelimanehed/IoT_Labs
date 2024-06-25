void setup() {
  // Set the PWM pin
  pinMode(9, OUTPUT);
}

void loop() {
  // Set the PWM frequency
  analogWriteFrequency(9, 100);

  // Set the PWM duty cycle
  analogWrite(9, 50); // 50% duty cycle
  delay(100); // Wait for 100ms

  analogWrite(9, 10); // 10% duty cycle
  delay(100); // Wait for 100ms
}
