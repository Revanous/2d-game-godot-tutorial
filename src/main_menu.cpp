#include "main_menu.h"

#include <godot_cpp/classes/scene_tree.hpp>

using namespace godot;

void MainMenu::_bind_methods() {}

void MainMenu::_ready()
{
    game_title = get_node<Label>("GameTitle");
    play_game = get_node<CustomButton>("PlayGame");
    exit_game = get_node<CustomButton>("ExitGame");

    play_game->on_pressed = on_play_game;
    exit_game->on_pressed = [this]() { get_tree()->quit(); };
}