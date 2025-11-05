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

    bool test_bool = true;


// ---------------------------------------------------------------------- >>>>>
//      Invalid Move Tests
// ---------------------------------------------------------------------- >>>>>

    // Out of bound move.
    test_bool = test_bool && !( myGame.is_move_valid( 0, 0, 8, 0 ) );
    // Trivial move.
    test_bool = test_bool && !( myGame.is_move_valid( 0, 0, 0, 0 ) );
    // No piece at start square move.
    test_bool = test_bool && !( myGame.is_move_valid( 2, 0, 0, 0 ) );
    // Obstruction at end square move.
    test_bool = test_bool && !( myGame.is_move_valid( 0, 0, 1, 0 ) );
    // Wrong turn move.
    test_bool = test_bool && !( myGame.is_move_valid( 6, 0, 5, 0 ) );

    if( test_bool ){
        cout << "chess::is_move_valid invalid moves test: passed!" << endl;
    }else{
        cout << "chess::is_move_valid invalid moves test: failed!" << endl;
    }

    // Reset test boolean.
    test_bool = true;
// ---------------------------------------------------------------------- <<<<<


// ---------------------------------------------------------------------- >>>>>
//      Pawn Move Test
// ---------------------------------------------------------------------- >>>>>

    // Unstarted white pawn up 1.
    test_bool = test_bool && ( myGame.is_move_valid( 1, 2, 2, 2 ) );
    // Unstarted white pawn up 2.
    test_bool = test_bool && ( myGame.is_move_valid( 1, 2, 3, 2 ) );
    // Unstarted white pawn up 3.
    test_bool = test_bool && !( myGame.is_move_valid( 1, 2, 4, 2 ) );
    // White pawn down 1.
    test_bool = test_bool && !( myGame.is_move_valid( 1, 2, 0, 2 ) );
    // White pawn diagonal.
    test_bool = test_bool && !( myGame.is_move_valid( 1, 2, 2, 3 ) );

    // Set the turn to black's turn
    myGame.setTurn_cnt(1u);
    // Unstarted black pawn up 1.
    test_bool = test_bool && ( myGame.is_move_valid( 6, 2, 5, 2 ) );
    // Unstarted black pawn up 2.
    test_bool = test_bool && ( myGame.is_move_valid( 6, 2, 4, 2 ) );
    // Unstarted black pawn up 3.
    test_bool = test_bool && !( myGame.is_move_valid( 6, 2, 3, 2 ) );
    // Black pawn down 1.
    test_bool = test_bool && !( myGame.is_move_valid( 6, 2, 7, 2 ) );


    if( test_bool ){
        cout << "chess::is_move_valid pawn move test: passed!" << endl;
    }else{
        cout << "chess::is_move_valid pawn move test: failed!" << endl;
    }

    // Reset to white's move.
    myGame.setTurn_cnt(0);
    // Reset test boolean.
    test_bool = true;

// ---------------------------------------------------------------------- <<<<<


// ---------------------------------------------------------------------- >>>>>
//      Knight Move Test
// ---------------------------------------------------------------------- >>>>>

    // Basic knight moves.
    test_bool = test_bool && ( myGame.is_move_valid( 0, 1, 2, 0 ) );
    test_bool = test_bool && ( myGame.is_move_valid( 0, 1, 2, 2 ) );
    // Wrong knight move.
    test_bool = test_bool && !( myGame.is_move_valid( 0, 1, 3, 1 ) );

    // Set the turn to black's turn
    myGame.setTurn_cnt(1u);
    test_bool = test_bool && ( myGame.is_move_valid( 7, 1, 5, 0 ) );
    test_bool = test_bool && ( myGame.is_move_valid( 7, 1, 5, 2 ) );
    // Wrong knight move.
    test_bool = test_bool && !( myGame.is_move_valid( 7, 1, 4, 1 ) );

    if( test_bool ){
        cout << "chess::is_move_valid knight move test: passed!" << endl;
    }else{
        cout << "chess::is_move_valid knight move test: failed!" << endl;
    }

    // Reset to white's move.
    myGame.setTurn_cnt(0);
    // Reset test boolean.
    test_bool = true;
    
// ---------------------------------------------------------------------- <<<<<


// ---------------------------------------------------------------------- >>>>>
//      Bishop Move Test
// ---------------------------------------------------------------------- >>>>>

    chess::chs_piece newWB = chess::chs_piece(
        chess::CHS_PIECE_TYPE::BISHOP, chess::CHS_PIECE_COLOR::WHITE
    );
    myGame.set_piece_at( 3, 3, newWB );

    // Basic bishop moves.
    test_bool = test_bool && ( myGame.is_move_valid( 3, 3, 2, 2 ) );
    test_bool = test_bool && ( myGame.is_move_valid( 3, 3, 2, 4 ) );
    test_bool = test_bool && ( myGame.is_move_valid( 3, 3, 4, 2 ) );
    test_bool = test_bool && ( myGame.is_move_valid( 3, 3, 4, 4 ) );

    chess::chs_piece newBB = chess::chs_piece(
        chess::CHS_PIECE_TYPE::BISHOP, chess::CHS_PIECE_COLOR::BLACK
    );
    myGame.set_piece_at( 4, 4, newBB );

    // Set the turn to black's turn
    myGame.setTurn_cnt(1u);
    // Basic bishop moves.
    test_bool = test_bool && !( myGame.is_move_valid( 4, 4, 3, 3 ) );
    test_bool = test_bool && ( myGame.is_move_valid( 4, 4, 3, 5 ) );
    test_bool = test_bool && ( myGame.is_move_valid( 4, 4, 5, 3 ) );
    test_bool = test_bool && ( myGame.is_move_valid( 4, 4, 5, 5 ) );
    // Obstacle case.
    test_bool = test_bool && !( myGame.is_move_valid( 4, 4, 2, 2 ) );

    if( test_bool ){
        cout << "chess::is_move_valid bishop move test: passed!" << endl;
    }else{
        cout << "chess::is_move_valid bishop move test: failed!" << endl;
    }

    // Reset to white's move.
    myGame.setTurn_cnt(0);
    // Reset test boolean.
    test_bool = true;

// ---------------------------------------------------------------------- <<<<<


// ---------------------------------------------------------------------- >>>>>
//      Rook Move Test
// ---------------------------------------------------------------------- >>>>>

    // Clear the board.
    myGame.clearBoard();

    chess::chs_piece newWR = chess::chs_piece(
        chess::CHS_PIECE_TYPE::ROOK, chess::CHS_PIECE_COLOR::WHITE
    );
    myGame.set_piece_at( 3, 3, newWR );

    chess::chs_piece newBR = chess::chs_piece(
        chess::CHS_PIECE_TYPE::ROOK, chess::CHS_PIECE_COLOR::BLACK
    );
    myGame.set_piece_at( 3, 5, newBR );

    // Basic rook moves.
    test_bool = test_bool && !( myGame.is_move_valid( 3, 3, 3, 7 ) );
    test_bool = test_bool && ( myGame.is_move_valid( 3, 3, 0, 3 ) );
    test_bool = test_bool && ( myGame.is_move_valid( 3, 3, 4, 3 ) );
    test_bool = test_bool && ( myGame.is_move_valid( 3, 3, 3, 1 ) );
    test_bool = test_bool && !( myGame.is_move_valid( 3, 3, 4, 4 ) );

    // Set the turn to black's turn
    myGame.setTurn_cnt(1u);
    // Basic rook moves.
    test_bool = test_bool && !( myGame.is_move_valid( 3, 5, 3, 2 ) );
    test_bool = test_bool && ( myGame.is_move_valid( 3, 5, 3, 7 ) );
    test_bool = test_bool && ( myGame.is_move_valid( 3, 5, 1, 5 ) );
    test_bool = test_bool && ( myGame.is_move_valid( 3, 5, 6, 5 ) );
    test_bool = test_bool && !( myGame.is_move_valid( 3, 5, 2, 1 ) );

    if( test_bool ){
        cout << "chess::is_move_valid rook move test: passed!" << endl;
    }else{
        cout << "chess::is_move_valid rook move test: failed!" << endl;
    }

    // Reset to white's move.
    myGame.setTurn_cnt(0);
    // Reset test boolean.
    test_bool = true;

// ---------------------------------------------------------------------- <<<<<


// ---------------------------------------------------------------------- >>>>>
//      Queen Move Test
// ---------------------------------------------------------------------- >>>>>

    // Clear the board.
    myGame.clearBoard();

    chess::chs_piece newWQ = chess::chs_piece(
        chess::CHS_PIECE_TYPE::QUEEN, chess::CHS_PIECE_COLOR::WHITE );
    myGame.set_piece_at( 2, 2, newWQ );

    chess::chs_piece newBQ = chess::chs_piece(
        chess::CHS_PIECE_TYPE::QUEEN, chess::CHS_PIECE_COLOR::BLACK );
    myGame.set_piece_at( 5, 5, newBQ );

    chess::chs_piece newWP = chess::chs_piece(
        chess::CHS_PIECE_TYPE::PAWN, chess::CHS_PIECE_COLOR::WHITE );
    myGame.set_piece_at( 2, 5, newWP );

    // Horizontal and vertical moves.
    test_bool = test_bool && !( myGame.is_move_valid( 2, 2, 2, 6 ) );
    test_bool = test_bool && ( myGame.is_move_valid( 2, 2, 2, 0 ) );
    test_bool = test_bool && ( myGame.is_move_valid( 2, 2, 6, 2 ) );
    test_bool = test_bool && ( myGame.is_move_valid( 2, 2, 1, 2 ) );
    // Diagonal moves.
    test_bool = test_bool && !( myGame.is_move_valid( 2, 2, 6, 6 ) );
    test_bool = test_bool && ( myGame.is_move_valid( 2, 2, 0, 0 ) );
    test_bool = test_bool && ( myGame.is_move_valid( 2, 2, 3, 1 ) );
    test_bool = test_bool && ( myGame.is_move_valid( 2, 2, 0, 4 ) );

    // Set the turn to black's turn
    myGame.setTurn_cnt(1u);
    // Horizontal and vertical moves.
    test_bool = test_bool && ( myGame.is_move_valid( 5, 5, 5, 7 ) );
    test_bool = test_bool && ( myGame.is_move_valid( 5, 5, 5, 1 ) );
    test_bool = test_bool && ( myGame.is_move_valid( 5, 5, 7, 5 ) );
    test_bool = test_bool && !( myGame.is_move_valid( 5, 5, 1, 5 ) );
    // Diagonal moves.
    test_bool = test_bool && ( myGame.is_move_valid( 5, 5, 7, 7 ) );
    test_bool = test_bool && !( myGame.is_move_valid( 5, 5, 1, 1 ) );
    test_bool = test_bool && ( myGame.is_move_valid( 5, 5, 3, 7 ) );
    test_bool = test_bool && ( myGame.is_move_valid( 5, 5, 6, 4 ) );

    if( test_bool ){
        cout << "chess::is_move_valid queen move test: passed!" << endl;
    }else{
        cout << "chess::is_move_valid queen move test: failed!" << endl;
    }

    // Reset to white's move.
    myGame.setTurn_cnt(0);
    // Reset test boolean.
    test_bool = true;

// ---------------------------------------------------------------------- <<<<<


// ---------------------------------------------------------------------- >>>>>
//      King Move Test
// ---------------------------------------------------------------------- >>>>>

    // Clear the board.
    myGame.clearBoard();

    chess::chs_piece newWK = chess::chs_piece(
        chess::CHS_PIECE_TYPE::KING, chess::CHS_PIECE_COLOR::WHITE );
    myGame.set_piece_at( 3, 3, newWK );

    chess::chs_piece newBK = chess::chs_piece(
        chess::CHS_PIECE_TYPE::KING, chess::CHS_PIECE_COLOR::BLACK );
    myGame.set_piece_at( 5, 5, newBK );

    newWP = chess::chs_piece(
        chess::CHS_PIECE_TYPE::PAWN, chess::CHS_PIECE_COLOR::WHITE );
    myGame.set_piece_at( 4, 4, newWP );

    // All around.
    test_bool = test_bool && ( myGame.is_move_valid( 3, 3, 3, 4 ) );
    test_bool = test_bool && !( myGame.is_move_valid( 3, 3, 4, 4 ) );
    test_bool = test_bool && ( myGame.is_move_valid( 3, 3, 4, 3 ) );
    test_bool = test_bool && ( myGame.is_move_valid( 3, 3, 4, 2 ) );
    test_bool = test_bool && ( myGame.is_move_valid( 3, 3, 3, 2 ) );
    test_bool = test_bool && ( myGame.is_move_valid( 3, 3, 2, 2 ) );
    test_bool = test_bool && ( myGame.is_move_valid( 3, 3, 2, 3 ) );
    test_bool = test_bool && ( myGame.is_move_valid( 3, 3, 2, 4 ) );

    // All around.
    myGame.setTurn_cnt(1u);
    test_bool = test_bool && ( myGame.is_move_valid( 5, 5, 5, 6 ) );
    test_bool = test_bool && ( myGame.is_move_valid( 5, 5, 6, 6 ) );
    test_bool = test_bool && ( myGame.is_move_valid( 5, 5, 6, 5 ) );
    test_bool = test_bool && ( myGame.is_move_valid( 5, 5, 6, 4 ) );
    test_bool = test_bool && ( myGame.is_move_valid( 5, 5, 5, 4 ) );
    test_bool = test_bool && !( myGame.is_move_valid( 5, 5, 4, 4 ) );
    test_bool = test_bool && ( myGame.is_move_valid( 5, 5, 4, 5 ) );
    test_bool = test_bool && ( myGame.is_move_valid( 5, 5, 4, 6 ) );

    if( test_bool ){
        cout << "chess::is_move_valid king move test: passed!" << endl;
    }else{
        cout << "chess::is_move_valid king move test: failed!" << endl;
    }

    // Clear the board.
    myGame.clearBoard();

    myGame.set_piece_at( 0, 4, chess::chs_piece(
        chess::CHS_PIECE_TYPE::KING, chess::CHS_PIECE_COLOR::WHITE ) );
    myGame.set_piece_at( 0, 7, chess::chs_piece(
        chess::CHS_PIECE_TYPE::ROOK, chess::CHS_PIECE_COLOR::WHITE ) );
    myGame.set_piece_at( 0, 0, chess::chs_piece(
        chess::CHS_PIECE_TYPE::ROOK, chess::CHS_PIECE_COLOR::WHITE ) );
    myGame.set_piece_at( 7, 4, chess::chs_piece(
        chess::CHS_PIECE_TYPE::KING, chess::CHS_PIECE_COLOR::BLACK ) );
    myGame.set_piece_at( 7, 7, chess::chs_piece(
        chess::CHS_PIECE_TYPE::ROOK, chess::CHS_PIECE_COLOR::BLACK ) );
    myGame.set_piece_at( 7, 0, chess::chs_piece(
        chess::CHS_PIECE_TYPE::ROOK, chess::CHS_PIECE_COLOR::BLACK ) );
    
    myGame.setTurn_cnt(0);
    // Right-side white king castling.
    test_bool = test_bool && ( myGame.is_move_valid( 0, 4, 0, 6 ) );
    // Left-side white king castling.
    test_bool = test_bool && ( myGame.is_move_valid( 0, 4, 0, 2 ) );
    // Right-side white king castling with obstruction.
    myGame.set_piece_at( 0, 5, chess::chs_piece(
        chess::CHS_PIECE_TYPE::BISHOP, chess::CHS_PIECE_COLOR::WHITE ) );
    test_bool = test_bool && !( myGame.is_move_valid( 0, 4, 0, 6 ) );
    // Left-side white king castling with obstruction.
    myGame.set_piece_at( 0, 1, chess::chs_piece(
        chess::CHS_PIECE_TYPE::KNIGHT, chess::CHS_PIECE_COLOR::WHITE ) );
    test_bool = test_bool && !( myGame.is_move_valid( 0, 4, 0, 2 ) );

    myGame.setTurn_cnt(1u);
    // Right-side black king castling.
    test_bool = test_bool && ( myGame.is_move_valid( 7, 4, 7, 6 ) );
    // Left-side black king castling.
    test_bool = test_bool && ( myGame.is_move_valid( 7, 4, 7, 2 ) );
    // Right-side black king castling with obstruction.
    myGame.set_piece_at( 7, 5, chess::chs_piece(
        chess::CHS_PIECE_TYPE::BISHOP, chess::CHS_PIECE_COLOR::BLACK ) );
    test_bool = test_bool && !( myGame.is_move_valid( 7, 4, 7, 6 ) );
    // Left-side black king castling with obstruction.
    myGame.set_piece_at( 7, 1, chess::chs_piece(
        chess::CHS_PIECE_TYPE::KNIGHT, chess::CHS_PIECE_COLOR::BLACK ) );
    test_bool = test_bool && !( myGame.is_move_valid( 7, 4, 7, 2 ) );

    myGame.setTurn_cnt(0);
    // White king right-side castling with threat.
    myGame.clearBoard();
    myGame.set_piece_at( 0, 4, chess::chs_piece(
        chess::CHS_PIECE_TYPE::KING, chess::CHS_PIECE_COLOR::WHITE ) );
    myGame.set_piece_at( 0, 7, chess::chs_piece(
        chess::CHS_PIECE_TYPE::ROOK, chess::CHS_PIECE_COLOR::WHITE ) );
    test_bool = test_bool && ( myGame.is_move_valid( 0, 4, 0, 6 ) );
    myGame.set_piece_at( 2, 5, chess::chs_piece(
        chess::CHS_PIECE_TYPE::ROOK, chess::CHS_PIECE_COLOR::BLACK ) );
    test_bool = test_bool && !( myGame.is_move_valid( 0, 4, 0, 6 ) );
    
    // White king left-side castling with threat.
    myGame.set_piece_at( 0, 0, chess::chs_piece(
        chess::CHS_PIECE_TYPE::ROOK, chess::CHS_PIECE_COLOR::WHITE ) );
    test_bool = test_bool && ( myGame.is_move_valid( 0, 4, 0, 2 ) );
    myGame.set_piece_at( 2, 2, chess::chs_piece(
        chess::CHS_PIECE_TYPE::KNIGHT, chess::CHS_PIECE_COLOR::BLACK ) );
    test_bool = test_bool && !( myGame.is_move_valid( 0, 4, 0, 6 ) );
    
    myGame.setTurn_cnt(1u);
    // Black king right-side castling with threat.
    myGame.set_piece_at( 7, 4, chess::chs_piece(
        chess::CHS_PIECE_TYPE::KING, chess::CHS_PIECE_COLOR::BLACK ) );
    myGame.set_piece_at( 7, 7, chess::chs_piece(
        chess::CHS_PIECE_TYPE::ROOK, chess::CHS_PIECE_COLOR::BLACK ) );
    test_bool = test_bool && ( myGame.is_move_valid( 7, 4, 7, 6 ) );
    myGame.set_piece_at( 5, 6, chess::chs_piece(
        chess::CHS_PIECE_TYPE::ROOK, chess::CHS_PIECE_COLOR::WHITE ) );
    test_bool = test_bool && !( myGame.is_move_valid( 7, 4, 7, 6 ) );

    // Black king left-side castling with threat.
    myGame.set_piece_at( 7, 0, chess::chs_piece(
        chess::CHS_PIECE_TYPE::ROOK, chess::CHS_PIECE_COLOR::BLACK ) );
    test_bool = test_bool && ( myGame.is_move_valid( 7, 4, 7, 2 ) );
    myGame.set_piece_at( 5, 2, chess::chs_piece(
        chess::CHS_PIECE_TYPE::KNIGHT, chess::CHS_PIECE_COLOR::WHITE ) );
    test_bool = test_bool && !( myGame.is_move_valid( 7, 4, 7, 2 ) );

    if( test_bool ){
        cout << "chess::is_move_valid king castling test: passed!" << endl;
    }else{
        cout << "chess::is_move_valid king castling test: failed!" << endl;
    }

// ---------------------------------------------------------------------- <<<<<


// ---------------------------------------------------------------------- >>>>>
//      get_all_valid_atk_sq Tests
// ---------------------------------------------------------------------- >>>>>

    test_bool = true;   
    bool tmp_bool = false;
    myGame.resetBoard();

    vector< pair<int,int> > valid_mov_vec = myGame.get_all_valid_move_sq( 0, 1 );
    tmp_bool = false;
    for( pair<int,int> mov_z : valid_mov_vec )
        {tmp_bool = tmp_bool || mov_z == pair<int,int>(2,0);}
    test_bool = test_bool && tmp_bool;
    tmp_bool = false;
    for( pair<int,int> mov_z : valid_mov_vec )
        {tmp_bool = tmp_bool || mov_z == pair<int,int>(2,2);}
    test_bool = test_bool && tmp_bool;

    // Pawn possible moves before and after first move.
    valid_mov_vec = myGame.get_all_valid_move_sq( 1, 2 );
    test_bool = valid_mov_vec.size() == 2;
    myGame.play( 1, 2, 2, 2 );
    myGame.play( 6, 6, 5, 6 );
    valid_mov_vec = myGame.get_all_valid_move_sq( 2, 2 );
    test_bool = valid_mov_vec.size() == 1;


    if( test_bool ){
        cout << "chess::get_all_valid_move_sq test: passed!" << endl;
    }else{
        cout << "chess::get_all_valid_move_sq test: failed!" << endl;
    }
    
// ---------------------------------------------------------------------- <<<<<

// ---------------------------------------------------------------------- >>>>>
//      get_all_valid_atk_sq Tests Part 2
// ---------------------------------------------------------------------- >>>>>

    // Castle possible moves with castling.
    test_bool = true;   
    myGame.clearBoard();

    myGame.set_piece_at( 0, 4, chess::chs_piece(
        chess::CHS_PIECE_TYPE::KING, chess::CHS_PIECE_COLOR::WHITE ) );
    myGame.set_piece_at( 0, 7, chess::chs_piece(
        chess::CHS_PIECE_TYPE::ROOK, chess::CHS_PIECE_COLOR::WHITE ) );
    myGame.set_piece_at( 0, 0, chess::chs_piece(
        chess::CHS_PIECE_TYPE::ROOK, chess::CHS_PIECE_COLOR::WHITE ) );
    myGame.set_piece_at( chess::BOARDHEIGHT - 1, 4, chess::chs_piece(
        chess::CHS_PIECE_TYPE::KING, chess::CHS_PIECE_COLOR::BLACK ) );
    myGame.set_piece_at( chess::BOARDHEIGHT - 1, 7, chess::chs_piece(
        chess::CHS_PIECE_TYPE::ROOK, chess::CHS_PIECE_COLOR::BLACK ) );
    myGame.set_piece_at( chess::BOARDHEIGHT - 1, 0, chess::chs_piece(
        chess::CHS_PIECE_TYPE::ROOK, chess::CHS_PIECE_COLOR::BLACK ) );

    // White castling move possibility check.
    valid_mov_vec = myGame.get_all_valid_move_sq( 0, 4 );
    test_bool = test_bool && ( valid_mov_vec.size() == 7 );
    tmp_bool = false;
    for( pair<int,int> mov_z : valid_mov_vec )
        {tmp_bool = tmp_bool || mov_z == pair<int,int>(0,6);}
    test_bool = test_bool && tmp_bool;
    tmp_bool = false;
    for( pair<int,int> mov_z : valid_mov_vec )
        {tmp_bool = tmp_bool || mov_z == pair<int,int>(0,2);}
    test_bool = test_bool && tmp_bool;

    // Black castling move possibility check.
    myGame.setTurn_cnt(1);
    valid_mov_vec = myGame.get_all_valid_move_sq( chess::BOARDHEIGHT - 1, 4 );
    test_bool = test_bool && ( valid_mov_vec.size() == 7 );
    tmp_bool = false;
    for( pair<int,int> mov_z : valid_mov_vec )
        {tmp_bool = tmp_bool || mov_z == pair<int,int>( chess::BOARDHEIGHT - 1, 6 );}
    test_bool = test_bool && tmp_bool;
    tmp_bool = false;
    for( pair<int,int> mov_z : valid_mov_vec )
        {tmp_bool = tmp_bool || mov_z == pair<int,int>( chess::BOARDHEIGHT - 1, 2 );}
    test_bool = test_bool && tmp_bool;

    if( test_bool ){
        cout << "chess::get_all_valid_move_sq castling case test: passed!" << endl;
    }else{
        cout << "chess::get_all_valid_move_sq castling case test: failed!" << endl;
    }

// ---------------------------------------------------------------------- <<<<<

}



void tests::chess_atk_check_tests(){


    chess myGame;

    bool test_bool = true;

    // Obtain the attack lists from a fresh game start.
    myGame.resetBoard();
    myGame.upd_atk_lists();
    auto tmp_W = myGame.getAtk_list_by_W();
    auto tmp_B = myGame.getAtk_list_by_B();

    // Create vector of expected white attack square count on each square.
    vector<int> expected_W_atk_sq = { 
        0, 1, 1, 1, 1, 1, 1, 0, 
        1, 1, 1, 4, 4, 1, 1, 1,
        2, 2, 3, 2, 2, 3, 2, 2 };
    expected_W_atk_sq.reserve(64);
    for( unsigned int z = 0; z < 40; z++ ){
        expected_W_atk_sq.push_back(0);
    }

    // Create vector of expected black attack square count on each square.
    vector<int> expected_B_atk_sq;
    expected_B_atk_sq.reserve( 64 );
    for( unsigned int z = 0; z < 40; z++ ){
        expected_B_atk_sq.push_back(0);
    }
    for( unsigned int z = 0; z < 24; z++ ){
        expected_B_atk_sq.push_back( expected_W_atk_sq.at( 23 - z ) );
    }

    // Compare expected results with found results.
    for( unsigned int z = 0; z < tmp_W.size(); z++ ){
        test_bool = test_bool && ( tmp_W[z].size() == expected_W_atk_sq[z] );
        test_bool = test_bool && ( tmp_B[z].size() == expected_B_atk_sq[z] );
    }

    if( test_bool ){
        cout << "upd_atk_lists test passed!" << endl;
    }else{
        cout << "upd_atk_lists test failed!" << endl;
    }


// ---------------------------------------------------------------------- >>>>>
//      is_atk_valid tests
// ---------------------------------------------------------------------- >>>>>

    test_bool = true;

    // Pawn test.
    myGame.clearBoard();
    myGame.setTurn_cnt(0);
    myGame.set_piece_at( 2, 3, chess::chs_piece( chess::CHS_PIECE_TYPE::PAWN, chess::CHS_PIECE_COLOR::WHITE ) );
    myGame.set_piece_at( 3, 2, chess::chs_piece( chess::CHS_PIECE_TYPE::PAWN, chess::CHS_PIECE_COLOR::BLACK ) );
    test_bool = test_bool && ( myGame.is_atk_valid( 2, 3, 3, 2 ) );
    test_bool = test_bool && !( myGame.is_atk_valid( 2, 3, 3, 4 ) );
    test_bool = test_bool && !( myGame.is_atk_valid( 3, 2, 2, 3 ) );
    myGame.setTurn_cnt(1u);
    test_bool = test_bool && ( myGame.is_atk_valid( 3, 2, 2, 3 ) );
    test_bool = test_bool && !( myGame.is_atk_valid( 3, 2, 2, 4 ) );

    // Knight test.
    myGame.clearBoard();
    myGame.setTurn_cnt(0);
    myGame.set_piece_at( 2, 3, chess::chs_piece( chess::CHS_PIECE_TYPE::KNIGHT, chess::CHS_PIECE_COLOR::WHITE ) );
    myGame.set_piece_at( 4, 2, chess::chs_piece( chess::CHS_PIECE_TYPE::KNIGHT, chess::CHS_PIECE_COLOR::BLACK ) );
    test_bool = test_bool && ( myGame.is_atk_valid( 2, 3, 4, 2 ) );
    test_bool = test_bool && !( myGame.is_atk_valid( 2, 3, 1, 5 ) );
    myGame.setTurn_cnt(1u);
    test_bool = test_bool && ( myGame.is_atk_valid( 4, 2, 2, 3 ) );
    test_bool = test_bool && !( myGame.is_atk_valid( 4, 2, 6, 1 ) );

    // Bishop test.
    myGame.clearBoard();
    myGame.setTurn_cnt(0);
    myGame.set_piece_at( 2, 3, chess::chs_piece( chess::CHS_PIECE_TYPE::BISHOP, chess::CHS_PIECE_COLOR::WHITE ) );
    myGame.set_piece_at( 4, 5, chess::chs_piece( chess::CHS_PIECE_TYPE::BISHOP, chess::CHS_PIECE_COLOR::BLACK ) );
    test_bool = test_bool && ( myGame.is_atk_valid( 2, 3, 4, 5 ) );
    test_bool = test_bool && !( myGame.is_atk_valid( 2, 3, 1, 2 ) );
    myGame.setTurn_cnt(1u);
    test_bool = test_bool && ( myGame.is_atk_valid( 4, 5, 2, 3 ) );
    test_bool = test_bool && !( myGame.is_atk_valid( 4, 5, 6, 3 ) );

    // Rook test.
    myGame.clearBoard();
    myGame.setTurn_cnt(0);
    myGame.set_piece_at( 4, 1, chess::chs_piece( chess::CHS_PIECE_TYPE::ROOK, chess::CHS_PIECE_COLOR::WHITE ) );
    myGame.set_piece_at( 1, 1, chess::chs_piece( chess::CHS_PIECE_TYPE::ROOK, chess::CHS_PIECE_COLOR::BLACK ) );
    myGame.set_piece_at( 4, 5, chess::chs_piece( chess::CHS_PIECE_TYPE::ROOK, chess::CHS_PIECE_COLOR::BLACK ) );
    test_bool = test_bool && ( myGame.is_atk_valid( 4, 1, 1, 1 ) );
    test_bool = test_bool && ( myGame.is_atk_valid( 4, 1, 4, 5 ) );
    test_bool = test_bool && !( myGame.is_atk_valid( 4, 1, 4, 4 ) );
    myGame.setTurn_cnt(1u);
    test_bool = test_bool && ( myGame.is_atk_valid( 1, 1, 4, 1 ) );
    test_bool = test_bool && ( myGame.is_atk_valid( 4, 5, 4, 1 ) );
    test_bool = test_bool && !( myGame.is_atk_valid( 1, 1, 3, 1 ) );
    test_bool = test_bool && !( myGame.is_atk_valid( 4, 5, 7, 5 ) );

    // Queen test.
    myGame.clearBoard();
    myGame.setTurn_cnt(0);
    myGame.set_piece_at( 4, 3, chess::chs_piece( chess::CHS_PIECE_TYPE::QUEEN, chess::CHS_PIECE_COLOR::WHITE ) );
    myGame.set_piece_at( 4, 7, chess::chs_piece( chess::CHS_PIECE_TYPE::PAWN, chess::CHS_PIECE_COLOR::BLACK ) );
    myGame.set_piece_at( 2, 4, chess::chs_piece( chess::CHS_PIECE_TYPE::KNIGHT, chess::CHS_PIECE_COLOR::BLACK ) );
    myGame.set_piece_at( 0, 7, chess::chs_piece( chess::CHS_PIECE_TYPE::ROOK, chess::CHS_PIECE_COLOR::BLACK ) );
    test_bool = test_bool && ( myGame.is_atk_valid( 4, 3, 4, 7 ) );
    test_bool = test_bool && !( myGame.is_atk_valid( 4, 3, 2, 4 ) );
    test_bool = test_bool && ( myGame.is_atk_valid( 4, 3, 0, 7 ) );


    // White King test.
    myGame.clearBoard();
    myGame.setTurn_cnt(0);
    myGame.set_piece_at( 4, 3, chess::chs_piece( chess::CHS_PIECE_TYPE::KING, chess::CHS_PIECE_COLOR::WHITE ) );
    myGame.set_piece_at( 3, 3, chess::chs_piece( chess::CHS_PIECE_TYPE::PAWN, chess::CHS_PIECE_COLOR::BLACK ) );
    myGame.set_piece_at( 5, 4, chess::chs_piece( chess::CHS_PIECE_TYPE::KNIGHT, chess::CHS_PIECE_COLOR::BLACK ) );
    test_bool = test_bool && !( myGame.is_atk_valid( 4, 3, 3, 3 ) );
    test_bool = test_bool && ( myGame.is_atk_valid( 4, 3, 5, 4 ) );
    // Black King test.
    myGame.clearBoard();
    myGame.setTurn_cnt(1u);
    myGame.set_piece_at( 4, 3, chess::chs_piece( chess::CHS_PIECE_TYPE::KING, chess::CHS_PIECE_COLOR::BLACK ) );
    myGame.set_piece_at( 3, 3, chess::chs_piece( chess::CHS_PIECE_TYPE::PAWN, chess::CHS_PIECE_COLOR::WHITE ) );
    myGame.set_piece_at( 5, 4, chess::chs_piece( chess::CHS_PIECE_TYPE::KNIGHT, chess::CHS_PIECE_COLOR::WHITE ) );
    test_bool = test_bool && !( myGame.is_atk_valid( 4, 3, 3, 3 ) );
    test_bool = test_bool && ( myGame.is_atk_valid( 4, 3, 5, 4 ) );


    if( test_bool ){
        cout << "is_atk_valid test passed!" << endl;
    }else{
        cout << "is_atk_valid test failed!" << endl;
    }

// ---------------------------------------------------------------------- <<<<<


// ---------------------------------------------------------------------- >>>>>
//      get_all_valid_atk_sq tests
// ---------------------------------------------------------------------- >>>>>

    test_bool = true;
    // Pawn test.
    myGame.clearBoard();
    myGame.setTurn_cnt(0);

    vector<pair<int,int>> valid_atk_vec;

    myGame.set_piece_at( 2, 3, 
        chess::chs_piece( chess::CHS_PIECE_TYPE::KNIGHT, chess::CHS_PIECE_COLOR::WHITE ) );
    myGame.set_piece_at( 4, 4, 
        chess::chs_piece( chess::CHS_PIECE_TYPE::PAWN, chess::CHS_PIECE_COLOR::BLACK ) );
    valid_atk_vec = myGame.get_all_valid_atk_sq(2,3);
    test_bool = test_bool && ( valid_atk_vec.size() == 1 );
    test_bool = test_bool && ( valid_atk_vec.at(0).first == 4 && valid_atk_vec.at(0).second == 4 );
    
    myGame.set_piece_at( 4, 5, 
        chess::chs_piece( chess::CHS_PIECE_TYPE::KING, chess::CHS_PIECE_COLOR::WHITE ) );
    valid_atk_vec = myGame.get_all_valid_atk_sq(4,5);
    test_bool = test_bool && ( valid_atk_vec.size() == 1 );
    test_bool = test_bool && ( valid_atk_vec.at(0).first == 4 && valid_atk_vec.at(0).second == 4 );

    myGame.set_piece_at( 0, 4, 
        chess::chs_piece( chess::CHS_PIECE_TYPE::ROOK, chess::CHS_PIECE_COLOR::BLACK ) );
    valid_atk_vec = myGame.get_all_valid_atk_sq(2,3);
    test_bool = test_bool && ( valid_atk_vec.size() == 2 );
    test_bool = test_bool && ( valid_atk_vec.at(1).first == 0 && valid_atk_vec.at(1).second == 4 );
    
    valid_atk_vec = myGame.get_all_valid_atk_sq(4,5);
    test_bool = test_bool && ( valid_atk_vec.size() == 0 );


    myGame.setTurn_cnt(1);
    myGame.set_piece_at( 3, 4, 
        chess::chs_piece( chess::CHS_PIECE_TYPE::BISHOP, chess::CHS_PIECE_COLOR::BLACK ) );
    valid_atk_vec = myGame.get_all_valid_atk_sq(3,4);
    test_bool = test_bool && ( valid_atk_vec.size() == 2 );
    test_bool = test_bool && ( valid_atk_vec.at(0).first == 4 && valid_atk_vec.at(0).second == 5 );
    test_bool = test_bool && ( valid_atk_vec.at(1).first == 2 && valid_atk_vec.at(1).second == 3 );
    
    myGame.setTurn_cnt(0);
    valid_atk_vec = myGame.get_all_valid_atk_sq(4,5);
    test_bool = test_bool && ( valid_atk_vec.size() == 1 );
    test_bool = test_bool && ( valid_atk_vec.at(0).first == 4 && valid_atk_vec.at(0).second == 4 );

    if( test_bool ){
        cout << "get_all_valid_atk_sq test passed!" << endl;
    }else{
        cout << "get_all_valid_atk_sq test failed!" << endl;
    }


// ---------------------------------------------------------------------- <<<<<


// ---------------------------------------------------------------------- >>>>>
//      get_all_atk_sq_spec white check tests
// ---------------------------------------------------------------------- >>>>>

    test_bool = true;
    myGame.clearBoard();
    myGame.setTurn_cnt(0);

    myGame.set_piece_at( 3, 4, chess::chs_piece(
         chess::CHS_PIECE_TYPE::KING, chess::CHS_PIECE_COLOR::WHITE ) );
    myGame.set_piece_at( 6, 4, chess::chs_piece(
         chess::CHS_PIECE_TYPE::ROOK, chess::CHS_PIECE_COLOR::BLACK ) );
    myGame.set_piece_at( 2, 3, chess::chs_piece(
         chess::CHS_PIECE_TYPE::BISHOP, chess::CHS_PIECE_COLOR::BLACK ) );
    myGame.set_piece_at( 6, 7, chess::chs_piece(
         chess::CHS_PIECE_TYPE::QUEEN, chess::CHS_PIECE_COLOR::BLACK ) );
    
    // Check attacked square by the rook.
    vector< pair<int,int> > all_atk_sq_vec = myGame.get_all_atk_sq( 6, 4 );
    vector< pair<int,int> > all_atk_sq_sepc_vec = myGame.get_all_atk_sq_spec( 6, 4 );
    test_bool = test_bool && ( all_atk_sq_vec.size() == 11 );
    test_bool = test_bool && ( all_atk_sq_sepc_vec.size() == 14 );
    // Check attacked square by the bishop.
    all_atk_sq_vec = myGame.get_all_atk_sq( 2, 3 );
    all_atk_sq_sepc_vec = myGame.get_all_atk_sq_spec( 2, 3 );
    test_bool = test_bool && ( all_atk_sq_vec.size() == 8 );
    test_bool = test_bool && ( all_atk_sq_sepc_vec.size() == 11 );
    // Check attacked square by the queen.
    all_atk_sq_vec = myGame.get_all_atk_sq( 6, 7 );
    all_atk_sq_sepc_vec = myGame.get_all_atk_sq_spec( 6, 7 );
    test_bool = test_bool && ( all_atk_sq_vec.size() == 14 );
    test_bool = test_bool && ( all_atk_sq_sepc_vec.size() == 15 );

    

    // Make sure the game's attack list consistent.
    auto b_atk_list = myGame.getAtk_list_by_B();
    vector<int> tmp = b_atk_list[ chess::sub2ind( 3, 4 ) ];
    test_bool = test_bool && ( tmp.size() == 3 && tmp[0] == 19 && tmp[1] == 52 && tmp[2] == 55 );
    tmp = b_atk_list[ chess::sub2ind( 2, 4 ) ];
    test_bool = test_bool && ( tmp.size() == 1 && tmp[0] == 52 );
    tmp = b_atk_list[ chess::sub2ind( 2, 3 ) ];
    test_bool = test_bool && ( tmp.size() == 1 && tmp[0] == 55 );
    tmp = b_atk_list[ chess::sub2ind( 4, 5 ) ];
    test_bool = test_bool && ( tmp.size() == 2 && tmp[0] == 19, tmp[1] == 55 );


    // See if the king can move towards a square hidden from attack by itself.
    test_bool = test_bool && !( myGame.ply( 3, 4, 2, 4 ) );
    // See if the king can attack towards a square hidden from attack by itself.
    test_bool = test_bool && !( myGame.ply( 3, 4, 2, 3 ) );

    if( test_bool ){
        cout << "all_atk_sq_sepc_vec white check case test passed!" << endl;
    }else{
        cout << "all_atk_sq_sepc_vec white check case test failed!" << endl;
    }

// ---------------------------------------------------------------------- <<<<<


// ---------------------------------------------------------------------- >>>>>
//      get_all_atk_sq_spec black check tests
// ---------------------------------------------------------------------- >>>>>

    test_bool = true;
    myGame.clearBoard();
    myGame.setTurn_cnt(1);

    myGame.set_piece_at( 3, 4, chess::chs_piece(
         chess::CHS_PIECE_TYPE::KING, chess::CHS_PIECE_COLOR::BLACK ) );
    myGame.set_piece_at( 6, 4, chess::chs_piece(
         chess::CHS_PIECE_TYPE::ROOK, chess::CHS_PIECE_COLOR::WHITE ) );
    myGame.set_piece_at( 2, 3, chess::chs_piece(
         chess::CHS_PIECE_TYPE::BISHOP, chess::CHS_PIECE_COLOR::WHITE ) );
    myGame.set_piece_at( 6, 7, chess::chs_piece(
         chess::CHS_PIECE_TYPE::QUEEN, chess::CHS_PIECE_COLOR::WHITE ) );

    // Check attacked square by the rook.
    all_atk_sq_vec = myGame.get_all_atk_sq( 6, 4 );
    all_atk_sq_sepc_vec = myGame.get_all_atk_sq_spec( 6, 4 );
    test_bool = test_bool && ( all_atk_sq_vec.size() == 11 );
    test_bool = test_bool && ( all_atk_sq_sepc_vec.size() == 14 );
    // Check attacked square by the bishop.
    all_atk_sq_vec = myGame.get_all_atk_sq( 2, 3 );
    all_atk_sq_sepc_vec = myGame.get_all_atk_sq_spec( 2, 3 );
    test_bool = test_bool && ( all_atk_sq_vec.size() == 8 );
    test_bool = test_bool && ( all_atk_sq_sepc_vec.size() == 11 );
    // Check attacked square by the queen.
    all_atk_sq_vec = myGame.get_all_atk_sq( 6, 7 );
    all_atk_sq_sepc_vec = myGame.get_all_atk_sq_spec( 6, 7 );
    test_bool = test_bool && ( all_atk_sq_vec.size() == 14 );
    test_bool = test_bool && ( all_atk_sq_sepc_vec.size() == 15 );
    
    // Make sure the game's attack list consistent.
    auto w_atk_list = myGame.getAtk_list_by_W();
    tmp = w_atk_list[ chess::sub2ind( 3, 4 ) ];
    test_bool = test_bool && ( tmp.size() == 3 && tmp[0] == 19 && tmp[1] == 52 && tmp[2] == 55 );
    tmp = w_atk_list[ chess::sub2ind( 2, 4 ) ];
    test_bool = test_bool && ( tmp.size() == 1 && tmp[0] == 52 );
    tmp = w_atk_list[ chess::sub2ind( 2, 3 ) ];
    test_bool = test_bool && ( tmp.size() == 1 && tmp[0] == 55 );
    tmp = w_atk_list[ chess::sub2ind( 4, 5 ) ];
    test_bool = test_bool && ( tmp.size() == 2 && tmp[0] == 19, tmp[1] == 55 );
    
    // See if the king can move towards a square hidden from attack by itself.
    test_bool = test_bool && !( myGame.ply( 3, 4, 2, 4 ) );
    // See if the king can attack towards a square hidden from attack by itself.
    test_bool = test_bool && !( myGame.ply( 3, 4, 2, 3 ) );

    if( test_bool ){
        cout << "all_atk_sq_sepc_vec black check case test passed!" << endl;
    }else{
        cout << "all_atk_sq_sepc_vec black check case test failed!" << endl;
    }

// ---------------------------------------------------------------------- <<<<<

}



void tests::chess_play_tests(){


    bool test_bool = true;

    chess myGame;

// ---------------------------------------------------------------------- >>>>>
//      Pawn Test
// ---------------------------------------------------------------------- >>>>>
    
    test_bool = true;
    myGame.clearBoard();
    myGame.setTurn_cnt(0);

    chess::chs_piece WP = chess::chs_piece( chess::CHS_PIECE_TYPE::PAWN, 
        chess::CHS_PIECE_COLOR::WHITE );
    chess::chs_piece BP = chess::chs_piece( chess::CHS_PIECE_TYPE::PAWN, 
        chess::CHS_PIECE_COLOR::BLACK );

    myGame.set_piece_at( 2, 3, WP );
    myGame.set_piece_at( 6, 4, BP );

    // White move fwd by 1.
    test_bool = test_bool && myGame.play( 2, 3, 3, 3 );
    test_bool = test_bool && myGame.is_sq_empty( 2, 3 );
    test_bool = test_bool && ( myGame.get_piece_at( 3, 3 ) == WP );
    
    // Black move fwd by 2.
    test_bool = test_bool && myGame.play( 6, 4, 4, 4 );
    test_bool = test_bool && myGame.is_sq_empty( 6, 4 );
    test_bool = test_bool && ( myGame.get_piece_at( 4, 4 ) == BP );
    // Attempt to push white pawn forward by 2 despite having moved already.
    test_bool = test_bool && !myGame.play( 3, 3, 5, 3 );
    
    // White pawn takes black pawn.
    test_bool = test_bool && myGame.play( 3, 3, 4, 4 );
    test_bool = test_bool && myGame.is_sq_empty( 3, 3 );
    test_bool = test_bool && ( myGame.get_piece_at( 4, 4 ) == WP );

    if( test_bool ){
        cout << "Pawn play test passed!" << endl;
    }else{
        cout << "Pawn play test failed!" << endl;
    }

// ---------------------------------------------------------------------- <<<<<


// ---------------------------------------------------------------------- >>>>>
//      Knight Test
// ---------------------------------------------------------------------- >>>>>

    test_bool = true;
    myGame.clearBoard();
    myGame.setTurn_cnt(0);

    chess::chs_piece WK = chess::chs_piece( chess::CHS_PIECE_TYPE::KNIGHT, 
        chess::CHS_PIECE_COLOR::WHITE );
    chess::chs_piece BK = chess::chs_piece( chess::CHS_PIECE_TYPE::KNIGHT, 
        chess::CHS_PIECE_COLOR::BLACK );
    
    myGame.set_piece_at( 3, 3, WK );
    myGame.set_piece_at( 4, 4, BK );
    
    // White knight moves south east.
    test_bool = test_bool && myGame.play( 3, 3, 2, 5 );
    test_bool = test_bool && myGame.is_sq_empty( 3, 3 );
    test_bool = test_bool && ( myGame.get_piece_at( 2, 5 ) == WK );
    
    
    // Black knight takes white knight.
    test_bool = test_bool && myGame.play( 4, 4, 2, 5 );
    test_bool = test_bool && myGame.is_sq_empty( 4, 4 );
    test_bool = test_bool && ( myGame.get_piece_at( 2, 5 ) == BK );
    

    if( test_bool ){
        cout << "Knight play test passed!" << endl;
    }else{
        cout << "Knight play test failed!" << endl;
    }

// ---------------------------------------------------------------------- <<<<<



// ---------------------------------------------------------------------- >>>>>
//      King Castling Test
// ---------------------------------------------------------------------- >>>>>
    
    test_bool = true;
    myGame.clearBoard();
    myGame.setTurn_cnt(0);

    chess::chs_piece WKG = chess::chs_piece( chess::CHS_PIECE_TYPE::KING, 
        chess::CHS_PIECE_COLOR::WHITE );
    chess::chs_piece WR = chess::chs_piece( chess::CHS_PIECE_TYPE::ROOK, 
        chess::CHS_PIECE_COLOR::WHITE );
    chess::chs_piece BR = chess::chs_piece( chess::CHS_PIECE_TYPE::ROOK, 
        chess::CHS_PIECE_COLOR::BLACK );
    

    myGame.set_piece_at( 0, 4, WKG );
    myGame.set_piece_at( 0, 7, WR );
    // Put knight that only threatens the rook.
    myGame.set_piece_at( 1, 5, BK );
    // Put rook that threatens the castling path.
    myGame.set_piece_at( 1, 6, BR );
    
    // Attempt castling when path is threatened.
    test_bool = test_bool && !myGame.play( 0, 4, 0, 6 );
    
    // Attemp castling without the black rook.
    myGame.clearSquare( 1, 6 );
    test_bool = test_bool && myGame.play( 0, 4, 0, 6 );
    test_bool = test_bool && myGame.is_sq_empty( 0, 4 );
    test_bool = test_bool && myGame.is_sq_empty( 0, 7 );
    test_bool = test_bool && ( myGame.get_piece_at( 0, 5 ) == WR );
    test_bool = test_bool && ( myGame.get_piece_at( 0, 6 ) == WKG );
    

    if( test_bool ){
        cout << "King castling play test passed!" << endl;
    }else{
        cout << "King castling play test failed!" << endl;
    }

// ---------------------------------------------------------------------- <<<<<

}



void tests::chess_promo_tests(){

    chess myGame;
    bool test_bool = true;


// ---------------------------------------------------------------------- >>>>>
//      Standard Promotion Scenario
// ---------------------------------------------------------------------- >>>>>
    
    test_bool = true;
    myGame.clearBoard();
    myGame.setTurn_cnt(0);

    chess::chs_piece WP = chess::chs_piece( chess::CHS_PIECE_TYPE::PAWN, chess::CHS_PIECE_COLOR::WHITE );
    chess::chs_piece BK = chess::chs_piece( chess::CHS_PIECE_TYPE::KNIGHT, chess::CHS_PIECE_COLOR::BLACK );

    myGame.set_piece_at( 6, 2, WP );
    myGame.set_piece_at( 3, 3, BK );

    // Check promo lock is false before going for the promotion move.
    test_bool = test_bool && !myGame.getPromo_lock();
    // Push the white pawn to the last row.
    test_bool = test_bool && myGame.play( 6, 2, 7, 2 );
    // Check promo lock is true after pawn reached promotion state.
    test_bool = test_bool && myGame.getPromo_lock();
    // Attempt to play the black knight before the promotion is completed.
    test_bool = test_bool && !myGame.play( 3, 3, 2, 5 );

    // Promote the pawn to a knight.
    myGame.promote( 2, chess::CHS_PIECE_TYPE::KNIGHT );
    // Check if the pawn is correctly promoted.
    test_bool = test_bool && ( myGame.get_piece_at( 7, 2 ).type == chess::CHS_PIECE_TYPE::KNIGHT &&
        myGame.get_piece_at( 7, 2 ).color == chess::CHS_PIECE_COLOR::WHITE );
    // Attempt to play the black knight after the promotion is completed.
    test_bool = test_bool && myGame.play( 3, 3, 2, 5 );
    // Attempt to play the pawn turned knight using a knight jump.
    test_bool = test_bool && myGame.play( 7, 2, 5, 3 );

    myGame.printBoard();

    if( test_bool ){
        cout << "Pawn standard promotion test: passed!" << endl;
    }else{
        cout << "Pawn standard promotion test: failed!" << endl;
    }

// ---------------------------------------------------------------------- <<<<<


}



void tests::chess_en_pass_tests(){

    bool test_bool = true;
    chess myGame;

    
    chess::chs_piece WP = chess::chs_piece( chess::CHS_PIECE_TYPE::PAWN, chess::CHS_PIECE_COLOR::WHITE );
    chess::chs_piece BP = chess::chs_piece( chess::CHS_PIECE_TYPE::PAWN, chess::CHS_PIECE_COLOR::BLACK );


// ---------------------------------------------------------------------- >>>>>
//      Standard En-Passant Scenario (BLACK take WHITE)
// ---------------------------------------------------------------------- >>>>>

    myGame.clearBoard();
    myGame.setTurn_cnt(0);

    myGame.set_piece_at( 1, 1, WP );
    myGame.set_piece_at( 3, 2, BP );

    test_bool = test_bool && myGame.play( 1, 1, 3, 1 );
    test_bool = test_bool && myGame.getEn_pass_flag();
    auto atk_list_by_B = myGame.getAtk_list_by_B();
    test_bool = test_bool && (atk_list_by_B[25].at(0) == 26 );
    test_bool = test_bool && myGame.play( 3, 2, 2, 1 );

    test_bool = test_bool && ( myGame.get_piece_at( 2, 1 ) == BP );
    test_bool = test_bool && ( myGame.is_sq_empty( 3, 1 ) );
    test_bool = test_bool && ( myGame.is_sq_empty( 3, 2 ) );

    if( test_bool ){
        cout << "En-passant standard test (BLACK take WHITE): passed!" << endl;
    }else{
        cout << "En-passant standard test (BLACK take WHITE): failed!" << endl;
    }

// ---------------------------------------------------------------------- <<<<<


// ---------------------------------------------------------------------- >>>>>
//      En-Passant Expiration Scenario 
// ---------------------------------------------------------------------- >>>>>

    myGame.clearBoard();
    myGame.setTurn_cnt(0);

    myGame.set_piece_at( 1, 1, WP );
    myGame.set_piece_at( 3, 2, BP );
    myGame.set_piece_at( 1, 6, WP );
    myGame.set_piece_at( 6, 6, BP );

    // Purposely give black en-passant opportunity.
    test_bool = test_bool && myGame.play( 1, 1, 3, 1 );
    test_bool = test_bool && myGame.getEn_pass_flag();
    atk_list_by_B = myGame.getAtk_list_by_B();
    test_bool = test_bool && (atk_list_by_B[25].at(0) == 26 );
    // Black purposely miss en-passant opportunity.
    test_bool = test_bool && myGame.play( 6, 6, 5, 6 );
    test_bool = test_bool && !myGame.getEn_pass_flag();
    atk_list_by_B = myGame.getAtk_list_by_B();
    test_bool = test_bool && ( atk_list_by_B[25].empty() );
    test_bool = test_bool && myGame.play( 1, 6, 2, 6 );
    // Attempt the en-passant late.
    test_bool = test_bool && !myGame.play( 3, 2, 2, 1 );

    if( test_bool ){
        cout << "En-passant expiration test: passed!" << endl;
    }else{
        cout << "En-passant expiration test: failed!" << endl;
    }
    
// ---------------------------------------------------------------------- <<<<<


// ---------------------------------------------------------------------- >>>>>
//      Standard En-Passant Scenario (WHITE take BLACK)
// ---------------------------------------------------------------------- >>>>>

    myGame.clearBoard();
    myGame.setTurn_cnt(1);

    myGame.set_piece_at( 6, 1, BP );
    myGame.set_piece_at( 4, 2, WP );
    
    test_bool = test_bool && myGame.play( 6, 1, 4, 1 );
    test_bool = test_bool && myGame.getEn_pass_flag();
    auto atk_list_by_W = myGame.getAtk_list_by_W();
    test_bool = test_bool && (atk_list_by_W[33].at(0) == 34 );
    test_bool = test_bool && myGame.play( 4, 2, 5, 1 );

    test_bool = test_bool && ( myGame.get_piece_at( 5, 1 ) == WP );
    test_bool = test_bool && ( myGame.is_sq_empty( 4, 1 ) );
    test_bool = test_bool && ( myGame.is_sq_empty( 4, 2 ) );

    if( test_bool ){
        cout << "En-passant standard test (WHITE take BLACK): passed!" << endl;
    }else{
        cout << "En-passant standard test (WHITE take BLACK): failed!" << endl;
    }

// ---------------------------------------------------------------------- <<<<<


}



void tests::chess_game_state_tests(){

    bool test_bool = true;
    chess myGame;

    // upd_game_state

// ---------------------------------------------------------------------- >>>>>
//      Standard Case
// ---------------------------------------------------------------------- >>>>>

    test_bool = true;
    myGame.clearBoard();
    myGame.setTurn_cnt(0);

    // Simple scenario where white king enters the checked state.
    test_bool = test_bool && ( myGame.getState() == chess::CHS_STATE::DRAW );
    myGame.set_piece_at( 0, 4, 
        chess::chs_piece( chess::CHS_PIECE_TYPE::KING, chess::CHS_PIECE_COLOR::WHITE ) );
    test_bool = test_bool && ( myGame.getState() == chess::CHS_STATE::WWIN );
    myGame.set_piece_at( 7, 7, 
        chess::chs_piece( chess::CHS_PIECE_TYPE::ROOK, chess::CHS_PIECE_COLOR::BLACK ) );
    test_bool = test_bool && ( myGame.getState() == chess::CHS_STATE::ONGOING );
    test_bool = test_bool && myGame.play( 0, 4, 1, 4 );
    test_bool = test_bool && ( myGame.getState() == chess::CHS_STATE::ONGOING );
    test_bool = test_bool && myGame.play( 7, 7, 7, 4 );
    test_bool = test_bool && ( myGame.getState() == chess::CHS_STATE::WCHK );
    
    if( test_bool ){
        cout << "Chess state -> simple check case test: passed!" << endl;
    }else{
        cout << "Chess state -> simple check case test: failed!" << endl;
    }

// ---------------------------------------------------------------------- <<<<<


// ---------------------------------------------------------------------- >>>>>
//     Voluntary Enduced Check State Case
// ---------------------------------------------------------------------- >>>>>

    // Set a rook at the next column the king is to move to.
    myGame.set_piece_at( 7, 5, 
        chess::chs_piece( chess::CHS_PIECE_TYPE::ROOK, chess::CHS_PIECE_COLOR::BLACK ) );
    // Try to play the king towards the threatened column.
    test_bool = test_bool && !myGame.play( 1, 4, 1, 5 );
    // Place a white knight to block the black rook that is checking the white king.
    myGame.set_piece_at( 2, 4, 
        chess::chs_piece( chess::CHS_PIECE_TYPE::KNIGHT, chess::CHS_PIECE_COLOR::WHITE ) );
    // Game state now expected to switch back to ongoing.
    test_bool = test_bool && ( myGame.getState() == chess::CHS_STATE::ONGOING );
    // Attempt to play the white knight, which would leave the white king exposed to check.
    test_bool = test_bool && !myGame.play( 2, 4, 1, 2 );

    if( test_bool ){
        cout << "Chess state -> voluntary check state test: passed!" << endl;
    }else{
        cout << "Chess state -> voluntary check state test: failed!" << endl;
    }

// ---------------------------------------------------------------------- <<<<<


// ---------------------------------------------------------------------- >>>>>
//     Simultaneous Black and White Check
// ---------------------------------------------------------------------- >>>>>

    test_bool = true;
    myGame.clearBoard();
    myGame.setTurn_cnt(0);

    myGame.set_piece_at( 0, 4, 
        chess::chs_piece( chess::CHS_PIECE_TYPE::KING, chess::CHS_PIECE_COLOR::WHITE ) );
    myGame.set_piece_at( 4, 1, 
        chess::chs_piece( chess::CHS_PIECE_TYPE::KING, chess::CHS_PIECE_COLOR::BLACK ) );
    myGame.set_piece_at( 1, 4, 
        chess::chs_piece( chess::CHS_PIECE_TYPE::KNIGHT, chess::CHS_PIECE_COLOR::WHITE ) );
    myGame.set_piece_at( 7, 4, 
        chess::chs_piece( chess::CHS_PIECE_TYPE::ROOK, chess::CHS_PIECE_COLOR::BLACK ) );
    
    // Play the knight such that it attacks the black king while leaving the white
    // king open to be checked by the black rook.
    test_bool = test_bool && !myGame.play( 1, 4, 2, 2 );

    if( test_bool ){
        cout << "Chess state -> Simultaneous check test: passed!" << endl;
    }else{
        cout << "Chess state -> Simultaneous check test: failed!" << endl;
    }

// ---------------------------------------------------------------------- <<<<<

}



void tests::chess_psbl_plays_tests(){

    bool test_bool = true;
    chess myGame;

// ---------------------------------------------------------------------- >>>>>
//      Initial Board Possible Plays Case
// ---------------------------------------------------------------------- >>>>>

    test_bool = true;
    myGame.resetBoard();

    auto all_valid_moves = myGame.get_all_valid_moves();
    test_bool = test_bool && ( all_valid_moves.size() == 20 );
    auto all_valid_atks = myGame.get_all_valid_atks();
    test_bool = test_bool && ( all_valid_atks.size() == 0 );
    myGame.setTurn_cnt(1);
    all_valid_moves = myGame.get_all_valid_moves();
    test_bool = test_bool && ( all_valid_moves.size() == 20 );
    all_valid_atks = myGame.get_all_valid_atks();
    test_bool = test_bool && ( all_valid_atks.size() == 0 );

    

    if( test_bool ){
        cout << "Chess all plays -> initial board case tests: passed!" << endl;
    }else{
        cout << "Chess all plays -> initial board case tests: failed!" << endl;
    }

// ---------------------------------------------------------------------- <<<<<


// ---------------------------------------------------------------------- >>>>>
//      Zero Pawn Initial Board Case
// ---------------------------------------------------------------------- >>>>>

    test_bool = true;
    myGame.resetBoard();

    chess::chs_piece emp_pce;
    emp_pce.set_as_empty();
    pair<int,int> sub_idx_z;

    for( unsigned int z = 0; z < chess::BOARDWIDTH; z++ ){
        myGame.set_piece_at( 1, z, emp_pce );
        myGame.set_piece_at( chess::BOARDHEIGHT - 2, z, emp_pce );
    }

    all_valid_moves = myGame.get_all_valid_moves();
    test_bool = test_bool && ( all_valid_moves.size() == 47 );
    all_valid_atks = myGame.get_all_valid_atks();
    test_bool = test_bool && ( all_valid_atks.size() == 3 );
    myGame.setTurn_cnt(1);
    all_valid_moves = myGame.get_all_valid_moves();
    test_bool = test_bool && ( all_valid_moves.size() == 47 );
    all_valid_atks = myGame.get_all_valid_atks();
    test_bool = test_bool && ( all_valid_atks.size() == 3 );
    
    if( test_bool ){
        cout << "Chess all plays -> initial board without pawns case tests: passed!" << endl;
    }else{
        cout << "Chess all plays -> initial board without pawns case tests: failed!" << endl;
    }

// ---------------------------------------------------------------------- <<<<<


}


void tests::chess_checkmate_tests(){

    bool test_bool = true;
    chess myGame;

// ---------------------------------------------------------------------- >>>>>
//      White Check Test
// ---------------------------------------------------------------------- >>>>>

    test_bool = true;
    myGame.clearBoard();

    myGame.set_piece_at( 3, 4, chess::chs_piece( 
        chess::CHS_PIECE_TYPE::KING, chess::CHS_PIECE_COLOR::WHITE ) );
    myGame.set_piece_at( 7, 4, chess::chs_piece( 
        chess::CHS_PIECE_TYPE::ROOK, chess::CHS_PIECE_COLOR::BLACK ) );

    chess::CHS_STATE tmp = myGame.getState();
    // Simple rook check king.
    test_bool = test_bool && !( myGame.is_check_mate() );
    myGame.set_piece_at( 7, 5, chess::chs_piece( 
        chess::CHS_PIECE_TYPE::ROOK, chess::CHS_PIECE_COLOR::BLACK ) );
    test_bool = test_bool && !( myGame.is_check_mate() );
    myGame.set_piece_at( 7, 3, chess::chs_piece( 
        chess::CHS_PIECE_TYPE::ROOK, chess::CHS_PIECE_COLOR::BLACK ) );
    test_bool = test_bool && ( myGame.is_check_mate() );
    
    // Attempt to play the king when there is no way out of check.
    test_bool = test_bool && !( myGame.ply( 3, 4, 3, 5 ) );
        

    if( test_bool ){
        cout << "Chess white checkmate standard tests: passed!" << endl;
    }else{
        cout << "Chess white checkmate standard tests: failed!" << endl;
    }

// ---------------------------------------------------------------------- <<<<<


// ---------------------------------------------------------------------- >>>>>
//      Black Check Test
// ---------------------------------------------------------------------- >>>>>

    test_bool = true;
    myGame.clearBoard();

    myGame.set_piece_at( 3, 4, chess::chs_piece( 
        chess::CHS_PIECE_TYPE::KING, chess::CHS_PIECE_COLOR::BLACK ) );
    myGame.set_piece_at( 7, 4, chess::chs_piece( 
        chess::CHS_PIECE_TYPE::ROOK, chess::CHS_PIECE_COLOR::WHITE ) );

    tmp = myGame.getState();
    // Simple rook check king.
    test_bool = test_bool && !( myGame.is_check_mate() );
    myGame.set_piece_at( 7, 5, chess::chs_piece( 
        chess::CHS_PIECE_TYPE::ROOK, chess::CHS_PIECE_COLOR::WHITE ) );
    test_bool = test_bool && !( myGame.is_check_mate() );
    myGame.set_piece_at( 7, 3, chess::chs_piece( 
        chess::CHS_PIECE_TYPE::ROOK, chess::CHS_PIECE_COLOR::WHITE ) );
    test_bool = test_bool && ( myGame.is_check_mate() );

    if( test_bool ){
        cout << "Chess black checkmate standard tests: passed!" << endl;
    }else{
        cout << "Chess black checkmate standard tests: failed!" << endl;
    }

// ---------------------------------------------------------------------- <<<<<

}


void tests::chess_full_game_tests(){

    bool test_bool = true;
    chess myGame;
    chess::CHS_STATE tmp_state;

// ---------------------------------------------------------------------- >>>>>
//      Full Play Scenario of "The Evergreen Game"
// ---------------------------------------------------------------------- >>>>>

    myGame.resetBoard();

    test_bool = test_bool && myGame.ply_ag_coord( 'e',2,'e',4 );    
    test_bool = test_bool && myGame.ply_ag_coord( 'e',7,'e',5 );
    test_bool = test_bool && myGame.ply_ag_coord( 'g',1,'f',3 );
    test_bool = test_bool && myGame.ply_ag_coord( 'b',8,'c',6 );
    test_bool = test_bool && myGame.ply_ag_coord( 'f',1,'c',4 );
    test_bool = test_bool && myGame.ply_ag_coord( 'f',8,'c',5 );
    test_bool = test_bool && myGame.ply_ag_coord( 'b',2,'b',4 );
    test_bool = test_bool && myGame.ply_ag_coord( 'c',5,'b',4 );
    test_bool = test_bool && myGame.ply_ag_coord( 'c',2,'c',3 );
    test_bool = test_bool && myGame.ply_ag_coord( 'b',4,'a',5 );
    test_bool = test_bool && myGame.ply_ag_coord( 'd',2,'d',4 );
    test_bool = test_bool && myGame.ply_ag_coord( 'e',5,'d',4 );
    test_bool = test_bool && myGame.ply_ag_coord( 'e',1,'g',1 );
    test_bool = test_bool && myGame.ply_ag_coord( 'd',4,'d',3 );
    test_bool = test_bool && myGame.ply_ag_coord( 'd',1,'b',3 );
    test_bool = test_bool && myGame.ply_ag_coord( 'd',8,'f',6 );
    test_bool = test_bool && myGame.ply_ag_coord( 'e',4,'e',5 );
    test_bool = test_bool && myGame.ply_ag_coord( 'f',6,'g',6 );
    test_bool = test_bool && myGame.ply_ag_coord( 'f',1,'e',1 );
    test_bool = test_bool && myGame.ply_ag_coord( 'g',8,'e',7 );
    test_bool = test_bool && myGame.ply_ag_coord( 'c',1,'a',3 );
    test_bool = test_bool && myGame.ply_ag_coord( 'b',7,'b',5 );
    test_bool = test_bool && myGame.ply_ag_coord( 'b',3,'b',5 );
    test_bool = test_bool && myGame.ply_ag_coord( 'a',8,'b',8 );
    test_bool = test_bool && myGame.ply_ag_coord( 'b',5,'a',4 );
    test_bool = test_bool && myGame.ply_ag_coord( 'a',5,'b',6 );
    test_bool = test_bool && myGame.ply_ag_coord( 'b',1,'d',2 );
    test_bool = test_bool && myGame.ply_ag_coord( 'c',8,'b',7 );
    test_bool = test_bool && myGame.ply_ag_coord( 'd',2,'e',4 );
    test_bool = test_bool && myGame.ply_ag_coord( 'g',6,'f',5 );
    test_bool = test_bool && myGame.ply_ag_coord( 'c',4,'d',3 );
    test_bool = test_bool && myGame.ply_ag_coord( 'f',5,'h',5 );
    test_bool = test_bool && myGame.ply_ag_coord( 'e',4,'f',6 );
    test_bool = test_bool && myGame.ply_ag_coord( 'g',7,'f',6 );
    test_bool = test_bool && myGame.ply_ag_coord( 'e',5,'f',6 );
    test_bool = test_bool && myGame.ply_ag_coord( 'h',8,'g',8 );
    test_bool = test_bool && myGame.ply_ag_coord( 'a',1,'d',1 );
    test_bool = test_bool && myGame.ply_ag_coord( 'h',5,'f',3 );
    test_bool = test_bool && myGame.ply_ag_coord( 'e',1,'e',7 );
    test_bool = test_bool && myGame.ply_ag_coord( 'c',6,'e',7 );
    test_bool = test_bool && myGame.ply_ag_coord( 'a',4,'d',7 );
    test_bool = test_bool && myGame.ply_ag_coord( 'e',8,'f',8 );
    test_bool = test_bool && myGame.ply_ag_coord( 'a',3,'e',7 );
    tmp_state = myGame.getState();
    
    test_bool = test_bool && ( tmp_state == chess::CHS_STATE::WWIN );

    chess::chs_piece empty_piece;
    // Define the end game piece list.
    chess endGame;
    endGame.clearBoard();

    endGame.set_piece_at_ag_coord( 'd', 1, 
        chess::chs_piece( chess::CHS_PIECE_TYPE::ROOK, chess::CHS_PIECE_COLOR::WHITE ) );
    endGame.set_piece_at_ag_coord( 'g', 1, 
        chess::chs_piece( chess::CHS_PIECE_TYPE::KING, chess::CHS_PIECE_COLOR::WHITE ) );
    endGame.set_piece_at_ag_coord( 'a', 2, 
        chess::chs_piece( chess::CHS_PIECE_TYPE::PAWN, chess::CHS_PIECE_COLOR::WHITE ) );
    endGame.set_piece_at_ag_coord( 'f', 2, 
        chess::chs_piece( chess::CHS_PIECE_TYPE::PAWN, chess::CHS_PIECE_COLOR::WHITE ) );
    endGame.set_piece_at_ag_coord( 'g', 2, 
        chess::chs_piece( chess::CHS_PIECE_TYPE::PAWN, chess::CHS_PIECE_COLOR::WHITE ) );
    endGame.set_piece_at_ag_coord( 'h', 2, 
        chess::chs_piece( chess::CHS_PIECE_TYPE::PAWN, chess::CHS_PIECE_COLOR::WHITE ) );
    endGame.set_piece_at_ag_coord( 'c', 3, 
        chess::chs_piece( chess::CHS_PIECE_TYPE::PAWN, chess::CHS_PIECE_COLOR::WHITE ) );
    endGame.set_piece_at_ag_coord( 'd', 3, 
        chess::chs_piece( chess::CHS_PIECE_TYPE::BISHOP, chess::CHS_PIECE_COLOR::WHITE ) );
    endGame.set_piece_at_ag_coord( 'f', 3, 
        chess::chs_piece( chess::CHS_PIECE_TYPE::QUEEN, chess::CHS_PIECE_COLOR::BLACK ) );
    endGame.set_piece_at_ag_coord( 'b', 6, 
        chess::chs_piece( chess::CHS_PIECE_TYPE::BISHOP, chess::CHS_PIECE_COLOR::BLACK ) );
    endGame.set_piece_at_ag_coord( 'f', 6, 
        chess::chs_piece( chess::CHS_PIECE_TYPE::PAWN, chess::CHS_PIECE_COLOR::WHITE ) );
    endGame.set_piece_at_ag_coord( 'a', 7, 
        chess::chs_piece( chess::CHS_PIECE_TYPE::PAWN, chess::CHS_PIECE_COLOR::BLACK ) );
    endGame.set_piece_at_ag_coord( 'b', 7, 
        chess::chs_piece( chess::CHS_PIECE_TYPE::BISHOP, chess::CHS_PIECE_COLOR::BLACK ) );
    endGame.set_piece_at_ag_coord( 'c', 7, 
        chess::chs_piece( chess::CHS_PIECE_TYPE::PAWN, chess::CHS_PIECE_COLOR::BLACK ) );
    endGame.set_piece_at_ag_coord( 'd', 7, 
        chess::chs_piece( chess::CHS_PIECE_TYPE::QUEEN, chess::CHS_PIECE_COLOR::WHITE ) );
    endGame.set_piece_at_ag_coord( 'e', 7, 
        chess::chs_piece( chess::CHS_PIECE_TYPE::BISHOP, chess::CHS_PIECE_COLOR::WHITE ) );
    endGame.set_piece_at_ag_coord( 'f', 7, 
        chess::chs_piece( chess::CHS_PIECE_TYPE::PAWN, chess::CHS_PIECE_COLOR::BLACK ) );
    endGame.set_piece_at_ag_coord( 'h', 7, 
        chess::chs_piece( chess::CHS_PIECE_TYPE::PAWN, chess::CHS_PIECE_COLOR::BLACK ) );
    endGame.set_piece_at_ag_coord( 'b', 8, 
        chess::chs_piece( chess::CHS_PIECE_TYPE::ROOK, chess::CHS_PIECE_COLOR::BLACK ) );
    endGame.set_piece_at_ag_coord( 'f', 8, 
        chess::chs_piece( chess::CHS_PIECE_TYPE::KING, chess::CHS_PIECE_COLOR::BLACK ) );
    endGame.set_piece_at_ag_coord( 'g', 8, 
        chess::chs_piece( chess::CHS_PIECE_TYPE::ROOK, chess::CHS_PIECE_COLOR::BLACK ) );
    
    pair<int,int> curr_coord;
    for( unsigned int z = 0; z < chess::BOARDHEIGHT*chess::BOARDWIDTH; z++ ){
        curr_coord = chess::ind2sub( z );
        test_bool = test_bool && ( 
            myGame.get_piece_at( curr_coord.first, curr_coord.second ) ==
            endGame.get_piece_at( curr_coord.first, curr_coord.second )
        );
    }

    if( test_bool ){
        cout << "The Evergreen game playout test: passed!" << endl;
    }else{
        cout << "The Evergreen game playout test: failed!" << endl;
    }

// ---------------------------------------------------------------------- <<<<<

    
} 


