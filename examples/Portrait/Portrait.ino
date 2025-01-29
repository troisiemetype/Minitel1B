////////////////////////////////////////////////////////////////////////
/*
   Portrait - Version du 17 mars 2023 à 14h50
   Copyright 2017-2023 - Eric Sérandour
   https://entropie.org/3615/
   
   Attention : Ce programme fonctionne bien sur un ATMega 1284P.
   Sur un microcontrôleur qui dispose de moins de mémoire,
   il pourrait ne pas fonctionner correctement.
   
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
   
////////////////////////////////////////////////////////////////////////
  DEBUT DU PROGRAMME (Compile sous Arduino 1.8.19)
*///////////////////////////////////////////////////////////////////////

#include <Minitel1B_Hard.h>  // Voir https://github.com/eserandour/Minitel1B_Hard

#if defined(ESP32) || defined(ARDUINO_ARCH_ESP32)  // Pour ESP32
// Le troisième port série matériel de l'ESP32 (Serial2 / U2RXD U2TXD)
// est utilisé pour la connexion avec le Minitel.
Minitel minitel(Serial2, 16, 17);
#else  // Pour ATmega 1284P ou ATmega 2560 notamment
// Le deuxième port série matériel de l'ATMega (Serial1 / RXD1 TXD1)
// est utilisé pour la connexion avec le Minitel.
Minitel minitel(Serial1);
#endif

////////////////////////////////////////////////////////////////////////

// #include <avr/pgmspace.h> // Devenu inutile
typedef unsigned char PROGMEM prog_uchar;
// Voir https://github.com/eserandour/Conversion_Videotex_Hex
const int LONGUEUR_TRAME_PORTRAIT = 4802;
const prog_uchar PORTRAIT[] PROGMEM = {0x0C,0x0E,0x1B,0x42,0x1B,0x56,0x37,0x1B,0x46,0x1B,0x56,0x37,0x1B,0x46,0x1B,0x56,0x27,0x1B,0x46,0x1B,0x56,0x27,0x1B,0x46,0x1B,0x56,0x37,0x1B,0x46,0x1B,0x56,0x27,0x1B,0x46,0x1B,0x56,0x27,0x1B,0x46,0x1B,0x56,0x37,0x1B,0x46,0x1B,0x53,0x3F,0x1B,0x43,0x1B,0x53,0x3F,0x1B,0x43,0x1B,0x53,0x2B,0x1B,0x43,0x1B,0x53,0x23,0x1B,0x43,0x1B,0x53,0x67,0x1B,0x46,0x1B,0x53,0x68,0x1B,0x41,0x1B,0x56,0x7C,0x1B,0x41,0x1B,0x55,0x3F,0x1B,0x41,0x1B,0x55,0x6F,0x1B,0x41,0x1B,0x55,0x3F,0x1B,0x41,0x1B,0x51,0x2F,0x1B,0x41,0x1B,0x52,0x3F,0x1B,0x41,0x1B,0x52,0x27,0x1B,0x41,0x1B,0x52,0x2B,0x1B,0x41,0x1B,0x56,0x2F,0x1B,0x41,0x1B,0x56,0x2B,0x1B,0x41,0x1B,0x52,0x2F,0x1B,0x41,0x1B,0x56,0x7F,0x1B,0x45,0x1B,0x56,0x30,0x1B,0x46,0x1B,0x56,0x6B,0x1B,0x46,0x1B,0x56,0x23,0x1B,0x46,0x1B,0x56,0x6B,0x1B,0x46,0x1B,0x56,0x2B,0x1B,0x46,0x1B,0x56,0x6B,0x1B,0x46,0x1B,0x56,0x68,0x1B,0x46,0x1B,0x56,0x68,0x1B,0x46,0x1B,0x56,0x6B,0x1B,0x46,0x1B,0x56,0x2B,0x1B,0x42,0x1B,0x56,0x2B,0x1B,0x42,0x1B,0x52,0x28,0x1B,0x42,0x1B,0x52,0x6B,0x1B,0x42,0x1B,0x52,0x6B,0x1B,0x46,0x1B,0x56,0x27,0x1B,0x46,0x1B,0x56,0x37,0x1B,0x46,0x1B,0x56,0x37,0x1B,0x46,0x1B,0x56,0x27,0x1B,0x46,0x1B,0x56,0x37,0x1B,0x46,0x1B,0x56,0x77,0x1B,0x46,0x1B,0x56,0x37,0x1B,0x46,0x1B,0x56,0x77,0x1B,0x46,0x1B,0x53,0x37,0x1B,0x43,0x1B,0x53,0x77,0x1B,0x43,0x1B,0x53,0x33,0x1B,0x43,0x1B,0x53,0x3F,0x1B,0x43,0x1B,0x53,0x3F,0x1B,0x41,0x1B,0x53,0x68,0x1B,0x41,0x1B,0x55,0x37,0x1B,0x45,0x1B,0x52,0x27,0x1B,0x45,0x1B,0x56,0x2B,0x1B,0x45,0x1B,0x53,0x23,0x1B,0x45,0x1B,0x53,0x23,0x1B,0x42,0x1B,0x56,0x23,0x1B,0x42,0x1B,0x56,0x23,0x1B,0x42,0x1B,0x56,0x23,0x1B,0x46,0x1B,0x56,0x60,0x1B,0x42,0x1B,0x56,0x78,0x1B,0x45,0x1B,0x52,0x68,0x1B,0x41,0x1B,0x52,0x28,0x1B,0x41,0x1B,0x52,0x7F,0x1B,0x46,0x1B,0x56,0x30,0x1B,0x46,0x1B,0x56,0x68,0x1B,0x46,0x1B,0x56,0x68,0x1B,0x46,0x1B,0x56,0x6C,0x1B,0x46,0x1B,0x56,0x68,0x1B,0x46,0x1B,0x56,0x6B,0x1B,0x46,0x1B,0x56,0x68,0x1B,0x46,0x1B,0x56,0x68,0x1B,0x46,0x1B,0x56,0x68,0x1B,0x46,0x1B,0x56,0x68,0x1B,0x42,0x1B,0x56,0x68,0x1B,0x42,0x1B,0x52,0x68,0x1B,0x42,0x1B,0x52,0x28,0x1B,0x46,0x1B,0x56,0x37,0x1B,0x46,0x1B,0x56,0x37,0x1B,0x46,0x1B,0x56,0x37,0x1B,0x46,0x1B,0x56,0x3F,0x1B,0x46,0x1B,0x56,0x77,0x1B,0x46,0x1B,0x56,0x37,0x1B,0x46,0x1B,0x56,0x23,0x1B,0x46,0x1B,0x56,0x23,0x1B,0x46,0x1B,0x53,0x7F,0x1B,0x43,0x1B,0x53,0x37,0x1B,0x43,0x1B,0x53,0x37,0x1B,0x43,0x1B,0x53,0x77,0x1B,0x43,0x1B,0x53,0x7F,0x1B,0x41,0x1B,0x52,0x68,0x1B,0x45,0x1B,0x52,0x37,0x1B,0x42,0x1B,0x56,0x23,0x1B,0x46,0x1B,0x56,0x3F,0x1B,0x46,0x1B,0x56,0x3F,0x1B,0x46,0x1B,0x53,0x2F,0x1B,0x46,0x1B,0x53,0x2B,0x1B,0x46,0x1B,0x56,0x27,0x1B,0x46,0x1B,0x56,0x2B,0x1B,0x46,0x1B,0x56,0x28,0x1B,0x42,0x1B,0x56,0x28,0x1B,0x42,0x1B,0x52,0x6B,0x1B,0x45,0x1B,0x52,0x68,0x1B,0x41,0x1B,0x55,0x68,0x1B,0x45,0x1B,0x56,0x37,0x1B,0x46,0x1B,0x56,0x6F,0x1B,0x46,0x1B,0x56,0x6F,0x1B,0x46,0x1B,0x56,0x28,0x1B,0x46,0x1B,0x56,0x6F,0x1B,0x46,0x1B,0x56,0x68,0x1B,0x46,0x1B,0x56,0x7B,0x1B,0x46,0x1B,0x56,0x68,0x1B,0x46,0x1B,0x56,0x68,0x1B,0x46,0x1B,0x56,0x68,0x1B,0x42,0x1B,0x56,0x68,0x1B,0x42,0x1B,0x52,0x6B,0x1B,0x42,0x1B,0x52,0x6B,0x1B,0x46,0x1B,0x56,0x37,0x1B,0x46,0x1B,0x56,0x37,0x1B,0x46,0x1B,0x56,0x37,0x1B,0x46,0x1B,0x56,0x3F,0x1B,0x46,0x1B,0x56,0x7F,0x1B,0x46,0x1B,0x56,0x3F,0x1B,0x46,0x1B,0x56,0x37,0x1B,0x46,0x1B,0x56,0x74,0x1B,0x46,0x1B,0x53,0x7F,0x1B,0x43,0x1B,0x53,0x77,0x1B,0x43,0x1B,0x53,0x7F,0x1B,0x43,0x1B,0x53,0x7C,0x1B,0x43,0x1B,0x53,0x68,0x1B,0x45,0x1B,0x55,0x74,0x1B,0x42,0x1B,0x52,0x37,0x1B,0x46,0x1B,0x56,0x37,0x1B,0x46,0x1B,0x56,0x37,0x1B,0x46,0x1B,0x56,0x77,0x1B,0x46,0x1B,0x53,0x70,0x1B,0x46,0x1B,0x53,0x78,0x1B,0x46,0x1B,0x56,0x30,0x1B,0x46,0x1B,0x56,0x70,0x1B,0x46,0x1B,0x56,0x70,0x1B,0x42,0x1B,0x56,0x78,0x1B,0x42,0x1B,0x52,0x28,0x1B,0x42,0x1B,0x52,0x6B,0x1B,0x41,0x1B,0x55,0x68,0x1B,0x41,0x1B,0x56,0x37,0x1B,0x46,0x1B,0x56,0x68,0x1B,0x46,0x1B,0x56,0x28,0x1B,0x46,0x1B,0x56,0x20,0x1B,0x46,0x1B,0x56,0x7B,0x1B,0x46,0x1B,0x56,0x28,0x1B,0x46,0x1B,0x56,0x6F,0x1B,0x46,0x1B,0x56,0x68,0x1B,0x46,0x1B,0x56,0x68,0x1B,0x46,0x1B,0x56,0x28,0x1B,0x46,0x1B,0x56,0x6F,0x1B,0x42,0x1B,0x56,0x6B,0x1B,0x42,0x1B,0x52,0x68,0x1B,0x46,0x1B,0x56,0x37,0x1B,0x46,0x1B,0x56,0x37,0x1B,0x46,0x1B,0x56,0x37,0x1B,0x46,0x1B,0x56,0x77,0x1B,0x46,0x1B,0x56,0x77,0x1B,0x46,0x1B,0x56,0x37,0x1B,0x46,0x1B,0x56,0x37,0x1B,0x46,0x1B,0x56,0x30,0x1B,0x46,0x1B,0x53,0x77,0x1B,0x43,0x1B,0x53,0x37,0x1B,0x43,0x1B,0x53,0x33,0x1B,0x43,0x1B,0x53,0x77,0x1B,0x46,0x1B,0x53,0x28,0x1B,0x41,0x1B,0x55,0x27,0x1B,0x42,0x1B,0x56,0x37,0x1B,0x46,0x1B,0x56,0x77,0x1B,0x42,0x1B,0x56,0x70,0x1B,0x45,0x1B,0x56,0x70,0x1B,0x45,0x1B,0x56,0x70,0x1B,0x45,0x1B,0x56,0x70,0x1B,0x42,0x1B,0x56,0x74,0x1B,0x45,0x1B,0x56,0x70,0x1B,0x41,0x1B,0x56,0x70,0x1B,0x41,0x1B,0x52,0x7C,0x1B,0x41,0x1B,0x52,0x7C,0x1B,0x41,0x1B,0x52,0x70,0x1B,0x45,0x1B,0x55,0x78,0x1B,0x41,0x1B,0x56,0x37,0x1B,0x46,0x1B,0x56,0x6B,0x1B,0x46,0x1B,0x56,0x7C,0x1B,0x46,0x1B,0x56,0x68,0x1B,0x46,0x1B,0x56,0x6C,0x1B,0x46,0x1B,0x56,0x68,0x1B,0x46,0x1B,0x56,0x68,0x1B,0x46,0x1B,0x56,0x6B,0x1B,0x46,0x1B,0x56,0x68,0x1B,0x46,0x1B,0x56,0x68,0x1B,0x46,0x1B,0x56,0x68,0x1B,0x42,0x1B,0x56,0x68,0x1B,0x42,0x1B,0x52,0x68,0x1B,0x46,0x1B,0x56,0x37,0x1B,0x46,0x1B,0x56,0x37,0x1B,0x46,0x1B,0x56,0x77,0x1B,0x46,0x1B,0x56,0x77,0x1B,0x46,0x1B,0x56,0x3F,0x1B,0x46,0x1B,0x56,0x37,0x1B,0x46,0x1B,0x56,0x7F,0x1B,0x46,0x1B,0x56,0x77,0x1B,0x46,0x1B,0x56,0x27,0x1B,0x43,0x1B,0x53,0x77,0x1B,0x43,0x1B,0x53,0x7F,0x1B,0x43,0x1B,0x53,0x3C,0x1B,0x43,0x1B,0x53,0x37,0x1B,0x45,0x1B,0x56,0x6F,0x1B,0x42,0x1B,0x52,0x70,0x1B,0x41,0x1B,0x52,0x7C,0x1B,0x41,0x1B,0x55,0x7C,0x1B,0x41,0x1B,0x51,0x7C,0x1B,0x41,0x1B,0x51,0x70,0x1B,0x41,0x1B,0x51,0x77,0x1B,0x42,0x1B,0x56,0x37,0x1B,0x41,0x1B,0x56,0x6B,0x1B,0x44,0x1B,0x51,0x78,0x1B,0x44,0x1B,0x51,0x6C,0x1B,0x44,0x1B,0x51,0x74,0x1B,0x41,0x1B,0x51,0x33,0x1B,0x41,0x1B,0x55,0x37,0x1B,0x41,0x1B,0x56,0x37,0x1B,0x46,0x1B,0x56,0x68,0x1B,0x46,0x1B,0x56,0x78,0x1B,0x46,0x1B,0x56,0x78,0x1B,0x46,0x1B,0x56,0x68,0x1B,0x46,0x1B,0x56,0x68,0x1B,0x46,0x1B,0x56,0x7C,0x1B,0x46,0x1B,0x56,0x6F,0x1B,0x46,0x1B,0x56,0x68,0x1B,0x46,0x1B,0x56,0x68,0x1B,0x46,0x1B,0x56,0x68,0x1B,0x42,0x1B,0x56,0x68,0x1B,0x42,0x1B,0x52,0x68,0x1B,0x46,0x1B,0x56,0x3F,0x1B,0x46,0x1B,0x56,0x37,0x1B,0x46,0x1B,0x56,0x77,0x1B,0x46,0x1B,0x56,0x37,0x1B,0x46,0x1B,0x56,0x37,0x1B,0x46,0x1B,0x56,0x7F,0x1B,0x46,0x1B,0x56,0x3F,0x1B,0x46,0x1B,0x56,0x34,0x1B,0x46,0x1B,0x53,0x7F,0x1B,0x46,0x1B,0x53,0x7F,0x1B,0x43,0x1B,0x53,0x74,0x1B,0x43,0x1B,0x53,0x7F,0x1B,0x46,0x1B,0x53,0x7C,0x1B,0x45,0x1B,0x53,0x68,0x1B,0x45,0x1B,0x52,0x28,0x1B,0x45,0x1B,0x55,0x6B,0x1B,0x41,0x1B,0x55,0x2F,0x1B,0x44,0x1B,0x55,0x2F,0x1B,0x41,0x1B,0x52,0x2F,0x1B,0x41,0x1B,0x52,0x27,0x1B,0x42,0x1B,0x56,0x37,0x1B,0x45,0x1B,0x56,0x68,0x1B,0x41,0x1B,0x55,0x2F,0x1B,0x41,0x1B,0x52,0x27,0x1B,0x41,0x1B,0x52,0x23,0x1B,0x41,0x1B,0x52,0x2F,0x1B,0x41,0x1B,0x52,0x2F,0x1B,0x45,0x1B,0x56,0x77,0x1B,0x45,0x1B,0x56,0x30,0x1B,0x46,0x1B,0x56,0x78,0x1B,0x46,0x1B,0x56,0x7B,0x1B,0x46,0x1B,0x56,0x68,0x1B,0x46,0x1B,0x56,0x68,0x1B,0x46,0x1B,0x56,0x68,0x1B,0x46,0x1B,0x56,0x6F,0x1B,0x46,0x1B,0x56,0x6B,0x1B,0x46,0x1B,0x56,0x68,0x1B,0x46,0x1B,0x56,0x68,0x1B,0x42,0x1B,0x56,0x68,0x1B,0x42,0x1B,0x52,0x68,0x1B,0x46,0x1B,0x56,0x77,0x1B,0x46,0x1B,0x56,0x77,0x1B,0x46,0x1B,0x56,0x3C,0x1B,0x46,0x1B,0x56,0x74,0x1B,0x46,0x1B,0x56,0x7F,0x1B,0x46,0x1B,0x56,0x77,0x1B,0x46,0x1B,0x56,0x7B,0x1B,0x46,0x1B,0x56,0x37,0x1B,0x46,0x1B,0x56,0x34,0x1B,0x46,0x1B,0x53,0x7F,0x1B,0x46,0x1B,0x53,0x30,0x1B,0x43,0x1B,0x53,0x77,0x1B,0x46,0x1B,0x53,0x68,0x1B,0x42,0x1B,0x56,0x78,0x1B,0x42,0x1B,0x56,0x37,0x1B,0x42,0x1B,0x56,0x23,0x1B,0x42,0x1B,0x56,0x23,0x1B,0x42,0x1B,0x56,0x23,0x1B,0x42,0x1B,0x56,0x23,0x1B,0x42,0x1B,0x56,0x2B,0x1B,0x42,0x1B,0x56,0x37,0x1B,0x42,0x1B,0x56,0x28,0x1B,0x45,0x1B,0x52,0x27,0x1B,0x42,0x1B,0x52,0x2F,0x1B,0x42,0x1B,0x56,0x2F,0x1B,0x42,0x1B,0x56,0x63,0x1B,0x42,0x1B,0x52,0x68,0x1B,0x41,0x1B,0x55,0x68,0x1B,0x45,0x1B,0x56,0x37,0x1B,0x46,0x1B,0x56,0x78,0x1B,0x46,0x1B,0x56,0x68,0x1B,0x46,0x1B,0x56,0x68,0x1B,0x46,0x1B,0x56,0x68,0x1B,0x46,0x1B,0x56,0x78,0x1B,0x46,0x1B,0x56,0x78,0x1B,0x46,0x1B,0x56,0x78,0x1B,0x46,0x1B,0x56,0x68,0x1B,0x46,0x1B,0x56,0x68,0x1B,0x42,0x1B,0x56,0x68,0x1B,0x42,0x1B,0x52,0x68,0x1B,0x46,0x1B,0x56,0x77,0x1B,0x46,0x1B,0x56,0x37,0x1B,0x46,0x1B,0x56,0x77,0x1B,0x46,0x1B,0x56,0x37,0x1B,0x46,0x1B,0x56,0x77,0x1B,0x46,0x1B,0x56,0x37,0x1B,0x46,0x1B,0x56,0x37,0x1B,0x46,0x1B,0x56,0x27,0x1B,0x46,0x1B,0x56,0x37,0x1B,0x46,0x1B,0x56,0x37,0x1B,0x43,0x1B,0x53,0x3F,0x1B,0x43,0x1B,0x53,0x77,0x1B,0x46,0x1B,0x53,0x78,0x1B,0x45,0x1B,0x56,0x6B,0x1B,0x42,0x1B,0x56,0x34,0x1B,0x46,0x1B,0x56,0x70,0x1B,0x46,0x1B,0x56,0x70,0x1B,0x46,0x1B,0x56,0x6B,0x1B,0x46,0x1B,0x56,0x68,0x1B,0x42,0x1B,0x56,0x78,0x1B,0x42,0x1B,0x56,0x70,0x1B,0x42,0x1B,0x56,0x70,0x1B,0x45,0x1B,0x52,0x70,0x1B,0x42,0x1B,0x52,0x37,0x1B,0x42,0x1B,0x56,0x70,0x1B,0x42,0x1B,0x56,0x78,0x1B,0x45,0x1B,0x52,0x78,0x1B,0x41,0x1B,0x55,0x68,0x1B,0x42,0x1B,0x56,0x37,0x1B,0x46,0x1B,0x56,0x68,0x1B,0x46,0x1B,0x56,0x7C,0x1B,0x46,0x1B,0x56,0x78,0x1B,0x46,0x1B,0x56,0x6C,0x1B,0x46,0x1B,0x56,0x78,0x1B,0x46,0x1B,0x56,0x6B,0x1B,0x46,0x1B,0x56,0x68,0x1B,0x46,0x1B,0x56,0x68,0x1B,0x46,0x1B,0x56,0x68,0x1B,0x42,0x1B,0x56,0x78,0x1B,0x42,0x1B,0x52,0x68,0x1B,0x46,0x1B,0x56,0x7F,0x1B,0x46,0x1B,0x56,0x34,0x1B,0x46,0x1B,0x56,0x77,0x1B,0x46,0x1B,0x56,0x77,0x1B,0x46,0x1B,0x56,0x7F,0x1B,0x46,0x1B,0x56,0x77,0x1B,0x46,0x1B,0x56,0x3F,0x1B,0x46,0x1B,0x56,0x7F,0x1B,0x46,0x1B,0x56,0x70,0x1B,0x46,0x1B,0x56,0x77,0x1B,0x46,0x1B,0x53,0x74,0x1B,0x46,0x1B,0x53,0x70,0x1B,0x46,0x1B,0x53,0x23,0x1B,0x42,0x1B,0x53,0x28,0x1B,0x45,0x1B,0x52,0x6F,0x1B,0x42,0x1B,0x52,0x77,0x1B,0x42,0x1B,0x56,0x74,0x1B,0x46,0x1B,0x56,0x74,0x1B,0x46,0x1B,0x56,0x28,0x1B,0x45,0x1B,0x56,0x68,0x1B,0x41,0x1B,0x55,0x7C,0x1B,0x41,0x1B,0x55,0x7C,0x1B,0x41,0x1B,0x51,0x7C,0x1B,0x45,0x1B,0x52,0x34,0x1B,0x42,0x1B,0x52,0x68,0x1B,0x45,0x1B,0x52,0x68,0x1B,0x45,0x1B,0x55,0x7C,0x1B,0x41,0x1B,0x55,0x23,0x1B,0x42,0x1B,0x56,0x27,0x1B,0x46,0x1B,0x56,0x68,0x1B,0x46,0x1B,0x56,0x68,0x1B,0x46,0x1B,0x56,0x7C,0x1B,0x46,0x1B,0x56,0x78,0x1B,0x46,0x1B,0x56,0x68,0x1B,0x46,0x1B,0x56,0x7C,0x1B,0x46,0x1B,0x56,0x68,0x1B,0x46,0x1B,0x56,0x78,0x1B,0x46,0x1B,0x56,0x7C,0x1B,0x42,0x1B,0x56,0x78,0x1B,0x42,0x1B,0x52,0x68,0x1B,0x46,0x1B,0x56,0x77,0x1B,0x46,0x1B,0x56,0x77,0x1B,0x46,0x1B,0x56,0x37,0x1B,0x46,0x1B,0x56,0x73,0x1B,0x46,0x1B,0x56,0x74,0x1B,0x46,0x1B,0x56,0x3F,0x1B,0x46,0x1B,0x56,0x34,0x1B,0x46,0x1B,0x56,0x30,0x1B,0x46,0x1B,0x56,0x30,0x1B,0x46,0x1B,0x56,0x7F,0x1B,0x46,0x1B,0x56,0x7C,0x1B,0x46,0x1B,0x56,0x7C,0x1B,0x46,0x1B,0x53,0x7F,0x1B,0x46,0x1B,0x53,0x28,0x1B,0x42,0x1B,0x56,0x68,0x1B,0x42,0x1B,0x52,0x37,0x1B,0x42,0x1B,0x52,0x27,0x1B,0x46,0x1B,0x56,0x37,0x1B,0x46,0x1B,0x56,0x73,0x1B,0x42,0x1B,0x56,0x78,0x1B,0x45,0x1B,0x52,0x23,0x1B,0x41,0x1B,0x52,0x23,0x1B,0x41,0x1B,0x52,0x2B,0x1B,0x45,0x1B,0x52,0x37,0x1B,0x42,0x1B,0x52,0x74,0x1B,0x45,0x1B,0x52,0x68,0x1B,0x45,0x1B,0x55,0x6B,0x1B,0x45,0x1B,0x56,0x37,0x1B,0x46,0x1B,0x56,0x23,0x1B,0x46,0x1B,0x56,0x7C,0x1B,0x46,0x1B,0x56,0x78,0x1B,0x46,0x1B,0x56,0x78,0x1B,0x46,0x1B,0x56,0x78,0x1B,0x46,0x1B,0x56,0x68,0x1B,0x46,0x1B,0x56,0x78,0x1B,0x46,0x1B,0x56,0x78,0x1B,0x46,0x1B,0x56,0x78,0x1B,0x42,0x1B,0x56,0x68,0x1B,0x42,0x1B,0x52,0x78,0x1B,0x42,0x1B,0x52,0x78,0x1B,0x46,0x1B,0x56,0x7F,0x1B,0x46,0x1B,0x56,0x74,0x1B,0x46,0x1B,0x56,0x77,0x1B,0x46,0x1B,0x56,0x37,0x1B,0x46,0x1B,0x56,0x77,0x1B,0x46,0x1B,0x56,0x7F,0x1B,0x46,0x1B,0x56,0x77,0x1B,0x46,0x1B,0x56,0x7C,0x1B,0x46,0x1B,0x56,0x30,0x1B,0x46,0x1B,0x56,0x7C,0x1B,0x46,0x1B,0x56,0x7F,0x1B,0x46,0x1B,0x56,0x7F,0x1B,0x46,0x1B,0x56,0x7F,0x1B,0x46,0x1B,0x56,0x74,0x1B,0x42,0x1B,0x56,0x20,0x1B,0x42,0x1B,0x52,0x27,0x1B,0x42,0x1B,0x52,0x74,0x1B,0x42,0x1B,0x52,0x70,0x1B,0x42,0x1B,0x52,0x78,0x1B,0x45,0x1B,0x52,0x70,0x1B,0x41,0x1B,0x52,0x70,0x1B,0x45,0x1B,0x52,0x70,0x1B,0x41,0x1B,0x52,0x70,0x1B,0x41,0x1B,0x55,0x70,0x1B,0x41,0x1B,0x55,0x70,0x1B,0x45,0x1B,0x55,0x34,0x1B,0x45,0x1B,0x55,0x68,0x1B,0x45,0x1B,0x56,0x37,0x1B,0x46,0x1B,0x56,0x70,0x1B,0x46,0x1B,0x56,0x70,0x1B,0x46,0x1B,0x56,0x78,0x1B,0x46,0x1B,0x56,0x68,0x1B,0x46,0x1B,0x56,0x60,0x1B,0x46,0x1B,0x56,0x78,0x1B,0x46,0x1B,0x56,0x78,0x1B,0x46,0x1B,0x56,0x78,0x1B,0x46,0x1B,0x56,0x78,0x1B,0x42,0x1B,0x56,0x68,0x1B,0x42,0x1B,0x52,0x68,0x1B,0x42,0x1B,0x52,0x78,0x1B,0x46,0x1B,0x56,0x70,0x1B,0x46,0x1B,0x56,0x3F,0x1B,0x46,0x1B,0x56,0x77,0x1B,0x46,0x1B,0x56,0x7F,0x1B,0x46,0x1B,0x56,0x77,0x1B,0x46,0x1B,0x56,0x77,0x1B,0x46,0x1B,0x56,0x74,0x1B,0x46,0x1B,0x56,0x77,0x1B,0x46,0x1B,0x56,0x77,0x1B,0x46,0x1B,0x56,0x7C,0x1B,0x46,0x1B,0x56,0x7F,0x1B,0x46,0x1B,0x56,0x70,0x1B,0x46,0x1B,0x56,0x70,0x1B,0x46,0x1B,0x56,0x70,0x1B,0x46,0x1B,0x56,0x70,0x1B,0x45,0x1B,0x56,0x6B,0x1B,0x45,0x1B,0x52,0x74,0x1B,0x45,0x1B,0x52,0x68,0x1B,0x41,0x1B,0x52,0x2C,0x1B,0x41,0x1B,0x52,0x23,0x1B,0x45,0x1B,0x52,0x73,0x1B,0x45,0x1B,0x52,0x23,0x1B,0x45,0x1B,0x52,0x73,0x1B,0x41,0x1B,0x55,0x70,0x1B,0x41,0x1B,0x55,0x23,0x1B,0x41,0x1B,0x55,0x70,0x1B,0x41,0x1B,0x55,0x3C,0x1B,0x42,0x1B,0x56,0x23,0x1B,0x46,0x1B,0x56,0x7C,0x1B,0x46,0x1B,0x56,0x78,0x1B,0x46,0x1B,0x56,0x60,0x1B,0x46,0x1B,0x56,0x68,0x1B,0x46,0x1B,0x56,0x60,0x1B,0x46,0x1B,0x56,0x68,0x1B,0x46,0x1B,0x56,0x68,0x1B,0x46,0x1B,0x56,0x68,0x1B,0x46,0x1B,0x56,0x68,0x1B,0x42,0x1B,0x56,0x78,0x1B,0x42,0x1B,0x52,0x68,0x1B,0x42,0x1B,0x52,0x68,0x1B,0x46,0x1B,0x56,0x37,0x1B,0x46,0x1B,0x56,0x77,0x1B,0x46,0x1B,0x56,0x70,0x1B,0x46,0x1B,0x56,0x77,0x1B,0x46,0x1B,0x56,0x77,0x1B,0x46,0x1B,0x56,0x74,0x1B,0x46,0x1B,0x56,0x78,0x1B,0x46,0x1B,0x56,0x7F,0x1B,0x46,0x1B,0x56,0x74,0x1B,0x46,0x1B,0x56,0x74,0x1B,0x46,0x1B,0x56,0x60,0x1B,0x46,0x1B,0x56,0x74,0x1B,0x46,0x1B,0x56,0x7C,0x1B,0x46,0x1B,0x56,0x7F,0x1B,0x46,0x1B,0x56,0x70,0x1B,0x41,0x1B,0x56,0x68,0x1B,0x41,0x1B,0x55,0x30,0x1B,0x41,0x1B,0x55,0x74,0x1B,0x45,0x1B,0x52,0x7C,0x1B,0x45,0x1B,0x55,0x7C,0x1B,0x41,0x1B,0x55,0x2F,0x1B,0x41,0x1B,0x55,0x2F,0x1B,0x41,0x1B,0x55,0x2F,0x1B,0x41,0x1B,0x55,0x2F,0x1B,0x41,0x1B,0x55,0x2F,0x1B,0x41,0x1B,0x51,0x7C,0x1B,0x44,0x1B,0x55,0x7C,0x1B,0x44,0x1B,0x56,0x34,0x1B,0x46,0x1B,0x56,0x7C,0x1B,0x46,0x1B,0x56,0x78,0x1B,0x46,0x1B,0x56,0x68,0x1B,0x46,0x1B,0x56,0x60,0x1B,0x46,0x1B,0x56,0x78,0x1B,0x46,0x1B,0x56,0x78,0x1B,0x46,0x1B,0x56,0x78,0x1B,0x46,0x1B,0x56,0x78,0x1B,0x42,0x1B,0x56,0x68,0x1B,0x42,0x1B,0x52,0x68,0x1B,0x42,0x1B,0x52,0x68,0x1B,0x42,0x1B,0x52,0x78,0x1B,0x46,0x1B,0x56,0x3F,0x1B,0x46,0x1B,0x56,0x37,0x1B,0x46,0x1B,0x56,0x77,0x1B,0x46,0x1B,0x56,0x70,0x1B,0x46,0x1B,0x56,0x33,0x1B,0x46,0x1B,0x56,0x77,0x1B,0x46,0x1B,0x56,0x7F,0x1B,0x46,0x1B,0x56,0x7F,0x1B,0x46,0x1B,0x56,0x74,0x1B,0x46,0x1B,0x56,0x7C,0x1B,0x46,0x1B,0x56,0x7C,0x1B,0x46,0x1B,0x56,0x77,0x1B,0x46,0x1B,0x56,0x74,0x1B,0x46,0x1B,0x56,0x70,0x1B,0x46,0x1B,0x56,0x7C,0x1B,0x41,0x1B,0x55,0x78,0x1B,0x44,0x1B,0x51,0x7F,0x1B,0x44,0x1B,0x55,0x74,0x1B,0x41,0x1B,0x55,0x74,0x1B,0x45,0x1B,0x52,0x23,0x1B,0x45,0x1B,0x52,0x70,0x1B,0x45,0x1B,0x52,0x70,0x1B,0x41,0x1B,0x52,0x78,0x1B,0x45,0x1B,0x55,0x74,0x1B,0x41,0x1B,0x55,0x78,0x1B,0x41,0x1B,0x51,0x34,0x1B,0x44,0x1B,0x54,0x68,0x1B,0x44,0x1B,0x51,0x7F,0x1B,0x45,0x1B,0x56,0x30,0x1B,0x46,0x1B,0x56,0x7C,0x1B,0x46,0x1B,0x56,0x7C,0x1B,0x46,0x1B,0x56,0x78,0x1B,0x46,0x1B,0x56,0x78,0x1B,0x46,0x1B,0x56,0x78,0x1B,0x46,0x1B,0x56,0x7C,0x1B,0x46,0x1B,0x56,0x68,0x1B,0x42,0x1B,0x56,0x68,0x1B,0x42,0x1B,0x52,0x78,0x1B,0x42,0x1B,0x52,0x68,0x1B,0x42,0x1B,0x52,0x68,0x1B,0x46,0x1B,0x56,0x77,0x1B,0x46,0x1B,0x56,0x7F,0x1B,0x46,0x1B,0x56,0x70,0x1B,0x46,0x1B,0x56,0x7C,0x1B,0x46,0x1B,0x56,0x77,0x1B,0x46,0x1B,0x56,0x74,0x1B,0x46,0x1B,0x56,0x74,0x1B,0x46,0x1B,0x56,0x7C,0x1B,0x46,0x1B,0x56,0x7F,0x1B,0x46,0x1B,0x56,0x77,0x1B,0x46,0x1B,0x56,0x7C,0x1B,0x46,0x1B,0x56,0x7F,0x1B,0x46,0x1B,0x56,0x7C,0x1B,0x46,0x1B,0x56,0x74,0x1B,0x46,0x1B,0x56,0x7C,0x1B,0x44,0x1B,0x55,0x6B,0x1B,0x44,0x1B,0x54,0x6F,0x1B,0x44,0x1B,0x54,0x30,0x1B,0x44,0x1B,0x51,0x7F,0x1B,0x44,0x1B,0x55,0x7C,0x1B,0x44,0x1B,0x55,0x70,0x1B,0x41,0x1B,0x55,0x7C,0x1B,0x44,0x1B,0x51,0x7C,0x1B,0x44,0x1B,0x51,0x7C,0x1B,0x44,0x1B,0x51,0x34,0x1B,0x41,0x1B,0x51,0x63,0x1B,0x44,0x1B,0x54,0x7C,0x1B,0x44,0x1B,0x54,0x37,0x1B,0x41,0x1B,0x56,0x37,0x1B,0x46,0x1B,0x56,0x78,0x1B,0x46,0x1B,0x56,0x70,0x1B,0x46,0x1B,0x56,0x78,0x1B,0x46,0x1B,0x56,0x78,0x1B,0x46,0x1B,0x56,0x78,0x1B,0x46,0x1B,0x56,0x68,0x1B,0x42,0x1B,0x56,0x78,0x1B,0x42,0x1B,0x56,0x78,0x1B,0x42,0x1B,0x52,0x78,0x1B,0x42,0x1B,0x52,0x68,0x1B,0x42,0x1B,0x52,0x78,0x1B,0x46,0x1B,0x56,0x30,0x1B,0x46,0x1B,0x56,0x77,0x1B,0x46,0x1B,0x56,0x7F,0x1B,0x46,0x1B,0x56,0x74,0x1B,0x46,0x1B,0x56,0x34,0x1B,0x46,0x1B,0x56,0x30,0x1B,0x46,0x1B,0x56,0x30,0x1B,0x46,0x1B,0x56,0x3F,0x1B,0x46,0x1B,0x56,0x7F,0x1B,0x46,0x1B,0x56,0x74,0x1B,0x46,0x1B,0x56,0x74,0x1B,0x46,0x1B,0x56,0x7C,0x1B,0x46,0x1B,0x56,0x74,0x1B,0x46,0x1B,0x56,0x7C,0x1B,0x45,0x1B,0x56,0x60,0x1B,0x44,0x1B,0x52,0x7C,0x1B,0x44,0x1B,0x51,0x77,0x1B,0x44,0x1B,0x54,0x2B,0x1B,0x44,0x1B,0x54,0x64,0x1B,0x44,0x1B,0x54,0x20,0x1B,0x44,0x1B,0x54,0x2F,0x1B,0x44,0x1B,0x54,0x2F,0x1B,0x44,0x1B,0x54,0x27,0x1B,0x44,0x1B,0x51,0x37,0x1B,0x41,0x1B,0x51,0x78,0x1B,0x44,0x1B,0x51,0x78,0x1B,0x44,0x1B,0x54,0x3F,0x1B,0x44,0x1B,0x51,0x73,0x1B,0x44,0x1B,0x52,0x77,0x1B,0x46,0x1B,0x56,0x78,0x1B,0x46,0x1B,0x56,0x78,0x1B,0x46,0x1B,0x56,0x70,0x1B,0x46,0x1B,0x56,0x78,0x1B,0x46,0x1B,0x56,0x78,0x1B,0x46,0x1B,0x56,0x68,0x1B,0x42,0x1B,0x56,0x78,0x1B,0x42,0x1B,0x52,0x68,0x1B,0x42,0x1B,0x52,0x78,0x1B,0x42,0x1B,0x52,0x78,0x1B,0x42,0x1B,0x52,0x68,0x1B,0x42,0x1B,0x56,0x34,0x1B,0x46,0x1B,0x56,0x34,0x1B,0x46,0x1B,0x56,0x7F,0x1B,0x46,0x1B,0x56,0x77,0x1B,0x46,0x1B,0x56,0x77,0x1B,0x46,0x1B,0x56,0x73,0x1B,0x46,0x1B,0x56,0x7C,0x1B,0x46,0x1B,0x56,0x74,0x1B,0x46,0x1B,0x56,0x77,0x1B,0x46,0x1B,0x56,0x78,0x1B,0x46,0x1B,0x56,0x74,0x1B,0x46,0x1B,0x56,0x7F,0x1B,0x46,0x1B,0x56,0x60,0x1B,0x41,0x1B,0x56,0x70,0x1B,0x44,0x1B,0x52,0x7C,0x1B,0x44,0x1B,0x51,0x28,0x1B,0x44,0x1B,0x54,0x6F,0x1B,0x44,0x1B,0x54,0x74,0x1B,0x44,0x1B,0x54,0x70,0x1B,0x44,0x1B,0x54,0x2B,0x1B,0x44,0x1B,0x54,0x64,0x1B,0x44,0x1B,0x54,0x70,0x1B,0x44,0x1B,0x54,0x7C,0x1B,0x44,0x1B,0x51,0x74,0x1B,0x44,0x1B,0x51,0x7C,0x1B,0x44,0x1B,0x51,0x37,0x1B,0x44,0x1B,0x55,0x6B,0x1B,0x44,0x1B,0x54,0x7C,0x1B,0x44,0x1B,0x51,0x7F,0x1B,0x45,0x1B,0x56,0x30,0x1B,0x46,0x1B,0x56,0x70,0x1B,0x46,0x1B,0x56,0x7C,0x1B,0x46,0x1B,0x56,0x70,0x1B,0x46,0x1B,0x56,0x7C,0x1B,0x42,0x1B,0x56,0x78,0x1B,0x42,0x1B,0x52,0x78,0x1B,0x42,0x1B,0x52,0x78,0x1B,0x42,0x1B,0x52,0x78,0x1B,0x42,0x1B,0x52,0x78,0x1B,0x42,0x1B,0x52,0x78,0x1B,0x42,0x1B,0x52,0x77,0x1B,0x42,0x1B,0x56,0x7F,0x1B,0x46,0x1B,0x56,0x74,0x1B,0x46,0x1B,0x56,0x7F,0x1B,0x46,0x1B,0x56,0x37,0x1B,0x46,0x1B,0x56,0x7F,0x1B,0x46,0x1B,0x56,0x7C,0x1B,0x46,0x1B,0x56,0x77,0x1B,0x46,0x1B,0x56,0x70,0x1B,0x46,0x1B,0x56,0x78,0x1B,0x46,0x1B,0x56,0x7F,0x1B,0x45,0x1B,0x56,0x60,0x1B,0x41,0x1B,0x56,0x78,0x1B,0x44,0x1B,0x51,0x7C,0x1B,0x44,0x1B,0x54,0x6F,0x1B,0x44,0x1B,0x54,0x7C,0x1B,0x44,0x1B,0x54,0x6C,0x1B,0x44,0x1B,0x54,0x7B,0x1B,0x44,0x1B,0x54,0x70,0x1B,0x44,0x1B,0x54,0x74,0x1B,0x44,0x1B,0x54,0x70,0x1B,0x44,0x1B,0x54,0x23,0x1B,0x44,0x1B,0x54,0x2F,0x1B,0x44,0x1B,0x54,0x6F,0x1B,0x44,0x1B,0x54,0x30,0x1B,0x44,0x1B,0x51,0x37,0x1B,0x44,0x1B,0x51,0x68,0x1B,0x44,0x1B,0x54,0x24,0x1B,0x44,0x1B,0x54,0x37,0x1B,0x44,0x1B,0x51,0x77,0x1B,0x44,0x1B,0x52,0x7F,0x1B,0x44,0x1B,0x56,0x7C,0x1B,0x41,0x1B,0x56,0x70,0x1B,0x42,0x1B,0x56,0x30,0x1B,0x42,0x1B,0x52,0x78,0x1B,0x42,0x1B,0x52,0x78,0x1B,0x42,0x1B,0x52,0x68,0x1B,0x42,0x1B,0x52,0x78,0x1B,0x42,0x1B,0x52,0x68,0x1B,0x42,0x1B,0x52,0x78,0x1B,0x42,0x1B,0x52,0x74,0x1B,0x42,0x1B,0x52,0x7C,0x1B,0x42,0x1B,0x56,0x74,0x1B,0x46,0x1B,0x56,0x70,0x1B,0x46,0x1B,0x56,0x70,0x1B,0x46,0x1B,0x56,0x77,0x1B,0x46,0x1B,0x56,0x74,0x1B,0x46,0x1B,0x56,0x7C,0x1B,0x45,0x1B,0x56,0x60,0x1B,0x41,0x1B,0x56,0x70,0x1B,0x44,0x1B,0x52,0x7C,0x1B,0x44,0x1B,0x51,0x7C,0x1B,0x44,0x1B,0x51,0x7B,0x1B,0x44,0x1B,0x51,0x2C,0x1B,0x44,0x1B,0x54,0x2F,0x1B,0x44,0x1B,0x54,0x2F,0x1B,0x44,0x1B,0x54,0x6F,0x1B,0x44,0x1B,0x54,0x2B,0x1B,0x44,0x1B,0x54,0x60,0x1B,0x44,0x1B,0x54,0x7C,0x1B,0x44,0x1B,0x54,0x28,0x1B,0x44,0x1B,0x54,0x7C,0x1B,0x44,0x1B,0x54,0x70,0x1B,0x44,0x1B,0x54,0x78,0x1B,0x44,0x1B,0x54,0x74,0x1B,0x44,0x1B,0x51,0x37,0x1B,0x44,0x1B,0x55,0x68,0x1B,0x44,0x1B,0x54,0x70,0x1B,0x44,0x1B,0x54,0x77,0x1B,0x44,0x1B,0x54,0x37,0x1B,0x44,0x1B,0x54,0x7C,0x1B,0x44,0x1B,0x54,0x74,0x1B,0x44,0x1B,0x54,0x7F,0x1B,0x44,0x1B,0x52,0x7F,0x1B,0x41,0x1B,0x52,0x30,0x1B,0x42,0x1B,0x52,0x68,0x1B,0x42,0x1B,0x52,0x78,0x1B,0x42,0x1B,0x52,0x78,0x1B,0x42,0x1B,0x52,0x78,0x1B,0x42,0x1B,0x52,0x78,0x1B,0x42,0x1B,0x52,0x77,0x1B,0x42,0x1B,0x52,0x34,0x1B,0x42,0x1B,0x52,0x74,0x1B,0x42,0x1B,0x56,0x70,0x1B,0x42,0x1B,0x56,0x74,0x1B,0x46,0x1B,0x56,0x70,0x1B,0x42,0x1B,0x56,0x60,0x1B,0x41,0x1B,0x56,0x78,0x1B,0x41,0x1B,0x51,0x7C,0x1B,0x44,0x1B,0x51,0x20,0x1B,0x44,0x1B,0x51,0x6B,0x1B,0x44,0x1B,0x54,0x7C,0x1B,0x44,0x1B,0x54,0x70,0x1B,0x44,0x1B,0x54,0x74,0x1B,0x44,0x1B,0x54,0x3F,0x1B,0x44,0x1B,0x54,0x3F,0x1B,0x44,0x1B,0x51,0x78,0x1B,0x44,0x1B,0x51,0x7C,0x1B,0x44,0x1B,0x54,0x20,0x1B,0x44,0x1B,0x54,0x2B,0x1B,0x44,0x1B,0x54,0x64,0x1B,0x44,0x1B,0x54,0x70,0x1B,0x44,0x1B,0x54,0x2B,0x1B,0x44,0x1B,0x54,0x6F,0x1B,0x44,0x1B,0x54,0x37,0x1B,0x44,0x1B,0x51,0x37,0x1B,0x44,0x1B,0x55,0x7C,0x1B,0x44,0x1B,0x54,0x27,0x1B,0x44,0x1B,0x54,0x3F,0x1B,0x44,0x1B,0x54,0x37,0x1B,0x44,0x1B,0x54,0x7F,0x1B,0x44,0x1B,0x54,0x7B,0x1B,0x44,0x1B,0x54,0x6F,0x1B,0x44,0x1B,0x54,0x77,0x1B,0x44,0x1B,0x51,0x7F,0x1B,0x44,0x1B,0x52,0x34,0x1B,0x42,0x1B,0x52,0x60,0x1B,0x42,0x1B,0x52,0x78,0x1B,0x42,0x1B,0x52,0x78,0x1B,0x42,0x1B,0x52,0x78,0x1B,0x42,0x1B,0x52,0x74,0x1B,0x42,0x1B,0x52,0x7C,0x1B,0x42,0x1B,0x52,0x74,0x1B,0x42,0x1B,0x52,0x70,0x1B,0x45,0x1B,0x52,0x60,0x1B,0x41,0x1B,0x52,0x7C,0x1B,0x44,0x1B,0x51,0x7C,0x1B,0x44,0x1B,0x51,0x7C,0x1B,0x44,0x1B,0x51,0x74,0x1B,0x44,0x1B,0x51,0x70,0x1B,0x44,0x1B,0x51,0x7C,0x1B,0x44,0x1B,0x51,0x30,0x1B,0x44,0x1B,0x54,0x6F,0x1B,0x44,0x1B,0x54,0x7F,0x1B,0x44,0x1B,0x54,0x24,0x1B,0x44,0x1B,0x54,0x78,0x1B,0x44,0x1B,0x54,0x6F,0x1B,0x44,0x1B,0x54,0x6C,0x1B,0x44,0x1B,0x54,0x27,0x1B,0x44,0x1B,0x54,0x74,0x1B,0x44,0x1B,0x54,0x63,0x1B,0x44,0x1B,0x54,0x23,0x1B,0x44,0x1B,0x54,0x2F,0x1B,0x44,0x1B,0x54,0x2C,0x1B,0x44,0x1B,0x51,0x37,0x1B,0x44,0x1B,0x51,0x6F,0x1B,0x44,0x1B,0x54,0x7C,0x1B,0x44,0x1B,0x54,0x3F,0x1B,0x44,0x1B,0x54,0x27,0x1B,0x44,0x1B,0x54,0x27,0x1B,0x44,0x1B,0x54,0x33,0x1B,0x44,0x1B,0x54,0x7B,0x1B,0x44,0x1B,0x54,0x2F,0x1B,0x44,0x1B,0x54,0x74,0x1B,0x44,0x1B,0x54,0x34,0x1B,0x44,0x1B,0x51,0x7F,0x1B,0x44,0x1B,0x52,0x74,0x1B,0x42,0x1B,0x52,0x78,0x1B,0x42,0x1B,0x52,0x78,0x1B,0x42,0x1B,0x52,0x78,0x1B,0x42,0x1B,0x52,0x74,0x1B,0x42,0x1B,0x52,0x77,0x1B,0x42,0x1B,0x52,0x77,0x1B,0x41,0x1B,0x52,0x60,0x1B,0x41,0x1B,0x55,0x7C,0x1B,0x41,0x1B,0x51,0x70,0x1B,0x44,0x1B,0x51,0x2B,0x1B,0x44,0x1B,0x54,0x7C,0x1B,0x44,0x1B,0x54,0x38,0x1B,0x44,0x1B,0x54,0x68,0x1B,0x44,0x1B,0x54,0x6C,0x1B,0x44,0x1B,0x54,0x77,0x1B,0x44,0x1B,0x51,0x3F,0x1B,0x44,0x1B,0x54,0x6F,0x1B,0x44,0x1B,0x54,0x78,0x1B,0x44,0x1B,0x54,0x27,0x1B,0x44,0x1B,0x54,0x7F,0x1B,0x44,0x1B,0x54,0x70,0x1B,0x44,0x1B,0x54,0x6F,0x1B,0x44,0x1B,0x54,0x60,0x1B,0x44,0x1B,0x54,0x60,0x1B,0x44,0x1B,0x54,0x6F,0x1B,0x44,0x1B,0x54,0x7C,0x1B,0x44,0x1B,0x54,0x30,0x1B,0x44,0x1B,0x51,0x77,0x1B,0x44,0x1B,0x51,0x68,0x1B,0x44,0x1B,0x54,0x2F,0x1B,0x44,0x1B,0x54,0x37,0x1B,0x44,0x1B,0x54,0x37,0x1B,0x44,0x1B,0x54,0x6F,0x1B,0x44,0x1B,0x54,0x7F,0x1B,0x44,0x1B,0x54,0x24,0x1B,0x44,0x1B,0x54,0x73,0x1B,0x44,0x1B,0x54,0x7C,0x1B,0x44,0x1B,0x54,0x23,0x1B,0x44,0x1B,0x54,0x30,0x1B,0x44,0x1B,0x54,0x7F,0x1B,0x44,0x1B,0x52,0x77,0x1B,0x45,0x1B,0x52,0x30,0x1B,0x45,0x1B,0x52,0x78,0x1B,0x42,0x1B,0x52,0x74,0x1B,0x42,0x1B,0x52,0x74,0x1B,0x41,0x1B,0x52,0x78,0x1B,0x41,0x1B,0x51,0x7C,0x1B,0x44,0x1B,0x51,0x63,0x1B,0x44,0x1B,0x51,0x78,0x1B,0x44,0x1B,0x54,0x78,0x1B,0x44,0x1B,0x54,0x34,0x1B,0x44,0x1B,0x54,0x77,0x1B,0x44,0x1B,0x54,0x74,0x1B,0x44,0x1B,0x54,0x77,0x1B,0x44,0x1B,0x54,0x63,0x1B,0x44,0x1B,0x54,0x6C,0x1B,0x44,0x1B,0x54,0x33,0x1B,0x44,0x1B,0x54,0x77,0x1B,0x44,0x1B,0x54,0x70,0x1B,0x44,0x1B,0x54,0x68,0x1B,0x44,0x1B,0x54,0x37,0x1B,0x44,0x1B,0x54,0x70,0x1B,0x44,0x1B,0x54,0x7B,0x1B,0x44,0x1B,0x54,0x70,0x1B,0x44,0x1B,0x54,0x7F,0x1B,0x44,0x1B,0x54,0x7F,0x1B,0x44,0x1B,0x54,0x27,0x1B,0x44,0x1B,0x54,0x73,0x1B,0x44,0x1B,0x51,0x68,0x1B,0x44,0x1B,0x54,0x60,0x1B,0x44,0x1B,0x54,0x3F,0x1B,0x44,0x1B,0x54,0x7F,0x1B,0x44,0x1B,0x54,0x7F,0x1B,0x44,0x1B,0x54,0x7F,0x1B,0x44,0x1B,0x54,0x7F,0x1B,0x44,0x1B,0x54,0x7C,0x1B,0x44,0x1B,0x54,0x7B,0x1B,0x44,0x1B,0x54,0x33,0x1B,0x44,0x1B,0x54,0x68,0x1B,0x44,0x1B,0x54,0x74,0x1B,0x44,0x1B,0x54,0x7F,0x1B,0x44,0x1B,0x55,0x77,0x1B,0x45,0x1B,0x55,0x30};

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
  minitel.newScreen();
}

////////////////////////////////////////////////////////////////////////

void loop() {
  // Voir https://github.com/eserandour/Conversion_Videotex_Hex
  for (int i=0; i<LONGUEUR_TRAME_PORTRAIT; i++) {
    minitel.writeByte(pgm_read_byte_near(PORTRAIT + i));
  }
}

////////////////////////////////////////////////////////////////////////
