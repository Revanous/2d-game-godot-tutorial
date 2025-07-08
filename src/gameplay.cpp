#include "gameplay.h"

#include <godot_cpp/classes/viewport.hpp>
#include <godot_cpp/classes/packed_scene.hpp>
#include <godot_cpp/classes/global_constants.hpp>
#include <godot_cpp/classes/audio_stream.hpp>

#include <godot_cpp/variant/callable.hpp>
#include <godot_cpp/variant/string.hpp>
#include <godot_cpp/core/math.hpp>

#include "personal_macros.h"

using namespace godot;

void Gameplay::_bind_methods() {}

void Gameplay::_ready()
{
    resource_loader = ResourceLoader::get_singleton();

    screen_size = get_viewport()->get_visible_rect().size;
    screen_center = screen_size / 2.0f;
    screen_size -= player_radius;

    ellipse_size = screen_center * (float)Math_SQRT2 + mob_radius * 2.0f;
    ellipse_square = ellipse_size * ellipse_size;


    Ref<PackedScene> mob_scene = resource_loader->load("scenes/actors/mob.tscn");
    for (uint8_t i = 0; i < max_mob_count; ++i)
    {
        mobs[i] = Object::cast_to<Mob>(mob_scene->instantiate());
    }

    player = LOAD_INSTANCE("scenes/actors/player.tscn", Player, resource_loader);
    add_child(player);

    collision_radius = player_radius + mob_radius;
    collision_radius *= collision_radius;


    game_time_label = get_node<Label>("GameTime");

    input = Input::get_singleton();
    rng.instantiate();
    rng->randomize();
}

void Gameplay::_process(double delta)
{
    increase_difficulty(delta);
    move_player(delta);
    check_collisions();
    move_mobs(delta);
}

void Gameplay::prepare_game()
{
    game_time = 0.0f;
    difficulty_timer = 5.0f;
    mob_speed = start_mob_speed;

    player_position = screen_center;
    player->set_position(player_position);

    while(mob_count)
    {
        --mob_count;
        remove_child(mobs[mob_count]);
    }
}

inline void Gameplay::increase_difficulty(double delta)
{
    game_time += (float)delta;
    game_time_label->set_text(String::num(game_time, 0));

    if (game_time > difficulty_timer)
    {
        mob_speed += mob_speed_increase;
        if (mob_count < max_mob_count)
        {
            mob_positions[mob_count] = ellipse_size + screen_center + 1.0f;
            add_child(mobs[mob_count]);
            ++mob_count;
        }
        difficulty_timer += difficulty_increase_time;
    }
}

inline void Gameplay::move_player(double delta)
{
    Vector2 velocity;
    if (input->is_key_pressed(KEY_D))
    {
        velocity.x += 1.0f;
    }
    if (input->is_key_pressed(KEY_A))
    {
        velocity.x -= 1.0f;
    }
    if(input->is_key_pressed(KEY_S))
    {
        velocity.y += 1.0f;
    }
    if(input->is_key_pressed(KEY_W))
    {
        velocity.y -= 1.0f;
    }

    uint8_t is_moving = (uint8_t)(abs(velocity.x) + abs(velocity.y));
    uint8_t is_sprinting = input->is_key_pressed(KEY_SHIFT);
    if (is_moving)
    {
        float actual_speed = player_speed + is_sprinting * player_acceleration;

        velocity -= velocity * (float)DIAGONAL_DECREASE * (float)(is_moving - 1);
        player_position += velocity * actual_speed * (float)delta;
        player_position.x = Math::clamp(player_position.x, player_radius, screen_size.x);
        player_position.y = Math::clamp(player_position.y, player_radius, screen_size.y);

        player_rotation = velocity.angle();
        player->set_position(player_position);
    }
    is_moving = (is_moving + 1) / 2;
    player->set_animation(is_moving, is_sprinting, player_rotation);
}

inline void Gameplay::move_mobs(double delta)
{
    for (uint8_t i = 0; i < mob_count; ++i)
    {
        Vector2 relative_position = mob_positions[i] - screen_center;
        relative_position *= relative_position / ellipse_square;

        if (relative_position.x + relative_position.y > 1.0f)
        {
            uint32_t random_value = rng->randi() % 360;
            float angle = (float)random_value * (float)Math_PI / 180.0f;

            mob_velocities[i].x = Math::cos(angle);
            mob_velocities[i].y = Math::sin(angle);
            mob_positions[i] = screen_center - ellipse_size * mob_velocities[i];

            random_value %= 90;
            angle = angle + ((float)random_value - 45.0f) * (float)Math_PI / 180.0f;
            mob_velocities[i].x = Math::cos(angle);
            mob_velocities[i].y = Math::sin(angle);

            mob_speed_variances[i] = mob_speed + (float)random_value - 45.0f;
            mobs[i]->set_rotation(angle);
            mobs[i]->set_animation(random_value);
        }
        mob_positions[i] += mob_velocities[i] * mob_speed_variances[i] * (float)delta;
        mobs[i]->set_position(mob_positions[i]);
    }
}

inline void Gameplay::check_collisions()
{
    Vector2 player_position = player->get_position();
    for (uint8_t i = 0; i < mob_count; ++i)
    {
        Vector2 mob_position = mobs[i]->get_position();
        mob_position -= player_position;

        if (mob_position.x * mob_position.x + mob_position.y * mob_position.y < collision_radius)
        {
            on_game_over();
        }
    }
}