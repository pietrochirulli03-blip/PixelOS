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
    // degradazione naturale più morbida (meno “robotico”)
    energy -= 1;
    boredom += 1;
    loneliness += 1;

    // oscillazione emotiva più umana (non lineare)
    float emotionNoise = random(-3, 4) * 0.5;

    if (energy < 40) focus -= 1.5;
    if (focus < 30) stress += 1.2;
    if (stress > 60) happiness -= 1.0;
    if (curiosity > 70) boredom -= 1.5;
    if (happiness > 70) stress -= 1.0;

    curiosity += random(-1, 2);
    happiness += emotionNoise;
    focus += random(-1, 2);

    // LIMITI SICURI
    clampValues(energy);
    clampValues(curiosity);
    clampValues(boredom);
    clampValues(stress);
    clampValues(happiness);
    clampValues(focus);
    clampValues(loneliness);

    // bisogni più “smooth”
    needRest = (100 - energy) * 1.2;
    needExplore = curiosity + boredom * 0.6;
    needSocial = loneliness;

    chooseAction();
    evolveState();

    // sleep override
    if (energy <= 0)
    {
        state = SLEEPING;
        energy = 0;
        return;
    }
}
void Brain::chooseAction()
{
    if (needRest >= needExplore && needRest >= needSocial)
    {
        action = REST;
    }
    else if (needExplore >= needSocial)
    {
        if (curiosity > 70)
            action = EXPLORE;
        else
            action = OBSERVE;
    }
    else
    {
        action = SEEK_SOCIAL;
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
    int scoreSleep = 100 - energy;
    int scoreStress = stress;
    int scoreSocial = loneliness;
    int scoreBored = boredom;
    int scoreCurious = curiosity;
    int scoreHappy = happiness;

    if (scoreSleep > 80)
        state = SLEEPING;
    else if (scoreStress > 75)
        state = STRESSED;
    else if (scoreSocial > 70)
        state = SOCIAL;
    else if (scoreBored > 65)
        state = BORED;
    else if (scoreCurious > 70)
        state = CURIOUS;
    else if (scoreHappy > 75)
        state = HAPPY;
    else
        state = NEUTRAL;
}