
#include <ESP8266WiFi.h>
#include <ThingSpeak.h>                                  // ThingSpeak Library




int sensorPin = 0; 
int sensorValue;  


// Set Network Parameters
const char* ssid     = "KIAS";                        // WiFi Name
const char* password = "PaperDevice##895";                    // WiFi password

// ThingSpeak information
char thingSpeakAddress[] = "api.thingspeak.com";
unsigned long channelID = 907724;                         // ChannelID defined in ThingSpeak profile
char* readAPIKey = "Q82T1D26HULMQ1QM";                    // API key to read data
char* writeAPIKey = "YXO0TQ1J45ON2QBU";                   // API key to write data

unsigned int dataFieldOne = 1;                            // Field to write pulse sensor data




WiFiClient client;                                        // Create client object




//---------------------------------------------------------------------------------------------------------------------------------

  
void setup() {
  Serial.begin(9600);

  WiFi.begin( ssid, password );
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);
        Serial.println("Connecting to WiFi");
    }

    Serial.println( "Connected" );
    ThingSpeak.begin( client );
}

void loop()
{
  sensorValue = analogRead(sensorPin); 
 Serial.println("Percentage Soil Moisture : ");
 int pct = map (sensorValue,0,1023,100,0);
 Serial.println(pct);
 
  ThingSpeak.setField(dataFieldOne , pct );                      // Write sensor data to Thingspeak
  ThingSpeak.writeFields( channelID, writeAPIKey );

  delay(1000); 
}
