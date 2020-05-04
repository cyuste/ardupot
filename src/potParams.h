#ifndef POTPARAMS_H
#define POTPARAMS_H

#include <Arduino.h>
#include <Preferences.h>

#define APP_NAME "iflowerpot"
#define SSID_KEY "ssid"
#define PASSWD_KEY "paswd"

String getSSID();
String getPassword();
int storeSettings(const String* ssid, const String* password);

#endif