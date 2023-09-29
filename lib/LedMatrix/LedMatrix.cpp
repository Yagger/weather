#include <FastLED.h>
#include <FastLED_NeoMatrix.h>
#include <LedMatrix.h>

#define LEDS_PIN D4
#define LED_CHIPSET WS2812B
#define COLOR_ORDER GRB

LedMatrix::LedMatrix(int leds_rows, int leds_cols, int max_milliamps)
{
    num_rows = leds_rows;
    num_cols = leds_cols;
    int num_leds = leds_rows * leds_cols;
    CRGB leds[num_leds];
    matrix = new FastLED_NeoMatrix(leds, leds_cols, leds_rows,
                                   NEO_MATRIX_TOP + NEO_MATRIX_LEFT +
                                       NEO_MATRIX_COLUMNS + NEO_MATRIX_ZIGZAG);
    // FastLED.addLeds<LED_CHIPSET, LEDS_PIN, COLOR_ORDER>(leds, num_leds).setCorrection(TypicalLEDStrip);
    FastLED.addLeds<NEOPIXEL, LEDS_PIN>(leds, num_leds);
    FastLED.setMaxPowerInVoltsAndMilliamps(5, max_milliamps);
    matrix->begin();
    matrix->setTextWrap(false);
    matrix->setBrightness(50);

    // scrolling text
    scrollX = leds_cols;
    scrollLast = millis();
    scrollSpeed = 100;
}

uint16_t LedMatrix::hsv(int h, int s, int v)
{
    CRGB rgb = CHSV(h, s, v);
    return matrix->Color(rgb[0], rgb[1], rgb[2]);
}

void LedMatrix::clear()
{
    matrix->fillScreen(0);
}

void LedMatrix::px(int x, int y, uint16_t color)
{
    matrix->writePixel(x, y, color);
}

void LedMatrix::setCursor(int x, int y)
{
    matrix->setCursor(x, y);
}

void LedMatrix::print(String s)
{
    matrix->print(s);
}

void LedMatrix::show()
{
    matrix->show();
}

void LedMatrix::setTextColor(uint16_t color)
{
    matrix->setTextColor(color);
}

void LedMatrix::setFont(const GFXfont *f)
{
    matrix->setFont(f);
}

void LedMatrix::setBrightness(int brightness)
{
    matrix->setBrightness(brightness);
}

void LedMatrix::scrollText(String text, int row, int speed)
{
    int m = millis();
    if (m - scrollLast > speed)
    {
        scrollX--;
        if (scrollX < -((int)(text.length() * 5)))
        {
            scrollX = num_cols;
        }
        scrollLast = m;
    }
    matrix->setCursor(scrollX, row);
    matrix->print(text);
}

void LedMatrix::resetScroll()
{
    scrollX = num_cols;
    scrollLast = millis();
}

void LedMatrix::fillRect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color)
{
    matrix->fillRect(x, y, w, h, color);
}
