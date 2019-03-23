/*
  Listfiles

 Cet exemple montre comment imprimer les fichiers dans un
 répertoire sur une carte SD

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

File root;

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

  root = SD.open("/");

  printDirectory(root, 0);

  Serial.println("Fait!");
}

void loop() {
  // rien ne se passe après la fin de l'initialisation
}

void printDirectory(File dir, int numTabs) 
{
  while (true) 
  {

    File entry =  dir.openNextFile();
    if (! entry) 
    {
      // plus de fichiers
      break;
    }
    for (uint8_t i = 0; i < numTabs; i++) 
    {
      Serial.print('\t');
    }
    Serial.print(entry.name());
    if (entry.isDirectory()) 
    {
      Serial.println("/");
      printDirectory(entry, numTabs + 1);
    } 
    else 
    {
      // les fichiers ont des tailles, pas les répertoires
      Serial.print("\t\t");
      Serial.println(entry.size(), DEC);
    }
    entry.close();
  }
}
