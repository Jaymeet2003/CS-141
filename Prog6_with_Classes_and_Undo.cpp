/* 	Program 6 - Unscrambler with Classes and undo

	The user will be presented with a board that is filled with scrambled words.
	They have to rotate the rows and columns to get the words displayed in the right order.

	Author: Dale Reed
    Date: 11/6/2021
    Class: CS 141, Fall 2021, UIC
    System: Xcode on iMac
    
    Running the program looks like:
        Program 6: Unscrambler Undo
        CS 141, Fall 2021, UIC
         
        You will be presented with a board that is filled with scrambled words.
        Rotate the rows and columns to get the words displayed in the right order.
        Press 'U' to undo moves.

        1192 words have been read in from the dictionary.
           Choose board size. It must be a single digit >=4: 4
           Choose single-digit number of times to scramble board: 1

               A   B   C   D         Goal Board
              ----------------     ---------------
           0 | b |   | o | m |    | b | o | o | m |
              ----------------     ---------------
           1 |   | o | o | o |    |   | t | o | o |
              ----------------     ---------------
           2 | c | t | p | i |    |   | p | i | c |
              ----------------     ---------------
           3 | k |   | t | o |    | k |   | t | o |
              ----------------     ---------------
           Board string: b om oooctpik to
            Goal string: boom too pick to
           List is: 1:b om oooctpik to

        Enter one of the following:
           R Rotate a row or column
           G Generate a new board with new random words
           U Undo most recent move
           Q to quit.
        1. Your choice:
        
    Test Cases each worth 11 points, except last one worth 12 points
    1. Board size 4, scramble 1, undo, exit: 4 1 u q
    2. Board size 4, scramble 1, undo, rotate b -1, rotate 3 -1  (should find solution): 4 1 u r b -1 r 3 -1
    3. Board size 4, scramble 1, undo, rotate b -1, undo, rotate b -1, rotate 3 -1  (should find solution): 4 1 u r b -1 u r b -1 r 3 -1
    4. Size 4, scramble 2, undo, rotate c 2, rotate 1 4, 1 3, rotate 2 -3, undo 4 times: 4 2 u r c 2 r 1 4 1 3 r 2 -3 u u u u q
    5. Size 5, scramble 3, undo, rotate d 1, generate, undo, quit:  5 3 u r d 1 g 4 1 r b 1 u q
    6. Hidden 1
       Size 9, scramble 6, undo, rotate I 8, undo, quit: 9 6 u r I 8 u q
    7. Hidden 2
       Size 5, scramble 3, rotate E 1, rotate 4 3, undo 3x, rotate 0 1, quit: 5 3 r E 1 r 4 3 u u u r 0 1 q
    8. Hidden 3
       Size 5, scramble 4, generate size 4 scramble 1, quit: 5 4 g 4 1 q
    9. Hidden 4
       Size 5, scramble 4, generate size 4 scramble 1, rotate a -1, rotate 2 -1 (should find solution): 5 4 g 4 1 r a -1 r 2 -1
*/

#include <iostream>		// For Input and Output
#include <fstream>		// For file input and output
#include <cassert>		// For the assert statement
#include <vector>		// For vectors
#include <iomanip>		// For setw() and setfill()
using namespace std;


//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
class Board {
    public:
        // Constructors
        Board() { }
        
        // Copy Constructor
        Board( const Board & oldBoard) {
            boardLetters = oldBoard.boardLetters;
            boardWords = oldBoard.boardWords;
            completedBoard = oldBoard.completedBoard;
            boardCharsPerSide = oldBoard.boardCharsPerSide;
            boardSize = oldBoard.boardSize;
        }
        
        // Getters
        string getBoardLetters() {  return boardLetters; }
        
        // Utility functions
        void display();                         // Display the board
        void rotateRowOnce( int rowToRotate);   // Rotate a row circularly horizontally once
        void rotateColOnce( int colToRotate);   // Rotate a column circularly vertically once
        void getRotationValuesAndMakeRotations();  // Get & validate rotation values and rotate
        void makeRotations( char rowOrCol, int numPositionsToRotate);  // Make the rotations
        void scrambleBoard();                   // Scramble the initial board
        void setUpBoards();                     // Get random words and set up board
        bool hasBeenSolved() {             // Returns true if board is finished, false otherwise
            return boardLetters == completedBoard;
        }
        // Read words into the dictionary. This belongs to the Board class but is declared as
        // static because it only access the static variable dictionaryWords.  When structured
        // this way it means it can be called from *outside* the class, using the Board:: scope
        // resolution operator.
        static void readWordsIntoDictionary();
        
    private:
        string boardLetters = "";     // The board letters
        vector<string> boardWords;    // List of words randomly selected from dictionary
        string completedBoard = "";   // What the board looks like when completed
        int boardCharsPerSide = 0;    // Size of the board per side
        int boardSize = 0;            // Size of the board, which is boardCharsPerSide x boardCharsPerSide
        static vector<string> dictionaryWords;
        
        // Private utility functions
        void selectRandomWords();
        void initializeBoardUsingRandomWords();
        void undoMove( char rowOrCol, int shiftAmount);     // Undo a move, reversing the original
}; //end class Board

// Vector to store dictionary words.  This is declared as static within the Board class so that
// there is only one dictionary vector shared among all the Boards, since we only need to read it once.
// It is *declared* within the Board class so all Board objects know about it, but needs the
// declaration here so that memory is allocated for it on the stack at compile time.
vector<string> Board::dictionaryWords;
                                       
                                        
//---------------------------------------------------------------------------
// Undo a move.
void Board::undoMove( char rowOrCol, int shiftAmount)
{
    // Reverse the shift
    shiftAmount = shiftAmount -1;
    // Undo the move by doing the reverse rotation of the original move
    makeRotations( rowOrCol, shiftAmount);
}


//---------------------------------------------------------------------------
// Select random words from the dictionary to be used for the board
void Board::selectRandomWords()
{
    int maxTotalLengthOfWords = boardCharsPerSide * boardCharsPerSide;
	string allWordsPlusSpaces = "";
 
    // Clear the random words vector, in case this is not the first time we do this.
    boardWords.clear();
	
	while( allWordsPlusSpaces.length() < maxTotalLengthOfWords) {
		// Get a random word from the dictionary
		int randomWordIndex = rand() % dictionaryWords.size();
		string randomWord = dictionaryWords.at( randomWordIndex);
		
		// Verify that this new word will not go past the end of the board
		if( (randomWord.length() + allWordsPlusSpaces.length()) > maxTotalLengthOfWords) {
			continue;
		}
		
		// Length of new word is okay, so add it
		boardWords.push_back( randomWord);
		allWordsPlusSpaces += randomWord + " "; // add space at the end to separate words
	} // end while(allWordsPlusSpaces.length()...
} // end selectRandomWords()


//---------------------------------------------------------------------------
// Set up the board based on the random words chosen from the dictionary
void Board::initializeBoardUsingRandomWords()
{
    // Create the board by concatenating all the words, with a space between them.
    int i;
    for( i=0; i<boardWords.size()-1; i++) {
        boardLetters = boardLetters + boardWords[ i] + " ";
    }
    // Separately append the last word, without a following blank, in case the words fit
    // perfectly without any extra blanks at the end.
    boardLetters = boardLetters + boardWords[ i];
    
    // Append extra spaces if needed so board ends up the right size.  This is only
    // needed if dictionary does not include small words, e.g. of length 1-4.
    while( boardLetters.size() < boardSize) {
        boardLetters += " ";
    }
} // end initializeBoard()


//---------------------------------------------------------------------------
// Rotate characters within a single row of the board
void Board::rotateRowOnce(
        int rowToRotate)        // 0..(n-1) where n is the size of one side of the square board
{
	// Calculate the indices on the board for the start and end of the row
	int rowStartingBoardIndex = rowToRotate * boardCharsPerSide;
	int rowEndingBoardIndex = rowStartingBoardIndex + boardCharsPerSide - 1;
    // Store the last element on the row, as shifting right will overwrite it
    char lastElement = boardLetters.at( rowEndingBoardIndex);
    
    // Shift all row elements to the right by one, starting from the
    // right, working our way back to the left.
    // E.g.      b e l o w
    //  becomes: w b e l o
    for( int i=rowEndingBoardIndex; i>rowStartingBoardIndex; i--) {
        boardLetters.at(i) = boardLetters.at( i-1);  // Overwrite element i with its left neighbor
    }
    // Overwrite the left-most element of the row with what used to be the last element
    boardLetters.at( rowStartingBoardIndex) = lastElement;
} // end rotateRow()


//---------------------------------------------------------------------------
// Rotate characters within a single column of the board
void Board::rotateColOnce(
        int colToRotate)        // 'A'..('A'+n-1) where n is the size of one side of the square board
{
	// Calculate the indices on the board for the start and end of the column
	int colStartingBoardIndex = colToRotate;
	int colEndingBoardIndex = colStartingBoardIndex + (boardCharsPerSide * (boardCharsPerSide - 1));
    // Store the last element in the column, as shifting down will overwrite it
    char bottomElement = boardLetters.at( colEndingBoardIndex);
		
    // Shift all column elements to down by one, starting from the
    // bottom, working our way back up to the top.
	// E.g.  b		w
	//		 e		b
	//		 l	==>	e
	//		 o		l
	//		 w		o
    for( int i=colEndingBoardIndex; i>colStartingBoardIndex; i = i - boardCharsPerSide) {
        boardLetters.at(i) = boardLetters.at( i-boardCharsPerSide);  // Overwrite element i with its above neighbor
    }
    // Overwrite the top-most element of the row with what used to be the last element
    boardLetters.at( colStartingBoardIndex) = bottomElement;
} // end rotateCol()


//---------------------------------------------------------------------------
// Do the user-selected board rotation consisting of the row number or column
// letter, followed by the number of rotations, which can be negative.
// E.g. 2 1 would rotate row 2 to the right by 1
//      a -2 would rotate the first column (column A) up by 2
void Board::makeRotations(
        char rowOrCol,              // '0'..'9' for rows, 'A'..'I' for columns
        int numPositionsToRotate)   // 1..sizePerRow-1 for number of rotations
{
    // If the number of rotations is negative, translate it to the corresponding positive amount.
    // E.g. In a 4x4 board, rotating a column up 1 (-1) is equivalent to shifting it down 4-1 = 3 times.
    //		In a 5x5 board, rotating a row left 3 (-3) is equivalent to shifting right 5-3 = 2 times
    if( numPositionsToRotate < 0) {
        numPositionsToRotate = boardCharsPerSide + numPositionsToRotate;
    }
    
    // User input has been validated and converted to a positive number of shifts.  Do this many shifts.
    for( int i=0; i<numPositionsToRotate; i++) {
        if( rowOrCol >= '0' && rowOrCol <= '0'+9) {
            // Convert the row value '0'..'9' to a numeric value 0..9
            rotateRowOnce(rowOrCol-'0');
        }
        else {
            // Convert the column value 'A'..'I' to a numeric value 0..9
            rotateColOnce(rowOrCol-'A');
        }
    } //end for( int i...
} //end makeRotations()


//---------------------------------------------------------------------------
// Validate rotation values, ensuring they are in range, and then call the
// function to do the rotation itself.
void Board::getRotationValuesAndMakeRotations()
{
	char rowOrCol = ' ';
	int numPositionsToRotate = 0;
	
    // Infinite loop to handle user input validation
    while( true) {
        cout << "   Enter the row/column to rotate, and # of (+/-) rotations: ";
        cin >> rowOrCol >> numPositionsToRotate;
        rowOrCol = toupper(rowOrCol);   // Convert rowOrCol value to upper-case.  Numbers don't end up changing.
        
        // See if rowOrCol is not within the valid range
        if( !( (rowOrCol >= '0' && rowOrCol <= '0'+boardCharsPerSide - 1) ||   // Row is within valid row range
               (rowOrCol >= 'A' && rowOrCol <= 'A'+boardCharsPerSide - 1)      // Column is within valid column range
             )
          ) {
            // It is not within the valid ragne
            cout << "   *** Row/column value is not within the valid range.  Retry." << endl;
            continue;
        }
        // Validate numeric shift amount is within range
        if( abs( numPositionsToRotate) > boardCharsPerSide - 1) {
            cout << "   *** Shift value should be between -" << boardCharsPerSide - 1
                 << " and " << boardCharsPerSide - 1 << ". Retry."
                 << endl;
            continue;
        }
        
        // Now that row/col and # of rotations validation tests have passed, break out of the loop
        break;
    } //end while( true)
    
    // Now that rotation values have been validated, make the rotations
    makeRotations( rowOrCol, numPositionsToRotate);
} //end validateRotationValues()


//---------------------------------------------------------------------------
// Scramble the board, based on the selected difficulty level
void Board::scrambleBoard()
{
    // Prompt for and get the number of board scrambling steps.  Each step does a random row
    // rotation and then a random column rotation.
    int numberOfScrambles = -1;
    // Loop to validate user input
    do {
        cout << "   Choose single-digit number of times to scramble board: ";
        cin >> numberOfScrambles;
        
        // Validate user input, reprompting if not one of the valid options
        if ( numberOfScrambles < 1 || numberOfScrambles > 9) {
            cout << "   *** The number of times must be a single digit >= 1. Retry." << endl;
        }
    } while( numberOfScrambles < 1 || numberOfScrambles > 9);

	// Rotate random rows and then a random column. Repeat this <numScrambles> times.
	for( int i=0; i < numberOfScrambles; i++) {
		// Rotate a random row
		int randRow = rand() % boardCharsPerSide;
		rotateRowOnce(randRow);
		
		// Rotate a random column
		int randCol = rand() % boardCharsPerSide;
		rotateColOnce(randCol);
	}
}// end scrambleBoard()


//---------------------------------------------------------------------------
// Clear the board, generate random words, initialize the board, store copy
// of completed board to use in checking for a win, scramble the initial
// board and store a copy to allow resetting the board.
//    All this is done in this function because it is done once at the
// beginning of the game, and is also done again if 'G' to generate a new
// board is chosen.
//
void Board::setUpBoards()
{
    // Prompt for and get board size
    do {
        cout << "   Choose board size. It must be a single digit >=4: ";
        cin >> boardCharsPerSide;
        
        // Validate input to be >= 4 and <= 9
        if( boardCharsPerSide < 4 || boardCharsPerSide > 9) {
            cout << "   *** The board size must be a single digit >=4. Retry." << endl;
        }
    } while( boardCharsPerSide < 4 || boardCharsPerSide > 9);

	// Blank out all initial boards, in case this is not the first time doing setup.
	boardLetters = "";      // Playing board
	completedBoard = "";    // Completed board, used to check for win
 
    // Reset the move number
    
    // Compute the board size from the boardCharsPerSide
    boardSize = boardCharsPerSide * boardCharsPerSide;
    
    // Generate the random words, store a copy of the completed board, create and store
    // a copy of the initial scrambled board.
    selectRandomWords();
    // Append the words onto the board, with spaces in between
    initializeBoardUsingRandomWords();
    
    // Store the completed board, to later allow checking for win
    completedBoard = boardLetters;
    
    // Scramble the board, prompting for the number of desired rotations, which sets the difficulty.
    scrambleBoard();
} //end setUpBoards()


//---------------------------------------------------------------------------
// Display the current board.  While we visualize the board as two-dimensional,
// we store it as a single string, with the rows concatenated after each other.
void Board::display()
{
    // Display the top column letters.  Also clear the fill character, otherwise
    // it could be leftover as '-' from the previous board display.
    cout << endl
         << "    " << setfill(' ');
    for( int i=0; i<boardCharsPerSide; i++) {
        cout << setw( 4) << (char)('A'+i);
    }
    // Display the heading above the solved board on the right
    cout << "         Goal Board";
    
	// Display the board character by character, formatted as a square board
	for( int row=0; row<boardCharsPerSide; row++) {
        // Display a separator row of dash characters, like: "--------------"
		cout << "  \n      " << setw(boardCharsPerSide*4+3) << setfill('-') << "   ";
        // Display a second row of dashes for the right-hand goal board
  		cout << "  " << setw(boardCharsPerSide*4+3) << setfill('-') << "\n   ";
      
        // Display the row number
        cout << row << "";
        
        // Display the working board values on the left
		for(int col=0; col<boardCharsPerSide; col++) {
			int index = row*boardCharsPerSide + col; // compute the index into the 1D board vector
			cout << " | " << boardLetters[index];
		}
		cout << " |   ";      // Last '|' at the end of each line.
  
        // Display the solved board values to the right
		for(int col=0; col<boardCharsPerSide; col++) {
			int index = row*boardCharsPerSide + col; // compute the index into the 1D board vector
			cout << " | " << completedBoard[index];
		}
		cout << " | ";      // Last '|' at the end of each line.
	}
 
    // Display the bottom line on the board
	cout << "\n      " << setw(boardCharsPerSide*4) << setfill('-') << "";
     // Display the bottom line on the Goal board to the right
	cout << "     " << setw(boardCharsPerSide*4) << setfill('-') << "\n";
	
	// Display the board characters and goal characters as strings.
	cout << "   Board string: " << boardLetters << endl;
 	cout << "    Goal string: " << completedBoard << endl;
} // end display()


//---------------------------------------------------------------------------
// Read in all the words from the dictionary file into a vector.
// This is declared in the class as a static function, as it only accesses
// the static dictionaryWords class variable, which is a single vector shared among
// all Board objects.
// Word list adapted from https://www.ef.com/wwen/english-resources/english-vocabulary/top-3000-words/
//
void Board::readWordsIntoDictionary()
{
        ifstream inStream;                  // Declare an input stream for reading
        inStream.open( "commonWords.txt");  // Open dictionary file
        assert( inStream.fail() == false );  // Ensure file open worked
        
        // Clear vector in case it already had some words in it
        dictionaryWords.clear();
        
        // Keep repeating while input from the file yields a word
        string newWord;                     // Store a single input word
        while( inStream >> newWord) {        // While there is another word to be read
            // Add this new word to the end of the vector, growing it in the process
            dictionaryWords.push_back(newWord);
        }
        
        // Close the dictionary file
        inStream.close();
        
        cout << dictionaryWords.size() << " words have been read in from the dictionary." << endl;
} //end readWordsIntoDictionary()



//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
class Node {
    public:
        // Constructor
        Node() {
            oldMoveNumber = 0;
            pNext = NULL;
        }
        
        Node( Board theBoard, int theMoveNumber, Node *&pHead) {
            oldBoard = theBoard;            // Node's oldBoard field is set to the current Board
            oldMoveNumber = theMoveNumber;  // Store the move number
            this->pNext = pHead;            // Link it at the front of the list
            pHead = this;                   // Set new list head to be the calling object
        }
        
        // Data members
        Board oldBoard;     // The old board
        int oldMoveNumber;  // The old move number
        Node *pNext;        // Node pointer to the next list Node
        
    private:
        // We're making everything public for now, to simplify your coding
}; //end class Node


//--------------------------------------------------------------------------------
// Display the move numbers on the linked list.
void displayList( Node *pTemp)
{
    cout << "   List is: ";
    
    while( pTemp != NULL) {
        cout << pTemp->oldMoveNumber << ":" << pTemp->oldBoard.getBoardLetters();
        // If there is another Node, display "->"
        if( pTemp->pNext != NULL) {
            cout << " -> ";
        }
        // Advance to next list node
        pTemp = pTemp->pNext;
    }
    cout << endl
         << endl;
} // end displayList()


//--------------------------------------------------------------------------------
// Delete the front node on the list and restore current game values from the
// next node that reflects the previous move. Return true if the delete succeeds,
// else return false.
// A precondition to calling this function should be that the list has more than
// one node on it.
void deleteFrontNodeFromList(
        Node *&pHead,      // Pointer to the head of the list, which will advance
        Board &theBoard,   // Game board to be restored
        int &moveNumber)   // Current move number to be restored from list
{
    // Sanity check: ensure there is more than one node (the starting node) on the list.
    // This should have been taken care of as a precondition to calling this function.
    if( pHead->pNext == NULL) {
        cout << "   *** List has only one Node, so precondition was not met.  Exiting ***" << "\n";
        exit (0);  // Exit program after error message is given, to allow debugging.
    }
    
    cout << "   * Undoing move * \n";
    // Keep track of old head of the list which will be deleted
    Node *pTemp = pHead;
    
    // Advance the head pointer to the next node on the list
    pHead = pHead->pNext;
    
    // Restore the previous board and the old move number
    theBoard = pHead->oldBoard;
    moveNumber = pHead->oldMoveNumber;
    
    // Delete the old head of the list
    delete pTemp;
} //end deleteNodeFromList()


//--------------------------------------------------------------------------------
// Create a new node and prepend it to the beginning of the list
void prependNodeToList(
        Node *&pHead,          // Pointer to head of list, which will change
        Board theBoard,        // The board, to be added to the list node
        int theMoveNumber)     // The moveNumber, to be added to the list node
{
    // Create a new node, store current values into it, and prepend at front of list.
    // We don't need to store it into anything, because pHead keeps track of it.
    new Node( theBoard, theMoveNumber, pHead);
} //end prependNodeToList()


//--------------------------------------------------------------------------------
// Traverse the list and delete all the Nodes on the list.  This is needed when
// we generate a new board.  We don't want to have a "memory leak" by leaving the
// space for the old list allocated, but no longer accessible.
void deleteList( Node *&pHead)
{
    Node *pTemp = NULL;
    
    // Traverse the list, deleting each node as we go.
    while( pHead != NULL) {
        pTemp = pHead;          // Keep track of the old node at the front of the list
        pHead = pHead->pNext;   // Advance head pointer to the next list node, if any
        delete pTemp;           // Free up the memory from the old front of list node
    }
} //end deleteList()


//---------------------------------------------------------------------------
//
int main()
{
	// For random number generation seed the random number generator to 1, so that results
    // are predictable.  To make results different every time instead you would
    // use srand( time( NULL));   Don't do this if you want your code to match test cases!
    srand( 1);
	
	vector<string> dictionaryWords;	// Vector to store the words from the dictionary
	char userInput = ' ';			// Character to read in the user input
    int moveNumber = 1;             // Move number, incremented after each valid move
      
    // Display program identification and overview.
    cout << "Program 6: Unscrambler Undo \n"
         << "CS 141, Fall 2021, UIC	     \n"
         << " \n"
         << "You will be presented with a board that is filled with scrambled words.    \n"
         << "Rotate the rows and columns to get the words displayed in the right order. \n"
         << "Press 'U' to undo moves.   \n"
         << endl;
    
    // Read dictionary words
    Board::readWordsIntoDictionary();
    
    // Create a Board object
    Board theBoard;
    // Get random words and setup the board
    theBoard.setUpBoards();
    
    // Put new board into Node at front of list
    Node *pHead = NULL;
    new Node( theBoard, moveNumber, pHead);

	// While the board has not yet been solved, prompt for and process user input
    while( ! theBoard.hasBeenSolved() ) {
    	theBoard.display();
        displayList( pHead);
    	
    	cout << "Enter one of the following: \n"
    		 << "   R Rotate a row or column \n"
    		 << "   G Generate a new board with new random words \n"
             << "   U Undo most recent move \n"
    		 << "   Q to quit. \n"
             << moveNumber << ". Your choice: ";
    	cin >> userInput;
    	userInput = toupper(userInput);
    	
        // Handle menu options
    	switch( userInput) {
            // 'Q' for Quit
    		case 'Q': {
    			cout << "Thank you for playing! Exiting program... \n" << endl;
                exit( 0);      // Exit the program.
				break;
			}
            // 'R' to rotate
			case 'R': {
				theBoard.getRotationValuesAndMakeRotations();
                
                // Increment move number
                moveNumber++;
                // Append new Node to the front of the list
                new Node( theBoard, moveNumber, pHead);
                
                // See if this move led to a win
                if( theBoard.hasBeenSolved()) {
                    theBoard.display();     // Display the final solved board
                    cout << endl
                         << "Congratulations, you won! \n"
                         << "Exiting program... \n"
                         << endl;
                }
				break;
			}
            // 'G' to generate a new board with new random words
			case 'G': {
                // Select random words and setup all the boards
                theBoard = Board();   // Call default constructor to reset the board
                // Get random words and setup the board
                theBoard.setUpBoards();
                
                deleteList( pHead);  // Delete the nodes on the existing list
                moveNumber = 1;      // Reset the move number
                
                // Put new board into Node at front of list
                pHead = NULL;
                new Node( theBoard, moveNumber, pHead);
				break;
			}
            // 'U' to undo most recent move
            case 'U': {
                if( pHead->pNext == NULL) {
                    cout << "   *** You cannot undo past the beginning of the game.  Retry. ***" << "\n";
                    continue;  // Loop back up to retry
                }
                deleteFrontNodeFromList( pHead, theBoard, moveNumber);
                break;
            }
            default: {
				cout << "You did not enter one of the valid options. Try again." << endl;
				break;
			}
		} //end switch( userInput)

    } // end while( ! theBoard.hasBeenSolved() )
		
	return 0;
} //end main()
