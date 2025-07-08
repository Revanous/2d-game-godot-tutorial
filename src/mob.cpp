#include "mob.h"

#include <godot_cpp/classes/sprite_frames.hpp>

using namespace godot;

void Mob::_bind_methods() {}

void Mob::_ready()
{
    sprite = get_node<AnimatedSprite2D>("AnimatedSprite2D");
    animation_names = ((Ref<SpriteFrames>)sprite->get_sprite_frames())->get_animation_names();
    sprite->play();
}

void Mob::set_animation(uint32_t random_value)
{
    sprite->set_animation(animation_names[random_value % animation_names.size()]);
}