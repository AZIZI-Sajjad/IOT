// Requirements : 
  // Laser + Buzzer + PhotoResistance

int photoResistPin = A0;     // PhotoReisitance Position . 
int buzzerPin = 2;              // LED Position
int laserPin = 7;            // LASER Position
                                                                
void setup()                                                          
{
Serial.begin(9600);
pinMode(photoResistPin, INPUT);
pinMode(buzzerPin, OUTPUT);                                       
pinMode(laserPin, OUTPUT);
}

void loop()
{
int ldrValue = analogRead(photoResistPin);
digitalWrite(laserPin, HIGH);

delay(1);                     
Serial.println(ldrValue);        //Print the read value on arduino serial monitor


if(ldrValue>100){           
    digitalWrite(buzzerPin, HIGH);
}
else
{
    digitalWrite(buzzerPin, LOW); 
}
}
