#include <Arduino.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include "env.h"

void setup() {
  // Start the serial communication
  Serial.begin(115200);

  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");

  // Make API request
  String message = makeApiRequest(endpoint, api_key);

  // Display the message on LCD
  displayMessageOnLCD(message);
}

void loop() {
  // Your loop code, if needed
}

String makeApiRequest(const char *apiEndpoint, const char *apiKey) {
  String message;

  // Create HTTP client
  HTTPClient http;

  // Build the request URL
  String url = "http://" + String(apiEndpoint) + "/message";

  // Add headers to the request
  http.begin(url);
  http.addHeader("api-key", apiKey);

  // Make the request
  int httpCode = http.GET();

  // Check for a successful response
  if (httpCode == HTTP_CODE_OK) {
    // Parse JSON response
    DynamicJsonDocument jsonDocument(256);
    deserializeJson(jsonDocument, http.getString());

    // Extract message
    String line1 = jsonDocument["line_1"].as<String>();
    String line2 = jsonDocument["line_2"].as<String>();
    message = line1 + " " + line2;
  } else {
    Serial.println("Failed to get response. HTTP code: " + String(httpCode));
  }

  // Close connection
  http.end();

  return message;
}

void displayMessageOnLCD(String message) {
  // Add your code to display the message on the 16x2 LCD
  // Example: lcd.print(message);
}