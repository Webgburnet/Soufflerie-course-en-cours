long temps;
int a = 0;
int n;
int magnet = 6;
void setup() {
  // put your setup code here, to run once:
    Serial.begin(9600);
    temps = millis(); //initilisation du chronometr
}

void loop() {
  // put your main code here, to run repeatedly:
  
    if (digitalRead(magnet) == HIGH && a == 1){
      n++; // nombre de révolution
      a = 0 ; 
    } 
     if (digitalRead(magnet) == LOW ){
          a = 1;
        }
 
    
        
    if ((millis()- temps) >= 1000){
      Serial.print(n);
      Serial.println(" tours");
      Serial.print(n*2*3.14);
      Serial.println(" rad/s");
      temps = millis();
      n=0;
    }
    
}
