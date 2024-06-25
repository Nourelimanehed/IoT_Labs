#define PUSHBUTTON 5 // Pushbutton component on pin 5

bool buttonPressed = false; // Flag to indicate button press
int  buttonState=0;
void setup() {
  Serial.begin(9600); // Initialize communication with the PC
  pinMode(PUSHBUTTON, INPUT);
}

void loop() {
  buttonState = digitalRead(PUSHBUTTON);
  if (buttonState != buttonPressed) {
    if (buttonState == 1 )
    Serial.write("Button pressed");
    buttonPressed = 1 - buttonPressed;
  }
  // Your other main loop code here 
}
