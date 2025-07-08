#include "custom_button.h"

using namespace godot;

void CustomButton::_bind_methods() {}

void CustomButton::_pressed()
{
    on_pressed();
}