// Another new and improved formula for button presses--with simple debouncing!

const int LED = 13;    
const int BUTTON = 3;  
int val = 0;     
int old_val = 0; 
int state = 0;  

void setup() {
  pinMode(LED, OUTPUT);  
  pinMode(BUTTON, INPUT); 
}

void loop(){
 val = digitalRead(BUTTON); 
 // check if there was a transition
 if ((val == HIGH) && (old_val == LOW)){
   state = 1 - state;
   delay(10);
 }

 old_val = val; // val is now old, let's store it

 if (state == 1) {
   digitalWrite(LED, HIGH); // turn LED ON
 } else {
   digitalWrite(LED, LOW);
 }
}
