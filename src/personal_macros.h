#ifndef PERSONAL_MACROS_H
#define PERSONAL_MACROS_H

using namespace godot;

#define STR_HELPER(x) #x
#define STR(x) STR_HELPER(x)

#define BIND_METHOD(name, type, class_name)                                                    \
    ClassDB::bind_method(D_METHOD("get_" STR(name)), &class_name::get_##name);                 \
    ClassDB::bind_method(D_METHOD("set_" STR(name), "p_" STR(name)), &class_name::set_##name); \
    ADD_PROPERTY(PropertyInfo(Variant::type, STR(name)), "set_" STR(name), "get_" STR(name))

#define LOAD_INSTANCE(scene_path, class_name, resource_loader)\
    Object::cast_to<class_name>(((Ref<PackedScene>)resource_loader->load("res://" scene_path))->instantiate())

#define DIAGONAL_DECREASE 0.29289321881

#include <godot_cpp/classes/input.hpp>
#include <godot_cpp/classes/global_constants.hpp>
inline bool is_key_just_pressed(Key key, bool* key_state, Input* input)
{
    if (input->is_key_pressed(key))
    {
        if (!*key_state)
        {
            *key_state = true;
            return true;
        }
    }
    else
    {
        *key_state = false;
    }
    return false;
}

#endif