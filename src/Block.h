#ifndef BLOCK_H
#define BLOCK_H

#include <string>
#include "rsdl.hpp"
#include "Object.h"
#include "Geometry.h"

class Block : public Object {
public:
    Block(Rectangle position, std::string image_addr);
    void draw(rsdl::Window& win);
private:
    Rectangle position;
    std::string image_addr;
};

#endif
