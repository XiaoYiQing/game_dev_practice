#include "CHS_SFML_eng.h"

using namespace gameEngine;

void game::play_chess(){

    // Create a texture to hold the image
    string button_img_np_FFN = RES_PATH_XYQ_str + "/button_orange_long_1_np.png";
    string button_img_p_FFN = RES_PATH_XYQ_str + "/button_orange_long_1_p.png";
    string funny_img_FFN = RES_PATH_XYQ_str + "/funny_img_2.jpg";
    
    // Textures file full name for the white pieces.
    map< chess::CHS_PIECE_TYPE, string > CHS_PCE_W_tex_FFN_map;
    // Textures file full name for the black pieces.
    map< chess::CHS_PIECE_TYPE, string > CHS_PCE_B_tex_FFN_map;

    CHS_PCE_W_tex_FFN_map[ chess::CHS_PIECE_TYPE::PAWN ] = 
        RES_PATH_XYQ_str + "/button_orange_long_1_np.png";
    


}


