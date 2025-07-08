#ifndef GAME_RUNNING_H
#define GAME_RUNNING_H

#include <functional>
#include <godot_cpp/classes/node.hpp>
#include <godot_cpp/classes/scene_tree.hpp>
#include <godot_cpp/classes/input_event.hpp>
#include <godot_cpp/classes/resource_loader.hpp>
#include <godot_cpp/classes/audio_stream_player.hpp>

#include "gameplay.h"
#include "pause_menu.h"
#include "game_over_menu.h"

namespace godot
{

class GameRunning : public Node
{
    GDCLASS(GameRunning, Node);

private:
    const float bg_music_volume_normal = -20.0f;
    const float bg_music_volume_decreased = -30.0f;
    const float bg_music_volume_min = -50.0f;
    const float bg_music_fade_time = 1.0;
    const float bg_music_pause_trans_time = 0.5;

    const float gameover_volume_normal = -5.0f;
    const float gameover_volume_min = -20.0f;
    const float gameover_fade_time = 0.25;

    AudioStreamPlayer* background_music;
    AudioStreamPlayer* gameover_sound;

    Gameplay* gameplay;
    PauseMenu* pause_menu;
    GameOverMenu* game_over_menu;

    SceneTree* scene_tree;
    ResourceLoader* resource_loader;

protected:
    static void _bind_methods();

public:
    std::function<void()> on_enter_main_menu;

    void _ready() override;
    void _unhandled_input(const Ref<InputEvent>& event) override;

    void prepare_game();
    void toggle_game_pause();
    void over_game();
};

}

#endif