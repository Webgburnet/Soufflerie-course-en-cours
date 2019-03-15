/* sample for digital weight scale of hx711
 */

// Hx711.DOUT - pin #A2
// Hx711.SCK - pin #A3

#include <Hx711.h>
Hx711 scale(A2, A3);

float force=0;

void setup() {
  Serial.begin(9600);
}

void loop() {
  force=scale.getGram();
  Serial.print(force, 1);
  Serial.println(" g");
  delay(200);
}

