#include "bar_snap_em_up.h"
#include "mj/mj_game_list.h"

#include "bn_regular_bg_items_bar_ocean.h"


#define FLOOR (80 - 16)
#define CEILING (-72 - 8)

namespace
{
   constexpr bn::string_view code_credits[] = {"TheArticWinter, crex424"};
   constexpr bn::string_view graphics_credits[] = {""};
   constexpr bn::string_view sfx_credits[] = {""};
   constexpr bn::string_view music_credits[] = {""};
}

// Macros used to add game to game list
MJ_GAME_LIST_ADD(bar::bar_snap_em_up) // The class of the game is used here
MJ_GAME_LIST_ADD_CODE_CREDITS(code_credits)
MJ_GAME_LIST_ADD_GRAPHICS_CREDITS(graphics_credits)
MJ_GAME_LIST_ADD_MUSIC_CREDITS(music_credits)
MJ_GAME_LIST_ADD_SFX_CREDITS(sfx_credits)

namespace bar
{
   bn::fixed position_left = bn::display::width() / 20;
   bn::fixed position_right = bn::display::width() / -20;

   bn::fixed player_position_y = 20;
   bn::size player_size = {16, 16};

   bn::fixed bounce_position_y = CEILING;
   bn::size bounce_size = {8, 8};

   int TARGET_COUNT = 5;

   int game_timer = 0;
   int bouncer_hit_count = 0;
   int kraken_lives = 3;
   int completed_games_global;

   bn::random rng_spawn;

   bool bouncer_target_reached = false;

   bar_snap_em_up::bar_snap_em_up([[maybe_unused]] int completed_games, [[maybe_unused]] const mj::game_data &data) : mj::game("bar"),
                                                                                                                      _player_arms(),
                                                                                                                      _bouncers(),
                                                                                                                      _background(bn::regular_bg_items::bar_ocean.create_bg())
   {
      game_timer = 0;
      bouncer_hit_count = 0;
      kraken_lives = 3;
      bouncer_target_reached = false;
      rng_spawn = data.random;
      completed_games_global = completed_games;

      _player_arms.push_back(bar_player(position_left, player_position_y, player_size));
      _player_arms.push_back(bar_player(position_right, player_position_y, player_size));

      bar_spawn_bouncer(_bouncers, position_left, bounce_position_y, _recommended_bounce_speed(recommended_difficulty_level(completed_games, data)), bounce_size);
   }

   bn::string<16> bar_snap_em_up::title() const
   {
      return "Snap Em Up!";
   }

   int bar_snap_em_up::total_frames() const
   {
      return 180;
   }

   bn::fixed bar_snap_em_up::_recommended_bounce_speed(mj::difficulty_level difficulty)
   {
      if (difficulty == mj::difficulty_level::EASY)
      {
         TARGET_COUNT = 6;
         return 2;
      }
      else if (difficulty == mj::difficulty_level::NORMAL)
      {
         TARGET_COUNT = 7;
         return 2.5;
      }
      else if (difficulty == mj::difficulty_level::HARD)
      {
         TARGET_COUNT = 8;
         return 3.2;
      }
      return 1;
   }

   bn::fixed bar_snap_em_up::_recommended_spawn_speed(mj::difficulty_level difficulty)
   {
      if (difficulty == mj::difficulty_level::EASY)
      {
         return 20;
      }
      else if (difficulty == mj::difficulty_level::NORMAL)
      {
         return 15;
      }
      return 10;
   }

   mj::game_result bar_snap_em_up::play([[maybe_unused]] const mj::game_data &data)
   {
      for (bar_bouncer &bouncer : _bouncers)
      {
         bouncer.update();
         _player_arms[0].update_lower_right(bouncer);
         _player_arms[1].update_lower_left(bouncer);
      }

      for (int i = _bouncers.size() - 1; i >= 0; i--)
      {
         if (_bouncers[i].is_collided())
         {
            _bouncers.erase(_bouncers.begin() + i);
            bouncer_hit_count++;
         }
         if (_bouncers[i].get_sprite().y() >= FLOOR)
         {
            _bouncers.erase(_bouncers.begin() + i);
            kraken_lives--;
         }
      }

      if (game_timer >= _recommended_spawn_speed(recommended_difficulty_level(completed_games_global, data)))
      {
         game_timer = 0;
         if (rng_spawn.get_unbiased_int(0, 2) == 0)
            bar_spawn_bouncer(_bouncers, position_left, bounce_position_y, _recommended_bounce_speed(recommended_difficulty_level(completed_games_global, data)), bounce_size);
         else
            bar_spawn_bouncer(_bouncers, position_right, bounce_position_y, _recommended_bounce_speed(recommended_difficulty_level(completed_games_global, data)), bounce_size);
         rng_spawn = data.random;
      }

      if (bouncer_hit_count == TARGET_COUNT)
         bouncer_target_reached = true;

      game_timer++;
      mj::game_result result(victory(), false);
      return result;
   }

   bool bar_snap_em_up::victory() const
   {
      return bouncer_target_reached;
   }

   void bar_snap_em_up::fade_in([[maybe_unused]] const mj::game_data &data)
   {
   }

   void bar_snap_em_up::fade_out([[maybe_unused]] const mj::game_data &data)
   {
      _bouncers.clear();
   }
}