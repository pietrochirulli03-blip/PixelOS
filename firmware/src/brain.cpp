#include "brain.h"
#include <Arduino.h>

Brain::Brain()
{
    energy = 100;
    curiosity = 50;
    boredom = 0;

    focus = 50;
    stress = 0;
    memory = 50;

    happiness = 70;
    trust = 50;
    loneliness = 20;
}

void Brain::clampValues(int &v)
{
    if (v < 0)
        v = 0;
    if (v > 100)
        v = 100;
}

void Brain::begin()
{
    Serial.println("Brain online");
    randomSeed(micros());
}

void Brain::update()
{

    energy -= 1;
    clampValues(energy);

    // 🧪 TEST: cambiamenti casuali
    curiosity += random(-5, 10);
    boredom += random(-5, 10);
    stress += random(-5, 10);
    happiness += random(-5, 10);
    loneliness += random(-5, 10);
    trust += random(-5, 10);
    focus += random(-5, 10);

    clampValues(energy);
    clampValues(curiosity);
    clampValues(boredom);
    clampValues(stress);
    clampValues(happiness);
    clampValues(loneliness);
    clampValues(trust);
    clampValues(focus);

    evolveState();
    if (energy==0)
    {
        state = SLEEPING;
        return;
    }
    
}

void Brain::printStatus()
{

    Serial.print("Energy: ");
    Serial.println(energy);
    Serial.print("Curiosity: ");
    Serial.println(curiosity);
    Serial.print("Boredom: ");
    Serial.println(boredom);
    Serial.print("Happiness: ");
    Serial.println(happiness);
    Serial.print("Stress: ");
    Serial.println(stress);
    Serial.print("Loneliness: ");
    Serial.println(loneliness);

    Serial.print("STATE: ");

    switch (state)
    {
    case SLEEPING:
        Serial.println("sleep 😴");
        break;
    case BORED:
        Serial.println("bored 😐");
        break;
    case CURIOUS:
        Serial.println("curious 🤖");
        break;
    case STRESSED:
        Serial.println("stressed ⚠️");
        break;
    case HAPPY:
        Serial.println("happy 😄");
        break;
    case SOCIAL:
        Serial.println("social 🤝");
        break;
    case NEUTRAL:
        Serial.println("neutral 🤝");
        break;
    }

    Serial.println("---------------");
}
void Brain::evolveState()
{

    if (energy < 20)
    {
        state = SLEEPING;
    }
    else if (stress > 70)
    {
        state = STRESSED;
    }
    else if (loneliness > 60)
    {
        state = SOCIAL;
    }
    else if (boredom > 60)
    {
        state = BORED;
    }
    else if (curiosity > 70)
    {
        state = CURIOUS;
    }
    else if (happiness > 70)
    {
        state = HAPPY;
    }
    else
    {
        state = NEUTRAL;
    }
}