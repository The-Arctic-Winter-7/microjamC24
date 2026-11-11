#pragma once

#include <bn_sprite_ptr.h>
#include <bn_display.h>

#include "mj/mj_game.h"

#include "bn_sprite_items_bar_bouncer.h"

namespace bar
{
    class bar_bouncer
    {
        // The bounds of the screen
        static constexpr int MAX_X = bn::display::width() / 2;
        static constexpr int MIN_X = -bn::display::width() / 2;
        static constexpr int MAX_Y = bn::display::height() / 2;
        static constexpr int MIN_Y = -bn::display::height() / 2;

    public:
        bn::sprite_ptr _sprite;
        bn::fixed _horizontal_speed;
        bool _is_hit;

        /**
         *  Bouncer constructor that creates sprites at the given coordinates and with randomized speeds. Extends the
         * Butano sprite pointer class bn::sprite_ptr.
         *
         *  @param start_x The starting x coordinate the bouncer spawns at
         *  @param start_y The starting y coordinate the bouncer spawns at
         */
        bar_bouncer(bn::fixed x_start, bn::fixed y_start, bn::fixed base_speed);

        /**
         *  Updates the position of the Bouncer sprite by checking whether or not it's position is greater
         * than the bounds of the screen.
         */
        void update();
    };
}