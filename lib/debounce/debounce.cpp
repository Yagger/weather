#include <debounce.h>

debounce::debounce(int pin, unsigned long time)
{
    btnPin = pin;
    debouncePeriod = time;
    lastToggleTime = 0;

    pinMode(btnPin, INPUT_PULLUP);
    currentState = digitalRead(btnPin);
    previousState = currentState;
    currentSteadyState = currentState;
    previousSteadyState = currentState;
    currentSteadyStateDuration = 0;
    previousSteadyStateDuration = 0;
    currentSteadyStateStarted = 0;
}

bool debounce::isDown(void)
{
    return currentSteadyState == LOW;
}

bool debounce::isUp(void)
{
    return currentSteadyState == HIGH;
}

bool debounce::isClicked(void)
{
    if (previousSteadyState == HIGH && currentSteadyState == LOW)
        return true;
    else
        return false;
}

bool debounce::isReleased(void)
{
    if (previousSteadyState == LOW && currentSteadyState == HIGH)
        return true;
    else
        return false;
}

bool debounce::isPressedFor(unsigned int duration)
{
    if (previousSteadyState == LOW && currentSteadyState == HIGH && previousSteadyStateDuration >= duration)
        return true;
    else
        return false;
}

void debounce::loop(void)
{
    currentTime = millis();
    currentState = digitalRead(btnPin);

    if (currentState != previousState)
    {
        lastToggleTime = currentTime;
        previousState = currentState;
        currentSteadyStateStarted = currentTime;
    }
    else if ((currentTime - lastToggleTime) >= debouncePeriod)
    {
        previousSteadyState = currentSteadyState;
        previousSteadyStateDuration = currentSteadyStateDuration;
        currentSteadyState = currentState;
        currentSteadyStateDuration = currentTime - currentSteadyStateStarted;
    }
}

unsigned int debounce::getCurrentSteadyStateDuration()
{
    return currentSteadyStateDuration;
}