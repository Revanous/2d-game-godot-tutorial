#ifndef PLAYER_H
#define PLAYER_H

#include <godot_cpp/classes/node2d.hpp>
#include <godot_cpp/classes/animated_sprite2d.hpp>
#include <godot_cpp/classes/gpu_particles2d.hpp>
#include <godot_cpp/variant/packed_string_array.hpp>

namespace godot
{

class Player : public Node2D
{
    GDCLASS(Player, Node2D);

private:
    const float rotation_speed = 0.15f;
    const float particles_amount = 0.5f;
    const float particles_amount_increase = 0.5f;
    const float animation_speed = 0.85f;
    const float animation_speed_increase = 0.4f;
    
    Vector2 screen_size;
    AnimatedSprite2D* sprite;
    GPUParticles2D* bubble_trail;
    PackedStringArray animation_names;

protected:
    static void _bind_methods();

public:
    void _ready() override;
    void set_animation(uint8_t is_moving, uint8_t is_sprinting, float angle);
};

}

#endif