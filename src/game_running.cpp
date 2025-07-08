#include "game_running.h"

#include <godot_cpp/classes/packed_scene.hpp>
#include <godot_cpp/classes/input_event_key.hpp>
#include <godot_cpp/classes/audio_stream.hpp>

#include <godot_cpp/classes/tween.hpp>
#include <godot_cpp/classes/method_tweener.hpp>
#include <godot_cpp/classes/callback_tweener.hpp>
#include <godot_cpp/variant/callable.hpp>

#include "personal_macros.h"

using namespace godot;

void GameRunning::_bind_methods() {}

void GameRunning::_ready()
{
    set_process_mode(PROCESS_MODE_ALWAYS);

    resource_loader = ResourceLoader::get_singleton();
    scene_tree = get_tree();


    gameplay = LOAD_INSTANCE("scenes/gameplay.tscn", Gameplay, resource_loader);
    gameplay->on_game_over = [this]() { over_game(); add_child(game_over_menu); };
    gameplay->set_process_mode(PROCESS_MODE_PAUSABLE);
    add_child(gameplay);

    pause_menu = LOAD_INSTANCE("scenes/menus/pause_menu.tscn", PauseMenu, resource_loader);
    pause_menu->on_resume_game = [this]() { toggle_game_pause(); };
    pause_menu->on_restart_game = [this]() { remove_child(pause_menu); prepare_game(); };
    pause_menu->on_enter_main_menu = [this]() { remove_child(pause_menu); on_enter_main_menu(); };

    game_over_menu = LOAD_INSTANCE("scenes/menus/game_over_menu.tscn", GameOverMenu, resource_loader);
    game_over_menu->on_start_game = [this]() { remove_child(game_over_menu); prepare_game(); };
    game_over_menu->on_enter_main_menu = [this]() { remove_child(game_over_menu); on_enter_main_menu(); };


    Ref<AudioStream> background_music_file = resource_loader->load("sounds/background_music.ogg");
    Ref<AudioStream> gameover_sound_file = resource_loader->load("sounds/gameover.wav");

    background_music = memnew(AudioStreamPlayer);
    background_music->set_stream(background_music_file);
    add_child(background_music);

    gameover_sound = memnew(AudioStreamPlayer);
    gameover_sound->set_stream(gameover_sound_file);
    add_child(gameover_sound);
}

void GameRunning::_unhandled_input(const Ref<InputEvent>& event)
{
    Ref<InputEventKey> key_event = event;

    if (key_event != nullptr && key_event->get_keycode() == Key::KEY_ESCAPE &&
        key_event->is_pressed() && !key_event->is_echo() && game_over_menu->is_game_running)
    {
        toggle_game_pause();
    }
}

void GameRunning::prepare_game()
{
    background_music->play();
    create_tween()->tween_method(Callable(background_music, "set_volume_db"), bg_music_volume_min, bg_music_volume_normal, bg_music_fade_time);

    gameplay->prepare_game();
}

void GameRunning::toggle_game_pause()
{
    bool is_game_paused = !scene_tree->is_paused();
    if (is_game_paused)
    {
        add_child(pause_menu);
        create_tween()->tween_method(Callable(background_music, "set_volume_db"), bg_music_volume_normal, bg_music_volume_decreased, bg_music_pause_trans_time);
    }
    else
    {
        remove_child(pause_menu);
        create_tween()->tween_method(Callable(background_music, "set_volume_db"), bg_music_volume_decreased, bg_music_volume_normal, bg_music_pause_trans_time);
    }
}

void GameRunning::over_game()
{
    Ref<Tween> tween_1 = create_tween();
    tween_1->tween_method(Callable(background_music, "set_volume_db"), bg_music_volume_normal, bg_music_volume_min, bg_music_fade_time);
    tween_1->tween_callback(Callable(background_music, "stop"));

    gameover_sound->play();
    create_tween()->tween_method(Callable(gameover_sound, "set_volume_db"), gameover_volume_min, gameover_volume_normal, gameover_fade_time);
}