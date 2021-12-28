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
  // LED
  digitalWrite(ledPin, HIGH);
  delay(ledDelayOn);
  digitalWrite(ledPin, LOW);
  delay(ledDelayOff);


  // LASER 
   digitalWrite(laserPin, HIGH);
   delay(laserDelayOn);
   digitalWrite(laserDelayOff, LOW);
   delay(10);
}  
