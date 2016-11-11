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
  // If you do not provide a password, wifiConnect will look for it
  // in the file system.
  //
  // Remember, for this to work, there needs to be a directory on the file system
  // called wifi which contain your credentials.
  //
  // If you wish to connect to a wifi network without a password you
  // would use:
  // wifiConnect("YourSSID","");
  //
  wifiConnect("mySSID");
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
