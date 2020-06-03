#include <ESP8266WiFi.h>
#include <ThingSpeak.h>                                   // ThingSpeak Library
#include <LiquidCrystal.h>                                // include the library code:

//------------------------ NETWORK PARAMETERS ----------------------------------------------------------------

// Set Network Parameters
const char* ssid     = "mamata112";                        // WiFi Name
const char* password = "CLB3526073";                        // WiFi password

//-------------------------- THINGSPEAK INFORMATION --------------------------------------------------------

char thingSpeakAddress[] = "api.thingspeak.com";
unsigned long channelID = 920513;                         // ChannelID defined in ThingSpeak profile
char* readAPIKey = "ANU4DM79M8932O6N";                    // API key to read data
char* writeAPIKey = "3SRDU8EMKWES4D5A";                   // API key to write data

unsigned int dataFieldOne = 1;                            // Field to write soil moisture data
unsigned int dataFieldTwo = 2;                            // Field to write humidity data
unsigned int dataFieldThree = 3;                          // Field to write temperature data

WiFiClient client;                                        // Create client object

//-------------------- INITIALIZE LCD DISPLAY-----------------------------------------------------------

const int RS = D2, EN = D3, d4 = D5, d5 = D6, d6 = D7, d7 = D8;   
LiquidCrystal lcd(RS, EN, d4, d5, d6, d7);

//---------------------- INITIALIZE DHT11 SENSOR (TEMPERATURE AND PRESSURE) ------------------------------------------------

#include "DHT.h"
#define DHTPIN 2                                          // D4 pin in NodeMCU
#define DHTTYPE DHT11                                     

DHT dht(DHTPIN, DHTTYPE);

//------------------------ INITIALIZE SOIL MOISTURE SENSOR -----------------------------------------------------------------

int sensorPin = 0;                                        // A0 pin in NodeMCU
int sensorValue;  

//------------------------ INITIALIZE RELAY FOR WATER PUMP ---------------------------------------------------------------
int pump = 5;                                             // D1 pin in NodeMCU


//---------------------------------------------------------------------------------------------------------------------------
//                                                 SETUP
//---------------------------------------------------------------------------------------------------------------------------



void setup() 
{
  Serial.begin(9600);
  dht.begin();                                             // Prepare DHT11 for reading
  
  pinMode(pump, OUTPUT);

  lcd.begin(16, 2);                                        // set up the LCD's number of columns and rows:
  lcd.clear();

  WiFi.begin( ssid, password );
  while (WiFi.status() != WL_CONNECTED)
  {
      delay(500);
      Serial.println("Connecting to WiFi");
  }

  Serial.println( "Connected" );
  ThingSpeak.begin( client );
}

//-----------------------------------------------------------------------------------------------------------
//                                                     LOOP
//-----------------------------------------------------------------------------------------------------------


void loop() 
{
  
//--------------- FOR DHT11 READING ------------------------------------------------------------------

  float h = 0;
  float t = 0;
  float f = 0;
  
  h = dht.readHumidity();
  t = dht.readTemperature();
  f = dht.readTemperature(true);
  if (isnan(h) || isnan(t) || isnan(f)) 
  {
    Serial.println(F("Failed to read from DHT sensor!"));
    Serial.println(h);
    Serial.println(t);
    Serial.println(f);
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
 int moisture_pct = map (sensorValue,0,1023,100,0);
 Serial.println(moisture_pct);

//----------------------- SHOW DATA ON LCD ----------------------------------------------------------------------------
  lcd.setCursor(0,0); // Sets the cursor to col 0 and row 0
  lcd.print("Soil:"); // Prints Sensor Val: to LCD
  lcd.print(moisture_pct); // Prints value on Potpin1 to LCD

  lcd.setCursor(8,0);
  lcd.print("Tmp:");
  lcd.print(hic);
  lcd.print("°C");
  
  lcd.setCursor(0,1);
  lcd.print("Humidity:");
  lcd.print(h);

  

//------------------------ TRIGGER FOR WATER PUMP ----------------------------------------------------------------

  if (moisture_pct <= 50)
  {
    Serial.println("Moisture content is less than threshold, turning on water pump...");
    delay(1000);
    digitalWrite(pump,HIGH);
    delay(1000);
  }
  else
  {
    Serial.println("Moisture content is enough. No need to water the plant.");
    digitalWrite(pump,LOW);
    delay(1000);
  }

//------------------------ SEND THINGSPEAK DATA ---------------------------------------------------------------

  ThingSpeak.setField(dataFieldOne , moisture_pct );               // Write soil moisture sensor data to Thingspeak
  ThingSpeak.setField(dataFieldTwo , h );                          // Write humidity sensor data to Thingspeak
  ThingSpeak.setField(dataFieldThree , hic );                      // Write temperature sensor data to Thingspeak
  ThingSpeak.writeFields( channelID, writeAPIKey );
  
  delay(500); 
 
}
