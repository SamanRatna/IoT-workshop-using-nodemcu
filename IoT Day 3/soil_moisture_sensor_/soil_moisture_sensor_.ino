
int sensorPin = 0; 
int sensorValue;  

void setup() 
{
 Serial.begin(9600);
}

void loop() 
{
 sensorValue = analogRead(sensorPin); 
 Serial.println("Percentage Soil Moisture : ");
 int pct = map (sensorValue,0,1023,100,0);
 Serial.println(pct);
 delay(1000); 
}
