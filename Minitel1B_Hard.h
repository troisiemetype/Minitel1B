////////////////////////////////////////////////////////////////////////
/*
	 Minitel1B_Hard - Fichier d'en-tête - Version du 5 mars 2023 à 21h27
	 Copyright 2016-2023 - Eric Sérandour
	 https://entropie.org/3615/
	 
	 Remerciements à :
	 BorisFR, iodeo
	 
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

#ifndef MINITEL1B_H  // Si la constante MINITEL1B_H n'est
#define MINITEL1B_H  // pas définie, on la définit.

// Selon la version d'Arduino
#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif  // Fin Si (ARDUINO)

////////////////////////////////////////////////////////////////////////

// Le standard Télétel

// Chapitre 2 : L'écran

// 1 Mode Vidéotex

// 1.2.3 Codage des caractères visualisables
// Jeu G0 => alphanumérique (voir p.100)
// Jeu G1 => semi-graphique (voir p.101 et 102)
// Jeu G2 => complément à G0 (voir p.103)
// Les caractères du jeu G2 sont obtenus si précédés du code SS2 (0x19).
// On peut les afficher directement en utilisant printSpecialChar(byte b) :
#define LIVRE              0x23
#define DOLLAR             0x24
#define DIESE              0x26
#define PARAGRAPHE         0x27
#define FLECHE_GAUCHE      0x2C
#define FLECHE_HAUT        0x2D
#define FLECHE_DROITE      0x2E
#define FLECHE_BAS         0x2F
#define DEGRE              0x30
#define PLUS_OU_MOINS      0x31
#define DIVISION           0x38
#define UN_QUART           0x3C
#define UN_DEMI            0x3D
#define TROIS_QUART        0x3E
#define OE_MAJUSCULE       0x6A
#define OE_MINUSCULE       0x7A
#define BETA               0x7B
// Les diacritiques ne peuvent pas être affichés seuls.
// printSpecialChar(byte b) n'aura donc aucun effet ici.
#define ACCENT_GRAVE       0x41
#define ACCENT_AIGU        0x42
#define ACCENT_CIRCONFLEXE 0x43
#define TREMA              0x48
#define CEDILLE            0x4B


// 1.2.4 Codage des attributs de visualisation (voir p.91)
// Ces fonctions sont obtenues si précédées du code ESC (0x1B).
// Nous avons alors accès à la grille C1. On peut y accéder directement
// en utilisant attributs(byte attribut).
// Couleur de caractère
#define CARACTERE_NOIR    0x40
#define CARACTERE_ROUGE   0x41
#define CARACTERE_VERT    0x42
#define CARACTERE_JAUNE   0x43
#define CARACTERE_BLEU    0x44
#define CARACTERE_MAGENTA 0x45
#define CARACTERE_CYAN    0x46
#define CARACTERE_BLANC   0x47
// Couleur de fond              // En mode texte, l'espace (0x20) est l'élément déclencheur du changement de couleur de fond (voir p.93). Ce changement est valide jusqu'à la fin d'une rangée.
#define FOND_NOIR         0x50  // Pour éviter d'avoir cet espace à l'écran, une autre solution (dans ce cas le caractère sera noir), est de mettre en oeuvre le fond inversé.
#define FOND_ROUGE        0x51  // Par exemple :
#define FOND_VERT         0x52  // minitel.attributs(CARACTERE_VERT);
#define FOND_JAUNE        0x53  // minitel.attributs(INVERSION_FOND);
#define FOND_BLEU         0x54  // minitel.print("J'ECRIS ICI MON TEXTE");
#define FOND_MAGENTA      0x55  // minitel.attributs(FOND_NORMAL);
#define FOND_CYAN         0x56
#define FOND_BLANC        0x57
// Taille
#define GRANDEUR_NORMALE  0x4C  // Non utilisable en mode graphique
#define DOUBLE_HAUTEUR    0x4D  // Non utilisable en mode graphique
#define DOUBLE_LARGEUR    0x4E  // Non utilisable en mode graphique
#define DOUBLE_GRANDEUR   0x4F  // Non utilisable en mode graphique
// Clignotement ou fixité
#define CLIGNOTEMENT      0x48
#define FIXE              0x49
// Début et fin de masquage
#define MASQUAGE          0x58
#define DEMASQUAGE        0x5F
// Début ou fin de lignage
#define FIN_LIGNAGE       0x59
#define DEBUT_LIGNAGE     0x5A  // En mode texte, l'espace (0x20) marque le début d'une zone de lignage. C'est l'élément déclencheur (voir p.93).
// Fond inversé ou normal
#define FOND_NORMAL       0x5C  // Non utilisable en mode graphique
#define INVERSION_FOND    0x5D  // Non utilisable en mode graphique
// Echappement vers la norme ISO 6429
#define CSI               0x1B5B


// 1.2.5 Fonctions de mise en page (voir p.94)
#define BS   0x08  // BackSpace : Déplacement du curseur d'un emplacement de caractère à gauche.
#define HT   0x09  // Horizontal Tab : Déplacement du curseur d'un emplacement de caractère à droite.
#define LF   0x0A  // Line Feed : Déplacement du curseur d'un emplacement de caractère vers le bas.
#define VT   0x0B  // Vertical Tab : Déplacement du curseur d'un emplacement de caractère vers le haut.
#define CR   0x0D  // Carriage Return : Retour du curseur au début de la rangée courante.
// Les fonctions de type CSI sont développées à l'intérieur de la classe Minitel (plus bas).
#define RS   0x1E  // Record Separator : Retour du curseur en première position de la rangée 01. Ce code est un séparateur explicite d'article.
#define FF   0x0C  // Form Feed : Retour du curseur en première position de la rangée 01 avec effacement complet de l'écran.
#define US   0x1F  // Unit Separator : Séparateur de sous-article.
#define CAN  0x18  // Cancel : Remplissage à partir de la position courante du curseur et jusqu'à la fin de la rangée par des espaces du jeu courant ayant l'état courant des attributs. La position courante du curseur n'est pas déplacée.


// 1.2.6 Autres fonctions (voir p.98)
// 1.2.6.1 Fonctions diverses :
#define REP  0x12  // Repetition : Permet de répéter le dernier caractère visualisé avec les attributs courants de la position active d'écriture.
#define NUL  0x00  // Null :
#define SP   0x20  // Space :
#define DEL  0x7F  // Delete :
#define BEL  0x07  // Bell : Provoque l'émission d'un signal sonore
// 1.2.6.2 Demande de position du curseur
//...
// 1.2.6.3 Fonctions d'extension de code
#define SO   0x0E  // Shift Out : Accès au jeu G1. => Mode semi-graphique
#define SI   0x0F  // Shift In : Accès au jeu G0.  => Mode alphanumérique
#define SS2  0x19  // Single Shift 2 : Appel d'un caractère unique du jeu G2.
#define ESC  0x1B  // Escape : Echappement et accès à la grille C1.
// 1.2.6.4 Visualisation du curseur
#define CON  0x11  // Visualisation de la position active du curseur (curseur actif).
#define COFF 0x14  // Arrêt de la visualisation de la position active (curseur inactif).


// 1.2.7 Filtages particuliers (voir p.99)
//...


// 1.2.8 Comportements en cas d'erreur et resynchronisation (voir p.99)
// ...




// Chapitre 3 : Le clavier

// 6 Séquences émises par les touches de fonction en mode Vidéotex ou Mixte (voir p.123)
#define ENVOI          0x1341
#define RETOUR         0x1342
#define REPETITION     0x1343
#define GUIDE          0x1344
#define ANNULATION     0x1345
#define SOMMAIRE       0x1346
#define CORRECTION     0x1347
#define SUITE          0x1348
#define CONNEXION_FIN  0x1359  // Non documenté

// 7 Codes et séquences émis par les touches de gestion du curseur et d'édition en mode Vidéotex ou Mixte (voir p.124)
#define TOUCHE_FLECHE_HAUT         0x1B5B41
#define SUPPRESSION_LIGNE          0x1B5B4D
#define TOUCHE_FLECHE_BAS          0x1B5B42
#define INSERTION_LIGNE            0x1B5B4C
#define TOUCHE_FLECHE_DROITE       0x1B5B43
#define DEBUT_INSERTION_CARACTERE  0x1B5B3468
#define FIN_INSERTION_CARACTERE    0x1B5B346C
#define TOUCHE_FLECHE_GAUCHE       0x1B5B44
#define SUPRESSION_CARACTERE       0x1B5B50
// #define DEL                        0x7F  // Déjà défini plus haut (1.2.6.1)
// #define CR                         0x0D  // Déjà défini plus haut (1.2.5)
#define HOME                       0x1B5B4B
#define EFFACEMENT_PAGE            0x1B5B324A


// Chapitre 6 : Le Protocole (voir p.134)

// 1 Généralités (voir p.134)
#define CODE_EMISSION_ECRAN        0x50
#define CODE_EMISSION_CLAVIER      0x51
#define CODE_EMISSION_MODEM        0x52
#define CODE_EMISSION_PRISE        0x53
#define CODE_RECEPTION_ECRAN       0x58
#define CODE_RECEPTION_CLAVIER     0x59
#define CODE_RECEPTION_MODEM       0x5A
#define CODE_RECEPTION_PRISE       0x5B

// 3 Commandes d'aiguillages et de blocage des modules (voir p.134)
// 3.2 Format des commandes (voir p.135)
#define AIGUILLAGE_OFF             0x60
#define AIGUILLAGE_ON              0x61
// 3.4 Demande de statut d'aiguillages des modules (voir p.136)
#define TO                         0x62
#define FROM                       0x63

// 6 Demandes d'identification et de position curseur (voir p.139)
// 6.1 Demande d'identification du Minitel (voir p.139)
#define ENQROM                     0x7B

// 7 Commandes relatives au modem (voir p.139)
#define CONNEXION                  0x68
#define DECONNEXION                0x67

// 8 Commandes relatives à la prise (voir p.141)
#define PROG                       0x6B
#define STATUS_VITESSE             0x74

// 9 Commandes relatives au clavier (voir p.141)
#define ETEN                       0x41  // Clavier en mode étendu

// 10 Commandes relatives à l'écran (voir p.142)
#define ROULEAU                    0x43  // Ecran en mode rouleau

// 11 Commandes relatives à plusieurs modules (voir p.143)
#define START                      0x69
#define STOP                       0x6A
#define MINUSCULES                 0x45  // Mode minuscules / majuscules du clavier

// 12 Commandes Protocole relatives au changement de standard  (voir p.144)
#define MIXTE1                     0x327D
#define MIXTE2                     0x327E
#define TELINFO                    0x317D

// 13 L'état initial du minitel
// 13.2 Sur réception d'une commande de reset
#define RESET                      0x7F

// Constantes personnelles pour hline et vline
#define CENTER  0
#define TOP     1
#define BOTTOM  2
#define LEFT    3
#define RIGHT   4
#define UP      5
#define DOWN    6

const uint32_t UTF8_TABLE[][2] = {
	{0xC2A3, 0x1923},		// £ (VGP5 et VGP2)
	{0xC2A7, 0x1927},		// § (VGP5 seulement)
	{0xC2B0, 0x1930},		// ° (VGP5 et VGP2)
	{0xC2B1, 0x1931},		// ± (VGP5 et VGP2)
	{0xC2BC, 0x193C},		// ¼ (VGP5 et VGP2)
	{0xC2BD, 0x193D},		// ½ (VGP5 et VGP2)
	{0xC2BE, 0x193E},		// ¾ (VGP5 et VGP2)
	{0xC380, 0x0F41},		// À (Aucune lettre accentuée majuscule n'est disponible - voir p.90)
	{0xC382, 0x0F41},		// Â (Aucune lettre accentuée majuscule n'est disponible - voir p.90)
	{0xC384, 0x0F41},		// Ä (Aucune lettre accentuée majuscule n'est disponible - voir p.90)
	{0xC387, 0x0F43},		// Ç (Aucune lettre accentuée majuscule n'est disponible - voir p.90)
	{0xC388, 0x0F45},		// È (Aucune lettre accentuée majuscule n'est disponible - voir p.90)
	{0xC389, 0x0F45},		// É (Aucune lettre accentuée majuscule n'est disponible - voir p.90)
	{0xC38A, 0x0F45},		// Ê (Aucune lettre accentuée majuscule n'est disponible - voir p.90)
	{0xC38B, 0x0F45},		// Ë (Aucune lettre accentuée majuscule n'est disponible - voir p.90)
	{0xC38E, 0x0F49},		// Î (Aucune lettre accentuée majuscule n'est disponible - voir p.90)
	{0xC38F, 0x0F49},		// Ï (Aucune lettre accentuée majuscule n'est disponible - voir p.90)
	{0xC394, 0x0F4F},		// Ô (Aucune lettre accentuée majuscule n'est disponible - voir p.90)
	{0xC396, 0x0F4F},		// Ö (Aucune lettre accentuée majuscule n'est disponible - voir p.90)
	{0xC399, 0x0F55},		// Ù (Aucune lettre accentuée majuscule n'est disponible - voir p.90)
	{0xC39B, 0x0F55},		// Û (Aucune lettre accentuée majuscule n'est disponible - voir p.90)
	{0xC39C, 0x0F55},		// Ü (Aucune lettre accentuée majuscule n'est disponible - voir p.90)
	{0xC3A0, 0x194161},		// à (VGP5 et VGP2)
	{0xC3A2, 0x194361},		// â (VGP5 et VGP2)
	{0xC3A4, 0x194861},		// ä (VGP5 seulement)
	{0xC3A7, 0x194B63},		// ç (VGP5 et VGP2)
	{0xC3A8, 0x194165},		// è (VGP5 et VGP2)
	{0xC3A9, 0x194265},		// é (VGP5 et VGP2)
	{0xC3AA, 0x194365},		// ê (VGP5 et VGP2)
	{0xC3AB, 0x194865},		// ë (VGP5 et VGP2)
	{0xC3AE, 0x194369},		// î (VGP5 et VGP2)
	{0xC3AF, 0x194869},		// ï (VGP5 et VGP2)
	{0xC3B4, 0x19436F},		// ô (VGP5 et VGP2)
	{0xC3B6, 0x19486F},		// ö (VGP5 seulement)
	{0xC3B7, 0x1938},		// ÷ (VGP5 et VGP2)
	{0xC3B9, 0x194175},		// ù (VGP5 et VGP2)
	{0xC3BB, 0x194375},		// û (VGP5 et VGP2)
	{0xC3BC, 0x194875},		// ü (VGP5 seulement)
	{0xC592, 0x196A},		// Œ (VGP5 et VGP2)
	{0xC593, 0x197A},		// œ (VGP5 et VGP2)
	{0xCEB2, 0x197B},		// β (VGP5 seulement)
	{0xE28094, 0x60},		// —
	{0xE28099, 0x27},		// ' (it seems OSX encodes apostrophe like this)
	{0xE28690, 0x192C},		// ←
	{0xE28691, 0x5E},		// ↑
	{0xE28692, 0x192E},		// →
	{0xE28693, 0x192F},		// ↓
};

////////////////////////////////////////////////////////////////////////

class Minitel : public Stream
{
public:
#if defined(ESP32) || defined(ARDUINO_ARCH_ESP32)

	Minitel(HardwareSerial& serial);
	Minitel(HardwareSerial& serial, uint8_t, uint8_t);

#elif defined(ARDUINO_ARCH_RP2040)
	// RP2040 overloads the HardwareSerial class, which is onlu used for Serial (i.e. USB)
	// Both UART use the SerialUART class.
	Minitel(SerialUART& serial);
	Minitel(SerialUART& serial, uint8_t, uint8_t);	

#else

	Minitel(HardwareSerial& serial);

#endif

	// Ecrire un octet, un mot ou un code de 4 octets maximum / Lire un octet
	size_t writeWord(word w);
	size_t writeCode(unsigned long code);  // 4 octets maximum

	// methods that are pure virtual into the Stream class.
	size_t write(uint8_t);
	int available();
	int read();
	int peek();

//	size_t write(uint16_t w);
	size_t write(const uint8_t* str, size_t size);
	
	// Identification du type de Minitel
	unsigned long identifyDevice();
	
	// Vitesse de la liaison série
	// A la mise sous tension du Minitel, la vitesse des échanges entre
	// le Minitel et le périphérique est de 1200 bauds par défaut.
	// L'usager du Minitel peut programmer au clavier la vitesse des
	// échanges avec le périphérique quel que soit l'état du terminal
	// grâce aux commandes suivantes :
	// Fnct P + 3 : 300 bauds
	// Fnct P + 1 : 1200 bauds
	// Fnct P + 4 : 4800 bauds
	// Fnct P + 9 : 9600 bauds (pour le Minitel 2 seulement)
	// Attention ! Si le Minitel et le périphérique ne communiquent pas
	// à la même vitesse, on perd la liaison.
	int changeSpeed(int bauds);  // A tout moment, un périphérique peut modifier les vitesses d'échange de la prise (vitesses possibles : 300, 1200, 4800 bauds ; également 9600 bauds pour le Minitel 2).
	int currentSpeed();  // Pour connaitre la vitesse d'échange en cours, le Minitel et le périphérique échangeant à la même vitesse.
	int searchSpeed();  // Pour connaitre la vitesse du Minitel, le Minitel et le périphérique n'échangeant pas nécessairement à la même vitesse.
	
	// Séparateurs
	void newScreen();  // Attention ! newScreen réinitialise les attributs de visualisation.
	void newXY(int x, int y);  // Attention ! newXY réinitialise les attributs de visualisation.
	
	// Curseur
	void cursor();  // Curseur visible
	void noCursor();  // Curseur invisible
	void moveCursorXY(int x, int y);  // Adressage direct du curseur en colonne x et rangée y.
	void moveCursorLeft(int n);  // Curseur vers la gauche de n colonnes. Arrêt au bord gauche de l'écran.
	void moveCursorRight(int n);  // Curseur vers la droite de n colonnes. Arrêt au bord droit de l'écran.
	void moveCursorDown(int n);  // Curseur vers le bas de n rangées. Arrêt en bas de l'écran.
	void moveCursorUp(int n);  // Curseur vers le haut de n rangées. Arrêt en haut de l'écran.
	void moveCursorReturn(int n);  // Retour du curseur au début de la rangée courante puis curseur vers le bas de n rangées. Arrêt en bas de l'écran.
	int getCursorX();  // Colonne où se trouve le curseur
	int getCursorY();  // Rangée où se trouve le curseur
	
	// Effacements, Suppressions, Insertions
	void cancel();  // Remplissage à partir de la position courante du curseur et jusqu'à la fin de la rangée par des espaces du jeu courant ayant l'état courant des attributs. Le position courante du curseur n'est pas déplacée.
	void clearScreenFromCursor();  // Effacement depuis le curseur inclus jusqu'à la fin de l'écran.
	void clearScreenToCursor();  // Effacement depuis le début de l'écran jusqu'au curseur inclus.
	void clearScreen();  // Effacement de tout l'écran (la position du curseur n'est pas modifiée).
	void clearLineFromCursor();  // Effacement depuis le curseur inclus jusqu'à la fin de la rangée.
	void clearLineToCursor();  // Effacement depuis le début de la rangée jusqu'au curseur inclus.
	void clearLine();  // Effacement total de la rangée où est le curseur.
	void deleteChars(int n);  // Suppression de n caractères en commençant à la position curseur incluse.
	void insertChars(int n);  // Insertion de n caractères en commençant à la position curseur incluse (modèle RTIC uniquement, pas le MATRA ou le TELIC).
	void startInsert();  // Début du mode insertion de caractères.
	void stopInsert();  // Fin du mode insertion de caractères.
	void deleteLines(int n);  // Suppression de n rangées à partir de celle où est le curseur.
	void insertLines(int n);  // Insertion de n rangées à partir de celle où est le curseur.
	
	// Modes du standard Télétel
	void textMode();      // Accès au jeu G0 - Mode Vidéotex 40 colonnes (par défaut à la mise sous tension du Minitel)
	void graphicMode();   // Accès au jeu G1 - Mode Vidéotex 40 colonnes
	byte pageMode();      // Mode page
	byte scrollMode();    // Mode rouleau
	byte modeMixte();     // Mode Vidéotex => Mode Mixte 80 colonnes (Aucun caractère semi-graphique (jeu G1) n'est visualisable)
	byte modeVideotex();  // Mode Mixte => Mode Vidéotex 40 colonnes

	// Standards
	byte standardTeleinformatique();  // Standard Télétel => Standard Téléinformatique 80 colonnes (Possibilités de programmation moins étendues)
	byte standardTeletel();           // Standard Téléinformatique => Standard Télétel (inclut les modes Vidéotex et Mixte)

	// Contenu
	void attributs(byte attribut);

	void printChar(char caractere);  // Caractère du jeu G0 exceptés ceux codés 0x60, 0x7E, 0x7F.
	void printSpecialChar(byte b);  // Caractère du jeu G2. Voir plus haut, au niveau de 1.2.3, les constantes possibles.
//	byte getCharByte(char caractere);
	String getString(unsigned long code);  // Unicode => UTF-8
	int getNbBytes(unsigned long code);  // À utiliser en association avec getString(unsigned long code) juste ci-dessus.
	void graphic(byte b, int x, int y);  // Jeu G1. Voir page 101. Sous la forme 0b000000 à 0b111111 en allant du coin supérieur gauche au coin inférieur droit. En colonne x et rangée y.
	void graphic(byte b);  // Voir la ligne ci-dessus.
	void repeat(int n);  // Permet de répéter le dernier caractère visualisé avec les attributs courants de la position active d'écriture.
	void bip();  // Bip sonore
	
	// Géométrie
	void rect(int x1, int y1, int x2, int y2);  // Rectangle défini par 2 points.
	void hLine(int x1, int y, int x2, int position);  // Ligne horizontale. position = TOP, CENTER ou BOTTOM.
	void vLine(int x, int y1, int y2, int position, int sens);  // Ligne verticale. position = LEFT, CENTER ou RIGHT. sens = DOWN ou UP.
	
	// Clavier
	unsigned long getKeyCode(bool unicode = true);  // Codes Minitel => Unicode par défaut (si false : pas de conversion)
	byte smallMode();  // Mode minuscules du clavier
	byte capitalMode();  // Mode majuscules du clavier
	byte extendedKeyboard();  // Clavier étendu
	byte standardKeyboard();  // Clavier standard
	byte echo(boolean commande);  // Active ou désactive l'écho à l'écran de ce qui est tapé au clavier
	
	// Protocole
	byte aiguillage(boolean commande, byte emetteur, byte recepteur);
	byte statusAiguillage(byte module);
	byte connexion(boolean commande);
	byte reset();

	static uint32_t getUTFReplacement(uint32_t code);
	
private:
#if defined(ARDUINO_ARCH_RP2040)
	SerialUART& mySerial;
#else
	HardwareSerial& mySerial; 
#endif

	uint8_t rx_pin;
	uint8_t tx_pin;
	
	byte currentSize = GRANDEUR_NORMALE;
	boolean isValidChar(byte index);
	// boolean isDiacritic(unsigned char caractere);  // Obsolète depuis le 26/02/2023
	boolean isVisualisable(unsigned long code);
	void writeBytesP(int n);  // Pn, Pr, Pc
	
	// Protocole
	void writeBytesPRO(int n);  // PRO1, PRO2 ou PRO3
	unsigned long identificationBytes();
	int workingSpeed();
	byte workingStandard(unsigned long sequence);
	byte workingMode();
	byte workingKeyboard();
	byte workingAiguillage(byte module);
	byte workingModem();
	
	unsigned long getCursorXY();
};

////////////////////////////////////////////////////////////////////////

#endif // Fin Si (MINITEL1B_H)
