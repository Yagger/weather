#include <Arduino.h>
#include <LedMatrix.h>
#include <debounce.h>
#include <WiFiManager.h>
#include <EEPROM.h>
#include <FastLED.h>
#include <FastLED_NeoMatrix.h>
#include <Fonts/Org_01.h>
#include <Fonts/mini.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <ArduinoJson.h>
#include <NTPClient.h>
#include <WiFiUdp.h>
#include <ESP8266HTTPClient.h>

#define BUT1 D5
#define BUT2 D6
#define BUT3 D7
#define BUT4 D1
#define ROWS 16
#define COLS 32
#define EEPROM_SIZE 1024 * 4

struct Conf
{
    char status[255];
    char cityID[255];
    int tempH;
    int tempS;
    int timeH;
    int timeS;
};

void loadData(DynamicJsonDocument *jsonDoc_, unsigned int hours_);
void showWeather();
void checkReset();
void checkConfigure();
void checkPresses();
String getParam(String name);
void saveParamCallback();
void handleGet();
void handlePost();
void handle_NotFound();
void textOnBg(String text, uint16_t bgColor, uint16_t textColor, bool scroll);
void info1(String text, bool scroll);
void info2(String text, bool scroll);
void warning(String text, bool scroll);
void error(String text, bool scroll);

extern unsigned int m;
extern Conf conf;
extern int brightness;
extern int groupBy;
extern int groupByLast;
extern int timeH;
extern int timeS;
extern bool timeSUp;
extern int tempH;
extern int tempS;
extern bool tempSUp;
extern unsigned int saveColorsInConfAt;
extern int showTempMode;
extern unsigned int showTempModeLast;
extern String const configStatusInitialized;
extern LedMatrix mx;
extern WiFiManager wm;
extern ESP8266WebServer server;
extern char const *apName;
extern debounce b1;
extern debounce b2;
extern debounce b3;
extern debounce b4;
extern char const *apName;
extern unsigned int resetSpeed;
extern unsigned int configSpeed;
extern unsigned int jsonLastFetched;
extern unsigned int jsonFetchPeriod;
extern String jsonFetchError;
extern unsigned int jsonFetchErrorSince;
extern bool showConfigScreen;
extern WiFiUDP ntpUDP;
extern NTPClient timeClient;
extern const long utcOffset;
extern DynamicJsonDocument jsonDoc1Hour;
extern DynamicJsonDocument jsonDoc3Hours;
extern unsigned int lastNTPUpdate;
extern unsigned int noInternetSince;
extern bool isInitialLoading;
extern unsigned int timeUpdatedLast;