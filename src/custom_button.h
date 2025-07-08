#ifndef CUSTOM_BUTTON_H
#define CUSTOM_BUTTON_H

#include <functional>
#include <godot_cpp/classes/button.hpp>

namespace godot
{

class CustomButton : public Button
{
    GDCLASS(CustomButton, Button);

protected:
    static void _bind_methods();

public:
    std::function<void()> on_pressed;

    void _pressed() override;
};

}

#endif