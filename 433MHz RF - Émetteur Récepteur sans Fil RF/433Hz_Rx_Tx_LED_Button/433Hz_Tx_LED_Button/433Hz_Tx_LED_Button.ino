#include <VirtualWire.h>

#define button 6


char *data;
int val;
int value = 0;

void setup() 
{
  Serial.begin(9600);
  pinMode(button, INPUT);
  vw_set_tx_pin(12);
  vw_setup(2000);
  pinMode(button, INPUT_PULLUP);
}

void loop()
{
  val = digitalRead(button);
  if(val == LOW && value == 0)
  {
    const char *data="a";
    Serial.print("data sent = ");
    Serial.println(data);
    Serial.println("LED ON");
    vw_send((uint8_t *)data, strlen(data));
    vw_wait_tx();
    delay(300);
    value = 1;
  }
  else if(val == LOW && value == 1)
  {
    const char *data="b";
    Serial.print("data sent = ");
    Serial.println(data);
    Serial.println("LED OFF");
    vw_send((uint8_t *)data, strlen(data));
    vw_wait_tx();
    delay(300);
    value = 0;
  }
  //delay(200);
}
