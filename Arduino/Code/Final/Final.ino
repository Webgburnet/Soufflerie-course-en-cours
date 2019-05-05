#include <SPI.h>
#include  <Wire.h>
#include <math.h> // bibliothèque pour les fonctions mathématiques
#include  "Seeed_BMP280.h"// bibliothèque du capteur de Pression
#include <Keypad.h>//bibliothèque du keypad
#include "Seeed_MCP9808.h"//bibliothèque du capteur de température
#include <Hx711.h> // bibliothèque du capteur de force
#include "Adafruit_GFX.h"
#include "Adafruit_ILI9341.h"

#define  magnet 6
#define TFT_DC 9
#define TFT_CS 10
#define  Keypad1 A0
#define  Keypad2 A1
#define  Keypad3 A2
#define  Keypad4 A3
#define  Keypad5 A5
#define  Keypad6 A6
#define  Keypad7 A7
#define Hx711_Dout A8
#define Hx711_Sck A9

float const R=8.3144621; // R est déclaré comme étant une variable constante de type float
float const M_air=0.02896; // M est déclaré comme étant une variable constante de type float
float const K=273.15; // K est déclaré comme étant une variable constante de type float

const byte ROWS = 4; //4 lignes
const byte COLS = 3; //3 colones

Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC);
BMP280  bmp280 ; // definition du nom du capteur 
MCP9808  sensor_temp; // definition du nom du capteur

Hx711 scale(Hx711_Dout, Hx711_Sck); // la capteur de force se branche en analogique sur les ports A8, A9
byte rowPins[ROWS] = {Keypad5, Keypad4, Keypad2, Keypad1};   //definiton des broches pour les lignes
byte colPins[COLS] = {Keypad3, Keypad7, Keypad6};     //definiton des broches pour les colones

unsigned long temps_serial=0; // la variable temps est de typoe long
unsigned long date_courante = 0;
unsigned long interval = 2000;

byte magnet_etat = 0; // Etat du capteur magnétique
unsigned long compte_tours = 0; // Compte le nombre de tours
float vitesse_ang = 0; // Vitesse Angulaire
float pressure = 0 ; // Pression atmosphérique en Pascal de type flotant
float temp=0; // Temperature en Celsius de type flotant
float temp_K=0; // Temperature en Kelvin de type flotant
float rho=0; //Masse Volumique de type flotant
float Force=0; // Force est déclaré comme étant un float
double Cx=0; // Coefficient de trainée Cx 

unsigned int entree_nombre=0; //la variable entree_nombre est de type integer
unsigned int Tab[255]; //la variable tableau est de type integer
unsigned int i=0; // la variable i est de type integer
unsigned int j=0; // la variable j est de type integer
unsigned int k=0; //la variable k est de type integer
unsigned long Surface=0; // la variable Surface est de type integer

unsigned int num_ecran=0;
boolean premier_ecran = false;
boolean deuxieme_ecran = false;
boolean troisieme_ecran = false;
boolean quatrieme_ecran = false;

char keys[ROWS][COLS] = {   // description de la matrice
{'1','2','3'},
{'4','5','6'},
{'7','8','9'},
{'*','0','#'}
};
char key ;
unsigned int save_key; //Nombre en ASCII
unsigned int dec_key; // Conversion ASCII en nombre de 0 à 9

Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS ); //initialisation de la matrice

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600); // ouvre le port de serie a 9600 bps
  tft.begin();
  
  pinMode(magnet, INPUT);
  
  if(!bmp280.init())
  { // initialisation du capteur en I2C
    Serial.println("Erreur peripherique BMP280 ! "); // afficher erreur de périphérique  
  }
  
  if(sensor_temp.init()) // initialisation du capteur en I2C
  {
      Serial.println("Erreur peripherique MCP9808 ! "); // afficher sensor init failed 
  }
  
  temps_serial = millis(); // la variable temps est en milliseconde 

}

void loop() {
  if(Surface!=0)
  {
    // récupère la pression atmosphérique 
    pressure = bmp280.getPressure();
  
    //récupère et convertie la temperature en °C et K
    sensor_temp.get_temp(&temp);  //Obtenir la temperature, une valeur de type float
    temp_K=temp + K; // on convertie la valeur de la température en Kelvin
  
    // Calcul de la masse volumique de l'air
    rho = (pressure*M_air)/(R*temp_K);
    
    Force = scale.getGram(); //utilisation de la fonction scale.getGram() pour obtenir la valeur de la masse
    Force = Force*0.00981;// La Force est égale a la force multipliée par 0.00981 
    Force =  abs(Force);
  
    //Compte Tours
    if (digitalRead(magnet) == HIGH && magnet_etat == 1)
    {
      compte_tours++;//nombre de révolution +1
      //      Serial.print("compte_tours:");
      //      Serial.println(compte_tours);
      //enclanchement d'une vraiable pour évité que l'aimant active deux fois le capteur lors d'une meme revoltion
      magnet_etat = 0 ;                        
    }
    
    // sécurité qui interdit la prise de valeur des revolutions tant que l'aimant reste dectecté
     if (digitalRead(magnet) == LOW )
     {
          magnet_etat = 1; //reprise de la prise de donné
    //          Serial.print("compte_tours:");
    //          Serial.println(compte_tours);
     }    
    // a chaque fois que le chono arrive au bout d'une seconde il envoie les messages
    if ((millis()- temps_serial) >= 1000)
    {   
  
      vitesse_ang = compte_tours*2*3.14; //vitesse angulaire = nombre de révolution*2pi
      //Cx = Fx/(0.5*Surface*rho*(v*v)); // formule pour déterminer Cx
      Cx = Force/(0.5*(Surface*pow(10,-6))*rho*pow(vitesse_ang,2));
  
      Serial.print("Nombre de tours : ");
      Serial.print(compte_tours); // afficher la valeur de compte tours
      Serial.println(" tr/s"); // afficher tr/s 
    
      Serial.print("Vitesse Angulaire : ");
      Serial.print(vitesse_ang); // afficher la valeur de v
      Serial.println(" rad/s"); // afficher rad/s 
    
      Serial.print("Pression : "); // afficher pression 
      Serial.print(pressure); // afficher la valeur de pressure
      Serial.println(" Pa");
       
      Serial.print("Temp C : "); // afficher Temp C:
      Serial.print(temp); // afficher la valeur de temp
      Serial.println(" °C");
      
      Serial.print("Temp K : "); // afficher Temp K:
      Serial.print(temp_K); // afficher la valeur de temp_K
      Serial.println(" K");
      
      Serial.print("rho : "); // afficher rho: 
      Serial.print(rho); // afficher la valeur de rho
      Serial.println(" kg/m^3");
      
      Serial.print("Force : ");
      Serial.print(Force); // afficher la valeur de force  
      Serial.println(" N");// afficher N:
      
      Serial.print("Surface : ");
      Serial.print(Surface);
      Serial.println(" mm²");
      
      Serial.print("Cx:");
      Serial.print(Cx);
      Serial.println("");
      
      Serial.println();
      
      temps_serial = millis(); // reinitialisation du chrono
      compte_tours=0;
    }
  }
  
  if (millis() - date_courante > interval)
  {
    num_ecran++;
    if (num_ecran == 1)
    {
      premier_ecran = true;
    }
    if (num_ecran == 2)
    {
      deuxieme_ecran = true;
      num_ecran=0;
    }
    date_courante += interval;
  }
  if (deuxieme_ecran)
  {
    tft.setRotation(0);
    tft.setCursor(0, 0);
    tft.fillScreen(ILI9341_BLACK);
    tft.setTextSize(3);
    tft.println("Mesure : ");
    tft.println();
    
    tft.setTextSize(3);
    tft.print("P=");
    tft.print(pressure);
    tft.println("Pa");
    tft.setTextSize(1);
    tft.println();
    
    tft.setTextSize(3);
    tft.print("T=");
    tft.print(temp);
    tft.print((char)223);
    tft.println("C");
    tft.setTextSize(1);
    tft.println();
    
    tft.setTextSize(3);
    tft.print("T=");
    tft.print(temp_K);
    tft.println("K");
    tft.setTextSize(1);
    tft.println();
    
    tft.setTextSize(3);
    tft.print("F=") ; 
    tft.print(Force);
    tft.println("N");
    tft.setTextSize(1);
    tft.println();
    
    tft.setTextSize(3);
    tft.print("v=") ; 
    tft.print(vitesse_ang); 
    tft.println("rad/s");
    tft.setTextSize(1);
    tft.println();
    
    tft.setTextSize(3);
    tft.print("p="); 
    tft.print(rho) ;
    tft.println("kg/m^3");
    tft.setTextSize(1);
    tft.println();
    
    tft.setTextSize(3);
    tft.print("S=") ; 
    tft.print(Surface);
    tft.println("mm^2");
    tft.setTextSize(1);
    tft.println();
     
    tft.setTextSize(3);
    tft.print("Cx=");
    tft.print(Cx); 
    tft.println(""); 
    
    deuxieme_ecran=false;
  }
  
  if (premier_ecran)
  {
    tft.setRotation(0);
    tft.setCursor(0, 0);
    tft.fillScreen(ILI9341_BLACK);
    tft.setTextSize(3);
    tft.println("Info projet : ");
    tft.setTextSize(4);
    tft.println("Souflerie");
    tft.setTextSize(1);
    tft.println();
    tft.setTextSize(4);
    tft.println("Course en Cours");
    tft.println();
    tft.setTextSize(2);
    tft.println("Tom MARTIN");
    tft.println("Theophile CHARIER");
    tft.println("Antoine KLAPCZYNSKI");
    tft.println("Romain LOTTIN");
    tft.println("");
    tft.setTextSize(2);
    tft.println("Terminal STI2D");
    tft.println("Lycee Henri BRISSON");
    tft.println("18100 VIERZON");
    
    premier_ecran=false;
  }
 //}

  key = keypad.getKey();
  save_key = key; //Nombre en ASCII

if (Surface==0 || key=='*')
{
    //Vérification du keypad entrée
  //  if (key != NO_KEY)
  //  {
  //    Serial.print("Entrée Pad (Char) : ");
  //    Serial.println(key);
  //    Serial.print("Entrée Pad ASCII : ");
  //    Serial.println(save_key);
  //  }
    
    //Permet de rentrer un nombre au keypad et de le sauvegarder dans un tableau
    //Mettre une LED pour signaler une saisie ?
    if(key=='*')
    {
      Serial.println("Début Saisie");
      entree_nombre=1; // Entre dans la sauvegarde du nombre entrée dans le keypad
      i=0; //Réinialistion de l'entrée du tableau sauvergardant le keypad tapé.
      Surface=0; // Reinisialisation du nombre entrée au Keypad
    }
  
    //Permet de confirmer le nombre entrée au keypad et de convertir le tableau en un nombre
    if(key=='#')
    {
      entree_nombre=0;
      double surface_s=0;
      Serial.println("Fin Saisie");
      k=i; //sauvegarde de i pour les puissances de 10
      
      //Conversion du nombre entrée au Keypad
      for(j=0;j<i;j++)
      {
        surface_s=surface_s+Tab[j]*pow(10,k-1);
        k--;
        //Vérification de la bonne conversion du nombre
  //      Serial.print("Surface : ");
  //      Serial.println(Surface);
      }
      if(surface_s >=100)
      {
        Surface = surface_s + 1;
      }
      else
      {
        Surface=surface_s;
      }
      Serial.print("Surface s : ");
      Serial.println(surface_s);
      Serial.print("Surface : ");
      Serial.println(Surface);
    }
    
    // Conversion Table ASCII du keypad
    if(save_key==48) // Keypad 0
    {
      dec_key=0;
    }
    if(save_key==49) // Keypad 1
    {
      dec_key=1;
    }
    if(save_key==50) // Keypad 2
    {
      dec_key=2;
    }
    if(save_key==51) // Keypad 3
    {
      dec_key=3;
    }
    if(save_key==52) // Keypad 4
    {
      dec_key=4;
    }
    if(save_key==53) // Keypad 5
    {
      dec_key=5;
    }
    if(save_key==54) // Keypad 6
    {
      dec_key=6;
    }
    if(save_key==55) // Keypad 7
    {
      dec_key=7;
    }
    if(save_key==56) // Keypad 8
    {
      dec_key=8;
    }
    if(save_key==57) // Keypad 9
    {
      dec_key=9;
    }
  
    //Sauvegarde du keypad entrée
    if(entree_nombre==1 && key != NO_KEY && key!='*')
    {
      Tab[i]=dec_key;
      //Verification de l'enregistrement du nombre entrée au Keypad.
  //    Serial.print(i);
  //    Serial.print(" ");
  //    Serial.println(Tab[i]);
      i++;
    }
  }
}
