/*
Carte SD en lecture / écriture

 Cet exemple montre comment lire et écrire des données depuis et vers un fichier de carte SD
 Le circuit:
 * Carte SD connectée au bus SPI comme suit:
 ** MOSI - broche 11
 ** MISO - broche 12
 ** CLK - broche 13
 ** CS - broche 4 (pour MKRZero SD: SDCARD_SS_PIN)
 */

#include <SPI.h>
#include <SD.h>

const int chipSelect = 4;

File myFile;

void setup() 
{
  // Ouvrez les communications série et attendez que le port s'ouvre:
  Serial.begin(9600);
  while (!Serial) 
  {
    ; // attend que le port série se connecte. Nécessaire pour le port USB natif uniquement
  }


  Serial.print("\nInitialisation de la carte SD ...");

  // voir si la carte est présente et peut être initialisée:
  if (!SD.begin(chipSelect)) 
  {
    Serial.println("Carte manquante ou non présente");
    // ne fais rien de plus:
    while (1);
  }
  Serial.println("carte initialisée !");


  // ouvre le fichier. notez qu'un seul fichier peut être ouvert à la fois,
  // vous devez donc fermer celui-ci avant d'en ouvrir un autre.
  myFile = SD.open("test.txt", FILE_WRITE);

  // si le fichier s'est ouvert correctement, écrivez-le:
  if (myFile) 
  {
    Serial.print("Écrire dans test.txt ...");
    myFile.println("test 1, 2, 3.");
    // ferme le fichier:
    myFile.close();
    Serial.println("Fait.");
  } 
  else 
  {
    // si le fichier ne s'est pas ouvert, affiche une erreur:
    Serial.println("erreur d'ouverture test.txt");
  }

  // rouvre le fichier pour le lire:
  myFile = SD.open("test.txt");
  if (myFile) 
  {
    Serial.println("test.txt:");

    // lit le fichier jusqu'à ce qu'il n'y ait plus rien dedans:
    while (myFile.available()) 
    {
      Serial.write(myFile.read());
    }
    // ferme le fichier:
    myFile.close();
  } 
  else 
  {
    // si le fichier ne s'est pas ouvert, affiche une erreur:
    Serial.println("erreur d'ouverture test.txt");
  }
}

void loop() 
{
  // rien ne se passe après la fin de l'initialisation
}
