#include "pause_menu.h"

using namespace godot;

void PauseMenu::_bind_methods() {}

void PauseMenu::_ready()
{
    pause_heading = get_node<Label>("PauseHeading");
    resume_game = get_node<CustomButton>("ResumeGame");
    restart_game = get_node<CustomButton>("RestartGame");
    enter_main_menu = get_node<CustomButton>("ExitToMainMenu");
    exit_game = get_node<CustomButton>("ExitGame");

    resume_game->on_pressed = on_resume_game;
    restart_game->on_pressed = on_restart_game;
    enter_main_menu->on_pressed = on_enter_main_menu;
    exit_game->on_pressed = [this]() { get_tree()->quit(); };
}

void PauseMenu::_enter_tree()
{
    get_tree()->set_pause(true);
}

void PauseMenu::_exit_tree()
{
    get_tree()->set_pause(false);
}