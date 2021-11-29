/* ----------------------------------------------------------------------
    Program 2: Great 13
        Peg puzzle. Jump pegs to try and leave only a single peg.

    Course: CS 141, Fall 2021
    System: Mac using Xcode
    Author: Dale Reed
    
    Running the program looks like:
        
        Class:   CS 141, Fall '21
        Program: #2 Great 13
         
        Make a series of jumps until there is a single piece left in the
        middle. On each move you must jump an adjacent piece into an empty
        square, jumping horizontally, vertically, or diagonally.

             Board    Position
               #          A
             # # #      B C D
           # # . # #  E F G H I
             # # #      J K L
               #          M

        1. Enter position to move from, piece to jump, and destination (e.g. EFG): efg
             Board    Position
               #          A
             # # #      B C D
           . . # # #  E F G H I
             # # #      J K L
               #          M

        2. Enter position to move from, piece to jump, and destination (e.g. EFG):
        
        . . .
        
    Test cases used for this program are:
    1. (2 points) First user input is 'X' then exit
       Input: x
    2. (3 points) Moves then 'R' then restart the game then exit
       Input: acg ida r acg x
    3. (5 points) Attempt to move non-adjacent pieces then exit
       Input: feg ejg efg GAE HGF X
    4. (5 points) Source does not have a piece then exit
       Input: efg MJE hgf gkm lkj x
    5. (5 points) Square being jumped does not have a piece then exit
       Input: FGH efg hgf hgf ihg mkg x
    6. (5 points) Destination is not blank then exit
       Input: efg hgf ACG gfe fgh kgc mli mkg x
    7. (10 points, Zybooks has hidden inputs & outputs.) Multiple moves and errors then exit
       Input: acg ida mli lhd bcd ghi R mkg ilm bgl x
    8. (15 points, Zybooks has hidden inputs & outputs.) Check a winning set of moves
       Input: efg mje R efg mje dgj ihg jgd lkj acg eba adi jgd ida
    7. (5 points) Win the game
       Input: mkg ejm dgj mje lhd acg ida bgl efg lgb abe
  ----------------------------------------------------------------------
*/

#include <iostream>
#include <cctype>   // for toupper()
using namespace std;

// Global variables for the pieces are allowed for this program,
// but will generally not be allowed in the future.
char pA,pB,pC,pD,pE,pF,pG,pH,pI,pJ,pK,pL,pM;    // Board pieces
char moveFrom = ' ',        // Where to move from
     pieceToJump = ' ',     // What to jump
     moveTo = ' ';          // Where to move to
int numberOfPieces = 12;    // Only 12, since middle piece is blank
const char PlayerPiece = '#';  // Default piece character
const char BlankPiece = '.';   // Default blank piece
int moveNumber = 1;         // Gets incremented after each valid move


// ----------------------------------------------------------------------
void displayInstructions()
{
    cout << "Class:   CS 141           \n"
         << "Program: #2 Great 13      \n"
         << "  \n"
         << "Make a series of jumps until there is a single piece left in the   \n"
         << "middle. On each move you must jump an adjacent piece into an empty \n"
         << "square, jumping horizontally, vertically, or diagonally.           \n"
         << "Input of 'R' resets the board back to the beginning, and input of  \n"
         << "'X' exits the game.'   \n"
         << endl;
} //end displayInstructions()


// ----------------------------------------------------------------------
// Initialize the board.
// Set the pieces to the default player piece character, and set the
// moveNumber to the starting value.  This is called at the beginning of
// the game and also if input of 'R' to reset the board is provided.
void initializeBoard()
{
    pA=pB=pC=pD=pE=pF=pH=pI=pJ=pK=pL=pM= PlayerPiece;
    pG= BlankPiece;     // The middle blank piece
    moveNumber = 1;
    numberOfPieces = 12;
} //end initializeBoard()

    
// ----------------------------------------------------------------------
void displayBoard()
{
    cout <<"\n "
         <<                 "    Board   " <<            " Position \n"
         <<"       "             << pA <<             "          A    \n"
         <<"     " <<      pB<<" "<<pC<<" "<<pD<<       "      B C D  \n"
         <<"   "<<pE<<" "<<pF<<" "<<pG<<" "<<pH<<" "<<pI<<"  E F G H I\n"
         <<"     " <<      pJ<<" "<<pK<<" "<<pL<<       "      J K L  \n"
         <<"       "             << pM <<             "          M    \n"
         << endl;
} //end displayBoard()


// ----------------------------------------------------------------------
// This utility function takes a letter 'A'..'M' and sets the corresponding
// variable to have the newValue
void setValue( char thePiece, char newValue)
{
    switch( thePiece) {
        case 'A': pA = newValue; break;
        case 'B': pB = newValue; break;
        case 'C': pC = newValue; break;
        case 'D': pD = newValue; break;
        case 'E': pE = newValue; break;
        case 'F': pF = newValue; break;
        case 'G': pG = newValue; break;
        case 'H': pH = newValue; break;
        case 'I': pI = newValue; break;
        case 'J': pJ = newValue; break;
        case 'K': pK = newValue; break;
        case 'L': pL = newValue; break;
        case 'M': pM = newValue; break;
        // Sanity check
        default: cout << "Invalid value " << thePiece << "sent to fcn setValue.  Exiting.";
                exit( -1);
                break;
    } //end switch( thePiece)
    
} //end setValue()


// ----------------------------------------------------------------------
// Blank out where we're moving from, blank out the piece being jumped,
// and place piece in the destination square.
// This uses global variables moveFrom, pieceToJump, moveTo.
// Then decrement the numberOfPieces, which when equals 1 is used to
// indicate when the game is done.
void makeMove()
{
    // Change the board values involved in the move
    setValue( moveFrom, BlankPiece);       // Blank out where we're moving from
    setValue( pieceToJump, BlankPiece);    // Blank out the piece being jumped
    setValue( moveTo, PlayerPiece); // Overwrite blank at destination with PlayerPiece
    
    // Decrement the number of pieces remaining
    numberOfPieces--;
} //end makeMove()


// ----------------------------------------------------------------------
// Compare the three locations for this move against all possible valid
// letter combinations.  If they are valid (are adjacent) return false,
// else return true (they're not adjacent).
// Board looks like:
//      A
//    B C D
//  E F G H I
//    J K L
//      M
bool areNotAdjacent(
        char moveFrom,      // Letter 'A'..'M' where we're moving from
        char pieceToJump,   // Letter 'A'..'M' of piece to be jumped
        char moveTo)        // Letter 'A'..'M' where we're moving to
{
    // Check for all 32 valid adjacent patterns, roughly going top down,
    // also checking the inverse of each set (indented) as we go.
    if( ( moveFrom == 'A' && pieceToJump == 'B' && moveTo == 'E') ||
          ( moveFrom == 'E' && pieceToJump == 'B' && moveTo == 'A') ||
        ( moveFrom == 'A' && pieceToJump == 'C' && moveTo == 'G') ||
          ( moveFrom == 'G' && pieceToJump == 'C' && moveTo == 'A') ||
        ( moveFrom == 'A' && pieceToJump == 'D' && moveTo == 'I') ||
          ( moveFrom == 'I' && pieceToJump == 'D' && moveTo == 'A') ||
        ( moveFrom == 'B' && pieceToJump == 'C' && moveTo == 'D') ||
          ( moveFrom == 'D' && pieceToJump == 'C' && moveTo == 'B') ||
        ( moveFrom == 'B' && pieceToJump == 'G' && moveTo == 'L') ||
          ( moveFrom == 'L' && pieceToJump == 'G' && moveTo == 'B') ||
        ( moveFrom == 'B' && pieceToJump == 'F' && moveTo == 'J') ||
          ( moveFrom == 'J' && pieceToJump == 'F' && moveTo == 'B') ||
        ( moveFrom == 'C' && pieceToJump == 'G' && moveTo == 'K') ||
          ( moveFrom == 'K' && pieceToJump == 'G' && moveTo == 'C') ||
        ( moveFrom == 'D' && pieceToJump == 'H' && moveTo == 'L') ||
          ( moveFrom == 'L' && pieceToJump == 'H' && moveTo == 'D') ||
        ( moveFrom == 'D' && pieceToJump == 'G' && moveTo == 'J') ||
          ( moveFrom == 'J' && pieceToJump == 'G' && moveTo == 'D') ||
        ( moveFrom == 'E' && pieceToJump == 'F' && moveTo == 'G') ||
          ( moveFrom == 'G' && pieceToJump == 'F' && moveTo == 'E') ||
        ( moveFrom == 'E' && pieceToJump == 'J' && moveTo == 'M') ||
          ( moveFrom == 'M' && pieceToJump == 'J' && moveTo == 'E') ||
        ( moveFrom == 'F' && pieceToJump == 'G' && moveTo == 'H') ||
          ( moveFrom == 'H' && pieceToJump == 'G' && moveTo == 'F') ||
        ( moveFrom == 'G' && pieceToJump == 'H' && moveTo == 'I') ||
          ( moveFrom == 'I' && pieceToJump == 'H' && moveTo == 'G') ||
        ( moveFrom == 'G' && pieceToJump == 'K' && moveTo == 'M') ||
          ( moveFrom == 'M' && pieceToJump == 'K' && moveTo == 'G') ||
        ( moveFrom == 'I' && pieceToJump == 'L' && moveTo == 'M') ||
          ( moveFrom == 'M' && pieceToJump == 'L' && moveTo == 'I') ||
        ( moveFrom == 'J' && pieceToJump == 'K' && moveTo == 'L') ||
          ( moveFrom == 'L' && pieceToJump == 'K' && moveTo == 'J')
      ) {
      return false;   // They ARE adjacent, so areNotAdjacent is false
    }
    else {
        return true;  // They are NOT adjacent, so areNotAdjacent is true
    }
} //end areNotAdjacent()


// ----------------------------------------------------------------------
// If the existing board piece does not match the valueToMatch, return true,
// else return false.  This is used in three situations:
//   1. The location being moved has a piece on it
//   2. The square being jumped has a piece on it
//   3. The destination square does not have a piece on it
bool doesNotMatch(
        char thePiece,      // Letter of the board position being checked
        char valueToMatch)  // What we're comparing it to ('#' or '.')
{
    // Use the position letter to get the board value, storing into theValue
    char theValue = ' ';
    switch( thePiece) {
        case 'A': theValue = pA; break;
        case 'B': theValue = pB; break;
        case 'C': theValue = pC; break;
        case 'D': theValue = pD; break;
        case 'E': theValue = pE; break;
        case 'F': theValue = pF; break;
        case 'G': theValue = pG; break;
        case 'H': theValue = pH; break;
        case 'I': theValue = pI; break;
        case 'J': theValue = pJ; break;
        case 'K': theValue = pK; break;
        case 'L': theValue = pL; break;
        case 'M': theValue = pM; break;
        // Sanity check
        default: cout << "Invalid value " << thePiece << "sent to fcn setValue.  Exiting.";
                exit( -1);
                break;
    } //end switch( thePiece)
    
    // Now do the comparison and return the appropriate value
    if( theValue != valueToMatch) {
        return true;
    }
    else {
        return false;
    }
} //end doesNotMatch()


// ----------------------------------------------------------------------
// Main section of program, containing main game play loop
int main() {
    displayInstructions();
    
    // Set board values to the default starting position
    initializeBoard();
    
    // Game play loop
    displayBoard();
    while( numberOfPieces > 1) {
        cout << moveNumber << ". "
             << "Enter positions from, jump, and to (e.g. EFG): ";
        cin >> moveFrom;        // Read just the first user input, handling inputs 'X' or 'R'
        moveFrom = toupper( moveFrom);   // Fold input into upper case to simplify comparisons
        
        // If 'X' to exit was chosen, break out of game play loop
        if( moveFrom == 'X') {
            cout << "Exiting" << endl;
            break;
        }
        
        // See if 'R' to reset the board was chosen
        if( moveFrom == 'R') {
            cout << "\n"
                 << "   *** Restarting"
                 << endl;
            initializeBoard();
            displayBoard();
            continue;   // jump up to the top of game play loop
        }

        // Since neither 'X' or 'R' were chosen as the first input, now also read
        // piece-to-jump and destination inputs.
        cin >> pieceToJump >> moveTo;
        pieceToJump = toupper( pieceToJump);   // Fold pieceToJump into upper case
        moveTo = toupper( moveTo);             // Fold moveTo into upper case
        
        // Ensure set of pieces (from, jump, to) are adjacent
        if( areNotAdjacent( moveFrom, pieceToJump, moveTo)) {
            // Give error message and jump back up to retry
            cout << "\n"
                 << "   *** Pieces must be adjacent. Please retry"
                 << endl
                 << endl;
            continue;   // Jump back up to the top of game play loop
        }
        
        // Ensure location we're moving FROM has a PlayerPiece in it
        if( doesNotMatch( moveFrom, PlayerPiece) ) {
            // Give error message and jump back up to retry
            cout << "\n"
                 << "   *** Source must have a piece. Please retry"
                 << endl
                 << endl;
            continue;   // Jump back up to the top of game play loop
        }
        
        // Ensure piece being jumped isn't blank
        if( doesNotMatch( pieceToJump, PlayerPiece) ) {
            // Give error message and jump back up to retry
            cout << "\n"
                 << "   *** Must jump a piece. Please retry"
                 << endl
                 << endl;
            continue;   // Jump back up to the top of game play loop
        }
        
        // Ensure location we're moving TO is blank
        if( doesNotMatch( moveTo, BlankPiece) ) {
            // Give error message and jump back up to retry
            cout << "\n"
                 << "   *** Destination must be blank. Retry"
                 << endl
                 << endl;
            continue;   // Jump back up to the top of game play loop
        }
        
        // Make the move, update number of pieces, and update the move number
        makeMove();
        moveNumber++;
        
        displayBoard();
    } //end while( numberOfPieces > 1)
    
    // Check for a win by seeing if there is exactly one piece left.
    if( numberOfPieces == 1) {
        cout << "\n"
             << "Congratulations, you did it!"
             << endl;
    }
    else {
         cout << "\n"
              << "Better luck next time."
              << endl;
    }
    
    cout << "Done." << endl;
    return 0;
} //end main()
