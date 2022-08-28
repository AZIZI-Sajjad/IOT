#include <SoftwareSerial.h>
////////////////////////////////////
// Réf1: https://miliohm.com/sim800l-v2-tutorial-with-arduino/
// Réf2: https://www.youtube.com/watch?v=THCJWWsyh10
#include <Sim800L.h>
#define RX  10
#define TX  11
Sim800L GSM(RX, TX);
////////////////////////////////////
SoftwareSerial sim(RX, TX);
int _timeout;
String _buffer;
String number = "+336604xxxxx"; //-> change with your number
void setup() {
  //delay(7000); //delay for 7 seconds to make sure the modules get the signal
  Serial.begin(9600);
  _buffer.reserve(50);
  Serial.println("System Started...");

//////////////////////////
  Serial.println("GET PRODUCT INFO: ");
  Serial.println(GSM.getProductInfo());

  Serial.println("GET OPERATORS LIST: ");
  Serial.println(GSM.getOperatorsList());

  Serial.println("GET OPERATOR: ");
  Serial.println(GSM.getOperator());
//////////////////////////
  
  sim.begin(9600);
  delay(1000);
  Serial.println("Type s to send an SMS, r to receive an SMS, and c to make a call");
}
void loop() {
  if (Serial.available() > 0)
    switch (Serial.read())
    {
      case 's':
        SendMessage();
        break;
      case 'r':
        RecieveMessage();
        break;
      case 'c':
        callNumber();
        break;
    }
  if (sim.available() > 0)
    Serial.write(sim.read());
}

void SendMessage()
{
  Serial.println("Start SendMessage");
  //Serial.println ("Sending Message");
  sim.println("AT+CMGF=1");    //Sets the GSM Module in Text Mode
  delay(200);
  //Serial.println ("Set SMS Number");
  sim.println("AT+CMGS=\"" + number + "\"\r"); //Mobile phone number to send message
  delay(200);
  String SMS = "Hello, how are you? greetings from miliohm.com admin";
  sim.println(SMS);
  delay(100);
  sim.println((char)26);// ASCII code of CTRL+Z
  delay(200);
  _buffer = _readSerial();
  Serial.println("End SendMessage");
}
void RecieveMessage()
{
  Serial.println("Start RecieveMessage");
  Serial.println ("SIM800L Read an SMS");
  sim.println("AT+CMGF=1");
  delay (200);
  sim.println("AT+CNMI=1,2,0,0,0"); // AT Command to receive a live SMS
  delay(200);
  Serial.write ("Unread Message done");
}
String _readSerial() {
  _timeout = 0;
  while  (!sim.available() && _timeout < 12000  )
  {
    delay(13);
    _timeout++;
  }
  if (sim.available()) {
    return sim.readString();
  }
  Serial.println("End RecieveMessage");
}
void callNumber() {
  Serial.println("Start callNumber");
  sim.print (F("ATD"));
  sim.print (number);
  sim.print (F(";\r\n"));
  _buffer = _readSerial();
  Serial.println(_buffer);
  Serial.println("End callNumber");
}
