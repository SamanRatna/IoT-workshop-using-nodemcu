// include the library code:
#include <LiquidCrystal.h>

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(7,8,9,10,11,12);

int sensorPin = 36; 
int sensorValue;  

void setup() 
{
  Serial.begin(9600);
  
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  lcd.clear();
}

void loop() 
{
  sensorValue = analogRead(sensorPin); 
  Serial.println("Percentage Soil Moisture : ");
  int pct = map (sensorValue,0,1023,100,0);
  Serial.println(pct);
  
  lcd.setCursor(0,0); // Sets the cursor to col 0 and row 0
  lcd.print("Soil Moisture: "); // Prints Sensor Val: to LCD
  lcd.print(pct); // Prints value on Potpin1 to LCD
  
  delay(1000); 
}
