/*   
 *  This library was written by Vittorio Esposito
 *    https://github.com/VittorioEsposito
 *
 *  Designed to work with the GSM Sim800L.
 *
 *  ENG
 *    This library uses SoftwareSerial, you can define RX and TX pins
 *    in the header "Sim800L.h", by default pins are RX=10 and TX=11.
 *    Be sure that GND is connected to arduino too. 
 *    You can also change the RESET_PIN as you prefer.
 *  
 *  ESP
 *    Esta libreria usa SoftwareSerial, se pueden cambiar los pines de RX y TX
 *    en el archivo header, "Sim800L.h", por defecto los pines vienen configurado en
 *    RX=10 TX=11.  
 *    Tambien se puede cambiar el RESET_PIN por otro que prefiera
 * 
 *  ITA
 *    Questa libreria utilizza la SoftwareSerial, si possono cambiare i pin di RX e TX
 *    dall' intestazione "Sim800L.h", di default essi sono impostati come RX=10 RX=11
 *    Assicurarsi di aver collegato il dispositivo al pin GND di Arduino.
 *    E' anche possibile cambiare il RESET_PIN.
 *
 *
 *   DEFAULT PINOUT: 
 *        _____________________________
 *       |  ARDUINO UNO >>>   Sim800L  |
 *        -----------------------------
 *            GND      >>>   GND
 *        RX  10       >>>   TX    
 *        TX  11       >>>   RX
 *       RESET 2       >>>   RST 
 *                 
 *   POWER SOURCE 4.2V >>> VCC
 *
 *
 *  SOFTWARE SERIAL NOTES:
 *
 *    PINOUT
 *    The library has the following known limitations:
 *    1. If using multiple software serial ports, only one can receive data at a time.
 *    2. Not all pins on the Mega and Mega 2560 support change interrupts, so only the following can be used for RX: 10, 11, 12, 13, 14, 15, 50, 51, 52, 53, A8 (62), A9 (63), A10 (64), A11 (65), A12 (66), A13 (67), A14 (68), A15 (69).
 *    3. Not all pins on the Leonardo and Micro support change interrupts, so only the following can be used for RX: 8, 9, 10, 11, 14 (MISO), 15 (SCK), 16 (MOSI).
 *    4. On Arduino or Genuino 101 the current maximum RX speed is 57600bps
 *    5. On Arduino or Genuino 101 RX doesn't work on Pin 13
 *  
 *    BAUD RATE
 *    Supported baud rates are 300, 600, 1200, 2400, 4800, 9600, 14400, 19200, 28800, 31250, 38400, 57600, and 115200.
 *
 *
 *  Edited on:  December 24, 2016
 *    Editor:   Vittorio Esposito
 *    
 *  Original version by:   Cristian Steib
 *        
 *
*/

#include <Sim800L.h>
#include <SoftwareSerial.h>               

#define RX  11
#define TX  10


Sim800L GSM(RX, TX);

/*
 * In alternative:
 * Sim800L GSM;                       // Use default pinout
 Serial.println("2/////////////");
 * Sim800L GSM(RX, TX, RESET);        
 Serial.println("3/////////////");
 * Sim800L GSM(RX, TX, RESET, LED);
 */

void setup(){
Serial.println("4/////////////");
  Serial.begin(9600);
  Serial.println("5/////////////");
  GSM.begin(9600);
  Serial.println("6/////////////");
  //GSM.println("AT+CPIN=\1234\r");    
  
  String pin = "0802";

  Serial.println("7/////////////");
  if (GSM.setPIN(pin)) Serial.println("Pin set");
    Serial.println("8/////////////");
  else Serial.println('Pin NOT set');

  Serial.println("9/////////////");
  Serial.println("GET PRODUCT INFO: ");
  Serial.println("10/////////////");
  Serial.println(GSM.getProductInfo());

Serial.println("11/////////////");
  Serial.println("GET OPERATORS LIST: ");
  Serial.println("12/////////////");
  Serial.println(GSM.getOperatorsList());

Serial.println("13/////////////");
  Serial.println("GET OPERATOR: ");
  Serial.println("14/////////////");
  Serial.println(GSM.getOperator());
  
}

void loop(){
  
}
