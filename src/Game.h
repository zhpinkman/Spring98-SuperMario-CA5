#ifndef GAME_H
#define GAME_H

#include "rsdl.hpp"
#include "AssetsAddresses.h"
#include "Mario.h"
#include "Block.h"
#include "Brick.h"
#include "Enemy.h"
#include <string>
#include <vector>

#define CELL_SIZE_PX 32

class Mario;

class Game {
public:
    Game();
    void run_level(std::string level_addr);
    ~Game();

    std::vector<Object*> get_obstacles() const { return obstacles; }
    std::vector<Enemy*> get_enemies() const { return enemies; }
    int get_camera_x() const { return camera_x; }
    void add_object(Object* object);
    void remove_object(Object* object);
    void add_enemy(Enemy* enemy);
    void remove_enemy(Enemy* enemy);
    void add_brick(Brick* brick);
    void remove_brick(Brick* brick);
    void add_block(Block* block);
    void increment_coin();
    rsdl::Window* get_window() { return &win; }
    void on_marios_death();

private:
    void load_level(std::string level_addr);
    void load_map_cell(int x, int y, char cell);
    void draw_background();
    void draw();
    void handle_events();
    void update();
    void update_camera();
    void set_mario(Mario* mario);
    void handle_object_interactions();
    void draw_banner();

    rsdl::Window win;
    int camera_x;
    bool game_running;
    Mario* mario;
    int n_coins, n_lives;
    ExactRectangle marios_initial_pos;

    std::vector<Block*> blocks;
    std::vector<Brick*> bricks;
    std::vector<Enemy*> enemies;
    std::vector<Object*> obstacles;
    std::vector<Object*> objects;
};


#endif
