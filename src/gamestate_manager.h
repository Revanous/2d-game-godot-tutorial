#ifndef MAIN_H
#define MAIN_H

#include <godot_cpp/classes/node.hpp>
#include <godot_cpp/classes/audio_stream_player.hpp>

#include "gameplay.h"
#include "main_menu.h"
#include "game_running.h"

namespace godot
{

class GameStateManager : public Node
{
    GDCLASS(GameStateManager, Node);

private:
    MainMenu* main_menu;
    GameRunning* game_running;
    AudioStreamPlayer* underwater_ambience;

protected:
    static void _bind_methods();

public:
    void _ready() override;
};

}

#endif