#include  "Seeed_BMP280.h"// bibliothèque du capteur de Pression
#include  <Wire.h> // bibliothèque du capteur de Pression
#include <Keypad.h>//bibliothèque du keypad
#include <math.h> // bibliothèque pour les fonctions mathématiques
#include "Seeed_MCP9808.h"//bibliothèque du capteur de température
#include <Hx711.h> // bibliothèque du capteur de force
#include "SPI.h"
#include "Adafruit_GFX.h"
#include "Adafruit_ILI9341.h"

// For the Adafruit shield, these are the default.
#define TFT_DC 9
#define TFT_CS 10
#define  magnet  6 // la variable magnet est de type integer
#define  DOUT  A8
#define  DSCK  A9
#define  Keypad1  6
#define  Keypad2  7
#define  Keypad3  8
#define  Keypad4  9
#define  Keypad5  11
#define  Keypad6  12
#define  Keypad7  13

  Hx711 scale(DOUT, DSCK); // la capteur de force se branche en analogique sur les ports 2 et 3 
  Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC); // Use hardware SPI (on Uno, #13, #12, #11) and the above for CS/DC
  BMP280  bmp280 ; // nom du capteur 
  MCP9808  sensor; // nom du capteur 



const byte ROWS = 4; //4 lignes
const byte COLS = 3; //3 colones
char keys[ROWS][COLS] = {   // description de la matrice
{'1','2','3'},
{'4','5','6'},
{'7','8','9'},
{'*','0','#'}
};
byte rowPins[ROWS] = {Keypad5, Keypad4, Keypad2, Keypad1};   //definiton des broches pour les lignes
byte colPins[COLS] = {Keypad3, Keypad7, Keypad6};     //definiton des broches pour les colones
Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS ); //initialisation de la matrice

int entree_nombre=0; //la variable entree_nombre est de type integer
int Tab[255]; //la variable tableau est de type integer
int i=0; // la variable i est de type integer
int j=0; // la variable j est de type integer
int k=0; //la variable k est de type integer
int Surface=0; // la variable Surface est de type integer

float Cx=0; // la variable Cx est de type float
float Fx=0; // la variable Fx est de type float

unsigned long temps=0; // la variable temps est de typoe long
unsigned long start=0 ;

int a = 0; // la variable a est de type integer
int n = 0; // la variable n est de type integer
float v = 0; // la variable v est de type integer 
int S =0;

float Force=0; // Force est déclaré comme étant un float


float const R=8.3144621; // R est déclaré comme étant une variable constante de type float
float const M_air=0.02896; // M est déclaré comme étant une variable constante de type float
float const K=273.15;

  void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600); // ouvre le port de serie a 9600 bps
  tft.begin();
  
  if(!bmp280.init()){ // initialisation du capteur en I2C
  Serial.println("Device error!"); // afficher erreur de périphérique  
  }
    if(sensor.init()) // initialisation du capteur en I2C
    {
        Serial.println("sensor init failed!!"); // afficher sensor init failed 
    }

    temps = millis(); // la variable temps est en milliseconde 
    pinMode(magnet, INPUT);
}

void loop() {
  
  // récupère et imprime les données de pression atmosphérique 
  float pressure = bmp280.getPressure();
  int pressure_dec = pressure; // on déclare pressure_dec comme étant la valeur presure entière 

    float temp; // on déclare temp en tant que float 
    float temp_K; // on déclare temp_K en tant que float
    sensor.get_temp(&temp);  //Obtenir la temperature, une valeur de type float
    temp_K=temp + K; // on convertie la valeur de la température en Kelvin

   float rho = (pressure*M_air)/(R*temp_K); // La valeur de rho est de type float et est égale à la pression multipliée par la masse molaire de l'air divisé par la constante R qui est multipliée par la température 
 
   Force = scale.getGram(); //scale.getValue();//scale.getGram();//, 1; //utilisation de la fonction scale.getGram() pour obtenir la valeur de la masse
   Force = Force*0.00981; // La Force est égale a la force multipliée par 0.00981 
   Fx = Force; // on dit que Fx est égale a la force
  

    if (digitalRead(magnet) == HIGH && a == 1){ //si detection de l'aimant
      n++;//nombre de révolution +1
      Serial.print("n:");
      Serial.println(n);
      a = 0 ;                        //enclanchement d'une vraiable pour évité que l'aimant active deux fois le capteur lors d'une meme revoltion
    }
     if (digitalRead(magnet) == LOW )
     {// sécurité qui interdit la prise de valeur des revolutions tant que l'aimant reste dectecté
          a = 1; //reprise de la prise de donné
          Serial.print("n:");
          Serial.println(n);
        }
   
    if ((millis()- temps) >= 1000){   // a chaque fois que le chono arrive au bout d'une seconde il envoie la vitesse angulaire
 
      v = n*2*3.14; //vitesse angulaire = nombre de révolution*2pi
      Serial.print(v); // afficher la valeur de v
      Serial.println("rad/s"); // afficher rad/s 
      temps = millis(); // reinitialisation du chrono
      n=0;
  
    
//      float vit_dec=v; // on déclare vit dec comme étant une variable de type float
//      
//   Cx = Fx/(0.5*Surface*rho_dec*(v*v)); // formule pour déterminer Cx
//   int Cx_dec=Cx; // on déclare la variable Cx_dec comme étant égale a Cx
//   Cx_flot=Cx*100-Cx_dec*100; // Cx_flot est la valeur decimale
//   
//   Serial.print("Pression : "); // afficher pression 
//   Serial.println(pressure); // afficher la valeur de pressure  
//   Serial.print("Temp C : "); // afficher Temp C:
//   Serial.println(temp); // afficher la valeur de temp 
//   Serial.print("Temp K : "); // afficher Temp K:
//   Serial.println(temp_K); // afficher la valeur de temp_K 
//   Serial.print("rho : "); // afficher rho: 
//   Serial.println(rho); // afficher la valeur de rho
   Serial.print(Force); // afficher la valeur de force  
   Serial.println(" N");// afficher N:
//   Serial.print("Surface:");
//   Serial.println(Surface);
//   Serial.println();
   }
   
   if ((millis() - start)>10000)
   {
   tft.setRotation(0);
   tft.setCursor(0, 0);
   tft.fillScreen(ILI9341_BLACK);
   tft.setTextSize(3);
   tft.println("Info projet"); 
   tft.setTextSize(3);
   tft.print(":rho"); 
   tft.println(rho) ; tft.println(":rho"); 
   tft.setTextSize(3);
   tft.print(Force) ; tft.setTextSize(3); tft.println(":F"); 
   tft.setTextSize(3);
   tft.print(v) ; tft.setTextSize(3); tft.println(":v"); 
   tft.setTextSize(3);
   tft.print(Surface) ; tft.setTextSize(3); tft.println(":S"); 
   start = millis();
  }
}
