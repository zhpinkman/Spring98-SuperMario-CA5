#ifndef SRC_MARIO_H
#define SRC_MARIO_H

#include "rsdl.hpp"
#include <string>

class Mario {

public:
    Mario(Rectangle position);
    void draw(Window& win);
    void handle_key_press(char key);
    void handle_key_release(char key);
    void update();

private:
    Rectangle position;
    enum State {STANDING, WALKING, JUMPING} state;
    enum Direction {LEFT, RIGHT} direction;
    enum Strength {NORMAL, BIG} strength;

    float vx, vy;
    float ax, ay;
    float exact_x, exact_y;

};


#endif 
