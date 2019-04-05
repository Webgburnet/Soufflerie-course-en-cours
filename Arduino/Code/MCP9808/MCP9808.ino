#include "Seeed_MCP9808.h" // bibliothèque du capteur de température 


MCP9808  sensor; // nom du capteur 

void setup() {
  // put your setup code here, to run once:
Serial.begin(115200); // vitesse de transmission de 115200 bauds 
    if(sensor.init()) // initialisation du capteur en I2C 
    {
        Serial.println("sensor init failed!!"); // afficher sensor init failed 
    }
    sensor.set_upper_limit(SET_UPPER_LIMIT_ADDR,0x01e0); //la limite est de 30°C
    delay(10); // attendre 10 ms 
    sensor.set_critical_limit(SET_CRITICAL_LIMIT_ADDR,0x0200); //La limite est de 32°C
    delay(10); // attendre 10 ms 
    sensor.set_config(SET_CONFIG_ADDR,0x0008); //Activer le bit d'alerte. Le bit d'alerte émet une valeur basse lorsque la valeur de température dépasse la limite. Sinon, elle reste élevée

    Serial.println("sensor init!!"); // on affiche capteur initialisé!! 
}

void loop() {
    // put your main code here, to run repeatedly:
    float temp=0; // on déclare temp comme étant une valeur de type float 
    sensor.get_temp(&temp);//Obtenir la temperature, une valeur de type float
    Serial.print("la temperature est de : "); // afficher la température est de 
    Serial.println(temp); // afficher la valeur de temp
    delay(1000); // attendre 1000 ms 
}
