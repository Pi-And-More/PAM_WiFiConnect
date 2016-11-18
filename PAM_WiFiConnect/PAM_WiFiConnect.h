#ifndef PAM_WiFiConnect_H
#define PAM_WiFiConnect_H

#include <Arduino.h>

void wifiConnect (String, String);
void wifiConnect (String);
void wifiConnect ();
void wifiConnect (bool);
void waitWiFiConnect (bool);
void waitWiFiConnect ();

#endif
