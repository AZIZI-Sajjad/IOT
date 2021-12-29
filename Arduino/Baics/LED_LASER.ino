// SDA's First Ardiuno Project !!!! ;)


// LASER
int laserPin = 8;
int laserDelayOn = 2000;
int laserDelayOff = 1000;

// LED
int ledPin = 13;
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
  digitalWrite(ledPin, HIGH); digitalWrite(laserPin, HIGH);
  delay(ledDelayOn);
  digitalWrite(ledPin, LOW); digitalWrite(laserPin, LOW);
  delay(ledDelayOff);

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
