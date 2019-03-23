#include "Mario.h"
#include "AssetsAddresses.h"
#include "Physics.h"
#include "utility.h"

using namespace std;


const double Mario::max_vx = 20;
const double Mario::max_vy = 30;
const double Mario::friction_constant = 0.12, Mario::stop_threshold = 5;
const int Mario::max_jump_time = 5;

Mario::Mario(ExactRectangle _position) :
    walk_index_handler(2,3) {

    state = STANDING;
    direction = RIGHT;
    strength = NORMAL;

    position = _position;
    vx = vy = ax = 0;
    ay = GRAVITATIONAL_ACCELERATION;
}

void Mario::handle_key_press(char key) {
    cout<<"key pressed: "<<key<<endl;

    if (key == 'd') {
        if (state == SLIDING)
            ax = 2;
        else
            ax = 2.5;
    } else if (key == 'a') {
        if (state == SLIDING)
            ax = -2;
        else
            ax = -2.5;
    } else if (key == 'w') {
        if (state != JUMPING && !jump_key_held) {
            vy = -22;
            ay = 0;
            jump_timer = max_jump_time;
        }
        jump_key_held = true;
    }
}

void Mario::handle_key_release(char key) {
    cout<<"key released"<<key<<endl;
    if (key == 'd' && ax >= 0) {
        ax = 0;
    } else if (key == 'a' && ax < 0) {
        ax = 0;
    } else if (key == 'w') {
        jump_key_held = false;
        ay = GRAVITATIONAL_ACCELERATION;
        jump_timer = 0;
    }
}

void Mario::set_vx(double vx) {
    this->vx = closest_in_interval(vx, -max_vx, max_vx);
}

void Mario::set_vy(double vy) {
    this->vy = closest_in_interval(vy, -max_vy, max_vy);
}

void Mario::move_one_frame() {
    MovingObject::move_one_frame();
    vx = max(min(vx, max_vx), -max_vx);
    vy = max(min(vy + ay, max_vy), -max_vy);
}


void Mario::update(const std::vector<Object *> &obstacles) {
    move_one_frame_with_obstacles(obstacles);
    apply_friction();
    update_state(obstacles);
    update_direction();
    handle_jump_continuation();
}

void Mario::update_state(const std::vector<Object *> &obstacles) {
    if (!is_touching_ground(obstacles)) {
        state = JUMPING;
    } else if (vx != 0) {
        if (ax * vx < 0) {
            state = SLIDING;
        } else if (state != WALKING) {
            state = WALKING;
            walk_index_handler.reset();
        } else {
            walk_index_handler.next();
        }
    } else {
        state = STANDING;
    }
}

bool Mario::is_touching_ground(const vector<Object *>& obstacles) {
    bool result = false;
    for (int i = 0; i < obstacles.size(); i++) {
        if (compare_floats(obstacles[i]->get_position().y, position.y + position.h)) {
            result = true;
        }
    }
    return result;
}

void Mario::update_direction() {
    if (vx > 0) {
        direction = RIGHT;
    } else if (vx < 0) {
        direction = LEFT;
    }
}

void Mario::apply_friction() {
    if (ax != 0 || vx == 0)
        return;

    if (state == WALKING) {
        if (vx > 0) {
            vx = max(vx - (friction_constant * vx), 0.0);
            if (vx < stop_threshold)
                vx = 0;
        }
        else if (vx < 0) {
            vx = min(vx - (friction_constant * vx), 0.0);
            if (vx > -stop_threshold)
                vx = 0;
        }
    }
}

void Mario::handle_jump_continuation() {
    if (jump_timer > 0)
        jump_timer--;
    if (jump_timer == 0 || vy == 0) {
        ay = GRAVITATIONAL_ACCELERATION;
        jump_timer = 0;
    }
}

string Mario::get_image_addr() const {
    string address = MARIO_ADDR;

    if (strength == NORMAL)
        address += "/normal";
    else if (strength == BIG)
        address += "/big";

    if (state == STANDING)
        address += "/standing";
    else if (state == WALKING)
        address += "/walking";
    else if (state == JUMPING)
        address += "/jumping";
    else if (state == SLIDING)
        address += "/sliding";

    if (direction == RIGHT)
        address += "-right";
    else if (direction == LEFT)
        address += "-left";

    if (state == WALKING) {
        address+= "-" + to_string(walk_index_handler.current() + 1);
    }
    address += ".png";
    return address;
}
