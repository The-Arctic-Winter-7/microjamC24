#pragma once

#include <bn_sprite_ptr.h>

namespace bar
{
    class bar_bouncer
    {
    private:
    public:
        bn::sprite_ptr sprite;
        bn::fixed x_speed;
        bn::fixed y_speed;

        /**
         *  Bouncer constructor that creates sprites at the given coordinates and with randomized speeds. Extends the
         * Butano sprite pointer class bn::sprite_ptr.
         *
         *  @param start_x The starting x coordinate the bouncer spawns at
         *  @param start_y The starting y coordinate the bouncer spawns at
         */
        bar_bouncer(bn::fixed x_start, bn::fixed y_start);

        /**
         *  Updates the position of the Bouncer sprite by checking whether or not it's position is greater
         * than the bounds of the screen.
         */
        void update();
    };
}