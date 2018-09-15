#include  "ESP8266WiFi.h"
 
const char* ssid ="KJN"; //PW WiFi
const char* password = "bakabaka"; 
 
int motor1 = 2; // D4
int motor2 = 12; // D6
WiFiServer server(80);

void setup() {
Serial.begin(115200);
delay(10);

pinMode(motor1, OUTPUT);
digitalWrite(motor1, LOW);
pinMode(motor2, OUTPUT);
digitalWrite(motor2, LOW);

// Connect to WiFi network
Serial.println();
Serial.println();
Serial.print("Connecting to ");
Serial.println(ssid);
 
WiFi.begin(ssid, password);

while (WiFi.status() != WL_CONNECTED) {
  delay(500);
  Serial.println(" . ");
}
 
Serial.println("");
Serial.println("WiFi connected");
 
// Start the server

server.begin();
Serial.println("Server started");
 
// Print the IP address
Serial.print("Use this URL to connect: ");
Serial.print("http://");
Serial.print(WiFi.localIP());
Serial.println("/"); 
}


void loop() {
// Check if a client has connected
WiFiClient client = server.available();
if (!client) {
  return;
}
else
{
   Serial.print("server not available ");
}

// Wait until the client sends some data
Serial.println("new client");
int timewate = 0;
while(!client.available()){
  delay(1);
  timewate = timewate +1;
  if(timewate>1800)
  {
    Serial.println(">>> Client Timeout !");
    client.stop();
    return;
  }
}
 
// Read the first line of the request
String request = client.readStringUntil('\r');
Serial.println(request);
client.flush();
 
// Match the request 
int value = LOW;
if (request.indexOf("/UP") != -1)  {
  Serial.println("dupa");
  value = HIGH;
  digitalWrite(motor1, HIGH);
  digitalWrite(motor2, LOW);
  
}
 
if (request.indexOf("/DOWN") != -1)  {
  Serial.println("huj");
  value = LOW;
  digitalWrite(motor2, HIGH);
  digitalWrite(motor1, LOW);
}

 
// Return the response
client.println("HTTP/1.1 200 OK");
client.println("Content-Type: text/html");
client.println(""); //  do not forget this one
client.println("");
client.println("");
client.print("Led pin is now: ");
client.print(value);
client.println("");
client.println("");
client.println("");
client.println("");
client.println("");
client.println("");
delay(1);
Serial.println("Client disonnected");
Serial.println("");
}
