          int relay = 5;            // Pin D1 on NodeMCU
          
          void setup() {
          pinMode(relay,OUTPUT);
          Serial.begin(9600);
          
          }
          
          void loop() {
          digitalWrite(relay,HIGH);
          Serial.println("relay on");
          delay(2000);
          digitalWrite(relay,LOW);
          Serial.println("relay off");
          delay(2000);
          }
