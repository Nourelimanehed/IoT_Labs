// Define the pins for the light sensor and LED
const int lightSensorPin = A0; 
const int ledPin = 12;          
void setup() {
  pinMode(ledPin, OUTPUT);       
  Serial.begin(9600);          
}

void loop() {
  int lightValue = analogRead(lightSensorPin); 
  Serial.println(lightValue);


  int threshold = 30; 

  if (lightValue < threshold) {
    digitalWrite(ledPin, HIGH); // Turn on the LED
  } else {
    digitalWrite(ledPin, LOW);  // Turn off the LED
  }
}
