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

enum BrainAction {
    REST,
    EXPLORE,
    OBSERVE,
    THINK,
    SEEK_SOCIAL
};

class Brain {

public:

    Brain();

    void begin();
    void update();
    void printStatus();

    // Getter
    int getEnergy() const { return energy; }
    int getCuriosity() const { return curiosity; }
    int getBoredom() const { return boredom; }
    int getStress() const { return stress; }
    int getHappiness() const { return happiness; }
    int getLoneliness() const { return loneliness; }

    BrainState getState() const { return state; }
    BrainAction getAction() const { return action; }

private:
    int energy = 100;
    int curiosity = 50;
    int boredom = 0;
    int focus = 50;
    int stress = 0;
    int memory = 50;
    int happiness = 70;
    int trust = 50;
    int loneliness = 20;

    int needRest = 0;
    int needExplore = 0;
    int needSocial = 0;

    BrainState state = NEUTRAL;
    BrainAction action = REST;
    void evolveState();
    void chooseAction();
    void clampValues(int &v);
};