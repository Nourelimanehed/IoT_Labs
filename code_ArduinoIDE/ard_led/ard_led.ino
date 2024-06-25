
int pin = 13;
void setup()
{
  pinMode(pin, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  Serial.println("LED is ON");
  digitalWrite(pin, HIGH);
  delay(1000);
  Serial.println("LED is OFF");
  digitalWrite(pin, LOW);
  delay(1000);
}
