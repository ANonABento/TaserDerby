#include <WiFi.h>
#include <WebServer.h>

// --- Configuration ---
const int RELAY_PIN = 4;
// How long the penalty pulse lasts in milliseconds. 
// 50ms is very fast (just a click)
const int PULSE_DURATION = 50; 

// Wi-Fi network credentials - **MUST BE CHANGED** 
const char* ssid = "Shiba 8"; // 165KingWest 
const char* password = "88888888"; //165Budds

WebServer server(80);

// --- Function Prototypes ---
void handleRoot();
void handleLose(); // The new pulse handler
void enableCORS(); // Helper for browser security

void setup() {
  Serial.begin(115200);
  pinMode(RELAY_PIN, OUTPUT);
  digitalWrite(RELAY_PIN, LOW); // Start OFF (assuming LOW = ON)

  // Connect to Wi-Fi
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi connected.");
  Serial.print("ESP32 IP Address: ");
  Serial.println(WiFi.localIP());

  // --- Routes ---
  server.on("/", HTTP_GET, handleRoot);
  
  // The crucial route for the React App
  // When React sends a POST to http://[IP]/lose, this function runs
  server.on("/lose", HTTP_POST, handleLose);
  // Also allow GET for easy testing in browser address bar: http://[IP]/lose
  server.on("/lose", HTTP_GET, handleLose); 

  server.begin();
  Serial.println("HTTP server started.");
}

void loop() {
  server.handleClient();
}

// --- Handlers ---

// 1. Root Page (Optional, for manual testing)
void handleRoot() {
  String html = "<html><body><h1>ESP32 Derby Controller</h1>";
  html += "<p>Relay is ready for penalty signal.</p>";
  html += "<form action='/lose' method='POST'><button style='font-size:2em; background:red;'>TEST PENALTY PULSE</button></form>";
  html += "</body></html>";
  server.send(200, "text/html", html);
}

// 2. The Pulse Handler (The logic you wanted)
void handleLose() {
  enableCORS(); // Important for React to be allowed to talk to this
  Serial.println("Defeat signal received! Initiating penalty pulse...");

  // 1. Turn Relay ON
  digitalWrite(RELAY_PIN, HIGH); 
  
  // 2. Wait for the duration
  delay(PULSE_DURATION); 
  
  // 3. Turn Relay OFF
  digitalWrite(RELAY_PIN, LOW);
  
  Serial.println("Penalty pulse complete.");
  server.send(200, "text/plain", "Penalty Delivered");
}

// Helper to allow your React app (running on localhost) to talk to this IP
void enableCORS() {
  server.sendHeader("Access-Control-Allow-Origin", "*");
  server.sendHeader("Access-Control-Max-Age", "10000");
  server.sendHeader("Access-Control-Allow-Methods", "POST,GET,OPTIONS");
  server.sendHeader("Access-Control-Allow-Headers", "Origin, X-Requested-With, Content-Type, Accept");
}