int relay = 5;            // Pin D1 on NodeMCU

int sensorPin = 0;        // Pin A0 on NodeMCU
int sensorValue;  

void setup() 
{
  pinMode(relay,OUTPUT);
  Serial.begin(9600);
}

void loop() 
{

sensorValue = analogRead(sensorPin); 
Serial.println("Percentage Soil Moisture : ");
int pct = map (sensorValue,0,1023,100,0);
Serial.println(pct);

if (pct <= 50)
{
  digitalWrite(relay,HIGH);
  Serial.println("relay on");
  delay(2000);
}
else
{
  digitalWrite(relay,LOW);
  Serial.println("relay off");
  delay(2000);
}


}
