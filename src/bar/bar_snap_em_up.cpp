#include "bar_snap_em_up.h"
#include "mj/mj_game_list.h"


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
   bar_snap_em_up::bar_snap_em_up([[maybe_unused]] int complete_games, [[maybe_unused]] const mj::game_data &data) : mj::game("bar")
   {
   }

   bn::string<16> bar_snap_em_up::title() const 
   {
      return "Snap Em Up!";
   }

   int bar_snap_em_up::total_frames() const
   {
      return 300;
   }

   mj::game_result bar_snap_em_up::play([[maybe_unused]] const mj::game_data &data)
   {
      mj::game_result result(victory(), false);
      return result;
   }

   bool bar_snap_em_up::victory() const
   {
      return false;
   }

   void bar_snap_em_up::fade_in([[maybe_unused]]const mj::game_data &data)
   {
   }

   void bar_snap_em_up::fade_out([[maybe_unused]]const mj::game_data &data)
   {
   }

}