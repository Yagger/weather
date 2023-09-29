#include <Arduino.h>
#include <FastLED_NeoMatrix.h>

class LedMatrix
{
private:
    int num_rows;
    int num_cols;
    FastLED_NeoMatrix *matrix;

    // scrolling test
    int scrollX;
    int scrollLast;
    int scrollSpeed;

public:
    LedMatrix(int leds_rows, int leds_cols, int max_amps);
    void clear(void);
    void px(int x, int y, uint16_t color);
    void setCursor(int x, int y);
    void print(String s);
    void show(void);
    void scrollText(String text, int row, int speed);
    uint16_t hsv(int h, int s, int v);
    void setTextColor(uint16_t color);
    void setFont(const GFXfont *f);
    void setBrightness(int brightness);
    void resetScroll(void);
    void fillRect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color);
    //
    void textOnBg(String text, int width, uint16_t bgColor, uint16_t textColor);
};