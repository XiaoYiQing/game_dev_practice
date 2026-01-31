#ifndef CHESS_TEST_H
#define CHESS_TEST_H

#include "chess.h"
#include "CHS_SFML_eng.h"

using namespace std;

extern string RES_PATH_XYQ_str;

namespace tests{

    void chess_base_tests();

    void chess_chs_move_tests();

    void chess_game_manip_tests();

    void chess_incident_safe_tests();

    void chess_chk_persist_tests();

    void valid_atk_maps_tests();
    
    void valid_move_maps_tests();

    void legal_move_maps_tests();

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

    void chess_alg_coord_trans_tests();

    void chess_upd_pre_legal_tests();

    void chess_upd_pre_legal_tests_emp();

    void chess_upd_pre_legal_tests_occ();


    void CHS_SFML_eng_tests();

    void chess_all_alg_comm_tests();

    void chess_minmax_tests();

    void chess_minmaxAB_tests();

    void chess_minmax_bestMove_tests();

    void chess_minmaxAB_bestMove_tests();

    void chess_minmaxAB_split_tests();

}


namespace tests_chess{

    /**
     * Specialized helper function for determining if an integer is in the target
     * vector<int> of index "vecIdx" within the array of vector<int> "tarArr".
     */
    bool is_int_at_tar_vec( int tar, int vecIdx, 
        std::array<vector<int>, 64>& tarArr );

}




#endif  // CHESS_TEST_H