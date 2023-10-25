#include "common.h"

void loadData()
{
    jsonLastFetched = m;
    WiFiClient client;
    HTTPClient http;
    String url = "http://misc.bux.ee/forecast/" + String(conf.cityID) +
                 "?limit=" + String(COLS) +
                 "&groupBy=" + String(groupBy);
    http.begin(client, url.c_str());
    int httpResponseCode = http.GET();
    if (httpResponseCode > 0)
    {
        // Serial.print("HTTP Response code: ");
        // Serial.println(httpResponseCode);
        String payload = http.getString();
        // Serial.println(payload);
        auto error = deserializeJson(jsonDoc, payload);
        if (error)
        {
            // Serial.print(F("deserializeJson() failed with code "));
            // Serial.println(error.c_str());
            jsonFetchError = error.c_str();
            jsonFetchErrorSince = m;
            http.end();
            return;
        }
    }
    else
    {
        // Serial.print("Error code: ");
        // Serial.println(httpResponseCode);
        jsonFetchError = (String)httpResponseCode;
        jsonFetchErrorSince = m;
        http.end();
        return;
    }
    timeClient.setTimeOffset(jsonDoc["CityInfo"]["Offset"]);
    jsonFetchError = "";
    jsonFetchErrorSince = 0;
    isInitialLoading = false;
    // Free resources
    http.end();
}

void loadData2(DynamicJsonDocument *jsonDoc_, unsigned int hours_)
{
    jsonLastFetched = m;
    WiFiClient client;
    HTTPClient http;
    String url = "http://misc.bux.ee/forecast/" + String(conf.cityID) +
                 "?limit=" + String(COLS) +
                 "&groupBy=" + String(hours_);
    http.begin(client, url.c_str());
    int httpResponseCode = http.GET();
    if (httpResponseCode > 0)
    {
        // Serial.print("HTTP Response code: ");
        // Serial.println(httpResponseCode);
        String payload = http.getString();
        // Serial.println(payload);
        auto error = deserializeJson(*jsonDoc_, payload);
        if (error)
        {
            // Serial.print(F("deserializeJson() failed with code "));
            // Serial.println(error.c_str());
            jsonFetchError = error.c_str();
            jsonFetchErrorSince = m;
            http.end();
            return;
        }
    }
    else
    {
        // Serial.print("Error code: ");
        // Serial.println(httpResponseCode);
        jsonFetchError = (String)httpResponseCode;
        jsonFetchErrorSince = m;
        http.end();
        return;
    }
    timeClient.setTimeOffset((*jsonDoc_)["CityInfo"]["Offset"]);
    jsonFetchError = "";
    jsonFetchErrorSince = 0;
    isInitialLoading = false;
    // Free resources
    http.end();
}