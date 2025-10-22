#include "chess_test.h"


using namespace gameEngine;

void tests::chess_base_tests(){
    
    // Test boolean init.
    bool test_bool = true;

    chess myGame = chess();

    // Test the initilization of a board.
    chess::chs_piece currPiece;
    for( unsigned int i = 0; i < chess::BOARDHEIGHT; i++ ){
    for( unsigned int j = 0; j < chess::BOARDWIDTH; j++ ){
        currPiece = myGame.get_piece_at(i,j);
        test_bool = test_bool && ( currPiece.type == chess::CHS_PIECE_TYPE::NO_P );
        test_bool = test_bool && ( currPiece.color == chess::CHS_PIECE_COLOR::NO_C );
    }
    }

    if( test_bool ){
        cout << "chess_base_tests init test: passed!" << endl;
    }else{
        cout << "chess_base_tests init test: failed!" << endl;
    }

    // Test set_piece_at and get_piece_at.
    chess::chs_piece pawnW = chess::chs_piece( chess::CHS_PIECE_TYPE::PAWN,
        chess::CHS_PIECE_COLOR::WHITE ); 
    cout << "Print white pawn symbol (Expected to be WP): ";
    pawnW.printPiece();
    cout << endl;

    // Insert a white pawn and verify
    unsigned int tar_i = 3;
    unsigned int tar_j = 5;
    myGame.set_piece_at( tar_i, tar_j, pawnW );
    currPiece = myGame.get_piece_at( tar_i, tar_j );
    test_bool = test_bool && ( currPiece.type == chess::CHS_PIECE_TYPE::PAWN );
    test_bool = test_bool && ( currPiece.color == chess::CHS_PIECE_COLOR::WHITE );
    
    if( test_bool ){
        cout << "chess_base_tests access test: passed!" << endl;
    }else{
        cout << "chess_base_tests access test: passed!" << endl;
    }

    // Add another piece and see the print result.
    myGame.set_piece_at( 7, 7, chess::chs_piece( chess::CHS_PIECE_TYPE::KNIGHT,
        chess::CHS_PIECE_COLOR::BLACK ) );
    myGame.printBoard();

}



void tests::chess_chs_move_tests(){

    // // Test boolean init.
    // bool test_bool = true;

    // chess myGame = chess();


    // chess::chs_move spec_move( 0, 0, 1, 0 );
    // // Coloreless case.
    // test_bool = test_bool && !( spec_move.is_move_valid( chess::CHS_PIECE_TYPE::ROOK, 
    //     chess::CHS_PIECE_COLOR::NO_C ) );
    // // Typeless case.
    // test_bool = test_bool && !( spec_move.is_move_valid( chess::CHS_PIECE_TYPE::NO_P, 
    //     chess::CHS_PIECE_COLOR::WHITE ) );
    
    // // Invalid initial position case (< 0).
    // spec_move.pt_a = pair<int,int>(-1,0);   
    // spec_move.pt_b = pair<int,int>(1,0);
    // test_bool = test_bool && !( spec_move.is_move_valid( chess::CHS_PIECE_TYPE::ROOK, 
    //     chess::CHS_PIECE_COLOR::WHITE ) );
    // // Invalid initial position case (>= BOARDHEIGHT).
    // spec_move.pt_a = pair<int,int>(chess::BOARDHEIGHT,0);   
    // spec_move.pt_b = pair<int,int>(1,0);
    // test_bool = test_bool && !( spec_move.is_move_valid( chess::CHS_PIECE_TYPE::ROOK, 
    //     chess::CHS_PIECE_COLOR::WHITE ) );
    
    // // Invalid final position case (< 0).
    // spec_move.pt_a = pair<int,int>(0,0);
    // spec_move.pt_b = pair<int,int>(0,-1);
    // test_bool = test_bool && !( spec_move.is_move_valid( chess::CHS_PIECE_TYPE::ROOK, 
    //     chess::CHS_PIECE_COLOR::WHITE ) );
    // // Invalid final position case (>= BOARDWIDTH).
    // spec_move.pt_a = pair<int,int>(0,0);
    // spec_move.pt_b = pair<int,int>(0,chess::BOARDWIDTH);
    // test_bool = test_bool && !( spec_move.is_move_valid( chess::CHS_PIECE_TYPE::ROOK, 
    //     chess::CHS_PIECE_COLOR::WHITE ) );
    // // Null move case.
    // spec_move.pt_a = pair<int,int>(1,1);
    // spec_move.pt_b = pair<int,int>(1,1);
    // test_bool = test_bool && !( spec_move.is_move_valid( chess::CHS_PIECE_TYPE::ROOK, 
    //     chess::CHS_PIECE_COLOR::WHITE ) );

    // if( test_bool ){
    //     cout << "chess_chs_move_tests fringe case tests: passed!" << endl;
    // }else{
    //     cout << "chess_chs_move_tests fringe case tests: failed!" << endl;
    // }
    // test_bool = true;


    // // Pawn move test.
    // chess::chs_piece wPawn = chess::chs_piece( chess::CHS_PIECE_TYPE::PAWN,
    //     chess::CHS_PIECE_COLOR::WHITE );
    // chess::chs_piece bPawn = chess::chs_piece( chess::CHS_PIECE_TYPE::PAWN,
    //     chess::CHS_PIECE_COLOR::BLACK );

    // chess::chs_move move_bad( 2, 4, 3, 4 );
    // chess::chs_move move_good( 2, 4, 1, 4 );
    // test_bool = test_bool && !( move_bad.is_move_valid( wPawn ) );
    // test_bool = test_bool && ( move_good.is_move_valid( wPawn ) );
    // test_bool = test_bool && ( move_bad.is_move_valid( bPawn ) );
    // test_bool = test_bool && !( move_good.is_move_valid( bPawn ) );
    // if( test_bool ){
    //     cout << "chess_chs_move_tests pawn case tests: passed!" << endl;
    // }else{
    //     cout << "chess_chs_move_tests pawn case tests: failed!" << endl;
    // }
    // test_bool = true;


    // // Knight move test.
    // chess::chs_piece wKnight = chess::chs_piece( chess::CHS_PIECE_TYPE::KNIGHT,
    //     chess::CHS_PIECE_COLOR::WHITE );

    // move_bad = chess::chs_move( 4, 4, 3, 5 );
    // move_good = chess::chs_move( 4, 4, 3, 6 );
    // test_bool = test_bool && !( move_bad.is_move_valid( wKnight ) );
    // test_bool = test_bool && ( move_good.is_move_valid( wKnight ) );
    // if( test_bool ){
    //     cout << "chess_chs_move_tests knight case tests: passed!" << endl;
    // }else{
    //     cout << "chess_chs_move_tests knight case tests: failed!" << endl;
    // }
    // test_bool = true;


    // // Bishop move test.
    // chess::chs_piece wBishop = chess::chs_piece( chess::CHS_PIECE_TYPE::BISHOP,
    //     chess::CHS_PIECE_COLOR::WHITE );
    // move_bad = chess::chs_move( 4, 4, 7, 6 );
    // move_good = chess::chs_move( 4, 4, 2, 2 );
    // test_bool = test_bool && !( move_bad.is_move_valid( wBishop ) );
    // test_bool = test_bool && ( move_good.is_move_valid( wBishop ) );
    // if( test_bool ){
    //     cout << "chess_chs_move_tests bishop case tests: passed!" << endl;
    // }else{
    //     cout << "chess_chs_move_tests bishop case tests: failed!" << endl;
    // }
    // test_bool = true;


    // // Rook move test.
    // chess::chs_piece wRook = chess::chs_piece( chess::CHS_PIECE_TYPE::ROOK,
    //     chess::CHS_PIECE_COLOR::WHITE );
    // move_bad = chess::chs_move( 4, 4, 5, 7 );
    // move_good = chess::chs_move( 4, 4, 2, 4 );
    // test_bool = test_bool && !( move_bad.is_move_valid( wRook ) );
    // test_bool = test_bool && ( move_good.is_move_valid( wRook ) );
    // if( test_bool ){
    //     cout << "chess_chs_move_tests rook case tests: passed!" << endl;
    // }else{
    //     cout << "chess_chs_move_tests rook case tests: failed!" << endl;
    // }
    // test_bool = true;

    // // Queen move test.
    // chess::chs_piece wQueen = chess::chs_piece( chess::CHS_PIECE_TYPE::QUEEN,
    //     chess::CHS_PIECE_COLOR::WHITE );
    // move_bad = chess::chs_move( 4, 4, 5, 6 );
    // move_good = chess::chs_move( 4, 4, 0, 0 );
    // chess::chs_move move_good2 = chess::chs_move( 4, 4, 4, 0 );
    // test_bool = test_bool && !( move_bad.is_move_valid( wQueen ) );
    // test_bool = test_bool && ( move_good.is_move_valid( wQueen ) );
    // test_bool = test_bool && ( move_good2.is_move_valid( wQueen ) );
    // if( test_bool ){
    //     cout << "chess_chs_move_tests queen case tests: passed!" << endl;
    // }else{
    //     cout << "chess_chs_move_tests queen case tests: failed!" << endl;
    // }
    // test_bool = true;

    // // King move test.
    // chess::chs_piece wKing = chess::chs_piece( chess::CHS_PIECE_TYPE::KING,
    //     chess::CHS_PIECE_COLOR::WHITE );
    // move_bad = chess::chs_move( 4, 4, 6, 6 );
    // move_good = chess::chs_move( 4, 4, 5, 5 );
    // move_good2 = chess::chs_move( 4, 4, 4, 5 );
    // test_bool = test_bool && !( move_bad.is_move_valid( wKing ) );
    // test_bool = test_bool && ( move_good.is_move_valid( wKing ) );
    // test_bool = test_bool && ( move_good2.is_move_valid( wKing ) );
    // if( test_bool ){
    //     cout << "chess_chs_move_tests king case tests: passed!" << endl;
    // }else{
    //     cout << "chess_chs_move_tests king case tests: failed!" << endl;
    // }
    // test_bool = true;


}


void tests::chess_game_manip_tests(){

    // Test boolean init.
    bool test_bool = true;

    chess myGame = chess();


// ---------------------------------------------------------------------- >>>>>
//      Test clearBoard
// ---------------------------------------------------------------------- >>>>>

    // Put two test pieces on the empty board.
    chess::chs_piece myPiece( chess::CHS_PIECE_TYPE::PAWN, chess::CHS_PIECE_COLOR::WHITE );
    myGame.set_piece_at( 1, 2, myPiece );
    test_bool = test_bool && ( myGame.get_piece_at( 1, 2 ).type == chess::CHS_PIECE_TYPE::PAWN && 
        myGame.get_piece_at( 1, 2 ).color == chess::CHS_PIECE_COLOR::WHITE );
    myPiece = chess::chs_piece( chess::CHS_PIECE_TYPE::KNIGHT, chess::CHS_PIECE_COLOR::BLACK );
    myGame.set_piece_at( 5, 4, myPiece );
    test_bool = test_bool && ( myGame.get_piece_at( 5, 4 ).type == chess::CHS_PIECE_TYPE::KNIGHT && 
        myGame.get_piece_at( 5, 4 ).color == chess::CHS_PIECE_COLOR::BLACK );

    // Clear the board and check the two pieces location for empty case.
    myGame.clearBoard();
    cout << endl;
    test_bool = test_bool && ( myGame.get_piece_at( 1, 2 ).type == chess::CHS_PIECE_TYPE::NO_P && 
        myGame.get_piece_at( 1, 2 ).color == chess::CHS_PIECE_COLOR::NO_C );
    test_bool = test_bool && ( myGame.get_piece_at( 5, 4 ).type == chess::CHS_PIECE_TYPE::NO_P && 
        myGame.get_piece_at( 5, 4 ).color == chess::CHS_PIECE_COLOR::NO_C );
    
    if( test_bool ){
        cout << "chess clearBoard test: passed!" << endl;
    }else{
        cout << "chess clearBoard test: failed!" << endl;
    }

// ---------------------------------------------------------------------- <<<<<


// ---------------------------------------------------------------------- >>>>>
//      Test resetBoard
// ---------------------------------------------------------------------- >>>>>
    
    test_bool = true;
    myGame.resetBoard();
    myGame.printBoard();
    test_bool = test_bool && ( myGame.getState() == chess::CHS_STATE::ONGOING );
    test_bool = test_bool && ( myGame.getTurn_cnt() == 0 );
    test_bool = test_bool && ( myGame.getNo_change_turn_cnt() == 0 );

    unsigned int col_idx = 0;
    unsigned int row_idx = 0;
    test_bool = test_bool && ( myGame.get_piece_at( row_idx, col_idx ) == 
        chess::chs_piece( chess::CHS_PIECE_TYPE::ROOK, chess::CHS_PIECE_COLOR::WHITE ) );
    test_bool = test_bool && ( myGame.get_piece_at( row_idx, chess::BOARDWIDTH - 1 - col_idx ) == 
        chess::chs_piece( chess::CHS_PIECE_TYPE::ROOK, chess::CHS_PIECE_COLOR::WHITE ) );
    test_bool = test_bool && ( myGame.get_piece_at( chess::BOARDHEIGHT - 1 - row_idx, col_idx ) == 
        chess::chs_piece( chess::CHS_PIECE_TYPE::ROOK, chess::CHS_PIECE_COLOR::BLACK ) );
    test_bool = test_bool && ( myGame.get_piece_at( chess::BOARDHEIGHT - 1 - row_idx, chess::BOARDWIDTH - 1 - col_idx ) == 
        chess::chs_piece( chess::CHS_PIECE_TYPE::ROOK, chess::CHS_PIECE_COLOR::BLACK ) );
    col_idx = 1;
    test_bool = test_bool && ( myGame.get_piece_at( row_idx, col_idx ) == 
        chess::chs_piece( chess::CHS_PIECE_TYPE::KNIGHT, chess::CHS_PIECE_COLOR::WHITE ) );
    test_bool = test_bool && ( myGame.get_piece_at( row_idx, chess::BOARDWIDTH - 1 - col_idx ) == 
        chess::chs_piece( chess::CHS_PIECE_TYPE::KNIGHT, chess::CHS_PIECE_COLOR::WHITE ) );
    test_bool = test_bool && ( myGame.get_piece_at( chess::BOARDHEIGHT - 1 - row_idx, col_idx ) == 
        chess::chs_piece( chess::CHS_PIECE_TYPE::KNIGHT, chess::CHS_PIECE_COLOR::BLACK ) );
    test_bool = test_bool && ( myGame.get_piece_at( chess::BOARDHEIGHT - 1 - row_idx, chess::BOARDWIDTH - 1 - col_idx ) == 
        chess::chs_piece( chess::CHS_PIECE_TYPE::KNIGHT, chess::CHS_PIECE_COLOR::BLACK ) );
    col_idx = 2;
    test_bool = test_bool && ( myGame.get_piece_at( row_idx, col_idx ) == 
        chess::chs_piece( chess::CHS_PIECE_TYPE::BISHOP, chess::CHS_PIECE_COLOR::WHITE ) );
    test_bool = test_bool && ( myGame.get_piece_at( row_idx, chess::BOARDWIDTH - 1 - col_idx ) == 
        chess::chs_piece( chess::CHS_PIECE_TYPE::BISHOP, chess::CHS_PIECE_COLOR::WHITE ) );
    test_bool = test_bool && ( myGame.get_piece_at( chess::BOARDHEIGHT - 1 - row_idx, col_idx ) == 
        chess::chs_piece( chess::CHS_PIECE_TYPE::BISHOP, chess::CHS_PIECE_COLOR::BLACK ) );
    test_bool = test_bool && ( myGame.get_piece_at( chess::BOARDHEIGHT - 1 - row_idx, chess::BOARDWIDTH - 1 - col_idx ) == 
        chess::chs_piece( chess::CHS_PIECE_TYPE::BISHOP, chess::CHS_PIECE_COLOR::BLACK ) );
    col_idx = 3;
    test_bool = test_bool && ( myGame.get_piece_at( row_idx, col_idx ) == 
        chess::chs_piece( chess::CHS_PIECE_TYPE::QUEEN, chess::CHS_PIECE_COLOR::WHITE ) );
    test_bool = test_bool && ( myGame.get_piece_at( row_idx, chess::BOARDWIDTH - 1 - col_idx ) == 
        chess::chs_piece( chess::CHS_PIECE_TYPE::KING, chess::CHS_PIECE_COLOR::WHITE ) );
    test_bool = test_bool && ( myGame.get_piece_at( chess::BOARDHEIGHT - 1 - row_idx, col_idx ) == 
        chess::chs_piece( chess::CHS_PIECE_TYPE::QUEEN, chess::CHS_PIECE_COLOR::BLACK ) );
    test_bool = test_bool && ( myGame.get_piece_at( chess::BOARDHEIGHT - 1 - row_idx, chess::BOARDWIDTH - 1 - col_idx ) == 
        chess::chs_piece( chess::CHS_PIECE_TYPE::KING, chess::CHS_PIECE_COLOR::BLACK ) );

    // Compare the pawns.
    row_idx = 1;
    for( unsigned int j = 0; j < chess::BOARDWIDTH; j++ ){
        test_bool = test_bool && ( myGame.get_piece_at( row_idx, j ) ==
            chess::chs_piece( chess::CHS_PIECE_TYPE::PAWN, chess::CHS_PIECE_COLOR::WHITE ) );
        test_bool = test_bool && ( myGame.get_piece_at( chess::BOARDHEIGHT - 1 - row_idx, j ) ==
            chess::chs_piece( chess::CHS_PIECE_TYPE::PAWN, chess::CHS_PIECE_COLOR::BLACK ) );
    }

    // Compare empty spaces.
    chess::chs_piece NONE_PIECE( chess::CHS_PIECE_TYPE::NO_P, chess::CHS_PIECE_COLOR::NO_C );
    for( unsigned int i = 2; i < chess::BOARDHEIGHT - 2; i++ ){
        for( unsigned int j = 0; j < chess::BOARDWIDTH; j++ ){
            test_bool = test_bool && ( myGame.get_piece_at( i, j ) == NONE_PIECE );
        }
    }

    if( test_bool ){
        cout << "chess resetBoard test: passed!" << endl;
    }else{
        cout << "chess resetBoard test: failed!" << endl;
    }
// ---------------------------------------------------------------------- <<<<<


}




void tests::chess_move_tests(){

    chess myGame = chess();

    myGame.resetBoard();



    bool test_bool = true;


// ---------------------------------------------------------------------- >>>>>
//      Pawn Move Test
// ---------------------------------------------------------------------- >>>>>
// ---------------------------------------------------------------------- <<<<<

// ---------------------------------------------------------------------- >>>>>
//      Pawn Move Test
// ---------------------------------------------------------------------- >>>>>

    // Unstarted white pawn up 1.
    test_bool = test_bool && ( myGame.is_move_valid( 1, 2, 2, 2 ) );
    // Unstarted white pawn up 2.
    test_bool = test_bool && ( myGame.is_move_valid( 1, 2, 3, 2 ) );
    // White pawn down 1.
    test_bool = test_bool && !( myGame.is_move_valid( 1, 2, 0, 2 ) );



    if( test_bool ){
        cout << "chess::is_move_valid pawn move test: passed!" << endl;
    }else{
        cout << "chess::is_move_valid pawn move test: failed!" << endl;
    }

// ---------------------------------------------------------------------- <<<<<

}
