#include <common.h>

unsigned int m = 0;
String const configStatusInitialized = "initialized";
int brightness = 150;
int groupBy = 1;
int groupByLast = 0;
int timeH = 80;
int timeS = 125;
bool timeSUp = false;
int tempH = 110;
unsigned int saveColorsInConfAt = 0;
int showTempMode = 0;
unsigned int showTempModeLast = 0;
char const *apName = "WT";
unsigned int resetSpeed = 200;
unsigned int configSpeed = 50;
unsigned int jsonLastFetched = 0;
unsigned int jsonFetchPeriod = 1000 * 60 * 10;
String jsonFetchError = "";
unsigned int jsonFetchErrorSince = 0;
bool showConfigScreen = false;
unsigned int lastNTPUpdate = 0;
unsigned int noInternetSince = 0;
bool isInitialLoading = true;
unsigned int timeUpdatedLast = 0;

Conf conf;
LedMatrix mx(ROWS, COLS, 5000);
WiFiManager wm;
ESP8266WebServer server(80);
DynamicJsonDocument jsonDoc1Hour(1024 * 8);
DynamicJsonDocument jsonDoc3Hours(1024 * 8);
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "pool.ntp.org");

debounce b1(BUT1, 50);
debounce b2(BUT2, 50);
debounce b3(BUT3, 50);
debounce b4(BUT4, 50);
