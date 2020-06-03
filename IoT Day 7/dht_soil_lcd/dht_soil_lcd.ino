//-------------------- INITIALIZE LCD DISPLAY-----------------------------------------------------------
// include the library code:
#include <LiquidCrystal.h>

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(7,8,9,10,11,12);

//---------------------- INITIALIZE DHT11 SENSOR (TEMPERATURE AND PRESSURE) -------------------------------------------------------------------------
#include "DHT.h"

#define DHTPIN 2        // Digital pin connected to the DHT sensor
#define DHTTYPE DHT11   // DHT 11

DHT dht(DHTPIN, DHTTYPE);
//------------------------ INITIALIZE SOIL MOISTURE SENSOR ----------------------------------------------------------------------
int sensorPin = 36; 
int sensorValue;  
//------------------------------------------------------------------------------------------------






void setup() 
{
 Serial.begin(9600);
 dht.begin();         // Prepare DHT11 for reading

 // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  lcd.clear();
}




void loop() 
{
  
//--------------- FOR DHT11 READING ------------------------------------------------------------------

  float h = dht.readHumidity();
  float t = dht.readTemperature();
  float f = dht.readTemperature(true);
  if (isnan(h) || isnan(t) || isnan(f)) 
  {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }

  float hif = dht.computeHeatIndex(f, h);
  float hic = dht.computeHeatIndex(t, h, false);

  Serial.print(F("Humidity: "));
  Serial.print(h);
  Serial.print(F("%  Temperature: "));
  Serial.print(t);
  Serial.print(F("°C "));
  Serial.print(f);
  Serial.print(F("°F  Heat index: "));
  Serial.print(hic);
  Serial.print(F("°C "));
  Serial.print(hif);
  Serial.println(F("°F"));
  
//---------------------- FOR SOIL MOISTURE READING -------------------------------------------------

 sensorValue = analogRead(sensorPin); 
 Serial.println("Percentage Soil Moisture : ");
 int pct = map (sensorValue,0,1023,100,0);
 Serial.println(pct);

//----------------------- SHOW DATA ON LCD ----------------------------------------------------------------------------
  lcd.setCursor(0,0); // Sets the cursor to col 0 and row 0
  lcd.print("Soil: "); // Prints Sensor Val: to LCD
  lcd.print(pct); // Prints value on Potpin1 to LCD

  lcd.setCursor(0,1);
  lcd.print("Humid: ");
  lcd.print(h);

  lcd.setCursor(10,1);
  lcd.print("Temp: ");
  lcd.print(hic);
  lcd.print(F("°C "));
  


  
  delay(1000); 


 
}
