int led = 5;
int pot = A0;

void setup()
{ 
  Serial.begin(115200);
  pinMode(pot, INPUT); 
  pinMode(led, OUTPUT);
}

void loop()
{
  int potencia = analogRead(A0);
  Serial.println(potencia);
  // potencia = 1023 - potencia;
  analogWrite(led, potencia);
}
