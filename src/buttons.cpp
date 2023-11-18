#include <common.h>

void checkReset()
{
    if (b1.isDown() && b2.isDown() && b3.isDown() && b4.isDown())
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
    if (b3.isDown() && b4.isDown() && !(b1.isDown() || b2.isDown()))
    {
        if (b3.getCurrentSteadyStateDuration() >= 2000 + (unsigned int)(COLS * configSpeed + configSpeed))
        {
            showConfigScreen = true;
        }
        else
        {
            for (int i = COLS - 1; i >= 0; i--)
            {
                if (b3.getCurrentSteadyStateDuration() >= 2000 + (unsigned int)((i + 1) * configSpeed))
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
    if (b1.isClicked() || b2.isClicked() || b3.isClicked() || b4.isClicked())
    {
        showConfigScreen = false;
    }

    // brightness
    if (b1.isDown() && b2.isDown() && !(b3.isDown() || b4.isDown()))
    {
        brightness -= 5;
        if (brightness < 10)
        {
            brightness = 255;
        }
    }

    // time color
    if (b1.isDown() && !(b2.isDown() || b3.isDown() || b4.isDown()))
    {
        if (timeSUp)
        {
            timeS += 10;
            if (timeS > 255)
            {
                timeS = 255;
                timeSUp = false;
                timeH += 5;
            }
        }
        else
        {
            timeS -= 10;
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
        saveColorsInConfAt = m + 5000;
    }
    if (b2.isDown() && !(b1.isDown() || b3.isDown() || b4.isDown()))
    {
        if (timeSUp)
        {
            timeS -= 10;
            if (timeS < 100)
            {
                timeSUp = false;
                timeH -= 5;
            }
        }
        else
        {
            timeS += 10;
            if (timeS > 255)
            {
                timeS = 255;
                timeSUp = true;
                timeH -= 5;
            }
        }
        if (timeH < 0)
        {
            timeH = 255;
        }
        saveColorsInConfAt = m + 5000;
    }

    // temp color
    if (b3.isDown() && !(b1.isDown() || b2.isDown() || b4.isDown()))
    {
        if (tempSUp)
        {
            tempS += 5;
            if (tempS > 255)
            {
                tempS = 255;
                tempSUp = false;
                tempH += 5;
            }
        }
        else
        {
            tempS -= 5;
            if (tempS < 185)
            {
                tempSUp = true;
                tempH += 5;
            }
        }
        if (tempH > 255)
        {
            tempH = 0;
        }
        saveColorsInConfAt = m + 5000;
    }
    if (b4.isDown() && !(b1.isDown() || b2.isDown() || b3.isDown()))
    {
        if (tempSUp)
        {
            tempS -= 5;
            if (tempS < 185)
            {
                tempSUp = false;
                tempH -= 5;
            }
        }
        else
        {
            tempS += 5;
            if (tempS > 255)
            {
                tempS = 255;
                tempSUp = true;
                tempH -= 5;
            }
        }
        if (tempH < 0)
        {
            tempH = 255;
        }
        saveColorsInConfAt = m + 5000;
    }
}