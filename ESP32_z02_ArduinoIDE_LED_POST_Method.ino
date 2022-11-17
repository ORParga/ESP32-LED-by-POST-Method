/*
 Name:    LED_AsyncWebServer_POST.ino
 Created: 15/11/2022 18:23:57
 Author:  ORParga1@gmail.com
 */
#ifdef ESP32
#include <WiFi.h>
#include <AsyncTCP.h>
#else
#include <ESP8266WiFi.h>
#include <ESPAsyncTCP.h>
#endif

//https://github.com/me-no-dev/ESPAsyncWebServer
#include <ESPAsyncWebServer.h>

// include libraries to include file system

//https://github.com/espressif/arduino-esp32/tree/master/libraries/SPIFFS
#include "FS.h"
#include "SPIFFS.h"

AsyncWebServer server(80);

bool connectToWiFi_STA()
{
  
    WiFi.mode(WIFI_MODE_STA);

    // REPLACE WITH YOUR NETWORK CREDENTIALS
    char* fav_ssid = "RODRIGUEZ_2";
    char* fav_password = "PITUFILLA";
    for (int intento = 0; intento < 10; intento++)
    {
        WiFi.begin(fav_ssid, fav_password);
        if (WiFi.status() == WL_CONNECTED) {
            Serial.print("ESP32 IP on the WiFi network:");
            Serial.println(WiFi.localIP());
            return true;
        }
        delay(1000);
        Serial.print(intento);
        Serial.print(" Connecting to WiFi: ");
        Serial.println(fav_ssid);
    }
    return false;
}
void listDir(fs::FS& fs, const char* dirname, uint8_t levels) {
    Serial.printf("Listing directory: %s\r\n", dirname);

    File root = fs.open(dirname);
    if (!root) {
        Serial.println("? failed to open directory");
        return;
    }
    if (!root.isDirectory()) {
        Serial.println(" ? not a directory");
        return;
    }

    File file = root.openNextFile();
    while (file) {
        if (file.isDirectory()) {
            Serial.print("  DIR : ");
            Serial.println(file.name());
            if (levels) {
                listDir(fs, file.name(), levels - 1);
            }
        }
        else {
            Serial.print("  FILE: ");
            Serial.print(file.name());
            Serial.print("\tSIZE: ");
            Serial.println(file.size());
        }
        file = root.openNextFile();
    }
}


void notFound(AsyncWebServerRequest* request) {
    Serial.println("server.on(notFound)");
    request->send(404, "text/plain", "Not found");
}

void serverConfig()
{

    // Confure the responses to the requests from index.html*********************************************************

    server.on("/", HTTP_GET, [](AsyncWebServerRequest* request) {
        Serial.println("server.on(\"/\", HTTP_GET...)");
        request->send(SPIFFS, "/clientWeb.html", "text/html");

        });
    server.on("/clientWeb.html", HTTP_GET, [](AsyncWebServerRequest* request) {
        Serial.println("server.on(\"/inicio.html\", HTTP_GET...)");
        request->send(SPIFFS, "/clientWeb.html", "text/html");

        });
    server.on("/", HTTP_POST, [](AsyncWebServerRequest* request) {}, NULL,
        [](AsyncWebServerRequest* request, uint8_t* data, size_t len, size_t index, size_t total) {

            char param[100];
            int sizeWord = len;
            if (sizeWord >= 100)sizeWord = 99;
            size_t i;
            for (i = 0; i < sizeWord; i++) {
                param[i] = data[i];
            }
            param[i] = 0;

            //The ESP32 checks if the Web is demanding the 'lightState' parameter
            if (strcmp(param, "lightState") == 0)
            {
              //The ESP32 sends an 'on' or an 'off' to the web as response to the web's request
                if (digitalRead(4))
                {
                    request->send(200, "text/html", "on");
                }
                else
                {
                    request->send(200, "text/html", "off");
                }

            }
            else {
                request->send(200, "text/html", "unknow");
            }
        });
    server.onNotFound(notFound);
    server.begin();
}
void setup() {
    //Iniciate Serial Monitor**************************************************************
    Serial.begin(115200);
    Serial.println("hola");
    //Iniciate File System*********************************************************
    if (!SPIFFS.begin(true)) {
        Serial.println("An Error has occurred while mounting SPIFFS");
        return;
    }

    //List contents of SPIFFS. Just to show if index.html is loaded on ESP32
    listDir(SPIFFS, "/", 0);
    //Inicialize WiFi, "**********************

    connectToWiFi_STA();

    //Configure the Web Server in the ESP32
    serverConfig();

    //Configure one pin for a button and another for a LED
    pinMode(16, OUTPUT);
    pinMode(4, INPUT);
}

void loop() {
    //Just turn on the led while you are pressing the button
    digitalWrite(16, digitalRead(4));
    delay(100);
}
