#ifndef MOB_H
#define MOB_H

#include <godot_cpp/classes/node2d.hpp>
#include <godot_cpp/classes/animated_sprite2d.hpp>
#include <godot_cpp/variant/packed_string_array.hpp>

namespace godot
{

class Mob : public Node2D
{
    GDCLASS(Mob, Node2D);

private:
    AnimatedSprite2D* sprite;
    PackedStringArray animation_names;

protected:
    static void _bind_methods();

public:
    void _ready() override;
    void set_animation(uint32_t random_value);
};

}

#endif