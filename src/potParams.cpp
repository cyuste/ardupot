#include "potParams.h"

Preferences preferences;

String getSSID()
{
  String ssid;
  preferences.begin(APP_NAME, true);
  ssid = preferences.getString(SSID_KEY, "no_wifi");
  preferences.end();
  return ssid;
}

String getPassword()
{
  String password;
  preferences.begin(APP_NAME, true);
  password = preferences.getString(PASSWD_KEY, "no_passwd");
  preferences.end();
  return password;
}

int storeSettings(const String* ssid, const String* password)
{
  preferences.begin(APP_NAME, false);
  preferences.putString(SSID_KEY, *ssid);
  preferences.putString(PASSWD_KEY, *password);
  preferences.end();
  return 0;
}