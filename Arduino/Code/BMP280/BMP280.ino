#include "Seeed_BMP280.h"
#include <Wire.h>

BMP280 bmp280;

void setup()
{
  Serial.begin(9600);
  bmp280.init();
}

void loop()
{

  float pressure=bmp280.getPressure();
  float temp=bmp280.getTemperature();
  float altitude=bmp280.calcAltitude(pressure);
  
  Serial.print("Temp: ");
  Serial.print(temp);
  Serial.println("C");
  
  Serial.print("Pressure: ");
  Serial.print(pressure);
  Serial.println("Pa");
  
  Serial.print("Altitude: ");
  Serial.print(altitude);
  Serial.println("m");
  
  Serial.println("\n");

  delay(1000);
}
