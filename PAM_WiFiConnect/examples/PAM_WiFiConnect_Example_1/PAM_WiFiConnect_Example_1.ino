//////////////////////////////////////////////////////////////////////
//
//                    PI and more
//              PAM_WiFiConnect library
//
// https://piandmore.wordpress.com/tag/pam_wificonnect
//
//////////////////////////////////////////////////////////////////////
//
// Include the PAM_WiFiConnect library
//
#include <PAM_WiFiConnect.h>
//
// Include the ESP8266WiFi library
//
#include <ESP8266WiFi.h>

void setup() {
  //
  // Connect to your wifi
  //
  wifiConnect("mySSID","myPassword");
  if (WiFi.status()==WL_CONNECTED) {
    //
    // success connecting
    //
  } else {
    //
    // failed to connect
    //
  }
}

void loop() {

}
