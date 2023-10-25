#include "common.h"

void renderClock(int h1, int h2, int m1, int m2, int t1, int t2, int temp, int tempMode, int curTemp);
uint16_t tempColor(int temp);
void renderWeather();

void showWeather()
{
    if ((showTempMode == 0 && m - showTempModeLast > 5000) || (showTempMode != 0 && m - showTempModeLast > 2000))
    {
        showTempModeLast = m;
        showTempMode++;
        if (showTempMode > 2)
        {
            showTempMode = 0;
        }
    }
    if (m - groupByLast > 30000)
    {
        groupByLast = m;
        if (groupBy != 3)
        {
            groupBy = 3;
        }
        else
        {
            groupBy = 1;
        }
        jsonLastFetched = 0;
    }
    int currentTemp = jsonDoc["Data"][0]["Temp"];
    int maxTemp = currentTemp;
    int minTemp = currentTemp;
    int temp = currentTemp;
    for (int i = 0; i < COLS; i++)
    {
        temp = jsonDoc["Data"][i]["Temp"];
        if (temp > maxTemp)
        {
            maxTemp = temp;
        }
        if (temp < minTemp)
        {
            minTemp = temp;
        }
    }
    if (showTempMode == 0)
    {
        temp = currentTemp;
    }
    else if (showTempMode == 1)
    {
        temp = maxTemp;
    }
    else
    {
        temp = minTemp;
    }
    int hours = timeClient.getHours();
    int minutes = timeClient.getMinutes();
    // int seconds = timeClient.getSeconds();
    unsigned h2 = (hours / 1U) % 10;
    unsigned h1 = (hours / 10U) % 10;
    unsigned m2 = (minutes / 1U) % 10;
    unsigned m1 = (minutes / 10U) % 10;
    // unsigned s2 = (seconds / 1U) % 10;
    // unsigned s1 = (seconds / 10U) % 10;
    unsigned t2 = (temp / 1U) % 10;
    unsigned t1 = (temp / 10U) % 10;
    renderClock(h1, h2, m1, m2, t1, t2, temp, showTempMode, currentTemp);
    renderWeather();
}

void renderClock(int h1, int h2, int m1, int m2, int t1, int t2, int temp, int tempMode, int curTemp)
{
    mx.fillRect(0, 0, COLS, 5, 0);
    mx.setFont(&ClockCompact);
    mx.setTextColor(mx.hsv(timeH, timeS, 255));

    // time
    mx.setCursor(0, 5);
    mx.print(String(h1));
    mx.print(" ");
    mx.print(String(h2));
    mx.print(" : ");
    mx.print(String(m1));
    mx.print(" ");
    mx.print(String(m2));

    // temp
    uint16_t color = tempColor(curTemp);
    mx.setTextColor(color);
    if (tempMode == 0 || temp == curTemp)
    {
        mx.setCursor(21, 5);
        if (temp > 0)
        {
            mx.print("+");
            mx.print(" ");
        }
        else if (temp < 0)
        {
            mx.print("-");
            mx.print(" ");
        }
        else
        {
            mx.print("    ");
        }
    }
    else if (tempMode == 1)
    {
        mx.px(21, 1, color);
        mx.px(22, 0, color);
        mx.px(23, 1, color);
        mx.setCursor(25, 5);
    }
    else
    {
        mx.px(21, 3, color);
        mx.px(22, 4, color);
        mx.px(23, 3, color);
        mx.setCursor(25, 5);
    }
    mx.print(String(t1));
    mx.print(" ");
    mx.print(String(t2));
}

uint16_t tempColor(int temp)
{
    int h = 0;
    if (temp <= 0)
    {
        h = 145;
    }
    else if (temp <= 10)
    {
        h = 138;
    }
    else if (temp <= 18)
    {
        h = 128;
    }
    else if (temp <= 26)
    {
        h = 30;
    }
    else
    {
        h = 0;
    }

    return mx.hsv(h, 225, 255);
}

void renderWeather()
{
    mx.fillRect(0, 5, COLS, 11, 0);
    float temp = jsonDoc["Data"][0]["Temp"];
    float maxTemp = temp;
    float minTemp = temp;
    float wind = jsonDoc["Data"][0]["Wind"];
    float maxWind = wind;
    float minWind = wind;
    float precip = jsonDoc["Data"][0]["Precip"];
    float maxPrecip = precip;
    float minPrecip = precip;
    float tempFrac = 0;
    for (int i = 0; i < COLS; i++)
    {
        temp = jsonDoc["Data"][i]["Temp"];
        if (temp > maxTemp)
        {
            maxTemp = temp;
        }
        if (temp < minTemp)
        {
            minTemp = temp;
        }
        wind = jsonDoc["Data"][i]["Wind"];
        if (wind > maxWind)
        {
            maxWind = wind;
        }
        if (wind < minWind)
        {
            minWind = wind;
        }
        precip = jsonDoc["Data"][i]["Precip"];
        if (precip > maxPrecip)
        {
            maxPrecip = precip;
        }
        if (precip < minPrecip)
        {
            minPrecip = precip;
        }
    }
    for (int i = 0; i < COLS; i++)
    {
        // Sky
        String sky = jsonDoc["Data"][i]["Sky"];
        uint16_t color = 0;
        if (sky == "sunny")
        {
            color = mx.hsv(0, 0, 255);
        }
        else if (sky == "fair")
        {
            color = mx.hsv(0, 0, 200);
        }
        else if (sky == "cloudy")
        {
            color = mx.hsv(0, 0, 125);
        }
        else if (sky != "night")
        {
            color = mx.hsv(0, 0, 125);
        }
        mx.px(i, 5, color);
        // Precip
        precip = jsonDoc["Data"][i]["Precip"];
        if (precip > 0)
        {
            mx.px(i, 6, mx.hsv(153, 255, 255));
        }
        if (precip > 2)
        {
            mx.px(i, 7, mx.hsv(153, 255, 255));
        }
        if (precip > 5)
        {
            mx.px(i, 8, mx.hsv(153, 255, 255));
        }
        // Temp
        temp = jsonDoc["Data"][i]["Temp"];
        tempFrac = (maxTemp - minTemp) / 6;
        mx.px(i, 14, mx.hsv(tempH, 170, 255));
        if (temp > minTemp + (tempFrac * 1.5))
        {
            mx.px(i, 13, mx.hsv(tempH, 187, 255));
        }
        if (temp > minTemp + (tempFrac * 2.5))
        {
            mx.px(i, 12, mx.hsv(tempH, 204, 255));
        }
        if (temp > minTemp + (tempFrac * 3.5))
        {
            mx.px(i, 11, mx.hsv(tempH, 221, 255));
        }
        if (temp > minTemp + (tempFrac * 4.5))
        {
            mx.px(i, 10, mx.hsv(tempH, 238, 255));
        }
        if (temp > minTemp + (tempFrac * 5.5))
        {
            mx.px(i, 9, mx.hsv(tempH, 255, 255));
        }
        // Wind
        wind = jsonDoc["Data"][i]["Wind"];
        if (wind > 6)
        {
            mx.px(i, 15, mx.hsv(80, 100, 255));
        }
        if (wind > 9)
        {
            mx.px(i, 15, mx.hsv(0, 100, 255));
        }
        if (wind > 15)
        {
            mx.px(i, 15, mx.hsv(0, 255, 255));
        }
    }
}