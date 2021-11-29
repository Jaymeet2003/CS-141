/*	Program 5 - Unscrambler

	The user will be presented with a board that is filled with scrambled words.
	They have to rotate the rows and columns to get the words displayed in the right order.

	Author: Ellen Kidane
    Date: 11/3/2021
    Class: CS 141, Fall 2021, UIC
    System: DevC++ on Windows10
*/

#include <iostream>		// For Input and Output
#include <fstream>		// For file input and output
#include <cassert>		// For the assert statement
#include <vector>		// For vectors
#include <iomanip>		// For setw() and setfill()
#include <algorithm>	// For sorting the dictionary (used for binary search with the extra credit)
using namespace std;


//--------------------------------------------------------------------------------
// Display welcome message, introducing the user to the program
void displayWelcomeMessage()
{
    cout << "Program 5: Unscrambler	\n"
         << "CS 141, Fall 2021, UIC	\n"
         << " \n"
         << "You will be presented with a board that is filled  \n"
    	 << "with scrambled words. Rotate the rows and columns  \n"
    	 << "to get the words displayed in the right order.     \n"
    	 << endl;
}//end displayWelcomeMessage()


//---------------------------------------------------------------------------
// Read in all the words from the dictionary file into a vector
void readWordsIntoDictionary(
        vector <string> & dictionary,   // Dictionary where words will be stored
        string fileName)                // File name where words will be read from
{
    ifstream inStream;                  // Declare an input stream for reading
    inStream.open( fileName);            // Open dictionary file
    assert( inStream.fail() == false );  // Ensure file open worked
    
    // Clear vector in case it already had some words in it
    dictionary.clear();
    
    // Keep repeating while input from the file yields a word
    string newWord;                     // Store a single input word
    while( inStream >> newWord) {        // While there is another word to be read
        // Add this new word to the end of the vector, growing it in the process
        dictionary.push_back(newWord);
    }
    
    // Close the dictionary file
    inStream.close();
} //end readWordsIntoDictionary()


//--------------------------------------------------------------------------------
// Prompt the user for their chosen board size (>=4) and return it
int getBoardSizeFromUser()
{
	int boardSizeChosen = 0;
    
    do {
        cout << "Choose your board size (must be a number greater than or equal to 4): ";
        cin >> boardSizeChosen;
        
        // Validate input to be >= 4
        if( boardSizeChosen < 4) {
            cout << "The board size must be at least 4. Retry." << endl;
        }
    } while( boardSizeChosen < 4);
    
    return boardSizeChosen;
} //end getBoardSizeFromUser()


//--------------------------------------------------------------------------------
// Prompt the user for their chosen number of scrambles and return it
int getNumScrambles()
{
    int numScramblesChosen = -1;
    
    do {
        cout << "Choose the number of times you would like the board to be scrambled (must be a single number >= 1): ";
        cin >> numScramblesChosen;
        
        // Validate user input, reprompting if not one of the valid options
        if ( numScramblesChosen < 1) {
            cout << "The number of times you select must be at least 1. Retry." << endl;
        }
    } while( numScramblesChosen < 1);
    
    return numScramblesChosen;
}//end getNumScrambles()


//---------------------------------------------------------------------------
// Select random words from the dictionary to be used for the board
void generateRandomWords(
		vector<string> dictionaryWords,	    // Vector of dictionary words
		vector<string> &wordsChosen,		// Vector to store and return the words that were randomly chosen
		int maxTotalLengthOfWords)			// Max total length of all the words plus spaces
{
	string allWordsPlusSpaces = "";
 
    // Clear the random words vector, in case this is not the first time we do this.
    wordsChosen.clear();
	
	while( allWordsPlusSpaces.length() < maxTotalLengthOfWords) {
		// Get a random word from the dictionary
		int randomWordIndex = rand() % dictionaryWords.size();
		string randomWord = dictionaryWords.at( randomWordIndex);
		
		// Verify that this new word will not go past the end of the board
		if( (randomWord.length() + allWordsPlusSpaces.length()) > maxTotalLengthOfWords) {
			continue;
		}
		
		// Length of new word is okay, so add it
		wordsChosen.push_back( randomWord);
		allWordsPlusSpaces += randomWord + " "; // add space at the end to separate words
		
		// Check if we have enough space to add another word or not because the
		// shortest words are 3 letters long so we need at least that many spaces.
		if( allWordsPlusSpaces.length() >= maxTotalLengthOfWords - 2) {	 // Less than 3 characters left
			// No space for another word, so we are done
			return;
		}
	} // end while(allWordsPlusSpaces.length()...
    
} // end generateRandomWords()


//---------------------------------------------------------------------------
// Print the words that will be used in the board
void printBoardWords(vector<string> wordsChosen)
{
	cout << "These are the words that you should try to spell out using the board, in order: \n";
    cout << "   ";
	for( int i=0; i<wordsChosen.size() - 1; i++) {
		cout << wordsChosen.at(i) << ", ";
	}
	// Print the last word outside of the loop so that there is no comma after it
	cout << wordsChosen.at(wordsChosen.size()-1) << "." << endl;
	cout << endl;
} // end printBoardWords()


//---------------------------------------------------------------------------
// Set up the board based on the random words chosen from the dictionary
void initializeBoard(
        vector<char> &theBoard,             // The board changes
        const vector<string> &wordsChosen,  // Efficiency of pass by const reference
        int boardSize)                      // The size of one of the sides of the square board
{
	
	// Initialize board to be all spaces
	for(int i=0; i<(boardSize*boardSize); i++) {
		theBoard[i] = ' ';
	}
	
	int boardIndex = 0;
	
	// Go through each of the chosen words
	for(int i=0; i<wordsChosen.size(); i++) {
		string oneWord = wordsChosen.at(i);
        
		// Sequentially add each character of each chosen word to the board
		for( int j=0; j<oneWord.size(); j++) {
			theBoard[ boardIndex] = oneWord.at(j);
			boardIndex++;
		}
		// Add a space after each word
		theBoard[ boardIndex] = ' ';
		boardIndex++;
	}
} // end initializeBoard()


//---------------------------------------------------------------------------
// Display the current board.  While we visualize the board as two-dimensional,
// we store it as one-dimensional, with the rows concatenated after each other.
void displayBoard(
        const vector<char> & theBoard,   // Pass by const reference for efficiency
        int boardSize)                   // Size of one side of the square board
{
    // Display the top column numbers.  Also clear the fill character, otherwise
    // it could be leftover as '-' from the previous board display.
    cout << "    " << setfill(' ');
    for( int i=0; i<boardSize; i++) {
        cout << setw( 4) << i;
    }
	// Display the board character by character, formatted as a square board
	for( int row=0; row<boardSize; row++) {
        // Display a separator row of dash characters, like: "--------------"
		cout << "  \n      " << setw(boardSize*4+3) << setfill('-') << "\n   ";
        // Display the row number
        cout << row << "";
		for(int col=0; col<boardSize; col++) {
			int index = row*boardSize + col; // compute the index into the 1D board vector
			cout << " | " << theBoard[index];
		}
		cout << " | ";      // Last '|' at the end of each line.
	}
	cout << "\n      " << setw(boardSize*4) << setfill('-') << "\n";
	
	// Display the board characters as a single connected string.
	// Note that the board already includes spaces, so we do not need to add any to the output below
	cout << "Current board words: ";
	for( int row=0; row<boardSize; row++) {
		for( int col=0; col<boardSize; col++) {
			int index = row*boardSize + col; // compute the index into the 1D board vector
			cout << theBoard[index];
		}
	}
	cout << endl << endl;
} // end displayBoard()


//---------------------------------------------------------------------------
// Rotate characters within a single row of the board
void rotateRow(
        vector<char> & theBoard,    // 1-D storage of the board
        int rowToRotate,            // 0..(n-1) where n is the size of one side of the square board
        int boardSize)              // Size of one side of the square board
{
	// Calculate the indices on the board for the start and end of the row
	int rowStartingBoardIndex = rowToRotate * boardSize;
	int rowEndingBoardIndex = rowStartingBoardIndex + boardSize - 1;
    // Store the last element on the row, as shifting right will overwrite it
    char lastElement = theBoard.at( rowEndingBoardIndex);
    
    // Shift all row elements to the right by one, starting from the
    // right, working our way back to the left.
    // E.g.      b e l o w
    //  becomes: w b e l o
    for( int i=rowEndingBoardIndex; i>rowStartingBoardIndex; i--) {
        theBoard.at(i) = theBoard.at( i-1);  // Overwrite element i with its left neighbor
    }
    // Overwrite the left-most element of the row with what used to be the last element
    theBoard.at( rowStartingBoardIndex) = lastElement;
} // end rotateRow()


//---------------------------------------------------------------------------
// Rotate characters within a single column of the board
void rotateCol(vector<char> & theBoard, int colToRotate, int boardSize) {
	
	// Calculate the indices on the board for the start and end of the column
	int colStartingBoardIndex = colToRotate;
	int colEndingBoardIndex = colStartingBoardIndex + (boardSize*(boardSize - 1));
    // Store the last element in the column, as shifting down will overwrite it
    char bottomElement = theBoard.at( colEndingBoardIndex);
		
    // Shift all column elements to down by one, starting from the
    // bottom, working our way back up to the top.
	// E.g.  b		w
	//		 e		b
	//		 l	==>	e
	//		 o		l
	//		 w		o
    for( int i=colEndingBoardIndex; i>colStartingBoardIndex; i = i - boardSize) {
        theBoard.at(i) = theBoard.at( i-boardSize);  // Overwrite element i with its above neighbor
    }
    // Overwrite the top-most element of the row with what used to be the last element
    theBoard.at( colStartingBoardIndex) = bottomElement;
} // end rotateCol()


//---------------------------------------------------------------------------
// Handle the rotation menu option that the user chooses.
// Each move has a letter (R or C) followed by two numbers,
//		the first representing the row/column number and 
//		the second representing the number of positions to rotate (including negative values).
// E.g. R 2 1 would rotate row 2 to the right by 1
//      c 1 -2 would rotate column 1 down by -2, i.e. up by 2
void handleRotation(vector<char> &theBoard, int boardSize)
{
	char rowOrCol = ' ';
	int rowOrColNum = -1;
	int numPositionsToRotate = 0;
	
    // Infinite loop to handle invalid user input. Valid input returns from function.
    while( true) {
        cout << "\n"
             << "   Enter the row/column you would like to rotate, and the number of positions to rotate by.\n"
             << "   This should be in the format of <R or C> <row/column number> <number of positions to rotate>, \n"
             << "   where valid row and column numbers are between 0 and " << boardSize - 1 << ", \n"
             << "   E.g. R 0 1 would rotate the top row (row 0) of the board to the right once, \n"
             << "        c 1 -2 would rotate the second column (col 1) of the board upwards twice. \n"
             << "   Your choice: ";
        cin >> rowOrCol;
        cin >> rowOrColNum;
        cin >> numPositionsToRotate;
        rowOrCol = toupper(rowOrCol);
        
        // Validate user input of 'R' or 'C'
        if( rowOrCol != 'R' && rowOrCol != 'C') {
            cout << "   First input must be 'R' or 'C'. Try again." << endl;
            continue;
        }
        // Validate row/col number is in range
        if( rowOrColNum < 0 || rowOrColNum >= boardSize) {
            cout << "   Number must be between 0 and " << boardSize - 1 << ". Try again." << endl;
            continue;
        }
        
        // If the number of rotations is negative, translate it to the positive amount
        // E.g. in a 4x4 board, rotating a column -1 is equivalent to shifting it down 3 times
        //		in a 5x5 board, rotating a row -6 is equivalent to shifting it by -1, 
		//						and also equivalent to shifting it right 4 times
        do {
        	if( numPositionsToRotate < 0) {
	        	numPositionsToRotate = boardSize + numPositionsToRotate;
			}
		} while( numPositionsToRotate < 0);
        
        // Now that user input has been validated, do the appropriate shift 
		// for the appropriate number of times
        if( rowOrCol == 'R') {
        	for( int i=0; i<numPositionsToRotate; i++) {
        		rotateRow(theBoard, rowOrColNum, boardSize);
			}
            break;  // break out of infinite move validation loop
        }
        else if(rowOrCol == 'C') {
        	for( int i=0; i<numPositionsToRotate; i++) {
        		rotateCol(theBoard, rowOrColNum, boardSize);
			}
            break;  // break out of infinite move validation loop
        }

    } //end while( true)
} //end handleRotation()


//---------------------------------------------------------------------------
// Scramble the board based on the difficulty level
void scrambleBoard(
        vector<char> &theBoard,   // The 1-D board to be scrambled
        int boardSize,            // Length of one of the sides of the square board
        int numScrambles)         // Number of rotations to be used in the scrambling algorithm
{
	// Rotate <numScrambles> random rows and <numScrambles> random columns,
	// 		alternating between row and column
	for( int i=0; i<numScrambles; i++) {
		
		// Rotate a random row
		int randRow = rand() % boardSize;
		rotateRow(theBoard, randRow, boardSize);
		
		// Rotate a random column
		int randCol = rand() % boardSize;
		rotateCol(theBoard, randCol, boardSize);
	}	
}// end scrambleBoard()


//---------------------------------------------------------------------------
// Check to see if the user won, by comparing moves board to original completed board.
bool checkForWin(
        const vector<char> &theBoard,        // The 1-D playing board, passed by const reference for efficiency
        const vector<char> &completedBoard)  // The 1-D completed board, passed by const reference for efficiency
{
	for(int i=0; i<theBoard.size(); i++) {
		if(theBoard.at(i) != completedBoard.at(i)) {
			return false;
		}
	}
	return true;
} // end checkForWin()

//---------------------------------------------------------------------------
// Clear the board, generate random words, initialize the board, store copy
// of completed board to use in checking for a win, scramble the initial
// board and store a copy to allow resetting the board.
//    All this is done in this function because it is done once at the
// beginning of the game, and is all done again if 'G' to generate a new
// board is chosen.
//
void setUpBoards(
        vector<string> dictionaryWords,
        vector<string> &boardWords,
        vector<char> &theBoard,
        vector<char> &completedBoard,
        vector<char> &beginningBoard,
        int boardSize,
        int numScrambles)
{
    int numBoardSlots = boardSize * boardSize;		// Total number of slots on the board
    
    // Generate the random words, store a copy of the completed board, create and store
    // a copy of the initial scrambled board.
    generateRandomWords( dictionaryWords, boardWords, numBoardSlots);
    initializeBoard(theBoard, boardWords, boardSize);
    completedBoard = theBoard; // Store the completed board, to later allow checking for win
    // Now scramble the board
    scrambleBoard(theBoard, boardSize, numScrambles);
    beginningBoard = theBoard; // Store the beginning scrambled board, to allow resetting it later
} //end setUpBoards()

//--------------------------------------------------------------------------------
// Use binary search to look up a search word in the dictionary vector, returning
// the index if found, -1 otherwise.
// (Used for menu option 'S' which is extra credit)
long binarySearch( string searchWord,            		// Word we are searching for
                   const vector< string> &dictionary)   // Dictionary of words as a vector, passed by const reference for efficiency
{
    long low, mid, high;    // array indices for binary search
    int searchResult = -1;  // Stores index of word if search succeeded, else -1
    int guessNumber = 1;    // Used to display the number of guesses
    
    // Binary search for word
    low = 0;
    high = dictionary.size() - 1;
    while( low <= high)  {
        mid = (low + high) / 2;
        // searchResult negative value means word is to the left, positive value means
        // word is to the right, value of 0 means word was found
        searchResult = searchWord.compare( dictionary[ mid]);
        if ( searchResult == 0)  {
            // Word IS in dictionary, so return the index where the word was found
            return mid;
        }
        else if (searchResult < 0)  {
            high = mid - 1; // word should be located prior to mid location
        }
        else  {
            low = mid + 1; // word should be located after mid location
        }
    } //end while( low...
    
    // Word was not found
    return -1;
}//end binarySearch()

//---------------------------------------------------------------------------
// Prompt the user for the board that they would like to have automatically solved,
// and read this into a board
// (Used for menu option 'S' which is extra credit)
void getBoard(
		vector<char> &theBoard, 			// The 1-D board to be filled in
		int boardSize)                      // The size of one of the sides of the square board
{
	string userBoardInput;
	cout << "Enter the board to be automatically solved, as a single connected string:" << endl;
	cin.ignore();
	getline(cin, userBoardInput);	// reads in the whole line of user input, including spaces
	
	// Initialize the board using the input
	int boardIndex = 0;
	// Sequentially add each character of the user input to the board
	for( int i=0; i<userBoardInput.size(); i++) {
		theBoard[ boardIndex] = userBoardInput.at(i);
		boardIndex++;
	}
	
} // end getBoard()

//---------------------------------------------------------------------------
// Split up the board into words, separating by whitespace, and saving
// all the words into a single vector
// (Used for menu option 'S' which is extra credit)
void splitBoardIntoVector(
		vector<string> &wordsInBoard,		// The vector of words contained in the board, which changes
		const vector<char> &theBoard, 		// The 1-D board, passed by const reference for efficiency
		int boardSize)                      // The size of one of the sides of the square board
{
	int boardIndex = 0;
	string tempString = "";
	
	while(boardIndex < theBoard.size()) {
		
		// Add a word to the vector
		// We know when we have reached the end of a word when the current character
		// is a space, but the tempString has some characters in it
		if( (theBoard.at(boardIndex) == ' ') && (tempString.size() != 0) ) {
			wordsInBoard.push_back(tempString);
			tempString = "";
		}
		// Skip space characters - this handles multiple spaces in a row
		else if(theBoard.at(boardIndex) == ' ') {
			boardIndex++;
			continue;
		}
		// Add other characters to the tempString
		else {
			tempString += theBoard.at(boardIndex);
		}
		
		boardIndex++;
	}
	
	// If there is a word at the end of the board without spaces after it,
	// also add this word to the vector
	// (it was not added in the loop above)
	if(tempString.length() != 0) {
		wordsInBoard.push_back(tempString);
	}
	
} // end splitBoardIntoVector()

//---------------------------------------------------------------------------
// Check if the board is solved, and returns true if it is, and false otherwise.
// This is done by splitting up the board into words, and verifying if all
// the words are in the dictionary by means of binary search.
// (Used for menu option 'S' which is extra credit)
bool isBoardSolved(
		const vector<string> &dictionaryWords,	// The dictionary, passed by const reference for efficiency
		const vector<char> &theBoard, 			// The 1-D board, passed by const reference for efficiency
		int boardSize)                      	// The size of one of the sides of the square board
{
	vector<string> wordsInBoard(0);
	splitBoardIntoVector(wordsInBoard, theBoard, boardSize);
	
	// Go through all the words in the board
	for(int i=0; i < wordsInBoard.size(); i++){
		// If this word is not in the dictionary, return false
		string currentWord = wordsInBoard.at(i);
		if( binarySearch(currentWord, dictionaryWords) == -1) {
			return false;
		}
	}
	
	// All the words have been found in the dictionary
	// So the board is solved - return true
	return true;
	
}// end isBoardSolved()

//---------------------------------------------------------------------------
// Prompt the user for a board, and automatically solve it.
// Returns true if the board was able to be solved, and false if not.
// This is done by trying various possibilities of moves to solve the board,
// and checking to see if the resulting board is made up of dictionary words
// (Used for menu option 'S' which is extra credit)
bool automaticSolver(
		const vector<string> &sortedDictionaryWords,	// The dictionary, passed by const reference for efficiency
		int boardSize)									// The size of one of the sides of the square board
{
	// Initialize the board to be solved based on user input
	vector<char> theBoardToSolve(boardSize*boardSize);
	getBoard(theBoardToSolve, boardSize);
	cout << "Checking for a solution..." << endl;	
	
	// Check if the board is already solved
	if ( isBoardSolved(sortedDictionaryWords, theBoardToSolve, boardSize) ) {
		cout << "Solution found! The complete board is:" << endl;
		displayBoard(theBoardToSolve, boardSize);
		return true;
	}
	
	vector<char> beginningBoardToSolve(theBoardToSolve);
	
	// Assuming the board was scrambled ONCE,
	// try all possible combinations of rotations
	for(int col=0; col<boardSize; col++) {
		
		for(int row=0; row<boardSize; row++) {
			
			// Reset the board back to how it was before any rotations
			theBoardToSolve = beginningBoardToSolve;
			
			// Rotate the current column by -1
			for( int i=0; i<(boardSize-1); i++) {
	    		rotateCol(theBoardToSolve, col, boardSize);
			}
			
			// Rotate the current row by -1
			for( int i=0; i<(boardSize-1); i++) {
	    		rotateRow(theBoardToSolve, row, boardSize);
			}	
			
			// If the board is solved by rotating this row/col combination,
			// display the solution and return true
			if ( isBoardSolved(sortedDictionaryWords, theBoardToSolve, boardSize) ) {
				cout << "Solution found! The complete board is:" << endl;
				displayBoard(theBoardToSolve, boardSize);
				return true;
			}
		} // end for(int row...
	} // end for(int col...


	// Assuming the board was scrambled TWICE,
	// try all possible combinations of rotations
	for(int col1=0; col1<boardSize; col1++) {
		for(int row1=0; row1<boardSize; row1++) {
			for(int col2=0; col2<boardSize; col2++) {
				for(int row2=0; row2<boardSize; row2++) {
			
					// Reset the board back to how it was before any rotations
					theBoardToSolve = beginningBoardToSolve;
					
					// Rotate the first column by -1
					for( int i=0; i<(boardSize-1); i++) {
			    		rotateCol(theBoardToSolve, col1, boardSize);
					}
					
					// Rotate the first row by -1
					for( int i=0; i<(boardSize-1); i++) {
			    		rotateRow(theBoardToSolve, row1, boardSize);
					}	
					
					// Rotate the second column by -1
					for( int i=0; i<(boardSize-1); i++) {
			    		rotateCol(theBoardToSolve, col2, boardSize);
					}
					
					// Rotate the second row by -1
					for( int i=0; i<(boardSize-1); i++) {
			    		rotateRow(theBoardToSolve, row2, boardSize);
					}
					
					// If the board is solved by rotating this row/col combination,
					// display the solution and return true
					if ( isBoardSolved(sortedDictionaryWords, theBoardToSolve, boardSize) ) {
						cout << "Solution found! The complete board is:" << endl;
						displayBoard(theBoardToSolve, boardSize);
						return true;
					}
				} // end for(int row2...
			} // end for(int col2...
		} // end for(int row1...
	} // end for(int col1...

	// Assuming the board was scrambled THREE times,
	// try all possible combinations of rotations
	for(int col1=0; col1<boardSize; col1++) {
		for(int row1=0; row1<boardSize; row1++) {
			for(int col2=0; col2<boardSize; col2++) {
				for(int row2=0; row2<boardSize; row2++) {
					for(int col3=0; col3<boardSize; col3++) {
						for(int row3=0; row3<boardSize; row3++) {
			
							// Reset the board back to how it was before any rotations
							theBoardToSolve = beginningBoardToSolve;
							
							// Rotate the first column by -1
							for( int i=0; i<(boardSize-1); i++) {
					    		rotateCol(theBoardToSolve, col1, boardSize);
							}
							
							// Rotate the first row by -1
							for( int i=0; i<(boardSize-1); i++) {
					    		rotateRow(theBoardToSolve, row1, boardSize);
							}	
							
							// Rotate the second column by -1
							for( int i=0; i<(boardSize-1); i++) {
					    		rotateCol(theBoardToSolve, col2, boardSize);
							}
							
							// Rotate the second row by -1
							for( int i=0; i<(boardSize-1); i++) {
					    		rotateRow(theBoardToSolve, row2, boardSize);
							}

							// Rotate the third column by -1
							for( int i=0; i<(boardSize-1); i++) {
					    		rotateCol(theBoardToSolve, col3, boardSize);
							}
							
							// Rotate the third row by -1
							for( int i=0; i<(boardSize-1); i++) {
					    		rotateRow(theBoardToSolve, row3, boardSize);
							}
							
							// If the board is solved by rotating this row/col combination,
							// display the solution and return true
							if ( isBoardSolved(sortedDictionaryWords, theBoardToSolve, boardSize) ) {
								cout << "Solution found! The complete board is:" << endl;
								displayBoard(theBoardToSolve, boardSize);
								return true;
							}
						} // end for(int row3...
					} // end for(int col3...
				} // end for(int row2...
			} // end for(int col2...
		} // end for(int row1...
	} // end for(int col1...
	
	// Solution was not found, so return false
	return false;
			
}// end automaticSolver()

//---------------------------------------------------------------------------
//
int main()
{
	// For random number generation seed the random number generator to 1, so that results
    // are predictable.  To make results different every time instead you would
    // use srand( time( NULL));   Don't do this if you want your code to match test cases!
    srand( 1);
	
	vector<string> dictionaryWords;					// Vector to store the words from the dictionary
	vector<string> sortedDictionaryWords(0);		// Vector to store the words from the dictionary, sorted for use in binary search
	vector<string> boardWords;						// Vector to store the random words chosen to be included in the board
	int boardSize = 5;								// Default number of rows and columns of the board
	int numBoardSlots = boardSize * boardSize;		// Total number of slots on the board
	vector<char> theBoard( numBoardSlots);			// 1D vector to store the board characters that change with moves.
	vector<char> beginningBoard( numBoardSlots);	// 1D vector to store the beginning scrambled board.  Used to reset board.
	vector<char> completedBoard( numBoardSlots);	// 1D vector to store what the completed board should look like.
                                                    //    Used to check for a win, where after moves the board matches.
	char userInput = ' ';							// Character to read in the user input
      
    displayWelcomeMessage();
    
    // Read in all the words from dictionary.txt file into a vector
    readWordsIntoDictionary( dictionaryWords, "dictionary-3to5-letters.txt");
    cout << dictionaryWords.size() << " words have been read in from the dictionary.\n" << endl;
	
    // Prompt initial user input, to allow testing just the reading of words.
    cout << "Enter Q to quit or B to begin: ";
    cin >> userInput;
    userInput = toupper(userInput);
    
    // User input was 'Q' so exit the program
    if(userInput == 'Q') {
    	cout << "Thank you for playing! \n"
    	     << "Exiting program... \n"
             << endl;
    	return 0;
	}
	
	// Ask the user for their chosen board size
	boardSize = getBoardSizeFromUser();
	numBoardSlots = boardSize * boardSize;
	
	// Use that board size to allocate space for the various board representations
	theBoard.resize( numBoardSlots);        // Playing board
	beginningBoard.resize( numBoardSlots);  // Beginning scrambled board, used to reset the board
	completedBoard.resize( numBoardSlots);  // Completed board, used to check for win
        
	// Ask the user for how many rotations they would like to be used for the scrambling of the board.
    int numScrambles = getNumScrambles();
    
    // Select random words and setup all the boards
    setUpBoards( dictionaryWords, boardWords, theBoard, completedBoard, beginningBoard, boardSize, numScrambles);

	// Loop to prompt for and process user input
    while(true) {
    	printBoardWords( boardWords);
    	cout << "Current board: \n";
    	displayBoard( theBoard, boardSize);
    	
    	cout << "Enter one of the following: \n"
    		 << "   R to rotate a row or column, \n"
    		 << "   C to view what the completed board should look like, \n"
    		 << "   B to reset the board back to the beginning, \n"
    		 << "   G to generate a new board with new random words, \n"
    		 << "   S to have the computer automatically solve a board that you enter (5 points extra credit), \n"
    		 << "   Q to quit. \n"
             << "Your choice: ";
    	cin >> userInput;
    	userInput = toupper(userInput);
    	
        // Handle menu options
    	switch( userInput) {
            // 'Q' for Quit
    		case 'Q': {
    			cout << "Thank you for playing! \n"
                     << "Exiting program... \n"
                     << endl;
    			return 0;
				break;
			}
            // 'R' to rotate
			case 'R': {
				handleRotation( theBoard, boardSize);
				break;
			}
            // 'C' to view completed board
			case 'C': {
				cout << "The completed board should look like: " << endl;
				displayBoard( completedBoard, boardSize);
				break;
			}
            // 'B' to view beginning board
			case 'B': {
				theBoard = beginningBoard;
				break;
			}
            // 'G' to generate a new board with new random words
			case 'G': {
                // Select random words and setup all the boards
                setUpBoards( dictionaryWords, boardWords, theBoard, completedBoard, beginningBoard, boardSize, numScrambles);
				break;
			}
			// 'S' to prompt the user for a board and have the computer automatically solve it
			case 'S' : {
				
				// If the dictionary has not yet been sorted
				if(sortedDictionaryWords.size() == 0) {
					// Sort the dictionary so that it will work with binary search
					// Make sure that the dictionary is restored to original order,
					// in case new random words are chosen for a board in the next menu option
					vector<string> tempVector = dictionaryWords;
					sort(dictionaryWords.begin(), dictionaryWords.end());
					sortedDictionaryWords = dictionaryWords;
					dictionaryWords = tempVector;
				}
						
				// Ask the user for the board and try to automatically solve it
				bool solutionFound = automaticSolver( sortedDictionaryWords, boardSize);
				// Print a message in case the solution was not found
				if(!solutionFound) {
					cout << "A solution was not found. The board should be entered in properly"
						 << " with all spaces, and should have been scrambled 1-3 times." << endl;
				}
				break;
			}
			default: {
				cout << "You did not enter one of the valid options. Try again." << endl;
				break;
			}
		} //end switch( userInput)
        
    	if( checkForWin( theBoard, completedBoard)) {
    		displayBoard( theBoard, boardSize);
    		cout << "Congratulations, you won! Thank you for playing!" << endl;
    		cout << "Exiting program..." << endl;
    		return 0;
		}
		    	
	} // end while(true)
		
	return 0;
} //end main()
