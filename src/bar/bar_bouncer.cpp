#include "bar_bouncer.h"

namespace bar
{
    bar_bouncer::bar_bouncer(bn::fixed x_start, bn::fixed y_start, bn::fixed base_speed) : _sprite(bn::sprite_items::bar_bouncer.create_sprite(x_start, y_start)),
                                                                                      _horizontal_speed(base_speed), _is_hit(false)
    {
    }

    void bar_bouncer::update()
    {
        bn::fixed y = _sprite.y();

        if(!_is_hit) {
            y += _horizontal_speed;
        } else {
            y -= _horizontal_speed;
        }

        if(y <= MIN_Y) {
            _is_hit = false;
        }
        
    }
}