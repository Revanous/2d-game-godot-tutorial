#include "game_over_menu.h"

using namespace godot;

void GameOverMenu::_bind_methods() {}

void GameOverMenu::_ready()
{
    game_over_heading = get_node<Label>("GameOverHeading");
    play_again = get_node<CustomButton>("PlayAgain");
    enter_main_menu = get_node<CustomButton>("ExitToMainMenu");
    exit_game = get_node<CustomButton>("ExitGame");

    play_again->on_pressed = on_start_game;
    enter_main_menu->on_pressed = on_enter_main_menu;
    exit_game->on_pressed = [this]() { get_tree()->quit(); };
}

void GameOverMenu::_enter_tree()
{
    is_game_running = false;
    get_tree()->set_pause(true);
}

void GameOverMenu::_exit_tree()
{
    is_game_running = true;
    get_tree()->set_pause(false);
}