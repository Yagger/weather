#include <common.h>

void setup()
{
  // Serial.begin(115200);

  EEPROM.begin(EEPROM_SIZE);
  EEPROM.get(0, conf);

  if ((String)conf.cityID == "" || strlen(conf.cityID) == 0)
  {
    // initialize config
    initialCityID.toCharArray(conf.cityID, initialCityID.length() + 1);
    EEPROM.put(0, conf);
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
}

void loop()
{
  wm.process();
  m = millis();
  server.handleClient();
  timeClient.update();
  b1.loop();
  b2.loop();
  b3.loop();
  b4.loop();
  mx.setFont(&Org_01);
  mx.setBrightness(brightness);

  Serial.println(WiFi.status());
  if (WiFi.status() == WL_CONNECTED)
  {
    noInternetSince = 0;
    mx.clear();
    if ((String)conf.cityID == "unknown" || showConfigScreen)
    {
      info2(WiFi.localIP().toString(), true);
    }
    else
    {
      if (jsonFetchError != "" && m - jsonFetchErrorSince > 30000)
      {
        error("Error: " + jsonFetchError, false);
        mx.show();
        if (m - jsonLastFetched >= 5000)
        {
          loadData();
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
        loadData();
        isInitialLoading = false;
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
    else if (m - noInternetSince > 30000)
    {
      mx.clear();
      info1("Connect to '" + (String)apName + "' WiFi network", true);
    }
    else if (isInitialLoading)
    {
      mx.clear();
      info1("Loading", false);
    }
  }

  checkReset();
  checkConfigure();
  checkPresses();

  mx.show();
}
