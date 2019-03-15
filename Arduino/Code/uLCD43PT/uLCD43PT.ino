#include <genieArduino.h>

Genie genie;
#define RESETLINE 4

#include <math.h>

const int B = 4275;               // B value of the thermistor
const int R0 = 100000;            // R0 = 100k
const int pinTempSensor = A0;     // Grove - Temperature Sensor connect to A0


void setup()
{ 
  Serial.begin(9600);  
  genie.Begin(Serial);  

  pinMode(RESETLINE, OUTPUT);  
  digitalWrite(RESETLINE, 1);  
  delay(100);
  digitalWrite(RESETLINE, 0);
  delay (100);
  
  genie.WriteContrast(15); 
  genie.WriteObject(GENIE_OBJ_LED_DIGITS, 1, 10);
}


void loop()
{
  int a = analogRead(pinTempSensor);
  float R = 1023.0/a-1.0;
  R = R0*R;
  float temperatures = 1.0/(log(R/R0)/B+1/298.15)-273.15;
  int temperatures_dec = temperatures;
  int temperatures_flot = temperatures*100 - temperatures_dec*100;
//  Serial.print("temperature = ");
//  Serial.println(temperatures);
//  Serial.print("temperature = ");
//  Serial.println(temperatures_dec);
//  Serial.print("temperature = ");
//  Serial.println(temperatures_flot);
  
  genie.WriteObject(GENIE_OBJ_LED_DIGITS, 0, temperatures_dec); //on affiche la température ambiante captée
  delay(100);
  genie.WriteObject(GENIE_OBJ_LED_DIGITS, 1, temperatures_flot); //on affiche la température ambiante captée
}


