#pragma once

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
};