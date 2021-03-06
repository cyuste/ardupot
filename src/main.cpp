#include <Arduino.h>
#include <ESPmDNS.h>
#include <WiFi.h>
#include "hygrometer.h"
#include "daemonHygro.h"
#include "httpServer.h"
#include "relay.h"
#include "httpAp.h"
#include "potParams.h"

#define HYGROMETER_PORT A0
#define MIN_HUMIDITY 5000
#define WATER_TIME_MS 30000

#define RELAY_PORT 8
#define DNS_NAME "esp32"
#define HTTP_LISTEN_PORT 80

Relay pump = Relay(RELAY_PORT);
Hygrometer hygro = Hygrometer(HYGROMETER_PORT);
DaemonHygro dhygro = DaemonHygro(&pump, &hygro, WATER_TIME_MS, MIN_HUMIDITY);
ESP32WebServer ws = ESP32WebServer(HTTP_LISTEN_PORT);
HttpServer httpServer = HttpServer(&dhygro, &ws);
HttpAp ap = HttpAp(&ws);
TaskHandle_t hygroTask;
TaskHandle_t httpTask;
TaskHandle_t apTask;

void setUpDns() {
  if (!MDNS.begin(DNS_NAME)) {
    Serial.println("Error setting up MDNS responder!");
    while(1) {
        delay(1000);
    }
  }
  Serial.println("mDNS responder started");
}

int setupWifi()
{
  int connectionAttemps = 0;

  String ssid = getSSID();
  String password = getPassword();
  // Connect to WiFi network
  Serial.println();
  Serial.println();
  Serial.print(F("Connecting to "));
  Serial.println(ssid);

  WiFi.mode(WIFI_STA);

  WiFi.begin(ssid.c_str(), password.c_str());
  while (WiFi.status() != WL_CONNECTED && connectionAttemps < 20)
  {
    connectionAttemps++;
    delay(500);
    Serial.print(F("."));
  }
  if (WiFi.status() != WL_CONNECTED)
  {
    Serial.println(F("WiFi not connected. Changing to AP mode"));
    return 0;
  }
  Serial.println(F("WiFi connected"));
  Serial.println("");
  Serial.println(WiFi.localIP());
  return 1;
}

void dhygroLoop(void * pvParameters)
{
  Serial.print("Hygrometer loop running on core ");
  Serial.println(xPortGetCoreID());
  for(;;)
  {
    dhygro.loop();
  }
}

void httpServerLoop(void * pvParameters)
{
  Serial.print("HTTP server loop running on core ");
  Serial.println(xPortGetCoreID());
  for(;;)
  {
    httpServer.loop();
  }
}

void apServerLoop(void * pvParameters)
{
  Serial.print("Config Mode, running on core ");
  Serial.println(xPortGetCoreID());
  for(;;)
  {
    ap.handleClient();
  }
}

void setup()
{
  Serial.begin(115200);
  Serial.println(F("Initializing..."));
  pump.init();
  if (setupWifi())
  {
    setUpDns();
    httpServer.init();
    Serial.println(F("Initialization Done! Delaying start"));
    delay(1000);
    Serial.println(F("GO!"));
    xTaskCreatePinnedToCore(
                      dhygroLoop,   /* Task function. */
                      "Task1",     /* name of task. */
                      10000,       /* Stack size of task */
                      NULL,        /* parameter of the task */
                      1,           /* priority of the task */
                      &hygroTask,      /* Task handle to keep track of created task */
                      0);          /* pin task to core 0 */                  
    delay(500); 
    xTaskCreatePinnedToCore(
                      httpServerLoop,   /* Task function. */
                      "Task2",     /* name of task. */
                      10000,       /* Stack size of task */
                      NULL,        /* parameter of the task */
                      1,           /* priority of the task */
                      &httpTask,      /* Task handle to keep track of created task */
                      1);          /* pin task to core 0 */    
  }
  else
  {
    ap.configMode();
    xTaskCreatePinnedToCore(
                  apServerLoop,   /* Task function. */
                  "Task3",     /* name of task. */
                  10000,       /* Stack size of task */
                  NULL,        /* parameter of the task */
                  1,           /* priority of the task */
                  &apTask,      /* Task handle to keep track of created task */
                  0);          /* pin task to core 0 */     
  }
}

void loop() {
}

