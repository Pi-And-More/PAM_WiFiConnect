//////////////////////////////////////////////////////////////////////
//
//                    PI and more
//              PAM_WiFiConnect library
//
// https://piandmore.wordpress.com/tag/pam_wificonnect
//
//////////////////////////////////////////////////////////////////////
//
// Include the PAM_WiFiConnect header
//
#include <PAM_WiFiConnect.h>
//
// Include the PAM_Tools library for the file system functions
//
#include <PAM_Tools.h>
//
// Include the ESP8266WiFi library for the ESP wifi functions
//
#include <ESP8266WiFi.h>

//
// wifiConnect will connect you to wifi network using
// the supplied credentials. It will than wait to connect
// for up to 5 times 10 seconds. 
//
void wifiConnect (String ssid, String password) {
  //
  // Convert ssid and password from String to a Char array
  //
  char xssid[50];
  ssid.toCharArray(xssid,50);
  char xpassword[50];
  password.toCharArray(xpassword,50);

  bool connected = false;
  byte cnt2 = 0;
  //
  // Wait in the loop while you are not connected to a wifi, boolean connected
  // accesspoint but a maximum of 5 iterations, byte cnt2.
  //
  while (!connected && cnt2<5) {
    //
    // Try to connect to a wifi accesspoint
    //
    WiFi.begin(xssid,xpassword);
    byte cnt = 0;

    //
    // Wait in the loop while we are not connected, WiFi.status()
    // but a maximum of 20 iterations, byte 20 after which we
    // disconnect from the wifi and try again.
    //
    while (WiFi.status()!=WL_CONNECTED && cnt<20) {
      delay(500);
      Serial.print(".");
      cnt++;
    }
    if (WiFi.status()!=WL_CONNECTED) {
      WiFi.disconnect();
    } else {
      connected = true;
    }
    Serial.println();
    cnt2++;
  }
}

//
// This instance of wifiConnect allows you to connect to a wifi by providing just the
// ssid. The password is retrieved from the file system.
//
void wifiConnect (String ssid) {
  //
  // The password is located in the folder wifi
  //
  String password = getStringKey("wifi",ssid);
  if (password!=NOSTRINGKEYFOUND) {
    wifiConnect(ssid,password);
  } else {
    WiFi.disconnect();
  }
}

//
// This instance of the wifiConnect function allows you to have your device connect to an
// available wifi point that it knows the password to. The way it does that is
// by having all the passwords of your available wifi ssid's stored in the file system,
// more specifically in the folder called wifi. Each file in the folder wifi, will have the
// ssid name as it's file name followed by the extension .txt. The content of the file will be
// one string containing the password for that ssid.
// wifi/myssid1.txt will contain for example mypassword1
// wifi.myssid2.txt will contain for example mypassword2
//
// What wifiConnect will do is get a list of all available wifi ssid's and cycle through
// each one to see if there is an associated password know. If there is, it connects to
// that network. If there isn't, it moves on to the next.
//
// There are two special cases. If you have a preffered network, your home one for example,
// you can put the name of the ssid in the file called wifi/1.txt. The next preferred 
// network will be in 2.txt etc. wifiConnect will try to connect to those first.
// If no network is found matching any of the credentials, it will connect to the network
// in wifi/0.txt which could be a hidden ssid.
//
// Please note that wifiConnect will only see broadcasted ssid's and only as a final
// resort connect to the ssid in 0.txt.
//
// You can start the function with (true) in which case there will be information about
// the found networks etc printed to Serial.
//
void wifiConnect (bool debug) {
  if (debug) {
    Serial.println("Trying to auto connect to wifi.");
  }
  byte j = 1;
  String found;
  //
  // First check if there are preferred networks. Please note that it assumes a consecutive
  // list of files, so 1.txt, 2.txt, 3.txt etc. If 2.txt for example is missing, the loop
  // stops and will not reach 3.txt
  //
  if (debug) {
    Serial.println("Scanning for wifi networks.");
  }
  int n = WiFi.scanNetworks();
  if (debug) {
    Serial.print("Found ");
    Serial.print(n);
    Serial.println(" networks:");
    Serial.println();
    for (int i=0;i<n;i++) {
      Serial.println(WiFi.SSID(i));
    }
    Serial.println();
    Serial.println("Checking for preferred networks");
  }
  do {
    found = getStringKey("wifi",String(j));
    if (found!=NOSTRINGKEYFOUND) {
      if (debug) {
        Serial.print("Checking for preferred network ");
        Serial.print(j);
        Serial.print(", ");
        Serial.println(found);
      }
      if (n>0) {
        for (int i=0;i<n;i++) {
          if (WiFi.SSID(i)==found) {
            //
            // One of the preferred networks is found. Connect to it by getting the password
            // and exit the function.
            //
            if (debug) {
              Serial.print("Going to connect to ");
              Serial.println(found);
            }
            wifiConnect(WiFi.SSID(i));
            if (WiFi.status()==WL_CONNECTED) {
              return;
            } else if (debug) {
              Serial.println("Connecting failed.");
            }
          }
        }
      }
      j++;
    }
  } while (found!=NOSTRINGKEYFOUND);
  if (debug) {
    Serial.println("Preferred networks not available.");
  }
  if (n>0) {
    for (int i=0;i<n;i++) {
      String pw = getStringKey("wifi",WiFi.SSID(i));
      if (pw!=NOSTRINGKEYFOUND) {
        //
        // A wifi network has been found for which we have a password. Connect to it and
        // exit the function.
        if (debug) {
          Serial.print("Going to connect to ");
          Serial.println(WiFi.SSID(i));
        }
        wifiConnect(WiFi.SSID(i),pw);
        return;
      }
    }
  }
  if (debug) {
    Serial.println("No network found with credentials.");
  }
  found = getStringKey("wifi",String(0));
  if (found!=NOSTRINGKEYFOUND) {
    //
    // Not connected to any network that has a visible ssid. Now try to connect to a
    // predefined, possibly hidden, ssid
    //
    if (debug) {
      Serial.print("Trying hidden SSID ");
      Serial.println(found);
    }
    wifiConnect(found);
  }
}

void wifiConnect () {
  wifiConnect(false);
}

//
// Sometimes you have an IoT device where you need an internet connection
// for example for a logger of some sort. In those cases, the wifi connection
// needs to be up. This function, which you can call in your setup,
// will continiously try to connect to the wifi and will not return to
// setup until it does have a connection.
//
void waitWiFiConnect (bool debug) {
  pinMode(2,OUTPUT);
  digitalWrite(2,LOW);
  bool connected = false;
  while (!connected) {
    wifiConnect(debug);
    if (WiFi.status()==WL_CONNECTED) {
      digitalWrite(2,HIGH);
      Serial.println(WiFi.localIP());
      connected = true;
    } else {
      digitalWrite(2,HIGH);
      delay(500);
      digitalWrite(2,LOW);
      if (debug) {
        Serial.println("Not connected, waiting 1 minute");
      }
      delay(60*1000);
    }
  }
}

void waitWiFiConnect () {
  waitWiFiConnect(false);
}
