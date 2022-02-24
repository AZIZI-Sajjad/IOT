/*
 * Ref : https://arduinogetstarted.com/tutorials/arduino-mysql
 * 1- Prepare DataBase MySQL 
 *      1.1 -> Log on to Data Base :
 *  Linux# mysql -u root -p 
 *      1.2 -> Create an account nammed "Arduino" :
 *  mysql> CREATE USER 'Arduino'@'localhost' IDENTIFIED BY 'ArduinoGetStarted.com';
 *  mysql> GRANT ALL PRIVILEGES ON *.* TO 'Arduino'@'localhost' WITH GRANT OPTION;
 *  mysql> FLUSH PRIVILEGES;
 *  
 *      1.3 -> Create a DataBase :
 *  mysql> CREATE DATABASE db_arduino CHARACTER SET = 'utf8' COLLATE = 'utf8_general_ci';
 *  
 *      1.4 -> Create a MySQL table 
        USE db_arduino;
        CREATE TABLE tbl_temp (
          temp_id    INT UNSIGNED NOT NULL AUTO_INCREMENT,
          temp_value FLOAT DEFAULT 0.00,
          PRIMARY KEY (temp_id)
        );
 *  mysql> 
 *  mysql> 
 *
 * 2 -  Linux Apache prepare and PHP file (PHP file to forme resuestes to DataBase :
 * Linux# sudo mkdir /var/www/html/insert_temp
 * Linux# sudo vim insert_temp.php 
 * **********************************************************************
  <?php
  
  if(isset($_GET["temperature"])) {
     $temperature = $_GET["temperature"]; // get temperature value from HTTP GET
  
     $servername = "localhost";
     $username = "Arduino";
     $password = "ArduinoGetStarted.com";
     $dbname = "db_arduino";
  
     // Create connection
     $conn = new mysqli($servername, $username, $password, $dbname);
     // Check connection
     if ($conn->connect_error) {
        die("Connection failed: " . $conn->connect_error);
     }
  
     $sql = "INSERT INTO tbl_temp (temp_value) VALUES ($temperature)";
  
     if ($conn->query($sql) === TRUE) {
        echo "New record created successfully";
     } else {
        echo "Error: " . $sql . " => " . $conn->error;
     }
  
     $conn->close();
  } else {
     echo "temperature is not set";
  }
  ?>
 * **********************************************************************
 * 2- Open Arduino IDE & Create an Arduino file and add this Arduino [C++] code into the file 
 *      /!\ Don't forget to adapte the IP adresse and SSID / WiFi KEY with your Environnement 
      then upload the Arduino file to NodeMCU via IDE
 * FOR TEST you can open a WEB navigateur and insert the following URL and the end new temprature added :
 *  Exemple ---> https://192.168.3.200/insert_temp.php?temperature=36.2
 *  vérifie on the MySQL CLI or with PhpMyAdmin
 *  mysql> USE db_arduino
 *  mysql> SELECT * from tbl_temp;
 *          +---------+------------+
 *          | temp_id | temp_value |
 *          +---------+------------+
 *          |       1 |       25.6 | 
 *          |       2 |       37.5 | 
 *          |       3 |     45.101 | 
 *          |       4 |       27.5 | 
 *          |       5 |     29.001 | 
 *          |       6 |       36.2 | 
 *          +---------+------------+
 *          6 rows in set (0.00 sec)
 *          
 */



 

//--> <SD> NodeMCU Inits
//----------------------------------------see here: https://www.youtube.com/watch?v=8jMr94B8iN0 to add NodeMCU ESP8266 library and board
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266HTTPClient.h>
//----------------------------------------
#define ON_Board_LED 2  //--> Defining an On Board LED (GPIO2 = D4), used for indicators when the process of connecting to a wifi router
#define LED_D8 15 //--> Defines an LED Pin. D8 = GPIO15
//----------------------------------------SSID and Password of your WiFi router.
const char* ssid = "Arduino"; //--> Your wifi name or SSID.
const char* password = "P@ssw0rd"; //--> Your wifi password.
//----------------------------------------


//--> </SD> NodeMCU 


WiFiClient client;

int    HTTP_PORT   = 80;
String HTTP_METHOD = "GET";
char   HOST_NAME[] = "192.168.3.200"; // change to your PC's IP address
String PATH_NAME   = "/insert_temp.php";
String queryString = "?temperature=29.1";

void setup() {
  Serial.begin(9600);
  
  //--> <SD> NodeMCU 
  // put your setup code here, to run once:
  delay(500);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password); //--> Connect to your WiFi router
  Serial.println("");
    
  pinMode(ON_Board_LED,OUTPUT); //--> On Board LED port Direction output
  digitalWrite(ON_Board_LED, HIGH); //--> Turn off Led On Board

  pinMode(LED_D8,OUTPUT); //--> LED port Direction output
  digitalWrite(LED_D8, LOW); //--> Turn off Led

  //----------------------------------------Wait for connection
  Serial.print("Connecting");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    //----------------------------------------Make the On Board Flashing LED on the process of connecting to the wifi router.
    digitalWrite(ON_Board_LED, LOW);
    delay(250);
    digitalWrite(ON_Board_LED, HIGH);
    delay(250);
    //----------------------------------------
  }
  //----------------------------------------
  digitalWrite(ON_Board_LED, HIGH); //--> Turn off the On Board LED when it is connected to the wifi router.
  //----------------------------------------If successfully connected to the wifi router, the IP Address that will be visited is displayed in the serial monitor
  Serial.println("");
  Serial.print("Successfully connected to : ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  Serial.println();
  //----------------------------------------
  //--> </SD> NodeMCU   

  //--> <SD> LED
  pinMode(LED_BUILTIN, OUTPUT);
  //--> </SD> LED 
}

void loop() {
  //--> <SD> LED
  digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(1000);                       // wait for a second
  //--> <SD> LED

 //--------------------------------------------------------------------------
  // connect to web server on port 80:
  if(client.connect(HOST_NAME, HTTP_PORT)) {
    // if connected:
    Serial.println("Connected to server");
    // make a HTTP request:
    // send HTTP header
    client.println(HTTP_METHOD + " " + PATH_NAME + queryString + " HTTP/1.1");
    client.println("Host: " + String(HOST_NAME));
    client.println("Connection: close");
    client.println(); // end HTTP header

    while(client.connected()) {
      if(client.available()){
        // read an incoming byte from the server and print it to serial monitor:
        char c = client.read();
        Serial.print(c);
      }
    }

    // the server's disconnected, stop the client:
    client.stop();
    Serial.println();
    Serial.println("disconnected");
  } else {// if not connected:
    Serial.println("connection failed");
  }


  
}
