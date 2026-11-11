#pragma once
#include <bn_display.h>
#include <bn_fixed.h>
#include <bn_sprite_animate_actions.h>
#include <bn_sprite_ptr.h>

#include "bn_sprite_items_bar_box.h"


// All game functions/classes/variables/constants scoped to the namespace
namespace bar
{
    class bar_player {
        
        public:
            /**
             * @param player_position_x where the player is spawned on the x axis. The character will be static.
             * @param player_position_y where the player is spawned on the y axis.
             */
            bar_player(bn::fixed player_postion_x, bn::fixed player_position_y);

            /**
            * Reads from the bumpers and triggers one of the arms to move.
            */
            void update();

        private:
            // The sprite to display the player
            bn::sprite_ptr _sprite;
            bn::sprite_animate_action _sprite_action;

            /**
             * Reads from the d-pad and sets direction sprites is pointing.
             * Regardless of direction, updates the sprite animation action.
             */
            void _update_animation();

    };
}
