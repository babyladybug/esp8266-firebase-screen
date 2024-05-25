#include "FirebaseESP8266.h"
#include <U8g2lib.h>
#include <Wire.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>
#include <OneButton.h>
#include <ArduinoJson.h>
#include <WiFiClientSecureBearSSL.h>
#include <FS.h>

#define FIREBASE_HOST "hvhvkjb"
#define FIREBASE_AUTH "yugyguy"

#define OLED_RESET -1

typedef enum {
  MENU,
  DOWNLOADS,
  ASK_HELP
} Screen;

Screen currentScreen = MENU;

const char* password = "99995555";
const char* ssid = "nlu-sv";

bool selection = false;
bool updateScreen = true;

String textFilePath = "/data.txt";
String textFileUrlPath = "/config.json";
String textFileUrl = "";
String textFile = "";

String dictionary[] = {"Hey?","Look here","Hide","Careful!","Need help","Not funny","Look out","Behind You","Almost done","Times up"};
int wordCount = 0;

int scrollyDir = 0;

String sentText = "";

OneButton upButton(12, true);
OneButton downButton(13, true);

FirebaseData firebaseData;
FirebaseAuth auth;
FirebaseConfig config;

ESP8266WebServer server(80);

IPAddress local_ip(192,168,11,4);
IPAddress gateway(192,168,11,1);
IPAddress netmask(255,255,255,0);

U8G2_SH1106_128X64_NONAME_F_HW_I2C display(U8G2_R0, /* reset=*/ OLED_RESET);



void setup() {
  config.database_url = FIREBASE_HOST;
  config.api_key = FIREBASE_AUTH;
  Firebase.begin(&config,&auth);
  Firebase.reconnectWiFi(true);

  if (!SPIFFS.begin()) {
    // SPIFFS initialization failed.
  }

  upButton.attachClick(singleTapUp);
  downButton.attachClick(singleTapDown);

  upButton.attachDoubleClick(doubleTapUp);
  downButton.attachDoubleClick(doubleTapDown);

  upButton.attachDuringLongPress(longPressUp);
  downButton.attachDuringLongPress(longPressDown);

  upButton.attachLongPressStop(longPressStopUp);
  downButton.attachLongPressStop(longPressStopDown);

  upButton.setDebounceTicks(80);
  downButton.setDebounceTicks(80);

  if (!display.begin()) {
    // SH1106 allocation failed
    for (;;) {}
  }
  
  text("You Cheat!",2,0,0,true,false); 
  delay(2000);
  readFlashJson();
  bootServer();
  readDownloads();
}

void loop() {
  server.handleClient();
  
  upButton.tick();
  downButton.tick();
  
  unsigned long now = millis();
  
  if (updateScreen) {
    selectedScreen();
    updateScreen = false;
  }
}
