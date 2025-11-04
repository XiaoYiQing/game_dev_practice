#ifndef CHESS_H
#define CHESS_H



#include <cmath>
#include <iostream>
#include <magic_enum.hpp>
#include <mutex>
#include <stack>
#include <string>
#include <vector>


using namespace std;


namespace gameEngine{


/*
TODO:
    It might be a good idea to implement the chess game as a 2 tiers class system.
    - The lower tier serves the purpose of representing the chess board state.
    - The upper tier class holds instance(s) of the lower tier class and manage
    the flow of the game from a higher level.

    Reasoning: Chess game features such as draw by lack of progress requires knowledge of 
    pass ~50 turns. It would then be reasonable to store the history of the game at the
    upper tier class using lower tier instances as pictures of each step of the game.

    The lower tier will have:
    1- The chess board.
    2- atk_list_by_W: list of threats by white pieces at all squares.
    3- atk_list_by_B: list of threats by black pieces at all squares.
    4- turn_cnt.
    5- en_pass_flag and en_pass_moves
    6- promo lock and promo_point
    7- state
*/

/**
 * My implementation of the chess game.
 * 
 * This basic implementation operates under the assumption that white starts at 
 * the lower side and black starts at the top side of the board.
 */
class chess{

public:

    // The dimensions of the chess board.
    static const unsigned int BOARDWIDTH = 8;
    static const unsigned int BOARDHEIGHT = 8;

    // Define the maximum number of consecutive moves without a pawn being moved
    // or a piece been captured.
    static const unsigned int DRAWMOVECOUNTMAX = 50;


// ====================================================================== >>>>>
//      Class Enum "CHS_PIECE_TYPE" Help Functions
// ====================================================================== >>>>>

    /**
     * Enum representing the possible chess pieces placed on the board.
     */
    enum class CHS_PIECE_TYPE{ NO_P, PAWN, KNIGHT, BISHOP, ROOK, QUEEN, KING };

    // The number of enum entries in the enum "CHS_PIECE_TYPE" (Uses magic enum).
    const static int CHS_PIECE_TYPE_Count = (int) magic_enum::enum_count<CHS_PIECE_TYPE>();

    /**
     * Obtain the string of the target enum case (Uses magic enum).
     * 
     * @param tar_CHS_PIECE_TYPE The target CHS_PIECE_TYPE enum.
     * @return The string representation of the target CHS_PIECE_TYPE enum.
     */
    static string get_CHS_PIECE_TYPE_Str( CHS_PIECE_TYPE tar_CHS_PIECE_TYPE );
    /**
     * Obtain the CHS_PIECE_TYPE enum whose native index matches the target index.
     * 
     * @param idx The target index for which we seek a matching CHS_PIECE_TYPE enum.
     * @return The matching CHS_PIECE_TYPE enum to the target index, if it exists.
     */
    static CHS_PIECE_TYPE get_CHS_PIECE_TYPE_AtIdx( int idx );

// ====================================================================== <<<<<


// ====================================================================== >>>>>
//      Class Enum "CHS_PIECE_COLOR" Help Functions
// ====================================================================== >>>>>

    /**
     * Enum representing the possible chess pieces placed on the board.
     */
    enum class CHS_PIECE_COLOR{ NO_C, WHITE, BLACK };

    // The number of enum entries in the enum "CHS_PIECE_COLOR" (Uses magic enum).
    const static int CHS_PIECE_COLOR_Count = (int) magic_enum::enum_count<CHS_PIECE_COLOR>();

    /**
     * Obtain the string of the target enum case (Uses magic enum).
     * 
     * @param tar_CHS_PIECE_COLOR The target CHS_PIECE_COLOR enum.
     * @return The string representation of the target CHS_PIECE_COLOR enum.
     */
    static string get_CHS_PIECE_COLOR_Str( CHS_PIECE_COLOR tar_CHS_PIECE_COLOR );
    /**
     * Obtain the CHS_PIECE_COLOR enum whose native index matches the target index.
     * 
     * @param idx The target index for which we seek a matching CHS_PIECE_COLOR enum.
     * @return The matching CHS_PIECE_COLOR enum to the target index, if it exists.
     */
    static CHS_PIECE_COLOR get_CHS_PIECE_COLOR_AtIdx( int idx );

// ====================================================================== <<<<<


// ====================================================================== >>>>>
//      Class Enum "CHS_STATE" Help Functions
// ====================================================================== >>>>>
/*
Update the state of the game:
    > 0 = unfinished ---> game is still in progress.
    > 1 = White check: game is ongoing but with the white king in check.
    > 2 = Black check: game is ongoing but with the black king in check.
    > 3 = White won: ---> game has ended with white being victorious.
    > 4 = Black won: -----> game has ended with black being victorious.
    > 5 = Draw: --------> game has ended with no one victorious.
*/

/**
 * Enum representing the states the game can be in.
 */
enum class CHS_STATE{ NO_S, ONGOING, WCHK, BCHK, WWIN, BWIN, DRAW };

// The number of enum entries in the enum "CHS_STATE" (Uses magic enum).
const static int CHS_STATE_Count = (int) magic_enum::enum_count<CHS_STATE>();
/**
 * Obtain the string of the target enum case (Uses magic enum).
 * 
 * @param tar_CHS_STATE The target CHS_STATE enum.
 * @return The string representation of the target CHS_STATE enum.
 */
static string get_CHS_STATE_Str( CHS_STATE tar_CHS_STATE );
/**
 * Obtain the CHS_STATE enum whose native index matches the target index.
 * 
 * @param idx The target index for which we seek a matching CHS_STATE enum.
 * @return The matching CHS_STATE enum to the target index, if it exists.
 */
static CHS_STATE get_CHS_STATE_AtIdx( int idx );

// ====================================================================== <<<<<


// ====================================================================== >>>>>
//      Chess Piece Class
// ====================================================================== >>>>>

    class chs_piece{

    public:

        /**
         * Comparison operator overload.
         * 
         * \param other Target chs_piece to compare with.
         * \return Result of the comparison.
         */
        bool operator==(const chs_piece& other) const;

        // Base constructor.
        chs_piece();

        chs_piece( CHS_PIECE_TYPE type, CHS_PIECE_COLOR color );

        // Set the piece into an empty space equivalent.
        void set_as_empty();

        /**
         * \brief Print the piece using the designated symbol.
         * 
         * Prints only the symbol with no space or line breaks to delimit the symbol.
         * 
         * \note This is a debug tool and has no impact on actual game functionalities.
         */
        void printPiece() const;

        /**
         * The type of piece.
         */
        CHS_PIECE_TYPE type;

        /**
         * The color of the piece.
         */
        CHS_PIECE_COLOR color;

        /**
         * The boolean indicating whether this piece has not yet performed its forst 
         * move yet.
         */
        bool not_moved;

    };

// ====================================================================== <<<<<



// ====================================================================== >>>>>
//      Chess Move Class
// ====================================================================== >>>>>

    /**
     * Specialized nested class for representing a chess move.
     * 
     * \warning This class does not check for validity of a move inherently. 
     *  However, it does define functions to do just so.
     */
    class chs_move{

        public:

        // Base constructor.
        chs_move();
        /**
         * Direct coordinate (individual numeral format) input constructor.
         * 
         * \param i_a Starting coordinate row index.
         * \param j_a Starting coordinate column index.
         * \param i_b Ending coordinate row index.
         * \param j_b Ending coordinate column index.
         */
        chs_move( int i_a, int j_a, int i_b, int j_b );
        /**
         * Direct coordinate (pair format) input constructor.
         * \param pt_a Starting coordinate.
         * \param pt_b Ending coordinate.
         */
        chs_move( pair<int,int> pt_a, pair<int,int> pt_b );

        // Starting coordinates.
        pair<int,int> pt_a;
        // Ending coordinate.
        pair<int,int> pt_b;

        /**
         * Obtain the vector representation of the move.
         * 
         * \return A pair of integers, representing a 2D vector.
         */
        std::pair<int,int> get_vec();
        

    };

// ====================================================================== <<<<<


// ====================================================================== >>>>>
//      Constructors
// ====================================================================== >>>>>

    chess();

// ====================================================================== <<<<<


// ====================================================================== >>>>>
//      Game Direct Manipulation Functions
// ====================================================================== >>>>>

    /**
     * Reset the state variables.
     */
    void resetStateVars();

    /**
     * \brief Set the board as completely blank.
     * 
     * All pieces of the board adopt the "no piece" state.
     * 
     * This function triggers a complete chess board state update.
     * 
     */
    void clearBoard();

    /**
     * Reset the board to the state of a fresh new game.
     * 
     * This function triggers a complete chess board state update.
     * 
     * \note This function serves as a game instance reset, though some class
     *  variables may not be affected.
     */
    void resetBoard();

    

    /**
     * \brief Set target square as empty.
     * 
     * This function triggers a complete chess board state update.
     */
    void clearSquare( unsigned int i, unsigned int j );

    /**
     * \brief Set the piece at the target coordinate as the target piece.
     * 
     * This function triggers a complete chess board state update.
     * 
     * \note Overwrites existing piece by default.
     * 
     * \param i The row index of the insertion point.
     * \param j The column index of the insertion point.
     * \param inPce The new piece to be inserted.
     * 
     * \warning Does not update the turn count.
     */
    void set_piece_at( const unsigned int i, const unsigned int j, const chs_piece inPce );
    /**
     * \brief Set the piece at the target algebraic coordinate as the target piece.
     * 
     * This function triggers a complete chess board state update.
     * 
     * \note Overwrites existing piece by default.
     * 
     * \param c The alphabet letter representing the target column (a to h).
     * \param n The row index (starting from 1 and up to 8 for standard chess board).
     * \param inPce The new piece to be inserted.
     * 
     * \warning Does not update the turn count.
     */
    void set_piece_at_ag_coord( const char c, const unsigned int n, const chs_piece inPce );

    

// ====================================================================== <<<<<


// ====================================================================== >>>>>
//      Gameplay Functions
// ====================================================================== >>>>>

    /**
     * Promote the pawn expected to be on the last row of the target column.
     * 
     * \param col_idx Index of the column where the promoting pawn is (assumed to 
     *  be) located.
     * \param promo_type The chess piece type the pawn is to promote into.
     * \return Boolean indicating whether the promotion is successful.
     */
    bool promote( unsigned int col_idx, CHS_PIECE_TYPE promo_type );


    bool play( chs_move tarMove );

    /* TODO: play is currently the true full function which determines if a move 
        or attack is valid. The other all possible move and attack functions are not 
        able to determine a very specific gap in their logic. If a king blocks 
        the path of attack of an enemy piece, the blocked squares would be deemed
        as safe for the king to move to with the current play validity logic. Of
        course, this isn't true since if the king moves then he would still be
        in check.
        
        This is not a fatal problem per see, as the play function specifically checks
        the final play validity condition where a king in check must be no longer in
        check after the play.
        However, if you deem this rather vulnerable safeguard to be insufficient, find
        a way to improve the move and attack validity functions to close this gap in 
        logic.
    */
    /**
     * Play a chess piece with the specified beginning and ending square coordinates.
     */
    bool play( unsigned int i_bef, unsigned int j_bef, 
        unsigned int i_aft, unsigned int j_aft );
    
    /**
     * Play a chess piece with the specified beginning and ending square coordinates.
     * 
     * The coordinates follow the algebraic coordinate system.
     * 
     * \note number indices are from 1 to 8.
     */
    bool play_ag_coord( char c1, int n1, char c2, int n2 );

    
    bool ply_ag_coord( char c1, int n1, char c2, int n2 );

    bool ply( chs_move tarMove );

    /**
     * \brief perform a ply (half-turn).
     * 
     * This is basically performing a play on the chess board, but with additional 
     * subroutines ran in order to check and preserve the logic state of the game.
     */
    bool ply( unsigned int i_bef, unsigned int j_bef, 
        unsigned int i_aft, unsigned int j_aft );

    /**
     * \brief Determine if the specified move (displacement) is valid.
     * 
     * Does not perform the move.
     * 
     * \note This function strictly checks whether the piece can perform a 
     *  displacement, not an attack. If the ending square has an opponent piece,
     *  this function returns false because such an action would be an attack, not 
     *  a move.
     * 
     * \param i_bef Row index of the starting position.
     * \param j_bef Column index of the starting position.
     * \param i_aft Row index of the landing position.
     * \param j_aft Column index of the landing position.
     * \return Boolean indicating whether this move is valid.
     */
    bool is_move_valid( unsigned int i_bef, unsigned int j_bef, 
        unsigned int i_aft, unsigned int j_aft ) const;
    
    /**
     * \brief Determine if the specified attack is valid.
     * 
     * Does not perform the attack.
     * 
     * \note If you attack an empty square, the function returns false because
     *  such an act is a move, not an attack.
     * 
     * \param i_bef Row index of the starting position.
     * \param j_bef Column index of the starting position.
     * \param i_aft Row index of the attack target's position.
     * \param j_aft Column index of the attack target's position.
     * \return Boolean indicating whether this attack is valid.
     */
    bool is_atk_valid( unsigned int i_bef, unsigned int j_bef, 
        unsigned int i_aft, unsigned int j_aft  ) const;
    
// ====================================================================== <<<<<


// ====================================================================== >>>>>
//      Game State Functions
// ====================================================================== >>>>>
    /**
     * \return True if the game is at white's turn to play.
     */
    bool is_white_turn();
    /**
     * \return True if the game is at black's turn to play.
     */
    bool is_black_turn();

    /**
     * \brief Check if the target coordinate square is empty.
     * 
     * An empty square is one which has the 'null' color and 'null' type chess piece.
     * 
     * \return Boolean indicating whether the square is empty.
     */
    bool is_sq_empty( int i, int j ) const;

    /**
     * \brief Obtain all squares attacked by the piece at the target coordinate.
     * 
     * This function does not differentiate between black and white pieces.
     * 
     * \note This function does not care if the attack is actually valid. 
     * For example, a black knight is currently blocking a white rook from checking the 
     * black king, but the squares where the black knight can otherwise have attacked
     * will still be put on this attack list.
     * 
     * \param i Target piece row index.
     * \param j Target piece column index.
     * \return All squares that are attacked by the target piece.
     */
    vector< pair<int,int> > get_all_atk_sq( int i, int j ) const;
    /**
     * \brief Obtain all valid attack coordinates by the piece at the target coordinate.
     * 
     * This function does not differentiate between black and white pieces.
     * 
     * \note If target is a white piece on a black turn or vice versa, this function
     *  will return an empty vector because a play on the wrong turn is invalid.
     * 
     * \param i Target piece row index.
     * \param j Target piece column index.
     * \return All squares that are valid attack point by the target piece.
     */
    vector< pair<int,int> > get_all_valid_atk_sq( int i, int j ) const;
    
    /**
     * \brief Obtain all valid move coordinates from the piece at the target coordinate.
     * 
     * This function does not differentiate between black and white pieces.
     * 
     * \note If target is a white piece on a black turn or vice versa, this function
     *  will return an empty vector because a play on the wrong turn is invalid.
     * 
     * \param i Target piece row index.
     * \param j Target piece column index.
     * \return All squares that are valid move point from the target piece.
     */
    vector< pair<int,int> > get_all_valid_move_sq( int i, int j ) const;
    
    /**
     * \brief Obtain all current valid moves.
     * 
     * \note Current turn must match the piece's color for its move to be considered valid.
     * 
     * \return All currently possible moves.
     */
    vector<chs_move> get_all_valid_moves() const;
    /**
     * \brief Obtain all current valid attacks.
     * 
     * \note Current turn must match the piece's color for its attacks to be considered valid.
     * 
     * \return All currently possible attacks.
     */
    vector<chs_move> get_all_valid_atks() const;

    bool is_check_mate();

    /**
     * Update the game's attack list.
     */
    void upd_atk_lists();

    /**
     * Update the game's state variable.
     */
    void upd_game_state();

    /**
     * Update all state related variables.
     */
    void upd_all();

    /**
     * \brief Print the state of the board onto the console terminal.
     * 
     * \note This is a debug tool and has no impact on actual game functionalities.
     */
    void printBoard() const;
    /**
     * \brief Print the state of the board onto the console terminal following
     *  the albegraic coordinate format.
     * 
     * \note This is a debug tool and has no impact on actual game functionalities.
     */
    void printBoard_ag_coord() const;

// ====================================================================== <<<<<


// ====================================================================== >>>>>
//      Access Function
// ====================================================================== >>>>>
    
    /**
     * \brief Convert 2D indexing to 1D.
     * 
     * Linear indexing uses column index as lower order term. 
     * 
     * For example:
     *  (0,0)=>0, (0,1)=>1, ... (0,7)=>7, (1,0)=>8, and so on.
     * 
     * \param i Row index.
     * \param j Column index.
     * \return The linear index equivalent.
     */
    static int sub2ind( int i, int j );
    /**
     * \brief Convert 2D indexing to 1D.
     * 
     * Linear indexing uses column index as lower order term. 
     * 
     * For example:
     *  (0,0)=>0, (0,1)=>1, ... (0,7)=>7, (1,0)=>8, and so on.
     * 
     * \param subIdx The 2D coordinate pair (first = row index, second = column index).
     * \return The linear index equivalent.
     */
    static int sub2ind( pair<int,int> subIdx );

    /**
     * \brief Convert 2D indexing to 1D.
     * 
     * Linear indexing uses column index as lower order term. 
     * 
     * For example:
     *  (0,0)=>0, (0,1)=>1, ... (0,7)=>7, (1,0)=>8, and so on.
     * 
     * \param sub_arr vector of 
     * \return The linear index equivalent vector.
     */
    static vector<int> sub2ind( vector<pair<int,int>> sub_arr );

    /**
     * \brief Convert linear indexing to 2D indexing.
     * 
     * Linear indexing uses column index as lower order term. 
     * 
     * \param linIdx The linear index.
     * \return The 2D coordinate pair equivalent (first = row index, second = column index).
     */
    static pair<int,int> ind2sub( int linIdx );
    /**
     * \brief Convert linear indexing to 2D indexing.
     * 
     * Linear indexing uses column index as lower order term. 
     * 
     * \param linIdxVec The linear index array.
     * \return The 2D coordinate pair array equivalent (first = row index, second = column index).
     */
    static vector< pair<int,int> > ind2sub( vector<int> linIdxVec );

    /**
     * Obtain the chess piece at the target coordinate.
     * 
     * \param i The row index of the target piece.
     * \param j The column index of the target piece.
     * \return The target piece at the coordinate.
     */
    chs_piece get_piece_at( unsigned int i, unsigned int j ) const;
    
    /**
     * \return Current game state turn count.
     */
    unsigned int getTurn_cnt() const;
    /**
     * \brief Forcibly set the game's current turn count.
     * 
     * \param turn_cnt The number of turns to set the game to 
     *  (disregarding current state).
     */
    void setTurn_cnt( const unsigned int turn_cnt );
    
    /**
     * \brief Get the current game state.
     * 
     * \return The current game state.
     */
    CHS_STATE getState() const;

    /**
     * \brief Set the current game state.
     * 
     * \param state The new state to be applied to the game instance.
     * 
     * \warning This function can completely break the game's logic flow.
     */
    void setState( const CHS_STATE state );

    /**
     * \return The number of consecutive turns where no significant changes has occurred.
     */
    unsigned int getNo_change_turn_cnt() const;
    /**
     * \param no_change_turn_cnt The number of consecutive turns where no significant
     *  changes has occurred to be directly applied to the current game instance.
     */
    void setNo_change_turn_cnt( const unsigned int no_change_turn_cnt );

    /**
     * Obtain the list of all white pieces attacking each and every square on the board.
     */
    std::array<vector<int>,BOARDHEIGHT*BOARDWIDTH> getAtk_list_by_W() const;
    /**
     * Obtain the list of all black pieces attacking each and every square on the board.
     */
    std::array<vector<int>,BOARDHEIGHT*BOARDWIDTH> getAtk_list_by_B() const;
    
    bool getEn_pass_flag() const;
    void setEn_pass_flag( bool en_pass_flag );
    
    vector<chs_move> getEn_pass_moves() const;
    void setEn_pass_moves( vector<chs_move> en_pass_move_in );
        
    /**
     * \return The flag indicating the game is awaiting for a pawn promotion.
     */
    bool getPromo_lock() const;
    /**
     * \brief Set the flag indicating the game is awaiting for a pawn promotion.
     * 
     * \warning Forcibly setting the promotion lock can disrupt the logic flow of the
     *  game.
     */
    void setPromo_lock( const bool promo_lock );
    
    /**
     * \brief Obtain the coordinate of the pawn currently awaiting promotion.
     * 
     * \return The coordinate of the pawn awaiting promotion.
     * 
     * \warning This coordinate is invalid if promo_lock is false.
     */
    pair<int,int> getPromo_point() const;
    /**
     * \brief Set the coordinate of the pawn currently awaiting promotion.
     * 
     * \warning Forcibly setting the promotion coordinate can disrupt the logic 
     *  flow of the game.
     */
    void setPromo_point( const pair<int,int> promo_point_in );
    

// ====================================================================== <<<<<


protected:

    /**
     * \brief Array representing the chess board.
     * 
     * - First indexing represents the row indexing.
     * 
     * - Second indexing represents the column indexing.
     * 
     * \note Remember that the lower right corner is a white square in chess.
     */
    chs_piece CHS_board[BOARDHEIGHT][BOARDWIDTH];
    
    /**
     * Array of lists of white pieces attacking the square associated to the index
     * in the array. The attacks are not necessarily valid.
     */
    std::array<vector<int>,BOARDHEIGHT*BOARDWIDTH> atk_list_by_W;
    /**
     * Array of lists of black pieces attacking the square associated to the index
     * in the array. The attacks are not necessarily valid.
     */
    std::array<vector<int>,BOARDHEIGHT*BOARDWIDTH> atk_list_by_B;

    // The number of times a play has been made. White start at turn 0.
    unsigned int turn_cnt;

    // The number of consecutive turns where the draw by lack of progress conditions applies.
    unsigned int no_change_turn_cnt;
    
    // Boolean indicating that an en-passant move is actively possible.
    bool en_pass_flag;
    // The specific en-passant move.
    vector<chs_move> en_pass_moves;

    // Game lock boolean for when a promotion is necessary for a pawn that reached
    // the last row.
    bool promo_lock;
    // The promotion target.
    pair<int,int> promo_point;

    // The state of the game.
    CHS_STATE state;
    

private:


};


};


#endif // CHESS_H