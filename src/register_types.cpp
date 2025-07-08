#include "register_types.h"

#include <gdextension_interface.h>
#include <godot_cpp/core/defs.hpp>
#include <godot_cpp/godot.hpp>

#include "gamestate_manager.h"
#include "main_menu.h"
#include "game_running.h"
#include "gameplay.h"
#include "pause_menu.h"
#include "game_over_menu.h"

#include "player.h"
#include "mob.h"
#include "custom_button.h"

using namespace godot;

void initialize_game_module(ModuleInitializationLevel p_level)
{
    if (p_level != MODULE_INITIALIZATION_LEVEL_SCENE)
        return;

    ClassDB::register_runtime_class<GameStateManager>();
    ClassDB::register_runtime_class<MainMenu>();
    ClassDB::register_runtime_class<GameRunning>();
    ClassDB::register_runtime_class<Gameplay>();
    ClassDB::register_runtime_class<PauseMenu>();
    ClassDB::register_runtime_class<GameOverMenu>();
    ClassDB::register_runtime_class<Player>();
    ClassDB::register_runtime_class<Mob>();
    ClassDB::register_runtime_class<CustomButton>();
}

void uninitialize_game_module(ModuleInitializationLevel p_level)
{
    if (p_level != MODULE_INITIALIZATION_LEVEL_SCENE)
        return;
}

extern "C"
{
    GDExtensionBool GDE_EXPORT personal_library_init(GDExtensionInterfaceGetProcAddress p_get_proc_address, const GDExtensionClassLibraryPtr p_library, GDExtensionInitialization* r_initialization)
    {
        godot::GDExtensionBinding::InitObject init_obj(p_get_proc_address, p_library, r_initialization);

        init_obj.register_initializer(initialize_game_module);
        init_obj.register_terminator(uninitialize_game_module);
        init_obj.set_minimum_library_initialization_level(MODULE_INITIALIZATION_LEVEL_SCENE);

        return init_obj.init();
    }
}