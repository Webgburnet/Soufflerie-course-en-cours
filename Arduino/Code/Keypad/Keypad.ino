#include <Keypad.h>
#include <math.h>

const byte ROWS = 4;
const byte COLS = 3;
char keys[ROWS][COLS] = {
{'1','2','3'},
{'4','5','6'},
{'7','8','9'},
{'*','0','#'}
};
byte rowPins[ROWS] = {7, 5, 3, 2};
byte colPins[COLS] = {4, 9, 8};
Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

int entree_nombre=0;
int Tab[255];
int i=0;
int j=0;
int k=0;
float Nombre_Keypad=0;

void setup(){
  Serial.begin(9600);
  Serial.println("Début Setup");
  Serial.println("Fin Setup");
}
void loop(){
  char key = keypad.getKey();
  int save_key = key; //Nombre en ASCII
  int dec_key; // Conversion ASCII en nombre de 0 à 9

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
    
    entree_nombre=1; // Entre dans la sauvegarde du nombre entrée dans le keypad
    i=0; //Réinialistion de l'entrée du tableau sauvergardant le keypad tapé.
    Nombre_Keypad=0; // Reinisialisation du nombre entrée au Keypad
  }

  //Permet de confirmer le nombre entrée au keypad et de convertir le tableau en un nombre
  if(key=='#')
  {
    entree_nombre=0;
    Serial.println("Fin Saisie");
    k=i; //sauvegarde de i pour les puissances de 10
    
    //Conversion du nombre entrée au Keypad
    for(j=0;j<i;j++)
    {
      Nombre_Keypad=Nombre_Keypad+Tab[j]*powf(10,k-1);
      k--;
      //Vérification de la bonne conversion du nombre
//      Serial.print("Nombre_Keypad : ");
//      Serial.println(Nombre_Keypad);
    }
    Serial.print("Nombre_Keypad : ");
    Serial.println(Nombre_Keypad);
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
//    Serial.println(i);
//    Serial.println(Tab[i]);
    i++;
  }
}
