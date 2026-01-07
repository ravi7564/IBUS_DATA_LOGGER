#include <Arduino.h>
#include <WiFi.h>
#include <ESPAsyncWebServer.h>
#include <IBusBM.h>
#include <ArduinoJson.h>
#include "index_html.h"

// Global Objects
IBusBM IBus;
AsyncWebServer server(80);
AsyncWebSocket ws("/ws");

// Configuration
const char* SSID_NAME = "ESP32-RC-DASHBOARD";
const uint32_t UPDATE_INTERVAL = 50; // ms

// Function Prototypes
void setupWebHandlers();

void setup() {
    Serial.begin(115200);
    delay(2000);
    Serial.println("\n[SYSTEM] Initializing...");

    // 1. Networking Setup
    WiFi.mode(WIFI_AP);
    if(WiFi.softAP(SSID_NAME)) {
        Serial.printf("[WiFi] Access Point '%s' is Live\n", SSID_NAME);
        Serial.print("[WiFi] IP Address: "); Serial.println(WiFi.softAPIP());
    }

    // 2. Server & WebSocket Setup
    setupWebHandlers();
    server.begin();
    Serial.println("[WEB] Server started on port 80");

    // 3. RC Receiver Setup (Hardware Serial 2)
    IBus.begin(Serial2, 1);
    Serial.println("[iBUS] Protocol initialized on RX2 (GPIO 16)");
}

void loop() {
    static unsigned long lastUpdate = 0;

    if (millis() - lastUpdate > UPDATE_INTERVAL) {
        StaticJsonDocument<128> doc;

        // Packing Channel Data
        for(int i=0; i<4; i++) {
            doc["c" + String(i)] = IBus.readChannel(i);
        }

        String jsonResponse;
        serializeJson(doc, jsonResponse);
        ws.textAll(jsonResponse);

        lastUpdate = millis();
    }

    ws.cleanupClients();
}

void setupWebHandlers() {
    // Handle WebSocket events (connect/disconnect)
    ws.onEvent([](AsyncWebSocket *s, AsyncWebSocketClient *c, AwsEventType t, void *a, uint8_t *d, size_t l){
        if(t == WS_EVT_CONNECT) Serial.printf("[WS] Client connected from %s\n", c->remoteIP().toString().c_str());
    });

    server.addHandler(&ws);

    // Serve HTML Dashboard
    server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
        request->send(200, "text/html", index_html);
    });
}