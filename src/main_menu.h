#ifndef MAIN_MENU_H
#define MAIN_MENU_H

#include <functional>
#include <godot_cpp/classes/node.hpp>
#include <godot_cpp/classes/label.hpp>

#include "custom_button.h"

namespace godot
{

class MainMenu : public Node
{
    GDCLASS(MainMenu, Node);

private:
    Label* game_title;
    CustomButton* play_game;
    CustomButton* exit_game;

protected:
    static void _bind_methods();

public:
    std::function<void()> on_play_game;

    void _ready() override;
};

}

#endif