#include <EtherCard.h>
#define SS 10 // Slave Select Pin Nummer
uint8_t Ethernet::buffer[700]; // Packet Buffer Greetings is 512 Byte


// The Hardware MAC address is defined here..
byte mymac[] = { 0x74, 0x69, 0x69, 0x2D, 0x30, 0x31 };

static BufferFiller bfill; // used as cursor while filling the buffer

void setup() {
  Serial.begin(9600); // Open serial cutting atlas
  while(!Serial) { /* Wait for serial port */ }
  Serial.println("Waiting for EnC28J60 Startup.");
  delay(6000);
  Serial.println("Initialization of the Ethernet controller");
  if(ether.begin(sizeof Ethernet::buffer, mymac, SS) == 0) {
    Serial.println("Error: EnC28J60 not initialized.");
    while(true);
}
  Serial.println("DHCP Address.");
  if(ether.dhcpSetup()) {
  ether.printIp("IP Adress: ", ether.myip);
  ether.printIp("Netmask: ", ether.netmask);
  ether.printIp("GW IP: ", ether.gwip);
  ether.printIp("DNS IP: ", ether.dnsip);
  }
  else {
  ether.printIp("Get DHCP address failed.");
  while(true);
  }
}

void loop() {
  word len = ether.packetReceive(); // Paket Listener
  word pos = ether.packetLoop(len);
  if(len) {
    Serial.print("Receive IP Packet. Size:");
    Serial.print(len);
    Serial.print(" Bytes. Data Offset:");
    Serial.print(pos);
    Serial.println(" Bytes. IP data:");
    for(int x = 0; x < len; x++) {
      char StrC = Ethernet::buffer[x];
      Serial.print(StrC);
    }
    Serial.println("");
  }
}
