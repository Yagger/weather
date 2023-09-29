#include <common.h>

void checkReset()
{
    if (b1.isDown())
    {
        if (b1.getCurrentSteadyStateDuration() >= 2000 + (unsigned int)(COLS * resetSpeed + resetSpeed))
        {
            wm.resetSettings();
            EEPROM.begin(EEPROM_SIZE);
            for (int i = 0; i < EEPROM_SIZE; i++)
            {
                EEPROM.write(i, 0);
            }
            EEPROM.end();
            ESP.restart();
        }
        else
        {
            for (int i = COLS - 1; i >= 0; i--)
            {
                if (b1.getCurrentSteadyStateDuration() >= 2000 + (unsigned int)((i + 1) * resetSpeed))
                {
                    mx.fillRect(0, ROWS - 1, COLS - i, 1, mx.hsv(255, 200, 255));
                    break;
                }
            }
        }
    }
}

void checkConfigure()
{
    if (b2.isDown())
    {
        if (b2.getCurrentSteadyStateDuration() >= 2000 + (unsigned int)(COLS * configSpeed + configSpeed))
        {
            showConfigScreen = true;
        }
        else
        {
            for (int i = COLS - 1; i >= 0; i--)
            {
                if (b2.getCurrentSteadyStateDuration() >= 2000 + (unsigned int)((i + 1) * configSpeed))
                {
                    mx.fillRect(0, ROWS - 1, COLS - i, 1, mx.hsv(70, 150, 150));
                    break;
                }
            }
        }
    }
}

void checkPresses()
{
    if (b1.isClicked())
    {
        groupBy++;
        if (groupBy > 6)
        {
            groupBy = 1;
        }
        jsonLastFetched = 0;
    }
    if (b2.isClicked())
    {
        showConfigScreen = false;
    }
    if (b2.isDown())
    {
        brightness -= 5;
        if (brightness < 10)
        {
            brightness = 255;
        }
    }
    if (b3.isDown())
    {
        if (timeSUp)
        {
            timeS += 5;
            if (timeS > 255)
            {
                timeS = 255;
                timeSUp = false;
                timeH += 5;
            }
        }
        else
        {
            timeS -= 5;
            if (timeS < 100)
            {
                timeSUp = true;
                timeH += 5;
            }
        }
        if (timeH > 255)
        {
            timeH = 0;
        }
    }
    if (b4.isDown())
    {
        tempH++;
        if (tempH > 255)
        {
            tempH = 0;
        }
        // Serial.println(tempH);
    }
}