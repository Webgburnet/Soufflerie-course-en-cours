/* sample for digital weight scale of hx711
   library design: Weihong Guan (@aguegu)
   library host on
  https://github.com/aguegu/ardulibs/tree/3cdb78f3727d9682f7fd22156604fc1e4edd75d1/hx711
*/

// Hx711.DOUT - pin #A2
// Hx711.SCK - pin #A3
float Force;
#include <Hx711.h>
Hx711 scale(A2, A3);

void setup() {
  Serial.begin(9600);
}

void loop() {
  Force = scale.getGram(), 1;
  Force = Force*0.00981;
  Serial.print(Force);
  Serial.println(" N");
  delay(200);
}

