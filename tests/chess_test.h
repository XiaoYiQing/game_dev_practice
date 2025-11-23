#ifndef CHESS_TEST_H
#define CHESS_TEST_H

#include "chess.h"
#include "CHS_SFML_eng.h"

using namespace std;

extern string RES_PATH_XYQ_str;

namespace tests{

    void chess_base_tests();

    void chess_chs_move_tests();

    void chess_alg_coord_trans_tests();

    void chess_game_manip_tests();

    void chess_move_tests();

    void chess_atk_check_tests();

    void chess_play_tests();

    void chess_promo_tests();

    void chess_en_pass_tests();
    
    void chess_game_state_tests();
    
    void chess_psbl_plays_tests();

    void chess_checkmate_tests();

    void chess_draw_tests();

    void chess_full_game_tests();

    void CHS_SFML_eng_tests();

    void chess_all_alg_comm_tests();

}




#endif  // CHESS_TEST_H