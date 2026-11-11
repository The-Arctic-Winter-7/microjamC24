#include "bar/bar_player.h"
#include <bn_keypad.h>

#define FLOOR (80 - 8)

namespace bar
{
    bn::fixed player_position_x = bn::display::width() / 2;
    bn::fixed player_position_y = FLOOR;

    bar_player::bar_player(bn::fixed player_position_x, bn::fixed player_position_y) : _sprite(bn::sprite_items::bar_box.create_sprite(player_position_x, player_position_y)),
                                                                                       _sprite_action(bn::create_sprite_animate_action_forever(_sprite, 16, bn::sprite_items::bar_box.tiles_item(), 0, 1, 2, 3))
    {
    }

    void bar_player::update(bn::vector<bar_bouncer, MAX_BOUNCERS> &bouncers)
    {
        _update_animation();

        if (bn::keypad::l_pressed())
        {
        }

        if (bn::keypad::r_pressed())
        {
        }
    }

    void bar::bar_player::_update_animation()
    {
        if (bn::keypad::a_pressed())
        {
        }

        if (bn::keypad::b_pressed())
        {
        }
    }
}
