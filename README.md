# PAM_WiFiConnect

An extension for the ESP8266WiFi library which allows for a.o. connecting to a wireless lan by providing just the SSID and the keys are stored in files in SPIFFS.
It requires the PAM_Tools library

The functions contained in it are:

//
// wifiConnect will connect you to wifi network using
// the supplied credentials. It will than wait to connect
// for up to 5 times 10 seconds. 
//
void wifiConnect (String ssid, String password)

//
// wifiConnectGetPW allows you to connect to a wifi by providing just the
// ssid. The password is retrieved from the file system.
//
void wifiConnectGetPW (String ssid)

//
// The wifiAutoConnect function allows you to have your device connect to an
// available wifi point that it knows the password to. The way it does that is
// by having all the passwords of your available wifi ssid's stored in the file system,
// more specifically in the folder called wifi. Each file in the folder wifi, will have the
// ssid name as it's file name followed by the extension .txt. The content of the file will be
// one string containing the password for that ssid.
// wifi/myssid1.txt will contain for example mypassword1
// wifi.myssid2.txt will contain for example mypassword2
//
// What wifiAutoConnect will do is get a list of all available wifi ssid's and cycle through
// each one to see if there is an associated password know. If there is, it connects to
// that network. If there isn't, it moves on to the next.
//
// There are two special cases. If you have a preffered network, your home one for example,
// you can put the name of the ssid in the file called wifi/1.txt. The next preferred 
// network will be in 2.txt etc. wifiAutoConnect will try to connect to those first.
// If no network is found matching any of the credentials, it will connect to the network
// in wifi/0.txt which could be a hidden ssid.
//
// Please note that wifiAutoConnect will only see broadcasted ssid's and only as a final
// resort connect to the ssid in 0.txt.
//
// You can start the function with (true) in which case there will be information about
// the found networks etc printed to Serial.
//
void wifiAutoConnect ()
void wifiAutoConnect (bool debug)

//
// Sometimes you have an IoT device where you need an internet connection
// for example for a logger of some sort. In those cases, the wifi connection
// needs to be up. This function, which you can call in your setup,
// will continiously try to connect to the wifi and will not return to
// setup until it does have a connection.
//
void waitWiFiConnect ()

You can read about it in more detail on https://piandmore.wordpress.com/tag/pam_wificonnect/
