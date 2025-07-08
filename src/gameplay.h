#ifndef GAMEPLAY_H
#define GAMEPLAY_H

#include <functional>
#include <godot_cpp/classes/node.hpp>
#include <godot_cpp/classes/input.hpp>
#include <godot_cpp/classes/label.hpp>

#include <godot_cpp/classes/resource_loader.hpp>
#include <godot_cpp/classes/random_number_generator.hpp>

#include "player.h"
#include "mob.h"

namespace godot
{

class Gameplay : public Node
{
    GDCLASS(Gameplay, Node);

private:
    static const uint8_t max_mob_count = 100;
    uint8_t mob_count = 0;

    const float difficulty_increase_time = 2.5f;
    float difficulty_timer;
    float game_time;

    const float player_speed = 400.0f;
    const float player_acceleration = 200.0f;
    const float player_radius = 25.0f;
    const float start_mob_speed = 375.0f;
    const float mob_speed_increase = 5.0f;
    const float mob_radius = 30.0f;
    float mob_speed;
    float player_rotation = 0.0f;

    float collision_radius;
    float mob_speed_variances[max_mob_count];

    Vector2 screen_center;
    Vector2 screen_size;
    Vector2 ellipse_size;
    Vector2 ellipse_square;

    Vector2 player_position;
    Vector2 mob_velocities[max_mob_count];
    Vector2 mob_positions[max_mob_count];

    Player* player;
    Mob* mobs[max_mob_count];

    Label* game_time_label;

    Input* input;
    ResourceLoader* resource_loader;
    Ref<RandomNumberGenerator> rng;

protected:
    static void _bind_methods();

public:
    std::function<void()> on_game_over;

    void _ready() override;
    void _process(double delta) override;
    void prepare_game();

    inline void increase_difficulty(double delta);
    inline void move_player(double delta);
    inline void move_mobs(double delta);
    inline void check_collisions();
};

}

#endif