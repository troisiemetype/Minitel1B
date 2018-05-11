# Minitel1B_Hard
<b>Minitel Library for Arduino (with HardwareSerial)</b>

Documentation utilisée : Spécifications Techniques d'Utilisation du Minitel 1B<br>
http://543210.free.fr/TV/stum1b.pdf

<b>Historique</b> :

11/05/2018 - Modifications des fonctions<br>
void printDiacriticChar(unsigned char caractere)<br>
boolean isDiacritic(unsigned char caractere)<br>
pour tenir compte de la remarque de Boris sur les caractères diacritiques majuscules.

18/06/2017 - Exemple Tweet_3615.ino<br>

15/06/2017 - 2 nouvelles fonctions qui donnent la position du curseur : <br>
int getCursorX()<br>
int getCursorY()<br>

06/06/2017 - Exemple d'utilisation du clavier et d'affichage d'une image :<br>
Couleurs_3615.ino<br>

06/06/2017 - 2 nouvelles fonctions graphiques :<br>
void graphic(byte b, int x, int y)<br>
void graphic(byte b)<br>

12/03/2016 - Début de la version HardwareSerial de Minitel1B sur GitHub<br>
