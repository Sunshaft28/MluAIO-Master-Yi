#include "../plugin_sdk/plugin_sdk.hpp"
#include "masteryi.h"


namespace masteryi
{

    script_spell* q = nullptr;

    TreeTab* main_tab = nullptr;
    float last_e_time = 0.0f;

    namespace draw_settings
    {
        TreeEntry* draw_range_q = nullptr;
    }

    namespace yitaric
    {
        TreeEntry* use_masteryi_taric = nullptr;
        TreeEntry* toggle_keybind = nullptr;
    }

    void on_draw();
    void on_process_spell_cast(game_object_script sender, spell_instance_script spell);

    void load()
    {
        q = plugin_sdk->register_spell(spellslot::q, 600);

        main_tab = menu->create_tab("MluAIO", "MluAIO Master Yi");
        main_tab->set_assigned_texture(myhero->get_square_icon_portrait());
        {
            main_tab->add_separator(myhero->get_model() + ".Mlu", "Yi Taric Synergy");
            main_tab->add_separator(myhero->get_model() + ".MluAIO", "");
            yitaric::use_masteryi_taric = main_tab->add_checkbox(myhero->get_model() + ".yitaric.", "Instant Alphastrike on Taric E cast", true);
            yitaric::toggle_keybind = main_tab->add_hotkey("intToggle", "Activate Keybind", TreeHotkeyMode::Toggle, 0x53 /*S key*/, true, true);
        }
        event_handler<events::on_draw>::add_callback(on_draw);
        event_handler<events::on_process_spell_cast>::add_callback(on_process_spell_cast);
    }

    void unload()
    {
        plugin_sdk->remove_spell(q);
        menu->delete_tab(main_tab);
        event_handler<events::on_draw>::remove_handler(on_draw);
        event_handler<events::on_process_spell_cast>::remove_handler(on_process_spell_cast);
    }

    void on_process_spell_cast(game_object_script sender, spell_instance_script spell)
    {

        if (sender && sender->get_champion() == champion_id::Taric && spell->get_spellslot() == spellslot::e)
        {
            last_e_time = gametime->get_time();
        }


        if (last_e_time + 0.1f >= gametime->get_time())
        {

            if (!q->is_ready())
                return;


            const auto target = target_selector->get_target(q->range(), damage_type::physical);


            if (target == nullptr || !target->is_valid_target() || target_selector->has_spellshield(target))
                return;


            q->cast(target);
        }
    }


    void on_draw()
    {
        if (myhero->is_dead())
            return;

        if (yitaric::toggle_keybind->get_bool() == true)
            return;
    }
};
