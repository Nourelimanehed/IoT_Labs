// C++ code
//
int force = 0;
void setup()
{
  pinMode(A0, INPUT);
  pinMode(3, OUTPUT);
}

void loop()
{
  force = analogRead(A0);
  analogWrite(3, force);
  delay(10); // Delay a little bit to improve simulation performance
}