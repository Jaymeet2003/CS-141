/*  Program 6 - Unscrambler (no classes, no undo)

    The user is presented with a board that is filled with scrambled words.
    They have to rotate the rows and columns to get the words displayed in the right order.

    Author: Jaymeet Patel
    Date: 27 Nov 2021
    Class: CS 141, Fall 2021, UIC
    System: VSCode on Windows

    Running the program looks like:
        Program 6: Unscrambler Undo
        CS 141, Fall 2021, UIC
         
        You will be presented with a board that is filled with scrambled words.
        Rotate the rows and columns to get the words displayed in the right order.
        Press 'U' to undo moves.

        1192 words have been read in from the dictionary.
           Choose board size. It must be a single digit >=4: 4
           Choose single-digit number of times to scramble board: 1

               A   B   C   D         Goal Board
              ----------------     ---------------
           0 | b |   | o | m |    | b | o | o | m |
              ----------------     ---------------
           1 |   | o | o | o |    |   | t | o | o |
              ----------------     ---------------
           2 | c | t | p | i |    |   | p | i | c |
              ----------------     ---------------
           3 | k |   | t | o |    | k |   | t | o |
              ----------------     ---------------
           Board string: b om oooctpik to
            Goal string: boom too pick to

        Enter one of the following:
           R Rotate a row or column
           G Generate a new board with new random words
           Q to quit.
        1. Your choice:
*/

#include <iostream>     // For Input and Output
#include <fstream>      // For file input and output
#include <cassert>      // For the assert statement
#include <vector>       // For vectors
#include <iomanip>      // For setw() and setfill()
#include <stdlib.h>
using namespace std;


// Class Board should be declared here and should have private data members for:
//    1. The board letters (as a string or vector of char)
//    2. The list of words randomly selected from the dictionary
//    3. What the original unscrambled board looks like (which is also the completed board)
//    4. The size of the board
// Your Board class should not include the dictionary, because if it does then each Node
// would have its own copy, and you only need a single copy of the dictionary.
// ...


class Board {
  
    private:
        string theBoard;
        vector<string> boardWords;
        string completedBoard;
        int boardSize;
    
    public:
        
        void initializeBoard() {
            int i;
            for( i=0; i< (int)boardWords.size()-1; i++) {
                theBoard += boardWords[i] + " ";
            }
            
            theBoard +=  boardWords[i];
            
            while((int) theBoard.size() < boardSize) {
                theBoard += " ";
            }
        }
        
        void selectRandomWords(vector<string> dictionaryWords)  {
            
            string allWordsPlusSpaces = "";
            boardWords.clear();
            
            while( (int)allWordsPlusSpaces.length() < boardSize) {
                int randomWordIndex = rand() % dictionaryWords.size();
                string randomWord = dictionaryWords.at( randomWordIndex);
                
                if( ((int)randomWord.length() + (int)allWordsPlusSpaces.length()) > boardSize) {
                    continue;
                }
                
                boardWords.push_back( randomWord);
                allWordsPlusSpaces += randomWord + " ";
            } 
        }
        
        void rotateRowOnce(int rowToRotate, int boardCharsPerSide) {

            int rowStartingBoardIndex = rowToRotate * boardCharsPerSide;
            int rowEndingBoardIndex = rowStartingBoardIndex + boardCharsPerSide - 1;
           
            char lastElement = theBoard.at( rowEndingBoardIndex);
           
            for( int i=rowEndingBoardIndex; i>rowStartingBoardIndex; i--) {
                theBoard.at(i) = theBoard.at( i-1); 
            }
           
            theBoard.at( rowStartingBoardIndex) = lastElement;
        }
        
        void rotateColOnce(int colToRotate, int boardCharsPerSide) {
        
            int colStartingBoardIndex = colToRotate;
            int colEndingBoardIndex = colStartingBoardIndex + (boardCharsPerSide * (boardCharsPerSide - 1));
           
            char bottomElement = theBoard.at( colEndingBoardIndex);
        
            for( int i=colEndingBoardIndex; i>colStartingBoardIndex; i = i - boardCharsPerSide) {
                theBoard.at(i) = theBoard.at( i-boardCharsPerSide); 
            }
           
            theBoard.at( colStartingBoardIndex) = bottomElement;
        }
        
        void scrambleBoard(int boardCharsPerSide) {

            int numberOfScrambles = -1;
            do {
                cout << "   Choose single-digit number of times to scramble board: ";
                cin >> numberOfScrambles;
                
                if ( numberOfScrambles < 1 || numberOfScrambles > 9) {
                    cout << "   * The number of times must be a single digit >= 1. Retry." << endl;
                }
            } while( numberOfScrambles < 1 || numberOfScrambles > 9);
            
            for( int i=0; i < numberOfScrambles; i++) {
                int randRow = rand() % boardCharsPerSide;
                rotateRowOnce(randRow, boardCharsPerSide);
                
                int randCol = rand() % boardCharsPerSide;
                rotateColOnce(randCol, boardCharsPerSide);
            }
        }
        
        void setUpBoards(vector<string> dictionaryWords, int &boardCharsPerSide) {
            
            do {
                cout << "   Choose board size. It must be a single digit >=4: ";
                cin >> boardCharsPerSide;
                
                if( boardCharsPerSide < 4 || boardCharsPerSide > 9) {
                    cout << "   * The board size must be a single digit >=4. Retry." << endl;
                }
            } while( boardCharsPerSide < 4 || boardCharsPerSide > 9);
            
            boardSize = boardCharsPerSide * boardCharsPerSide;
            theBoard = "";
            completedBoard = ""; 
            
            selectRandomWords( dictionaryWords);
            initializeBoard();
            completedBoard = theBoard;
            scrambleBoard(boardCharsPerSide);
        }
        
        void displayBoard(int boardCharsPerSide)  {
    
            cout << endl << "    " << setfill(' ');
            for( int i=0; i<boardCharsPerSide; i++) {
                cout << setw( 4) << (char)('A'+i);
            }
            
            cout << "         Goal Board";
            
            for( int row=0; row<boardCharsPerSide; row++) {
                
                cout << "  \n      " << setw(boardCharsPerSide*4+3) << setfill('-') << "   ";
                cout << "  " << setw(boardCharsPerSide*4+3) << setfill('-') << "\n   ";        
                cout << row << "";
                
                for(int col=0; col<boardCharsPerSide; col++) {
                    int index = row*boardCharsPerSide + col; 
                    cout << " | " << theBoard[index];
                }
                
                cout << " |   ";      
                
                for(int col=0; col<boardCharsPerSide; col++) {
                    int index = row*boardCharsPerSide + col; 
                    cout << " | " << completedBoard[index];
                }
                
                cout << " | ";      
            }
          
            cout << "\n      " << setw(boardCharsPerSide*4) << setfill('-') << "";
            cout << "     " << setw(boardCharsPerSide*4) << setfill('-') << "\n";
            cout << "   Board string: " << theBoard << endl;
            cout << "    Goal string: " << completedBoard << endl;
        } 
        
        void handleRotation(int boardCharsPerSide)  {
    
            char rowOrCol = ' ';
            int numPositionsToRotate = 0;
        
            while( true) {
                cout << "   Enter the row/column to rotate, and # of (+/-) rotations: ";
                cin >> rowOrCol >> numPositionsToRotate;
                rowOrCol = toupper(rowOrCol);   
                
                
                if( !( (rowOrCol >= '0' && rowOrCol <= '0'+boardCharsPerSide - 1) ||   
                       (rowOrCol >= 'A' && rowOrCol <= 'A'+boardCharsPerSide - 1)      
                     )
                  ) {
                    
                    cout << "   * Row/column value is not within the valid range.  Retry." << endl;
                    continue;
                }
                
                if( abs( numPositionsToRotate) > boardCharsPerSide - 1) {
                    cout << "   * Shift value should be between -" << boardCharsPerSide - 1
                         << " and " << boardCharsPerSide - 1 << ". Retry."
                         << endl;
                    continue;
                }
                break;
            } 
            
            
            if( numPositionsToRotate < 0) {
                numPositionsToRotate = boardCharsPerSide + numPositionsToRotate;
            }
            
            for( int i=0; i<numPositionsToRotate; i++) {
                if( rowOrCol >= '0' && rowOrCol <= '0'+9) {
                    rotateRowOnce(rowOrCol-'0', boardCharsPerSide);
                }
                else {
                    rotateColOnce(rowOrCol-'A', boardCharsPerSide);
                }
            } 
        } 
        
        string getTheBoard() {
            return theBoard;
        }
        
        void setTheBoard(string boardDetails) {
            theBoard = boardDetails;
            
        }
        
        string getCompletedBoard() {
            return completedBoard;
        }
};


//---------------------------------------------------------------------------
// Read in all the words from the dictionary file into a vector
void readWordsIntoDictionary(
        vector <string> & dictionary,   // Dictionary where words will be stored
        string fileName)                // File name where words will be read from
{
    ifstream inStream;                  // Declare an input stream for reading
    inStream.open( fileName);            // Open dictionary file
    assert( inStream.fail() == false );  // Ensure file open worked
    
    // Clear vector in case it already had some words in it
    dictionary.clear();
    
    // Keep repeating while input from the file yields a word
    string newWord;                     // Store a single input word
    while( inStream >> newWord) {        // While there is another word to be read
        // Add this new word to the end of the vector, growing it in the process
        dictionary.push_back(newWord);
    }
    
    // Close the dictionary file
    inStream.close();
} //end readWordsIntoDictionary()


// **  IMPORTANT!!!  READ THIS!!!  **
//
// FIRST get the program working using classes BEFORE implementing the linked-list portion
// outlined in the code below.
//
// Once your classes version of program 5 is working also implement a Node struct or class
// used to store each move.  Your Node class should have private data members for:
//       1. A Board  (of type Board defined above)
//       2. A moveNumber
//       3. A pointer to the next Node
// Implement class Board here
// ...

//-------------------------------------------------------------------------------------
// Node declaration to implement a linked list to store moves, used to implement
// undo. You should store the old move number, the old board, and a pointer
// to the next Node.  Note that for this program you are not required to use
// a class for the Node.  It could just be a struct without worrying about the
// proper uses of public and private.
class Node {
    public:
        string boardWordsDetails;
        int moveNumber;
        Node* next;
};


//--------------------------------------------------------------------------------
// Display the move numbers and board letters in each Node on the linked list.
// The pTemp pointer should iterate down the list, being used to display the
// values in each Node.
void displayList( Node *pTemp) {
    cout << "   List is: ";
    while (pTemp != NULL) {
        cout << pTemp->moveNumber << ":" << pTemp->boardWordsDetails;
        if (pTemp->moveNumber != 1) {
            cout << " -> ";
        }
        pTemp = pTemp->next;
    }
    cout << endl << endl;
} // end displayList()


//--------------------------------------------------------------------------------
// Undo the move represented by the front node on the list, then delete this node.
// Parameters should be:
//  - pointer to the head of the list, which could change, so should be: Node *&pHead
//  - the old game Board to be restored from what is initially the second
//    Node on the list, before the front Node is deleted.
//  - the old moveNumber, which should be restored again from what is initially
//    the second Node on the list, before the front Node is deleted
void deleteFrontNodeFromList(Node *&phead) {
    phead = phead->next;
} //end deleteFrontNodeFromList()


//--------------------------------------------------------------------------------
// Create a new node and prepend it to the beginning of the list.
// Parameters should be:
//  - pointer to the head of the list, which could change, so should be Node *&pHead.
//  - the Board to be added to the new Node at the front of the list
//  - the current moveNumber to be added to the new Node at the front of the list
void prependNodeToList(Node *&phead, string boardDetails, int move) {
    Node* temp = new Node;
    temp->boardWordsDetails = boardDetails;
    temp->moveNumber = move;
    temp->next = phead;
    phead = temp;
}


//---------------------------------------------------------------------------
//
int main()
{
    // For random number generation seed the random number generator to 1, so that results
    // are predictable.  To make results different every time instead you would
    // use srand( time( NULL));   Don't do this if you want your code to match test cases!
    srand( 1);
    vector<string> dictionaryWords; // Vector to store the words from the dictionary
    char userInput = ' ';           // Character to read in the user input
    int moveNumber = 1;             // Move number, incremented after each valid move
    int boardCharsPerSide;
    Node* phead = NULL;

      
    // Display program identification and overview.
    cout << "Program 6: Unscrambler Undo \n"
         << "CS 141, Fall 2021, UIC      \n"
         << " \n"
         << "You will be presented with a board that is filled with scrambled words.    \n"
         << "Rotate the rows and columns to get the words displayed in the right order. \n"
         << "Press 'U' to undo moves.   \n"
         << endl;
    
    // Read in all the words from dictionary file into a vector.
    // Word list adapted from https://www.ef.com/wwen/english-resources/english-vocabulary/top-3000-words/
    readWordsIntoDictionary( dictionaryWords, "commonWords.txt");
    cout << dictionaryWords.size() << " words have been read in from the dictionary." << endl;
    
    Board board;
    // Select random words and setup all the boards
    board.setUpBoards( dictionaryWords, boardCharsPerSide);
    prependNodeToList(phead, board.getTheBoard(), moveNumber);

    // Loop to prompt for and process user input
    while(true) {
        
        userInput = ' '; 
        
        board.displayBoard(boardCharsPerSide);
        displayList(phead);
        
        cout << "Enter one of the following: \n"
             << "   R Rotate a row or column \n"
             << "   G Generate a new board with new random words \n"
             << "   U Undo most recent move \n"
             << "   Q to quit. \n"
             << moveNumber << ". Your choice: ";
        cin >> userInput;
        
        if (userInput == ' ') break;
        
        userInput = toupper(userInput);
        
        // Handle menu options
        switch( userInput) {
            // 'Q' for Quit
            case 'Q': {
                cout << "Thank you for playing! Exiting program... \n" << endl;
                exit( 0);      // Exit the program.
                break;
            }
            // 'R' to rotate
            case 'R': {
                board.handleRotation(boardCharsPerSide);
                moveNumber++;
                prependNodeToList(phead, board.getTheBoard(), moveNumber);
                break;
            }
            // 'G' to generate a new board with new random words
            case 'G': {
                // Select random words and setup all the boards
                phead = NULL;
                board.setUpBoards( dictionaryWords, boardCharsPerSide);
                moveNumber = 1;
                prependNodeToList(phead, board.getTheBoard(), moveNumber);
                break;
            }
            case 'U': {
                if (moveNumber == 1) {
                    cout << "   * You cannot undo past the beginning of the game.  Retry. *" << endl;
                    continue;
                }
                cout << "   * Undoing move *" << endl;
                deleteFrontNodeFromList(phead);
                board.setTheBoard(phead->boardWordsDetails);
                moveNumber--;
                break;
            }
            default: {
                cout << "You did not enter one of the valid options. Try again." << endl;
                break;
            }
        } //end switch( userInput)
        
        // Check for a win
        if( board.getTheBoard() == board.getCompletedBoard()) {
            board.displayBoard(boardCharsPerSide);
            cout << "Congratulations, you won! \n" << "Exiting program... \n" << endl;
            return 0;
        }
  
    } // end while(true)
        
    return 0;
} //end main()
