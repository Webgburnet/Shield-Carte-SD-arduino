/*
  Ouvrir de fichier de carte SD

 Cet exemple montre comment lire un fichier depuis la carte SD en utilisant le
 Bibliothèque SD et l'envoyer sur le port série.

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
  File dataFile = SD.open("datalog.txt");

  // si le fichier est disponible, écrivez-le:
  if (dataFile) 
  {
    Serial.println("Début de lecture du fichier datalog.txt");
    while (dataFile.available()) 
    {
      Serial.write(dataFile.read());
    }
    dataFile.close();
    Serial.println("Début de lecture du fichier datalog.txt");
  }
  // si le fichier n'est pas ouvert, une erreur apparaît:
  else 
  {
    Serial.println("Erreur d'ouverture datalog.txt");
  }
}

void loop() 
{
  // rien ne se passe après la fin de l'initialisation
}
