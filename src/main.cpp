#include <common.h>

String initialCityID = "unknown";

void saveColorConf()
{
  conf.tempH = tempH;
  conf.timeH = timeH;
  conf.timeS = timeS;
  EEPROM.begin(EEPROM_SIZE);
  EEPROM.put(0, conf);
  EEPROM.end();
}

void setup()
{
  Serial.begin(115200);

  EEPROM.begin(EEPROM_SIZE);
  EEPROM.get(0, conf);

  if ((String)conf.status != configStatusInitialized)
  {
    // initialize config
    initialCityID.toCharArray(conf.cityID, 255);
    configStatusInitialized.toCharArray(conf.status, 255);
    conf.tempH = tempH;
    conf.timeH = timeH;
    conf.timeS = timeS;
    EEPROM.put(0, conf);
  }
  else
  {
    // Uncomment to reset colors back to initial greenish
    saveColorConf();
    tempH = conf.tempH;
    timeH = conf.timeH;
    timeS = conf.timeS;
  }
  EEPROM.end();

  mx.clear();
  mx.show();

  WiFi.mode(WIFI_AP);
  wm.setConfigPortalBlocking(false);
  std::vector<const char *> menu = {"wifi", "sep", "info", "exit"};
  wm.setMenu(menu);
  if (!wm.autoConnect(apName))
  {
    // ESP has a known bug and may not connect, but on the second try it usually always works.
    wm.autoConnect(apName);
  }

  server.on("/", HTTP_GET, handleGet);
  server.on("/", HTTP_POST, handlePost);
  server.onNotFound(handle_NotFound);
  server.begin();

  timeClient.begin();
  timeClient.update();
}

void loop()
{
  wm.process();
  m = millis();
  server.handleClient();
  b1.loop();
  b2.loop();
  b3.loop();
  b4.loop();
  mx.setFont(&Org_01);
  mx.setBrightness(brightness);

  if (m - timeUpdatedLast > 1000 * 60 * 60)
  {
    timeUpdatedLast = m;
    timeClient.update();
  }

  if (saveColorsInConfAt != 0 && m > saveColorsInConfAt)
  {
    saveColorsInConfAt = 0;
    saveColorConf();
  }

  if (WiFi.status() == WL_CONNECTED)
  {
    noInternetSince = 0;
    if ((String)conf.cityID == initialCityID || showConfigScreen)
    {
      mx.clear();
      info2(WiFi.localIP().toString(), true);
    }
    else
    {
      if (jsonFetchError != "" && (isInitialLoading || m - jsonFetchErrorSince > 60000))
      {
        mx.clear();
        error("Error: " + jsonFetchError, true);
        mx.show();
        if (m - jsonLastFetched >= 5000)
        {
          loadData(&jsonDoc1Hour, 1);
          loadData(&jsonDoc3Hours, 3);
          // Serial.print("Data 1 loaded: ");
          // String temp1 = jsonDoc1Hour["Data"][0]["Sky"];
          // Serial.println(temp1);
          // Serial.print("Data 3 loaded: ");
          // String temp3 = jsonDoc3Hours["Data"][0]["Sky"];
          // Serial.println(temp3);
        }
      }
      else if (jsonLastFetched == 0 || m - jsonLastFetched >= jsonFetchPeriod)
      {
        if (isInitialLoading)
        {
          mx.clear();
          info1("Loading", false);
          mx.show();
        }
        loadData(&jsonDoc1Hour, 1);
        loadData(&jsonDoc3Hours, 3);
        // Serial.print("Data 1 loaded: ");
        // String temp1 = jsonDoc1Hour["Data"][0]["Sky"];
        // Serial.println(temp1);
        // Serial.print("Data 3 loaded: ");
        // String temp3 = jsonDoc3Hours["Data"][0]["Sky"];
        // Serial.println(temp3);
      }
      else
      {
        showWeather();
      }
    }
  }
  else
  {
    if (noInternetSince == 0)
    {
      noInternetSince = m;
    }
    else if (isInitialLoading || m - noInternetSince > 30000)
    {
      mx.clear();
      info1("Connect to '" + (String)apName + "' WiFi network", true);
    }
  }

  checkReset();
  checkConfigure();
  checkPresses();

  mx.show();
}
