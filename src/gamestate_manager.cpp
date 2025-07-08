#include "gamestate_manager.h"

#include <functional>
#include <godot_cpp/classes/packed_scene.hpp>
#include <godot_cpp/classes/resource_loader.hpp>
#include <godot_cpp/classes/audio_stream.hpp>

#include <godot_cpp/classes/tween.hpp>
#include <godot_cpp/classes/method_tweener.hpp>
#include <godot_cpp/variant/callable.hpp>

#include "personal_macros.h"

using namespace godot;

void GameStateManager::_bind_methods() {}

void GameStateManager::_ready()
{
    main_menu = LOAD_INSTANCE("scenes/menus/main_menu.tscn", MainMenu, ResourceLoader::get_singleton());
    main_menu->on_play_game = [this]() { remove_child(main_menu); add_child(game_running); game_running->prepare_game(); };
    add_child(main_menu);

    game_running = memnew(GameRunning);
    game_running->on_enter_main_menu = [this]() { remove_child(game_running); add_child(main_menu); };


    Ref<AudioStream> underwater_ambience_sound = ResourceLoader::get_singleton()->load("sounds/underwater_ambience.ogg");
    underwater_ambience = memnew(AudioStreamPlayer);
    underwater_ambience->set_stream(underwater_ambience_sound);
    add_child(underwater_ambience);

    underwater_ambience->play();
    create_tween()->tween_method(Callable(underwater_ambience, "set_volume_db"), -50.0f, -20.0f, 1.0);
}