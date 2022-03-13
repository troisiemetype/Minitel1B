#include <Minitel1B_Hard.h>  // Voir https://github.com/eserandour/Minitel1B_Hard

// Le deuxième port série matériel de l'ATMega 1284P (Serial1 / RXD1 TXD1)
// est utilisé pour la connexion avec le Minitel.
Minitel minitel(Serial1);

///////////////////////////////////////////////////////////////////////////////////

void setup() {  
  // Le premier port série matériel de l'ATMega 1284P (Serial / RXD0 TXD0)
  // est utilisé pour la connexion avec le PC.
  Serial.begin(9600);  

  // A la mise sous tension du Minitel, la vitesse des échanges entre
  // le Minitel et le périphérique est de 1200 bauds par défaut.
  // On envisage cependant le cas où le Minitel se trouve dans un autre état.
  minitel.changeSpeed(minitel.searchSpeed());
  
  minitel.newScreen();
}

///////////////////////////////////////////////////////////////////////////////////

void loop() {
  minitel.print("Hello World ! ");
}

///////////////////////////////////////////////////////////////////////////////////
