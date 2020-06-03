// Initialize your microcontroller pin number
int LED1 = 12;
int LED2 = 11;
int LED2 = 10;

// the setup function runs once 
// when you press reset or power the board
void setup() 
{
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
}


// the loop function runs over and over
void loop() {
  digitalWrite(LED1, HIGH);   // turn the LED on
  digitalWrite(LED2, LOW);   // turn the LED o
   digitalWrite(LED3, LOW);   // turn the LED o
  delay(1000);               // wait for a second
  digitalWrite(LED1, LOW);    // turn the LED off
  digitalWrite(LED2, HIGH);   // turn the LED o
  digitalWrite(LED3, HIGH);
  delay(1000);               // wait for a second
}
