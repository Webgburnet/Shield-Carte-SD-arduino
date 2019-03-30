/*
  Enregistreur de données sur carte SD

 Cet exemple montre comment enregistrer les données de trois capteurs analogiques
 sur une carte SD utilisant la bibliothèque SD.

 Le circuit:
 * capteurs analogiques sur les entrées analogiques 0, 1 et 2
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
}

void loop() {
  // crée une chaîne pour assembler les données à consigner:
  String dataString = "";

  // lit trois capteurs et ajoute à la chaîne:
  for (int analogPin = 0; analogPin < 3; analogPin++) 
  {
    int sensor = analogRead(analogPin);
    dataString += String(sensor);
    if (analogPin < 2) 
    {
      dataString += ",";
    }
  }

  // ouvre le fichier. notez qu'un seul fichier peut être ouvert à la fois,
  // vous devez donc fermer celui-ci avant d'en ouvrir un autre.
  File dataFile = SD.open("datalog.txt", FILE_WRITE);

  // si le fichier est disponible, écrivez-le:
  if (dataFile) 
  {
    dataFile.println(dataString);
    dataFile.close();
    // print to the serial port too:
    Serial.println(dataString);
  }
  // si le fichier n'est pas ouvert, une erreur apparaît:
  else 
  {
    Serial.println("erreur d'ouverture datalog.txt");
  }
}
