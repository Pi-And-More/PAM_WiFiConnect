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
  // Connect to your wifi.
  // If you do not provide any SSID, wifiConnect will automatically try to connect
  // to know networks by scanning the available wifi networks and checking
  // if it has credentials.
  //
  // Remember, for this to work, there needs to be a directory on the file system
  // called wifi which contain your credentials.
  //
  wifiConnect();
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
