/*
  Test de carte SD

  Cet exemple montre comment utiliser les bibliothèques d’utilitaires sur lesquelles
  La bibliothèque SD est basée afin d’obtenir des informations sur votre carte SD.
  Très utile pour tester une carte lorsque vous n'êtes pas sûr de son fonctionnement ou non.

  Le circuit:
    Carte SD attachée au bus SPI comme suit:
 ** MOSI - broche 11 sur Arduino Uno / Duemilanove / Diecimila
 ** MISO - broche 12 sur Arduino Uno / Duemilanove / Diecimila
 ** CLK - broche 13 sur Arduino Uno / Duemilanove / Diecimila
 ** CS - dépend de votre blindage ou de votre module de carte SD.
 Broche 4 utilisée ici pour la cohérence avec d'autres exemples Arduino
*/
// inclure la bibliothèque SD:
#include <SPI.h>
#include <SD.h>

// configuration des variables à l'aide des fonctions de la bibliothèque d'utilitaires SD:
Sd2Card card;
SdVolume volume;
SdFile root;

// change ceci pour qu'il corresponde à votre bouclier SD ou à votre module;
// Shield Arduino Ethernet: broche 4
// Seede SD Card shield V4.0
// Shield et modules Adafruit SD: broche 10
// Shield Sparkfun SD: broche 8
// MKRZero SD: SDCARD_SS_PIN
const int chipSelect = 4;

void setup() {
  // Ouvrez les communications série et attendez que le port s'ouvre:
  Serial.begin(9600);
  while (!Serial) 
  {
    ; // attend que le port série se connecte. Nécessaire pour le port USB natif uniquement
  }


  Serial.print("\nInitialisation de la carte SD ...");

  // nous utiliserons le code d'initialisation des bibliothèques d'utilitaires
  // puisque nous testons simplement si la carte fonctionne!
  if (!card.init(SPI_HALF_SPEED, chipSelect)) 
  {
    Serial.println("Initialisation échouée. Choses à vérifier:");
    Serial.println("* une carte est-elle insérée?");
    Serial.println("* votre câblage est-il correct?");
    Serial.println("* avez-vous modifié la broche chipSelect pour qu'elle corresponde à votre bouclier ou à votre module?");
    while (1);
  } 
  else 
  {
    Serial.println("Le câblage est correct et une carte est présente.");
  }

  // print the type of card
  Serial.println();
  Serial.print("Type de carte : ");
  switch (card.type()) 
  {
    case SD_CARD_TYPE_SD1:
      Serial.println("SD1");
      break;
    case SD_CARD_TYPE_SD2:
      Serial.println("SD2");
      break;
    case SD_CARD_TYPE_SDHC:
      Serial.println("SDHC");
      break;
    default:
      Serial.println("Inconnue");
  }

  // Nous allons maintenant essayer d'ouvrir le 'volume' / 'partition' - ce devrait être FAT16 ou FAT32
  if (!volume.init(card)) 
  {
    Serial.println("Impossible de trouver la partition FAT16 / FAT32. \n Assurez-vous d’avoir formaté la carte.");
    while (1);
  }

  Serial.print("Clusters : ");
  Serial.println(volume.clusterCount());
  Serial.print("Blocs x Cluster : ");
  Serial.println(volume.blocksPerCluster());

  Serial.print("Total de blocs : ");
  Serial.println(volume.blocksPerCluster() * volume.clusterCount());
  Serial.println();

  // affiche le type et la taille du premier volume de type FAT
  uint32_t volumesize;
  Serial.print("Le type de volume est : FAT");
  Serial.println(volume.fatType(), DEC);

  volumesize = volume.blocksPerCluster();    // les clusters sont des collections de blocs
  volumesize *= volume.clusterCount();       // nous aurons beaucoup de clusters
  volumesize /= 2;                           // les blocs de la carte SD ont toujours 512 octets (2 blocs valent 1 Ko)
  Serial.print("Taille du Volume (Kb) : ");
  Serial.println(volumesize);
  Serial.print("Taille du Volume (Mb): ");
  volumesize /= 1024;
  Serial.println(volumesize);
  Serial.print("Taille du Volume (Gb): ");
  Serial.println((float)volumesize / 1024.0);

  Serial.println("\n Fichiers trouvés sur la carte (nom, date et taille en octets):");
  root.openRoot(volume);

  // liste tous les fichiers de la carte avec la date et la taille
  root.ls(LS_R | LS_DATE | LS_SIZE);
}

void loop(void) {
  // rien ne se passe après la fin de l'initialisation
}
