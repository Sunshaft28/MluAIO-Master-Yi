#include "../plugin_sdk/plugin_sdk.hpp"
#include "masteryi.h"
PLUGIN_TYPE(plugin_type::champion)

PLUGIN_NAME("MluAIO");
SUPPORTED_CHAMPIONS(champion_id::MasterYi);

PLUGIN_API bool on_sdk_load(plugin_sdk_core* plugin_sdk_good)
{
    // Global declaration macro
    //
    DECLARE_GLOBALS(plugin_sdk_good);

    //Switch by myhero champion id
    //
    switch (myhero->get_champion())
    {
    case champion_id::MasterYi:
        // Load Master Yi script
        //
        masteryi::load();
        return true;
    default:
        // We don't support this champ, print message and return false (core will not load this plugin and on_sdk_unload will be never called)
        //
        console->print("Champion %s is not supported!", myhero->get_model_cstr());
        return false;
    }

    return false;
}

PLUGIN_API void on_sdk_unload()
{
    switch (myhero->get_champion())
    {
    case champion_id::MasterYi:
        // Unload Master Yi script
        //
        masteryi::unload();
        break;
    default:
        break;
    }
}