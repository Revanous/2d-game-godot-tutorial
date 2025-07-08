#ifndef PAUSE_MENU_H
#define PAUSE_MENU_H

#include <functional>
#include <godot_cpp/classes/node.hpp>
#include <godot_cpp/classes/scene_tree.hpp>
#include <godot_cpp/classes/label.hpp>

#include "custom_button.h"

namespace godot
{

class PauseMenu : public Node
{
    GDCLASS(PauseMenu, Node);

private:
    SceneTree* scene_tree;
    Label* pause_heading;
    CustomButton* resume_game;
    CustomButton* restart_game;
    CustomButton* enter_main_menu;
    CustomButton* exit_game;

protected:
    static void _bind_methods();

public:
    std::function<void()> on_resume_game;
    std::function<void()> on_restart_game;
    std::function<void()> on_enter_main_menu;

    void _ready() override;
    void _enter_tree() override;
    void _exit_tree() override;
};

}

#endif