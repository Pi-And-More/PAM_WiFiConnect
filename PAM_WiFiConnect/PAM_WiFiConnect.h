#ifndef PAM_WiFiConnect_H
#define PAM_WiFiConnect_H

#include <Arduino.h>

void wifiConnect (String, String);
void wifiConnectGetPW (String);
void wifiAutoConnect ();
void wifiAutoConnect (boolean);

#endif
