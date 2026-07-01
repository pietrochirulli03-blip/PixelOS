#pragma once

enum BrainState {
    SLEEPING,
    BORED,
    CURIOUS,
    STRESSED,
    HAPPY,
    SOCIAL,
    NEUTRAL
};

class Brain {
public:
    Brain();

    void begin();
    void update();
    void printStatus();

private:
    int energy;
    int curiosity;
    int boredom;
    int focus;
    int stress;
    int memory;
    int happiness;
    int trust;
    int loneliness;

    BrainState state;

    void evolveState();
    void clampValues(int &v);
};