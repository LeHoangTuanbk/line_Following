#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WiFiMulti.h> 
#include <ESP8266mDNS.h>
#include <ESP8266WebServer.h>
#include <ArduinoJson.h>

ESP8266WiFiMulti wifiMulti;     // Create an instance of the ESP8266WiFiMulti class, called 'wifiMulti'

ESP8266WebServer server(80);    // Create a webserver object that listens for HTTP request on port 80

void move();

void setup(void){
  Serial.begin(9600);         // Start the Serial communication to send messages to the computer
  delay(10);
  Serial.println('\n');

  wifiMulti.addAP("abc", "12345678");   // add Wi-Fi networks you want to connect to

  Serial.println("Connecting ...");
  int i = 0;
  while (wifiMulti.run() != WL_CONNECTED) { // Wait for the Wi-Fi to connect: scan for Wi-Fi networks, and connect to the strongest of the networks above
    delay(250);
    Serial.print('.');
  }
  Serial.println('\n');
  Serial.print("Connected to ");
  Serial.println(WiFi.SSID());              // Tell us what network we're connected to
  Serial.print("IP address:\t");
  Serial.println(WiFi.localIP());           // Send the IP address of the ESP8266 to the computer

  server.on("/", HTTP_POST, move);

  server.begin();                           // Actually start the server
  Serial.println("HTTP server started");
}

// /move { pwm: number, dir: string} //: left, right, backward, forward

void loop(void){
  server.handleClient();                    // Listen for HTTP requests from clients
}

void move() {
  Serial.println("Get response!");
  if (server.hasArg("plain")== false){ //Check if body received
    Serial.println("Khong nhan duoc");
    server.send(200, "text/plain", "Body not received");
    return;
}
  String message;
  message += server.arg("plain");
  //message += "\n";
  server.send(200, "text/plain", message);
  Serial.println(message);
  // json 
  StaticJsonDocument<200> jsonBuffer;
  deserializeJson(jsonBuffer, message);
 
  String pwm = jsonBuffer["pwm"] ;
  String dir = jsonBuffer["dir"]; 
  
  Serial.println(pwm);
  Serial.println(dir);

  if (dir == "1") { // di thang
      Serial.println("1");
      analogWrite(15, pwm.toInt());
      digitalWrite(16, 0);
      analogWrite(2, pwm.toInt());
      digitalWrite(0, 0);
      delay(1000);
  }

  if (dir == "2") { // di lui
      Serial.println("2");
      digitalWrite(15, 0);
      analogWrite(16, pwm.toInt());
      digitalWrite(2, 0);
      analogWrite(0, pwm.toInt());
      delay(1000);
  }

  if (dir == "3") { // di lui
      Serial.println("3");
      analogWrite(15, pwm.toInt());
      digitalWrite(16,0);
      digitalWrite(2,0);
      digitalWrite(0,0);
      delay(1000);
  }

  if (dir == "4") {
      Serial.println("4");
      digitalWrite(15, 0);
      digitalWrite(16, 0);
      analogWrite(2, pwm.toInt());
      digitalWrite(0, 0);
      delay(1000);
  }

  server.send(200); // 200 mean ok!
}
