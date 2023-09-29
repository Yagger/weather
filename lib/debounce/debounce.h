#include <Arduino.h>

class debounce
{
private:
    int btnPin;
    unsigned long debouncePeriod;

    int currentState;
    int previousState;
    int currentSteadyState;
    int previousSteadyState;
    unsigned int currentSteadyStateDuration;
    unsigned int previousSteadyStateDuration;
    unsigned int currentSteadyStateStarted;

    unsigned long currentTime;
    unsigned long lastToggleTime;

public:
    debounce(int pin, unsigned long time);
    bool isDown(void);
    bool isUp(void);
    bool isClicked(void);
    bool isReleased(void);
    bool isPressedFor(unsigned int duration);
    void loop(void);

    unsigned int getCurrentSteadyStateDuration(void);
};
