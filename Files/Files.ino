/*
  Exemple de fichier de base de carte SD

 Cet exemple montre comment créer et détruire un fichier de carte SD
 Le circuit:
 * Carte SD connectée au bus SPI comme suit:
 ** MOSI - broche 11
 ** MISO - broche 12
 ** CLK - broche 13
 ** CS - broche 4 (pour MKRZero SD: SDCARD_SS_PIN)
 */
#include <SPI.h>
#include <SD.h>

File myFile;

void setup() 
{
  // Ouvrez les communications série et attendez que le port s'ouvre:
  Serial.begin(9600);
  while (!Serial) 
  {
    ; // attend que le port série se connecte. Nécessaire pour le port USB natif uniquement
  }


  Serial.print("\nInitializing SD card...");

  if (!SD.begin(4)) 
  {
    Serial.println("initialization failed!");
    while (1);
  }
  Serial.println("carte initialisée !");

  if (SD.exists("exemple.txt")) 
  {
    Serial.println("exemple.txt existe.");
  } 
  else 
  {
    Serial.println("exemple.txt n'existe pas.");
  }

  // open a new file and immediately close it:
  Serial.println("Création exemple.txt...");
  myFile = SD.open("exemple.txt", FILE_WRITE);
  myFile.close();

  // Check to see if the file exists:
  if (SD.exists("exemple.txt")) 
  {
    Serial.println("exemple.txt existe.");
  } 
  else 
  {
    Serial.println("exemple.txt n'existe pas.");
  }

  // delete the file:
  Serial.println("Removing exemple.txt...");
  SD.remove("exemple.txt");

  if (SD.exists("exemple.txt")) 
  {
    Serial.println("exemple.txt existe.");
  } 
  else 
  {
    Serial.println("exemple.txt n'existe pas.");
  }
}

void loop() {
  // rien ne se passe après la fin de l'initialisation
}
