#include "player.h"

#include <godot_cpp/classes/sprite_frames.hpp>
#include <godot_cpp/core/math.hpp>

using namespace godot;

void Player::_bind_methods() {}

void Player::_ready()
{
    sprite = get_node<AnimatedSprite2D>("AnimatedSprite2D");
    animation_names = ((Ref<SpriteFrames>)sprite->get_sprite_frames())->get_animation_names();
    sprite->play();

    bubble_trail = get_node<GPUParticles2D>("BubbleTrail");
}

void Player::set_animation(uint8_t is_moving, uint8_t is_sprinting, float angle)
{
    sprite->set_animation(animation_names[is_moving]);
    sprite->set_speed_scale(animation_speed + animation_speed_increase * is_sprinting);
    bubble_trail->set_emitting(is_moving);
    bubble_trail->set_amount_ratio(particles_amount + particles_amount_increase * is_sprinting);
    set_rotation(Math::lerp_angle(get_rotation(), angle, rotation_speed));
}