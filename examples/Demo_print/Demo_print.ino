////////////////////////////////////////////////////////////////////////
/*
	 Minitel1B_Hard - Démo - Version du 17 mars 2023 à 14h45
	 Copyright 2016, 2023 - Eric Sérandour
	 https://entropie.org/3615/
	 
	 Documentation utilisée :
	 Spécifications Techniques d'Utilisation du Minitel 1B
	 http://543210.free.fr/TV/stum1b.pdf
	 
////////////////////////////////////////////////////////////////////////
	 
	 This program is free software: you can redistribute it and/or modify
	 it under the terms of the GNU General Public License as published by
	 the Free Software Foundation, either version 3 of the License, or
	 (at your option) any later version.

	 This program is distributed in the hope that it will be useful,
	 but WITHOUT ANY WARRANTY; without even the implied warranty of
	 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	 GNU General Public License for more details.

	 You should have received a copy of the GNU General Public License
	 along with this program. If not, see <http://www.gnu.org/licenses/>.
*/
////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////

// DEBUT DU PROGRAMME

////////////////////////////////////////////////////////////////////////

#include <Minitel1B_Hard.h>  // Voir https://github.com/eserandour/Minitel1B_Hard
// On n'utilise pas la bibliothèque SoftwareSerial.

#if defined(ESP32) || defined(ARDUINO_ARCH_ESP32)  // Pour ESP32
// Le troisième port série matériel de l'ESP32 (Serial2 / U2RXD U2TXD)
// est utilisé pour la connexion avec le Minitel.
Minitel minitel(Serial2, 16, 17);
#else  // Pour ATmega 1284P ou ATmega 2560 notamment
// Le deuxième port série matériel de l'ATMega (Serial1 / RXD1 TXD1)
// est utilisé pour la connexion avec le Minitel.
Minitel minitel(Serial1);
#endif

int attente = 5000;

void newPage(String titre) {
	minitel.newScreen();
	minitel.println(titre);
	for (int i=1; i<=40; i++) {
		minitel.write(0x7E);
	}
	minitel.moveCursorReturn(1); 
}

////////////////////////////////////////////////////////////////////////

void demoNonPrintable(){
	newPage("Caractères non imprimables");

	minitel.print("Voilà une nouvelle ligne.");
	minitel.print('\n');
	minitel.print("Voilà un retour chariot.");
	minitel.print('\r');
	minitel.print("\tVoilà une tabulation.");
	minitel.print('\n');
	minitel.println();
	minitel.println("Nouvelle ligne suivie");
	minitel.println("d'un retour chariot");

	delay(attente);
}

void demoPrintf(){
	newPage("Utilisation de printf()");

	for(uint8_t i = 0; i < 16; ++i){
		minitel.printf("%i : nouvelle ligne : %x\n\r", i, i);
	}

	delay(attente);
}

void demoCaracteres() {
	newPage("LES CARACTERES");
	
	// Mode texte 
	
	minitel.println("MODE TEXTE SANS LIGNAGE :");
	for (int i=0x20; i<=0x7F; i++) {
		minitel.write(i);
	}
	minitel.moveCursorReturn(2);
	
	minitel.println("MODE TEXTE AVEC LIGNAGE :");
	minitel.attributs(DEBUT_LIGNAGE);  // En mode texte, le lignage est déclenché par le premier espace rencontré (0x20).
	for (int i=0x20; i<=0x7F; i++) {   
		minitel.write(i);   
	}
	minitel.attributs(FIN_LIGNAGE);
	minitel.moveCursorReturn(2);  

	// Mode semi-graphique
	
	minitel.textMode();
	minitel.println("MODE SEMI-GRAPHIQUE SANS LIGNAGE :");
	minitel.graphicMode();  
	for (int i=0x20; i<=0x7F; i++) {
		minitel.write(i);
	}
	minitel.moveCursorReturn(2);
	
	minitel.textMode();
	minitel.println("MODE SEMI-GRAPHIQUE AVEC LIGNAGE :");
	minitel.graphicMode();
	minitel.attributs(DEBUT_LIGNAGE);
	for (int i=0x20; i<=0x7F; i++) {
		minitel.write(i);
	}
	minitel.attributs(FIN_LIGNAGE);
	minitel.moveCursorReturn(2);
		
	delay(attente); 
}

////////////////////////////////////////////////////////////////////////

void demoGraphic() {
	newPage("LA FONCTION GRAPHIC");
	minitel.textMode();
	minitel.println("Un caractère semi-graphique est composé de 6 pseudo-pixels :");
	minitel.println();
	minitel.graphicMode();
	minitel.attributs(DEBUT_LIGNAGE);
	minitel.write(0x7F);
	minitel.attributs(FIN_LIGNAGE);
	minitel.textMode();
	minitel.print(" avec lignage ou ");
	minitel.graphicMode();
	minitel.write(0x7F);
	minitel.textMode();
	minitel.println(" sans lignage.");
	minitel.println();
	String chaine = "";
	chaine += "minitel.graphic(0b101011) donne ";
	minitel.textMode();
	minitel.print(chaine);
	minitel.graphicMode();
	minitel.graphic(0b101011);
	minitel.textMode();
	minitel.println();
	minitel.println();
	chaine = "";
	chaine += "minitel.graphic(0b110110,30,15) donne ";
	minitel.print(chaine);  
	minitel.graphicMode();
	minitel.graphic(0b110110,30,15);
	minitel.noCursor();
	delay(2*attente); 
}

////////////////////////////////////////////////////////////////////////

void demoTailles() { 
	newPage("LES TAILLES");
	minitel.println("GRANDEUR_NORMALE");
	minitel.attributs(DOUBLE_HAUTEUR);
	minitel.print("DOUBLE_HAUTEUR");  
	minitel.attributs(DOUBLE_LARGEUR);
	minitel.println();
	minitel.println("DOUBLE_LARGEUR");  
	minitel.attributs(DOUBLE_GRANDEUR); 
	minitel.println("DOUBLE_GRANDEUR");
	minitel.println();
	minitel.attributs(GRANDEUR_NORMALE);
	minitel.attributs(DEBUT_LIGNAGE);  // En mode texte, le lignage est déclenché par le premier espace rencontré (0x20).
	minitel.println("SEULEMENT EN MODE TEXTE");  
	minitel.attributs(FIN_LIGNAGE);
	minitel.println();
	delay(attente);  
}

////////////////////////////////////////////////////////////////////////

void demoCouleurs() {
	newPage("LES COULEURS");
	for (int i=0; i<=1; i++) {   
		if (i==0) { minitel.textMode(); }
		if (i==1) { minitel.graphicMode(); }
		minitel.attributs(INVERSION_FOND);
		minitel.print("CARACTERE_NOIR, FOND_BLANC");
		minitel.attributs(FOND_NORMAL);
		minitel.println(" (INVERSION)");      
		minitel.attributs(CARACTERE_ROUGE);
		minitel.println("CARACTERE_ROUGE");
		minitel.attributs(CARACTERE_VERT);
		minitel.println("CARACTERE_VERT");
		minitel.attributs(CARACTERE_JAUNE);
		minitel.println("CARACTERE_JAUNE");
		minitel.attributs(CARACTERE_BLEU);
		minitel.println("CARACTERE_BLEU");
		minitel.attributs(CARACTERE_MAGENTA);
		minitel.println("CARACTERE_MAGENTA");
		minitel.attributs(CARACTERE_CYAN);
		minitel.println("CARACTERE_CYAN");
		minitel.attributs(CARACTERE_BLANC);
		minitel.println("CARACTERE_BLANC");
		minitel.println();
	}
	delay(attente);
}

////////////////////////////////////////////////////////////////////////

void demoCurseur() {
	minitel.cursor();
	newPage("DEPLACER LE CURSEUR");
	minitel.moveCursorXY(20,12);
	for (int i=1; i<=100; i++) {
		delay(100);
		switch (random(4)) {
			case 0: minitel.moveCursorRight(1+random(3)); break;
			case 1: minitel.moveCursorLeft(1+random(3)); break;
			case 2: minitel.moveCursorDown(1+random(3)); break;
			case 3: minitel.moveCursorUp(1+random(3)); break;
		}
	}
	newPage("POSITIONNER LE CURSEUR");
	minitel.textMode();
	for (int i=1; i<1000; i++) {
		minitel.moveCursorXY(1+random(40),3+random(22));
		minitel.write(0x20 + random(0x60));
	}
	
	minitel.newScreen();
	minitel.textMode();
	minitel.noCursor();
	for (int i=1; i<1000; i++) {
		if (random(4)<3) { minitel.textMode(); }
		else {
			minitel.graphicMode();
			minitel.attributs(DEBUT_LIGNAGE);
		}
		minitel.attributs(0x4C+random(5));
		minitel.write(0x20 + random(0x60));
		minitel.attributs(FIN_LIGNAGE);
	}
}


////////////////////////////////////////////////////////////////////////

void setup() {
	// Le premier port série matériel de l'ATMega (Serial / RXD0 TXD0)
	// ou de l'ESP32 (Serial / U0RXD U0TXD) est utilisé pour la connexion
	// avec le PC.
	Serial.begin(9600);

	// Pour le cas où on utilise le shield 3615 avec une Arduino Mega 2560,
	// on relie avec un fil les broches 8 et 19 d'un côté et 9 et 18 de l'autre.
	// Les 2 broches 8 et 9 du shield 3615 sont dès lors respectivement reroutées
	// vers les broches 19 (RX1) et 18 (TX1).
	// Afin que les broches 8 et 9 de la carte Arduino ne perturbent pas
	// ce reroutage, on les définit comme des entrées.
	// pinMode(8,INPUT);
	// pinMode(9,INPUT);

	minitel.changeSpeed(minitel.searchSpeed());
}

////////////////////////////////////////////////////////////////////////

void loop() {
	demoNonPrintable();
	demoPrintf();
}

////////////////////////////////////////////////////////////////////////

