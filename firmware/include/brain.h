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

    // ===== Getter =====

    int getEnergy() const { return energy; }
    int getCuriosity() const { return curiosity; }
    int getBoredom() const { return boredom; }
    int getFocus() const { return focus; }
    int getStress() const { return stress; }
    int getMemory() const { return memory; }
    int getHappiness() const { return happiness; }
    int getTrust() const { return trust; }
    int getLoneliness() const { return loneliness; }

    BrainState getState() const { return state; }

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