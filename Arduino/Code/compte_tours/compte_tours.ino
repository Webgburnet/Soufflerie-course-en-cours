#define magnet = 2;

long temps;
int a = 0;
int n;

void setup() {
  // put your setup code here, to run once:
    Serial.begin(9600);
    temps = millis();
}

void loop() {
  // put your main code here, to run repeatedly:
  
    if (digitalRead(magnet) == HIGH){
      n++;
      Serial.print("magnet HIGH : ");
      Serial.println(n);
      a = 0 ; 
      do {
        if (digitalRead(magnet) == LOW ){
          a = 1;
          Serial.print("magnet LOW : ");
          Serial.println(n);
        }
      }
      while (a == 0);
    }
        
    if ((millis()- temps) >= 1000){
      Serial.print(n*2);
      Serial.println("rad/s");
      temps = millis();
      n=0;
    }
    
}
