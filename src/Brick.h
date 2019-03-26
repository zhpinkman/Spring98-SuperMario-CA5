#ifndef SRC_BRICK_H
#define SRC_BRICK_H

#include "ExactRectangle.h"
#include "Object.h"
#include "AnimationIndexHandler.h"

class Mario;

class Brick : public Object {
public:
    Brick(ExactRectangle position, Game* game);
    virtual void update();
    virtual void handle_interaction_with_mario(Mario* mario);
protected:
    double vy;
    double original_y;
    const static double bump_speed;
};

class RegularBrick : public Brick {
public:
    using Brick::Brick;
    virtual std::string get_image_addr() const;
private:

};

enum BrickContent{MUSHROOM, COIN};

class QuestionBrick : public Brick {
public:
    QuestionBrick(ExactRectangle position, Game* game, BrickContent content);
    virtual std::string get_image_addr() const;
    virtual void update();
    virtual void handle_interaction_with_mario(Mario* mario);
private:
    AnimationIndexHandler animation_index_handler;
    bool is_empty;
    BrickContent content;
};



#endif //SRC_BRICK_H
