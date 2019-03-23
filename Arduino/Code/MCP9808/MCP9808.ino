#include "Seeed_MCP9808.h"

MCP9808 capteur_MCP9808;

void setup()
{
    Serial.begin(9600);
    capteur_MCP9808.init();
    //La limite supérieure fixée est de 30 ° CC
    capteur_MCP9808.set_upper_limit(SET_UPPER_LIMIT_ADDR,0x01e0);
    delay(10);
    //La limite supérieure fixée est de 32 ° C
    capteur_MCP9808.set_critical_limit(SET_CRITICAL_LIMIT_ADDR,0x0200);
    delay(10);
    // Activer le bit d'alerte. Le bit d'alerte émet une valeur basse lorsque la valeur de température dépasse la limite. Sinon, elle reste élevée.
    capteur_MCP9808.set_config(SET_CONFIG_ADDR,0x0008);
    Serial.println("capteur_MCP9808 init!!");
}


void loop()
{
    float temp=0;
    // Obtenir la température, une valeur de type float.
    capteur_MCP9808.get_temp(&temp);
    Serial.print("temperature value is: ");
    Serial.println(temp);
    delay(1000);
}
