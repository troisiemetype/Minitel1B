// Version du 5 mars 2023 à 23h55

#include <Minitel1B_Hard.h>  // Voir https://github.com/eserandour/Minitel1B_Hard

// Le deuxième port série matériel de l'ATMega 1284P (Serial1 / RXD1 TXD1)
// est utilisé pour la connexion avec le Minitel.
Minitel minitel(Serial1);

#define TITRE "TEST CARACTÈRES SPÉCIAUX"

String texte="";
int nbCaracteres=0;
const int PREMIERE_LIGNE_EXPRESSION = 7;
const int NB_LIGNES_EXPRESSION = 15;
const String VIDE = ".";

unsigned long touche;
const int TAILLE_CACHE = 20;  // Peut être augmenté si besoin
int cache[TAILLE_CACHE] = {0};  // Utilisé pour enregistrer le nombre d'octets des caractères spéciaux

///////////////////////////////////////////////////////////////////////////////////

void setup() {  
  // Le premier port série matériel de l'ATMega 1284P (Serial / RXD0 TXD0)
  // est utilisé pour la connexion avec le PC.
  Serial.begin(9600);  

  // A la mise sous tension du Minitel, la vitesse des échanges entre
  // le Minitel et le périphérique est de 1200 bauds par défaut.
  // On envisage cependant le cas où le Minitel se trouve dans un autre état.
  minitel.changeSpeed(minitel.searchSpeed());
  minitel.smallMode();
  
  // Affichage de la page
  newPage(TITRE);  

  texte = "àâäèéêëîïôöùûüçÀÂÄÈÉÊËÎÏÔÖÙÛÜÇ";
  minitel.println(texte);
  Serial.println(texte);
  texte = "£§°±¼½¾β÷Œœ";
  minitel.println(texte);
  Serial.println(texte);
  texte = "—←↑→↓";
  minitel.println(texte);
  Serial.println(texte);
  Serial.println();
}

///////////////////////////////////////////////////////////////////////////////////

void loop() {
  // Affichage de la page
  //newPage(TITRE);
  
  // Lecture du champ expression
  lectureChamp(PREMIERE_LIGNE_EXPRESSION, NB_LIGNES_EXPRESSION);
  Serial.println(texte);
}

///////////////////////////////////////////////////////////////////////////////////

void newPage(String titre) {
  minitel.newScreen();
  minitel.println(titre);
  for (int i=1; i<=40; i++) {
    minitel.writeByte(0x7E);
  }
}

////////////////////////////////////////////////////////////////////////

void champVide(int premiereLigne, int nbLignes)
{
  minitel.noCursor();
  minitel.moveCursorXY(1,premiereLigne);
  minitel.clearScreenFromCursor();
  for (int j=0; j<nbLignes; j++) {
    minitel.attributs(CARACTERE_BLEU);
    minitel.print(VIDE);
    minitel.repeat(39);
    minitel.attributs(CARACTERE_BLANC);
  }
  texte="";
  nbCaracteres=0;
  for (int i=0; i<TAILLE_CACHE; i++) {
    cache[i] = 0;
  }
  minitel.moveCursorXY(31,24);
  minitel.print("puis ");
  minitel.attributs(INVERSION_FOND);
  minitel.print("ENVOI");
  minitel.attributs(FOND_NORMAL);
  minitel.moveCursorDown(premiereLigne-1);
  minitel.cursor();
}

////////////////////////////////////////////////////////////////////////

void correction(int nbLignes) {
  boolean texteCorrige = false;
  if ((nbCaracteres > 0) && (nbCaracteres <= 40*nbLignes)) {
    unsigned int index = texte.length()-1;
    if (texte.charAt(index) >> 8) {  // Caractère spécial
      if (cache[0] != 0) {
        texte = texte.substring(0,texte.length()-cache[0]);
        texteCorrige = true;
        for (int i=0; i<TAILLE_CACHE-1; i++) {
          cache[i]=cache[i+1];
        }
        cache[TAILLE_CACHE-1] = 0;
      }
    }
    else {
      texte = texte.substring(0,texte.length()-1);
      texteCorrige = true;
    }
    if (texteCorrige) {
      nbCaracteres--;
      if (nbCaracteres != 40*nbLignes) { minitel.moveCursorLeft(1); }
      minitel.attributs(CARACTERE_BLEU);
      minitel.print(VIDE);
      minitel.attributs(CARACTERE_BLANC);
      minitel.moveCursorLeft(1);
    }
    // Affichage des informations dans la console
    Serial.print("texte = "); Serial.println(texte);
    Serial.print("nbCaracteres = "); Serial.println(nbCaracteres);
    Serial.print("Cache[");Serial.print(TAILLE_CACHE);Serial.print("]={");
    for (int i=0; i<TAILLE_CACHE; i++) {
      Serial.print(cache[i]);
      if (i<TAILLE_CACHE-1) Serial.print(";");
    }
    Serial.println("} - Nombre d'octets des caractères spéciaux");
    Serial.println();
  }
}

////////////////////////////////////////////////////////////////////////

void lectureChamp(int premiereLigne, int nbLignes) {
  champVide(premiereLigne,nbLignes);
  boolean fin = false;
  while (!fin) {
    touche = minitel.getKeyCode();
    if ((touche != 0) &&
        (touche != CONNEXION_FIN) &&
        (touche != SOMMAIRE) &&
        (touche != ANNULATION) &&
        (touche != RETOUR) &&
        (touche != REPETITION) &&
        (touche != GUIDE) &&
        (touche != CORRECTION) &&
        (touche != SUITE) &&
        (touche != ENVOI)) {
      if (nbCaracteres < 40*nbLignes) {
        nbCaracteres++;
        texte += minitel.getString(touche);
        int nbBytes = minitel.getNbBytes (touche);
        if (nbBytes > 1) {  // Caractère spécial
          for (int i=TAILLE_CACHE-1; i>0; i--) {
            cache[i]=cache[i-1];
          }
          cache[0] = nbBytes;
        }
        // Affichage des informations dans la console
        Serial.print("Caractère : ");Serial.println(minitel.getString(touche));
        Serial.print(touche, HEX); Serial.println(" (Unicode)");
        unsigned long index = texte.length()-1;
        for (int i=nbBytes; i>0; i--) {
          Serial.print((byte) texte.charAt(index-i+1), HEX);
        }
        Serial.print(" (UTF-8) - Nb d'octets : "); Serial.println(nbBytes);
        Serial.print("texte = "); Serial.println(texte);
        Serial.print("nbCaracteres = "); Serial.println(nbCaracteres);
        Serial.print("Cache[");Serial.print(TAILLE_CACHE);Serial.print("]={");
        for (int i=0; i<TAILLE_CACHE; i++) {
          Serial.print(cache[i]);
          if (i<TAILLE_CACHE-1) Serial.print(";");
        }
        Serial.println("} - Nombre d'octets des caractères spéciaux");
        Serial.println();
      }
      if (nbCaracteres == 40*nbLignes) {
        minitel.moveCursorXY(40,(premiereLigne-1)+nbLignes);
      }
    }
    switch (touche) {
      case ENVOI : 
        fin = true;
        break;
      case ANNULATION :
        champVide(premiereLigne,nbLignes);
        break;
      case CORRECTION :
        correction(nbLignes);
        break;
    }    
  }
}

///////////////////////////////////////////////////////////////////////////////////







/*

// Version du 6 mars 2023 à 08h10
// Alternative au programme ci-dessus (sans cache)

#include <Minitel1B_Hard.h>  // Voir https://github.com/eserandour/Minitel1B_Hard

// Le deuxième port série matériel de l'ATMega 1284P (Serial1 / RXD1 TXD1)
// est utilisé pour la connexion avec le Minitel.
Minitel minitel(Serial1);

#define TITRE "TEST CARACTÈRES SPÉCIAUX"

String texte="";
int nbCaracteres=0;
const int PREMIERE_LIGNE_EXPRESSION = 7;
const int NB_LIGNES_EXPRESSION = 15;
const String VIDE = ".";

unsigned long touche;

///////////////////////////////////////////////////////////////////////////////////

void setup() {  
  // Le premier port série matériel de l'ATMega 1284P (Serial / RXD0 TXD0)
  // est utilisé pour la connexion avec le PC.
  Serial.begin(9600);  

  // A la mise sous tension du Minitel, la vitesse des échanges entre
  // le Minitel et le périphérique est de 1200 bauds par défaut.
  // On envisage cependant le cas où le Minitel se trouve dans un autre état.
  minitel.changeSpeed(minitel.searchSpeed());
  minitel.smallMode();
  
  // Affichage de la page
  newPage(TITRE);  

  texte = "àâäèéêëîïôöùûüçÀÂÄÈÉÊËÎÏÔÖÙÛÜÇ";
  minitel.println(texte);
  Serial.println(texte);
  texte = "£§°±¼½¾β÷Œœ";
  minitel.println(texte);
  Serial.println(texte);
  texte = "—←↑→↓";
  minitel.println(texte);
  Serial.println(texte);
  Serial.println();
}

///////////////////////////////////////////////////////////////////////////////////

void loop() {
  // Affichage de la page
  //newPage(TITRE);
  
  // Lecture du champ expression
  lectureChamp(PREMIERE_LIGNE_EXPRESSION, NB_LIGNES_EXPRESSION);
  Serial.println(texte);
}

///////////////////////////////////////////////////////////////////////////////////

void newPage(String titre) {
  minitel.newScreen();
  minitel.println(titre);
  for (int i=1; i<=40; i++) {
    minitel.writeByte(0x7E);
  }
}

////////////////////////////////////////////////////////////////////////

void champVide(int premiereLigne, int nbLignes)
{
  minitel.noCursor();
  minitel.moveCursorXY(1,premiereLigne);
  minitel.clearScreenFromCursor();
  for (int j=0; j<nbLignes; j++) {
    minitel.attributs(CARACTERE_BLEU);
    minitel.print(VIDE);
    minitel.repeat(39);
    minitel.attributs(CARACTERE_BLANC);
  }
  texte="";
  nbCaracteres=0;
  minitel.moveCursorXY(31,24);
  minitel.print("puis ");
  minitel.attributs(INVERSION_FOND);
  minitel.print("ENVOI");
  minitel.attributs(FOND_NORMAL);
  minitel.moveCursorDown(premiereLigne-1);
  minitel.cursor();
}

////////////////////////////////////////////////////////////////////////

void correction(int nbLignes) {
  if ((nbCaracteres > 0) && (nbCaracteres <= 40*nbLignes)) {
    if (nbCaracteres != 40*nbLignes) { minitel.moveCursorLeft(1); }
    minitel.attributs(CARACTERE_BLEU);
    minitel.print(VIDE);
    minitel.attributs(CARACTERE_BLANC);
    minitel.moveCursorLeft(1);
    unsigned int index = texte.length()-1;
    if (texte.charAt(index) >> 8) {  // Caractère spécial
      index--;
      if (texte.charAt(index) >> 8 == 0xFFFFFFFF && texte.charAt(index-1) == 0xFFFFFFE2) index--;  // Les caractères spéciaux codés sur 3 octets commencent par 0xE2
    }
    texte.remove(index);
    nbCaracteres--;
  }
  // Affichage des informations dans la console
  Serial.print("texte = "); Serial.println(texte);
  Serial.print("nbCaracteres = "); Serial.println(nbCaracteres);
  Serial.println();
}

////////////////////////////////////////////////////////////////////////

void lectureChamp(int premiereLigne, int nbLignes) {
  champVide(premiereLigne,nbLignes);
  boolean fin = false;
  while (!fin) {
    touche = minitel.getKeyCode();
    if ((touche != 0) &&
        (touche != CONNEXION_FIN) &&
        (touche != SOMMAIRE) &&
        (touche != ANNULATION) &&
        (touche != RETOUR) &&
        (touche != REPETITION) &&
        (touche != GUIDE) &&
        (touche != CORRECTION) &&
        (touche != SUITE) &&
        (touche != ENVOI)) {
      if (nbCaracteres < 40*nbLignes) {
        nbCaracteres++;
        texte += minitel.getString(touche);
        int nbBytes = minitel.getNbBytes(touche);
   
        // Affichage des informations dans la console
        Serial.print("Caractère : "); Serial.println(minitel.getString(touche));
        Serial.print(touche, HEX); Serial.println(" (Unicode)");
        unsigned long index = texte.length()-1;
        for (int i=nbBytes; i>0; i--) {
          Serial.print((byte) texte.charAt(index-i+1), HEX);
        }
        Serial.print(" (UTF-8) - Nb d'octets : "); Serial.println(nbBytes);
        Serial.print("texte = "); Serial.println(texte);
        Serial.print("nbCaracteres = "); Serial.println(nbCaracteres);
        Serial.println();
      }
      if (nbCaracteres == 40*nbLignes) {
        minitel.moveCursorXY(40,(premiereLigne-1)+nbLignes);
      }
    }
    switch (touche) {
      case ENVOI : 
        fin = true;
        break;
      case ANNULATION :
        champVide(premiereLigne,nbLignes);
        break;
      case CORRECTION :
        correction(nbLignes);
        break;
    }    
  }
}

///////////////////////////////////////////////////////////////////////////////////

*/
