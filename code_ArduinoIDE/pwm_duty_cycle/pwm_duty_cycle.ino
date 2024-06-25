int led = 9;
int br = 0;
int vol = 5;

void setup() {
  pinMode(led, OUTPUT);
}

void loop() {
  analogWrite(led, br);

  br = br + vol;

  if (br <= 0 || br >= 255) {
    vol = -vol;
  }

  delay(100);
}