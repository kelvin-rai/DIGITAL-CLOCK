#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

const char* ssid = "your_SSID";        // Replace with your Wi-Fi network name
const char* password = "your_PASSWORD"; // Replace with your Wi-Fi password

ESP8266WebServer server(80);           // Create a web server object that listens on port 80

const int ledPin = D1;                 // Pin where the LED is connected (D1 for example)

void handleRoot() {
  String html = "<h1>LED Control</h1>"
                "<p><a href=\"/on\">Turn On</a></p>"
                "<p><a href=\"/off\">Turn Off</a></p>";
  server.send(200, "text/html", html);
}

void handleLEDOn() {
  digitalWrite(ledPin, HIGH);          // Turn on the LED
  server.send(200, "text/html", "<h1>LED is ON</h1><p><a href=\"/\">Go Back</a></p>");
}

void handleLEDOff() {
  digitalWrite(ledPin, LOW);           // Turn off the LED
  server.send(200, "text/html", "<h1>LED is OFF</h1><p><a href=\"/\">Go Back</a></p>");
}

void setup() {
  Serial.begin(115200);
  pinMode(ledPin, OUTPUT);             // Set LED pin as output
  digitalWrite(ledPin, LOW);           // Ensure LED is off by default

  // Connect to Wi-Fi network
  WiFi.begin(ssid, password);
  Serial.print("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  Serial.println();
  Serial.print("Connected, IP address: ");
  Serial.println(WiFi.localIP());      // Print the IP address assigned to the NodeMCU

  // Define routes for the server
  server.on("/", handleRoot);
  server.on("/on", handleLEDOn);
  server.on("/off", handleLEDOff);

  server.begin();                      // Start the web server
  Serial.println("HTTP server started");
}

void loop() {
  server.handleClient();               // Handle incoming client requests
}
