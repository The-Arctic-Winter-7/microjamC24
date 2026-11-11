#include "bar_snap_em_up.h"
#include "mj/mj_game_list.h"

#define FLOOR (80 - 8)
#define CEILING (-72 - 8)

namespace 
{
    constexpr bn::string_view code_credits[] = { "TheArticWinter, crex424" };
    constexpr bn::string_view graphics_credits[] = { "To Be Announced" };
    constexpr bn::string_view sfx_credits[] = {"To Be Announced"};
    constexpr bn::string_view music_credits[] = {"To Be Announced"};
}

// Macros used to add game to game list
MJ_GAME_LIST_ADD(bar::bar_snap_em_up) // The class of the game is used here
MJ_GAME_LIST_ADD_CODE_CREDITS(code_credits)
MJ_GAME_LIST_ADD_GRAPHICS_CREDITS(graphics_credits)
MJ_GAME_LIST_ADD_MUSIC_CREDITS(music_credits)
MJ_GAME_LIST_ADD_SFX_CREDITS(sfx_credits)

namespace bar
{
   bn::fixed player_position_x = bn::display::width() / 20;
   bn::fixed player_position_y = FLOOR;
   bn::size player_size = {64, 64};

   bn::fixed bounce_position_x = bn::display::width() / 20;
   bn::fixed bounce_position_y = CEILING;
   bn::size bounce_size = {8, 8};
   bn::fixed bounce_speed;

   bn::vector<bar_bouncer, bar_player::MAX_BOUNCERS> bouncer = {};

   int game_timer = 0;

   bar_snap_em_up::bar_snap_em_up([[maybe_unused]] int completed_games, [[maybe_unused]] const mj::game_data &data) : mj::game("bar"),
      _player(bar_player(player_position_x, player_position_y, player_size)), 
      _bouncer(bar_bouncer(bounce_position_x, bounce_position_y, _recommended_bounce_speed(recommended_difficulty_level(completed_games, data)), bounce_size))
   {
      bn::fixed bounce_speed = _recommended_bounce_speed(recommended_difficulty_level(completed_games, data));
   }

   bn::string<16> bar_snap_em_up::title() const 
   {
      return "Snap Em Up!";
   }

   int bar_snap_em_up::total_frames() const
   {
      return 300;
   }

   bn::fixed bar_snap_em_up::_recommended_bounce_speed(mj::difficulty_level difficulty) 
   {
      if (difficulty == mj::difficulty_level::EASY)
      {
         return 1;
      } else if (difficulty == mj::difficulty_level::NORMAL) {
         return 2;
      }
      return 3;
   }

   mj::game_result bar_snap_em_up::play([[maybe_unused]] const mj::game_data &data)
   {
      _player.update(bouncer);

      if(game_timer >= 60) {
         game_timer = 0;
         //bar_spawn_bouncer(bouncer, bounce_position_x, bounce_position_y, bounce_speed, bounce_size);
         bouncer.push_back(_bouncer);
      }

      game_timer++;
      mj::game_result result(victory(), false);
      return result;
   }

   bool bar_snap_em_up::victory() const
   {
      return _player.intercepted_bounce();
   }

   void bar_snap_em_up::fade_in([[maybe_unused]]const mj::game_data &data)
   {
   }

   void bar_snap_em_up::fade_out([[maybe_unused]]const mj::game_data &data)
   {
   }

}