#include "checkers.h"

using namespace gameEngine;


void tests::checkers_test1(){

    gameEngine::checkers myGame;

    myGame.clearBoard();

    // Define the testing piece.
    unsigned int initPos_i = 1;
    unsigned int initPos_j = 3;
    // checkers::CHK_PIECE testPiece = checkers::CHK_PIECE::RED_P;
    checkers::CHK_PIECE testPiece = checkers::CHK_PIECE::BLK_P;
    string piece_kw = checkers::get_CHK_PIECE_Str( testPiece );
    // Insert the test piece.
    myGame.insertPiece( initPos_i, initPos_j, testPiece );
    // Add support pieces to the test.
    myGame.insertPiece( 4, 2, checkers::CHK_PIECE::RED_P );
    myGame.insertPiece( 2, 4, checkers::CHK_PIECE::RED_P );
    myGame.insertPiece( 5, 1, checkers::CHK_PIECE::RED_P );
    myGame.insertPiece( 3, 1, checkers::CHK_PIECE::BLK_P );
    myGame.insertPiece( 7, 5, checkers::CHK_PIECE::RED_P );
    myGame.insertPiece( 6, 6, checkers::CHK_PIECE::BLK_P );
    myGame.insertPiece( 1, 5, checkers::CHK_PIECE::BLK_P );
    

    
    // Check possible moves on all directions for our piece.
    vector<checkers::CHK_DIREC> canMoveDir = 
        myGame.theoMoveCheckAll( initPos_i, initPos_j, testPiece );

    // Write move results in console.
    for( checkers::CHK_DIREC direc_i : canMoveDir ){
        string direc_kw = checkers::get_CHK_DIREC_Str( direc_i );
        cout << piece_kw << " can move to " << direc_kw << " from (" << initPos_i << "," << initPos_j << ")" << endl;
    }
    if( canMoveDir.size() == 0 ){
        cout << piece_kw << " can't move anywhere from (" << initPos_i << "," << initPos_j << ")" << endl;
    }

    // Check possible attacks on all directions for our piece.
    vector<checkers::CHK_DIREC> canAtkDir = 
        myGame.theoAtkCheckAll( initPos_i, initPos_j, testPiece );
    for( checkers::CHK_DIREC direc_i : canAtkDir ){
        string direc_kw = checkers::get_CHK_DIREC_Str( direc_i );
        cout << piece_kw << " can attack " << direc_kw << " from (" << initPos_i << "," << initPos_j << ")" << endl;
    }
    if( canAtkDir.size() == 0 ){
        cout << piece_kw << " can't attack anywhere from (" << initPos_i << "," << initPos_j << ")" << endl;
    }


    myGame.upd_atk_posb();
    vector<checkers::CHK_move> B_atk_list = myGame.getB_atk_list();
    vector<checkers::CHK_move> R_atk_list = myGame.getR_atk_list();

    cout << "Possible black attack points: ";
    for( unsigned int x = 0; x < B_atk_list.size(); x++ ){
        cout << "(" << B_atk_list.at(x).i << "," << B_atk_list.at(x).j << "," <<
            checkers::get_CHK_DIREC_Str( B_atk_list.at(x).k ) << ")" << " ";
    }
    cout << endl;

    cout << "Possible red attack points: ";
    for( unsigned int x = 0; x < R_atk_list.size(); x++ ){
        cout << "(" << R_atk_list.at(x).i << "," << R_atk_list.at(x).j << "," <<
            checkers::get_CHK_DIREC_Str( R_atk_list.at(x).k ) << ")" << " ";
    }
    cout << endl;


    myGame.upd_displ_posb();
    vector<checkers::CHK_move> B_displ_list = myGame.getB_displ_list();
    vector<checkers::CHK_move> R_displ_list = myGame.getR_displ_list();

    cout << "Possible black displacement points: ";
    for( unsigned int x = 0; x < B_displ_list.size(); x++ ){
        cout << "(" << B_displ_list.at(x).i << "," << B_displ_list.at(x).j << "," <<
            checkers::get_CHK_DIREC_Str( B_displ_list.at(x).k ) << ")" << " ";
    }
    cout << endl;
    
    cout << "Possible red displacement points: ";
    for( unsigned int x = 0; x < R_displ_list.size(); x++ ){
        cout << "(" << R_displ_list.at(x).i << "," << R_displ_list.at(x).j << "," <<
            checkers::get_CHK_DIREC_Str( R_displ_list.at(x).k ) << ")" << " ";
    }
    cout << endl;

    myGame.printBoard();

}


void tests::checkers_test2(){
    
    using namespace gameEngine;

    checkers myGame;

    myGame.clearBoard();

    // Add support pieces to create the custom scenario.
    myGame.insertPiece( 2, 2, checkers::CHK_PIECE::BLK_P );
    myGame.insertPiece( 2, 4, checkers::CHK_PIECE::BLK_P );
    myGame.insertPiece( 4, 2, checkers::CHK_PIECE::RED_P );
    myGame.insertPiece( 4, 4, checkers::CHK_PIECE::RED_P );
    myGame.printBoard();

    myGame.play( 2,2, checkers::CHK_DIREC::DOWNRIGHT );
    myGame.printBoard();

    myGame.play( 4,4, checkers::CHK_DIREC::UPLEFT );
    myGame.printBoard();

    myGame.play( 2,4, checkers::CHK_DIREC::DOWNLEFT );
    myGame.printBoard();

    myGame.play( 4,2, checkers::CHK_DIREC::UPRIGHT );
    myGame.printBoard();
}


void tests::checkers_test3(){

    using namespace gameEngine;

    checkers myGame;

    myGame.clearBoard();

    // Add support pieces to create the custom scenario.
    myGame.insertPiece( 2, 1, checkers::CHK_PIECE::BLK_P );
    myGame.insertPiece( 3, 2, checkers::CHK_PIECE::RED_P );
    myGame.insertPiece( 5, 2, checkers::CHK_PIECE::RED_P );
    myGame.insertPiece( 2, 7, checkers::CHK_PIECE::RED_P );
    myGame.printBoard();

    myGame.play( 2, 1, checkers::CHK_DIREC::DOWNRIGHT );
    myGame.printBoard();

    myGame.play( 4, 3, checkers::CHK_DIREC::DOWNRIGHT );
    myGame.printBoard();

    myGame.play( 5, 2, checkers::CHK_DIREC::UPRIGHT );
    myGame.printBoard();

    myGame.play( 4, 3, checkers::CHK_DIREC::DOWNRIGHT );
    myGame.printBoard();

    myGame.play( 4, 3, checkers::CHK_DIREC::DOWNLEFT );
    myGame.printBoard();

    myGame.play( 6, 1, checkers::CHK_DIREC::DOWNLEFT );
    myGame.printBoard();

}


void tests::checkers_test4(){
    
    using namespace gameEngine;

    checkers myGame;

    myGame.clearBoard();
    // Add support pieces to create the custom scenario.
    myGame.insertPiece( 1, 1, checkers::CHK_PIECE::RED_P );
    myGame.insertPiece( 6, 4, checkers::CHK_PIECE::BLK_P );
    myGame.printBoard();

    myGame.play( 6, 4, checkers::CHK_DIREC::DOWNLEFT );
    myGame.printBoard();

    myGame.play( 1, 1, checkers::CHK_DIREC::UPRIGHT );
    myGame.printBoard();

    myGame.play( 7, 3, checkers::CHK_DIREC::UPRIGHT );
    myGame.play( 0, 2, checkers::CHK_DIREC::DOWNLEFT );
    myGame.printBoard();



}


void tests::checkers_test5(){

    using namespace gameEngine;

    checkers myGame;

    myGame.clearBoard();

    // Draw case.
    myGame.upd_game_state();
    cout << "Draw case evaluation: " << myGame.gameStateEval() << endl;

    // Red win case.
    myGame.insertPiece( 1, 1, checkers::CHK_PIECE::RED_P );
    myGame.upd_game_state();
    cout << "Red win case evaluation: " << myGame.gameStateEval() << endl;

    // Black win case.
    myGame.clearBoard();
    myGame.insertPiece( 6, 4, checkers::CHK_PIECE::BLK_P );
    myGame.upd_game_state();
    cout << "Black win case evaluation: " << myGame.gameStateEval() << endl;

    // Ongoing case 1 (Matching piece counts).
    myGame.insertPiece( 4, 2, checkers::CHK_PIECE::RED_P );
    myGame.upd_game_state();
    cout << "Ongoing evaluation (equal piece counts): " << myGame.gameStateEval() << endl;

    // Ongoing case 2 (Red leads by 1 piece).
    myGame.insertPiece( 1, 5, checkers::CHK_PIECE::RED_P );
    myGame.upd_game_state();
    cout << "Ongoing evaluation (Red leads by 1 piece): " << myGame.gameStateEval() << endl;

    // Ongoing case 3 (Black leads by 1 piece).
    myGame.insertPiece( 7, 3, checkers::CHK_PIECE::BLK_P );
    myGame.insertPiece( 7, 5, checkers::CHK_PIECE::BLK_P );
    myGame.upd_game_state();
    cout << "Ongoing evaluation (Black leads by 1 piece): " << myGame.gameStateEval() << endl;

    // Ongoing case 4 (Red leads by 1 crown piece).
    myGame.insertPiece( 0, 0, checkers::CHK_PIECE::CRED_P );
    myGame.upd_game_state();
    cout << "Ongoing evaluation (Red leads by 1 crown piece but falls by 1 piece): " << myGame.gameStateEval() << endl;

    // Ongoing case 5 (Black leads by 1 piece).
    myGame.insertPiece( 0, 2, checkers::CHK_PIECE::CBLK_P );
    myGame.upd_game_state();
    cout << "Ongoing evaluation (Black leads by 1 piece after adding a crown piece): " << myGame.gameStateEval() << endl;


    myGame.printBoard();

}



void tests::checkers_test6(){

    using namespace gameEngine;

    checkers myGame;
    myGame.clearBoard();

    vector<checkers::CHK_move> validMoveVect;

    // No piece case:
    validMoveVect = myGame.get_valid_moves();
    for( checkers::CHK_move move_z : validMoveVect ){
        cout << "(" << move_z.i << "," << move_z.j << "," <<
            checkers::get_CHK_DIREC_Str( move_z.k ) << ")" << " ";
    }

    // Scenario 1 (One black piece, black turn).
    myGame.insertPiece( 1, 1, checkers::CHK_PIECE::BLK_P );
    myGame.upd_atk_posb();
    validMoveVect = myGame.get_valid_moves();
    for( checkers::CHK_move move_z : validMoveVect ){
        cout << "(" << move_z.i << "," << move_z.j << "," <<
            checkers::get_CHK_DIREC_Str( move_z.k ) << ")" << " ";
    }
    cout << endl;

    // Scenario 2 (One black piece + One red piece, black turn).
    myGame.insertPiece( 5, 5, checkers::CHK_PIECE::RED_P );
    myGame.upd_atk_posb();
    validMoveVect = myGame.get_valid_moves();
    for( checkers::CHK_move move_z : validMoveVect ){
        cout << "(" << move_z.i << "," << move_z.j << "," <<
            checkers::get_CHK_DIREC_Str( move_z.k ) << ")" << " ";
    }
    cout << endl;

    // Scenario 3 (One black piece + One red piece, red turn).
    myGame.setTurn_cnt( myGame.getTurn_cnt() + 1 );
    validMoveVect = myGame.get_valid_moves();
    for( checkers::CHK_move move_z : validMoveVect ){
        cout << "(" << move_z.i << "," << move_z.j << "," <<
            checkers::get_CHK_DIREC_Str( move_z.k ) << ")" << " ";
    }
    cout << endl;

    // Scenario 4 (Added a black piece that can be attacked by red).
    myGame.insertPiece( 4, 6, checkers::CHK_PIECE::BLK_P );
    myGame.upd_atk_posb();
    validMoveVect = myGame.get_valid_moves();
    for( checkers::CHK_move move_z : validMoveVect ){
        cout << "(" << move_z.i << "," << move_z.j << "," <<
            checkers::get_CHK_DIREC_Str( move_z.k ) << ")" << " ";
    }
    cout << endl;

    // Scenraio 5 (Added crown red piece in position for attack backwards).
    myGame.insertPiece( 0, 2, checkers::CHK_PIECE::CRED_P );
    myGame.upd_atk_posb();
    validMoveVect = myGame.get_valid_moves();
    for( checkers::CHK_move move_z : validMoveVect ){
        cout << "(" << move_z.i << "," << move_z.j << "," <<
            checkers::get_CHK_DIREC_Str( move_z.k ) << ")" << " ";
    }
    cout << endl;

    myGame.printBoard();

}



void tests::checkers_test7(){

    using namespace gameEngine;

    checkers myGame;
    myGame.clearBoard();

    int scenario_cnt = 0;

    bool isMaximizing = false;
    int depth = 0;
    int finalScore = 0;

    // // [Scenario 1]: Game draw scenario.
    // scenario_cnt++;
    // myGame.upd_game_state();
    // isMaximizing = true;    depth = 0;
    // finalScore = myGame.minmax( isMaximizing, depth );
    // cout << "Scenario " << scenario_cnt << " score: " << finalScore << endl;

    // // [Scenario 2]: Red win scenario.
    // scenario_cnt++;
    // myGame.insertPiece( 1, 1, checkers::CHK_PIECE::RED_P );
    // myGame.upd_game_state();
    // isMaximizing = true;    depth = 0;
    // finalScore = myGame.minmax( isMaximizing, depth );
    // cout << "Scenario " << scenario_cnt << " score: " << finalScore << endl;

    // // [Scenario 3]: Black win scenario.
    // scenario_cnt++;
    // myGame.clearBoard();
    // myGame.insertPiece( 1, 1, checkers::CHK_PIECE::BLK_P );
    // myGame.upd_game_state();
    // isMaximizing = true;    depth = 0;
    // finalScore = myGame.minmax( isMaximizing, depth );
    // cout << "Scenario " << scenario_cnt << " score: " << finalScore << endl;

    // // [Scenario 4]: Red superiority in value.
    // scenario_cnt++;
    // myGame.insertPiece( 2, 2, checkers::CHK_PIECE::CRED_P );
    // myGame.upd_game_state();
    // isMaximizing = true;    depth = 0;
    // finalScore = myGame.minmax( isMaximizing, depth );
    // cout << "Scenario " << scenario_cnt << " score: " << finalScore << endl;

    // // [Scenario 5]: Black superiority in value.
    // scenario_cnt++;
    // myGame.insertPiece( 4, 6, checkers::CHK_PIECE::CBLK_P );
    // myGame.upd_game_state();
    // isMaximizing = true;    depth = 0;
    // finalScore = myGame.minmax( isMaximizing, depth );
    // cout << "Scenario " << scenario_cnt << " score: " << finalScore << endl;

    // // [Scenario 6]: 1 red vs 1 black in position to attack each other with 1 depth, black turn.
    // scenario_cnt++;
    // myGame.clearBoard();
    // myGame.insertPiece( 2, 2, checkers::CHK_PIECE::BLK_P );
    // myGame.insertPiece( 3, 3, checkers::CHK_PIECE::RED_P );
    // myGame.upd_atk_posb();
    // myGame.upd_game_state();
    // isMaximizing = true;    depth = 1;
    // finalScore = myGame.minmax( isMaximizing, depth );
    // cout << "Scenario " << scenario_cnt << " score: " << finalScore << endl;
    // myGame.printBoard();

    // // [Scenario 7]: 1 red vs 1 black in position to attack each other with 1 depth, red turn.
    // scenario_cnt++;
    // myGame.clearBoard();
    // myGame.insertPiece( 2, 2, checkers::CHK_PIECE::BLK_P );
    // myGame.insertPiece( 3, 3, checkers::CHK_PIECE::RED_P );
    // myGame.setTurn_cnt( 1 );     // Force red turn.
    // myGame.upd_atk_posb();
    // myGame.upd_game_state();
    // isMaximizing = false;    depth = 1;
    // finalScore = myGame.minmax( isMaximizing, depth );
    // cout << "Scenario " << scenario_cnt << " score: " << finalScore << endl;
    // myGame.printBoard();


    /* 
    [Scenario 8]: 1 red in attack position against one black and one crowned black.
    */
    scenario_cnt++;
    myGame.clearBoard();
    myGame.insertPiece( 2, 2, checkers::CHK_PIECE::BLK_P );
    myGame.insertPiece( 2, 4, checkers::CHK_PIECE::CBLK_P );
    myGame.insertPiece( 3, 3, checkers::CHK_PIECE::RED_P );
    myGame.setTurn_cnt( 1 );    // Force red turn.
    myGame.upd_atk_posb();
    myGame.upd_game_state();
    isMaximizing = false;    depth = 1;
    finalScore = myGame.minmax( isMaximizing, depth );
    cout << "Scenario " << scenario_cnt << " score: " << finalScore << endl;
    myGame.printBoard();




    // myGame.printBoard();

}