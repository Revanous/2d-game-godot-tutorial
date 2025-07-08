#ifndef GAME_OVER_MENU_H
#define GAME_OVER_MENU_H

#include <functional>
#include <godot_cpp/classes/node.hpp>
#include <godot_cpp/classes/scene_tree.hpp>
#include <godot_cpp/classes/label.hpp>

#include "custom_button.h"

namespace godot
{

class GameOverMenu : public Node
{
    GDCLASS(GameOverMenu, Node);

private:
    SceneTree* scene_tree;
    Label* game_over_heading;
    CustomButton* play_again;
    CustomButton* enter_main_menu;
    CustomButton* exit_game;

protected:
    static void _bind_methods();

public:
    bool is_game_running = true;
    std::function<void()> on_start_game;
    std::function<void()> on_enter_main_menu;

    void _ready() override;
    void _enter_tree() override;
    void _exit_tree() override;
};

}

#endif