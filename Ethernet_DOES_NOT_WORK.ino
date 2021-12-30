#include <Ethernet.h>

// SDA's First Ardiuno Project !!!! ;)

// ETHERNET
// Enter a MAC address and IP address for your controller below.
// The IP address will be dependent on your local network:
//#include <SPI.h>
#include <Ethernet.h>

// Enter a MAC address and IP address for your controller below.
// The IP address will be dependent on your local network:
byte mac[] = {
  0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED
};
IPAddress ip(192, 168, 2, 123);

// Initialize the Ethernet server library
// with the IP address and port you want to use
// (port 80 is default for HTTP):
EthernetServer server(80);
// ETHERNET



// GENERAL
int DelayOn = 2000;
int DelayOff = 1000;


// LASER
int laserPin = 10;
int laserDelayOn = 2000;
int laserDelayOff = 1000;

// LED
int ledPin = 12;
int ledDelayOn = 2000;
int ledDelayOff = 1000;

void setup() {
  // put your setup code here, to run once:


  
  // LED
  pinMode(ledPin, OUTPUT);
  // LASER 
  pinMode (laserPin,OUTPUT);
  

}

void loop() {
  // put your main code here, to run repeatedly:
  // LED & LASER At the same time 
  digitalWrite(ledPin, HIGH); digitalWrite(laserPin, LOW);
  delay(DelayOn);
  digitalWrite(ledPin, LOW); digitalWrite(laserPin, HIGH);
  delay(DelayOff);

/*
  // First LED then LASER 
  // LED
  digitalWrite(ledPin, HIGH); digitalWrite(laserPin, HIGH);
  delay(ledDelayOn);
  digitalWrite(ledPin, LOW); 
  delay(ledDelayOff);
  // LASER 
   digitalWrite(laserPin, HIGH);
   delay(laserDelayOn);
   digitalWrite(laserPin, LOW);
   delay(laserDelayOff);
*/
}  


///////////////////////////////////////////////// ERROR :

/*
Le croquis utilise 8508 octets (3%) de l'espace de stockage de programmes. Le maximum est de 253952 octets.
Les variables globales utilisent 195 octets (2%) de mémoire dynamique, ce qui laisse 7997 octets pour les variables locales. Le maximum est de 8192 octets.
avrdude: verification error, first mismatch at byte 0x096c
         0x8e != 0xce
avrdude: verification error; content mismatch
avrdude: verification error; content mismatch



*/
