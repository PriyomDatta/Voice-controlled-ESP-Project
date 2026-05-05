// Copyright 2024 Espressif Systems (Shanghai) PTE LTD
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at

//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include <Arduino.h>
#include <WiFi.h>
#include <ESPmDNS.h>
#include <NetworkUdp.h>
#include <ArduinoOTA.h>
/*****************************Priyom's code start*****************************/
#include "BluetoothSerial.h"

BluetoothSerial SerialBT;
const int LED_PIN = 2; // Built-in LED on most ESP32 boards
const int PIN_OPEN_FRONT = 13;
const int PIN_CLOSE_FRONT = 12;
const int PIN_OPEN_REAR = 14;
const int PIN_CLOSE_REAR = 27;

#define OPEN_FRONT_NORMAL_STATE  LOW  //set as HIGH/LOW
#define CLOSE_FRONT_NORMAL_STATE  LOW  //set as HIGH/LOW
#define OPEN_REAR_NORMAL_STATE  LOW  //set as HIGH/LOW
#define CLOSE_REAR_NORMAL_STATE  LOW  //set as HIGH/LOW
#define LED_NORMAL_STATE  LOW  //set as HIGH/LOW
/*****************************Priyom's code end*****************************/

const char *ssid = "PriyomPriyom";
const char *password = "1234priyom";
uint32_t last_ota_time = 0;

void setup() {
  Serial.begin(115200);
  //Serial.println("Booting");
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  //while (WiFi.waitForConnectResult() != WL_CONNECTED) {
    //Serial.println("Connection Failed! Rebooting...");
  //  delay(5000);
  //  ESP.restart();
  //}

  // Port defaults to 3232
  // ArduinoOTA.setPort(3232);

  // Hostname defaults to esp3232-[MAC]
  ArduinoOTA.setHostname("myesp32");

  // Password can be set with plain text (will be hashed internally)
  // The authentication uses PBKDF2-HMAC-SHA256 with 10,000 iterations
   ArduinoOTA.setPassword("admin");

  // Or set password with pre-hashed value (SHA256 hash of "admin")
  // SHA256(admin) = 8c6976e5b5410415bde908bd4dee15dfb167a9c873fc4bb8a81f6f2ab448a918
  // ArduinoOTA.setPasswordHash("8c6976e5b5410415bde908bd4dee15dfb167a9c873fc4bb8a81f6f2ab448a918");

  ArduinoOTA
    .onStart([]() {
      String type;
      if (ArduinoOTA.getCommand() == U_FLASH) {
        type = "sketch";
      } else {  // U_SPIFFS
        type = "filesystem";
      }

      // NOTE: if updating SPIFFS this would be the place to unmount SPIFFS using SPIFFS.end()
      //Serial.println("Start updating " + type);
    })
    .onEnd([]() {
      //Serial.println("\nEnd");
    })
    .onProgress([](unsigned int progress, unsigned int total) {
      if (millis() - last_ota_time > 500) {
        Serial.printf("Progress: %u%%\n", (progress / (total / 100)));
        last_ota_time = millis();
      }
    })
    .onError([](ota_error_t error) {
      Serial.printf("Error[%u]: ", error);
      if (error == OTA_AUTH_ERROR) {
        //Serial.println("Auth Failed");
      } else if (error == OTA_BEGIN_ERROR) {
        //Serial.println("Begin Failed");
      } else if (error == OTA_CONNECT_ERROR) {
        //Serial.println("Connect Failed");
      } else if (error == OTA_RECEIVE_ERROR) {
        //Serial.println("Receive Failed");
      } else if (error == OTA_END_ERROR) {
        //Serial.println("End Failed");
      }
    });

  ArduinoOTA.begin();

  //Serial.println("Ready");
  Serial.print("IP address: ");
  //Serial.println(WiFi.localIP());
/*****************************Priyom's code start*****************************/
pinMode(PIN_OPEN_FRONT, OUTPUT);
  pinMode(PIN_CLOSE_FRONT, OUTPUT);
  pinMode(PIN_OPEN_REAR, OUTPUT);
  pinMode(PIN_CLOSE_REAR, OUTPUT);
  pinMode(LED_PIN, OUTPUT);  //
  Serial.begin(9600);
  digitalWrite(PIN_OPEN_FRONT, OPEN_FRONT_NORMAL_STATE);
  digitalWrite(PIN_CLOSE_FRONT, CLOSE_FRONT_NORMAL_STATE);
  digitalWrite(PIN_OPEN_REAR, OPEN_REAR_NORMAL_STATE);
  digitalWrite(PIN_CLOSE_REAR, CLOSE_REAR_NORMAL_STATE);

  // Start Classic Bluetooth with a custom device name
  if (!SerialBT.begin("Smart_Door_Control")) {
    //Serial.println("An error occurred initializing Bluetooth");
  } else {
    //Serial.println("Bluetooth started. Pair with 'Smart_Door_Control'.");
  }

  digitalWrite(LED_PIN, !LED_NORMAL_STATE); // Indecator
  delay(100);
  digitalWrite(LED_PIN, LED_NORMAL_STATE); // Indecator
/*****************************Priyom's code end*****************************/

}

void loop() {
  ArduinoOTA.handle();
  /*****************************Priyom's code start*****************************/
if (SerialBT.available()) {
    char command = SerialBT.read();
    SerialBT.write(1);
    if (command == '1') {
      digitalWrite(PIN_OPEN_FRONT, !OPEN_FRONT_NORMAL_STATE); // Turn LED ON
      digitalWrite(LED_PIN, !LED_NORMAL_STATE); // Turn LED ON
      delay(100);
      ////Serial.println("LED ON");
      digitalWrite(PIN_OPEN_FRONT, OPEN_FRONT_NORMAL_STATE);
      digitalWrite(LED_PIN, LED_NORMAL_STATE); // Turn LED ON
    } else if (command == '0') {
      digitalWrite(PIN_CLOSE_FRONT, !CLOSE_FRONT_NORMAL_STATE); // Turn LED ON
      digitalWrite(LED_PIN, !LED_NORMAL_STATE); // Turn LED ON
      delay(100);
      ////Serial.println("LED ON");
      digitalWrite(PIN_CLOSE_FRONT, CLOSE_FRONT_NORMAL_STATE);
      digitalWrite(LED_PIN, LED_NORMAL_STATE); // Turn LED ON
    } else if (command == '3') {
      digitalWrite(PIN_OPEN_REAR, !OPEN_REAR_NORMAL_STATE); // Turn LED ON
      digitalWrite(LED_PIN, !LED_NORMAL_STATE); // Turn LED ON
      delay(100);
      ////Serial.println("LED ON");
      digitalWrite(PIN_OPEN_REAR, OPEN_REAR_NORMAL_STATE);
      digitalWrite(LED_PIN, LED_NORMAL_STATE); // Turn LED ON
    } else if (command == '2') {
      digitalWrite(PIN_CLOSE_REAR, !CLOSE_REAR_NORMAL_STATE); // Turn LED ON
      digitalWrite(LED_PIN, !LED_NORMAL_STATE); // Turn LED ON
      delay(100);
      ////Serial.println("LED ON");
      digitalWrite(PIN_CLOSE_REAR, CLOSE_REAR_NORMAL_STATE);
      digitalWrite(LED_PIN, LED_NORMAL_STATE); // Turn LED ON
    } else if (command == '4') {
      digitalWrite(PIN_OPEN_REAR, !OPEN_REAR_NORMAL_STATE); // Turn LED ON
      digitalWrite(PIN_OPEN_FRONT, !OPEN_FRONT_NORMAL_STATE);
      digitalWrite(LED_PIN, !LED_NORMAL_STATE); // Turn LED ON
      delay(100);
      ////Serial.println("LED ON");
      digitalWrite(PIN_OPEN_REAR, OPEN_REAR_NORMAL_STATE);
      digitalWrite(PIN_OPEN_FRONT, OPEN_FRONT_NORMAL_STATE);
      digitalWrite(LED_PIN, LED_NORMAL_STATE); // Turn LED ON
    }else if (command == '5') {
      digitalWrite(PIN_CLOSE_REAR, !CLOSE_REAR_NORMAL_STATE); // Turn LED ON
      digitalWrite(PIN_CLOSE_FRONT, !CLOSE_FRONT_NORMAL_STATE);
      digitalWrite(LED_PIN, !LED_NORMAL_STATE); // Turn LED ON
      delay(100);
      ////Serial.println("LED ON");
      digitalWrite(PIN_CLOSE_REAR, CLOSE_REAR_NORMAL_STATE);
      digitalWrite(PIN_CLOSE_FRONT, CLOSE_FRONT_NORMAL_STATE);
      digitalWrite(LED_PIN, LED_NORMAL_STATE); // Turn LED ON
    }
  }
  /*****************************Priyom's code end*****************************/
}
