#ifndef CHESS_TEST_H
#define CHESS_TEST_H

#include "chess.h"

using namespace std;

namespace tests{

    void chess_base_tests();

    void chess_chs_move_tests();

    void chess_game_manip_tests();

    void chess_move_tests();

    // TODO: Current test is rudimentary, and does not check thoroughly for edge cases.
    //      If time allows, try to do those.
    void chess_atk_check_tests();

    // TODO: Current test is rudimentary, and does not cover all possible plays.
    void chess_play_tests();

    void chess_promo_tests();

    void chess_en_pass_tests();
    
    void chess_game_state_tests();
    
    void chess_psbl_plays_tests();

    void chess_full_game_tests();

    

}




#endif  // CHESS_TEST_H