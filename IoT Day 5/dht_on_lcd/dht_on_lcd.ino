// include the library code:
#include <LiquidCrystal.h>

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(7,8,9,10,11,12);

#include <dht11.h>
#define DHT11PIN 4

dht11 DHT11;

void setup()
{
  Serial.begin(9600);
  lcd.begin(16, 2);
  lcd.clear();
}

void loop()
{
  Serial.println();

  int chk = DHT11.read(DHT11PIN);

  Serial.print("Humidity (%): ");
  float humidity = ((float)DHT11.humidity, 2);
  Serial.println(humidity);

  Serial.print("Temperature (C): ");
  float temperature = ((float)DHT11.temperature, 2);
  Serial.println(temperature);

  lcd.setCursor(0,0); // Sets the cursor to col 0 and row 0
  lcd.print("Temperature: "); // Prints Sensor Val: to LCD
  lcd.print(temperature); // Prints value on Potpin1 to LCD

  lcd.setCursor(0,1); // Sets the cursor to col 0 and row 0
  lcd.print("Humidity: "); // Prints Sensor Val: to LCD
  lcd.print(humidity); // Prints value on Potpin1 to LCD
  
  delay(2000);

}
