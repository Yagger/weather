#include <common.h>

void textOnBg(String text, uint16_t bgColor, uint16_t textColor, bool scroll)
{
    mx.fillRect(0, 5, COLS, 7, bgColor);
    mx.setTextColor(textColor);
    if (scroll)
    {
        mx.scrollText(text, 10, 100);
    }
    else
    {
        mx.setCursor(0, 10);
        mx.print(text);
    }
}

void info1(String text, bool scroll)
{
    textOnBg(text, mx.hsv(150, 150, 150), mx.hsv(20, 150, 255), scroll);
}

void info2(String text, bool scroll)
{
    textOnBg(text, mx.hsv(70, 150, 150), mx.hsv(40, 150, 255), scroll);
}

void warning(String text, bool scroll)
{
    textOnBg(text, mx.hsv(30, 255, 255), 0, scroll);
}

void error(String text, bool scroll)
{
    textOnBg(text, mx.hsv(0, 255, 255), 0, scroll);
}