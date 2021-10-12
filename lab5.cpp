/* 
Author:Jaymeet Patel
UIN: 656971609
System: Windows VSCode

Course: CS 141 Lab 5
*/




#include <iostream>

using namespace std;

 

//  Display the board using an array and length N of the array

void displayBoard(char arr[], int N){

 

	//  HINT: use a loop to iterate through the array

	//  N IS IMPORTANT

	//  Split the board into three different parts, TOP, MIDDLE, BOTTOM=

 

	//  CODE HERE

	cout << "-------" << endl;

	for (int i = 1; i < N+1; ++i){

      	cout << "|" << arr[i-1];
    
          	if ( (i % 3) == 0) {
        
             	cout << "|" << endl;
        
             	cout << "-------" << endl;
        
          	}

	}

}

 

//  Here you will need to take in the array as input and update it using reference parameters

//  You were provided the function please enter the missing parameters and complete the function.

void makeMove(char arr[], char piece, int position){

	//  CODE HERE

	arr[position - 1] = piece;

}

 

// Check whether the move position entered is valid, returning true or false.

// Receive parameters for the move position and all the board pieces.

// If the intended destination is already occupied or the selected

// move position is not between 1..9 (inclusive) then return false.

// *** In the line below supply the return type and any needed parameters and uncomment it.

// Please enter the parameters you feel are needed for this function as they are not provided for you

bool moveIsValid(char arr[], int pos){

	//  CODE HERE

	if ( arr[pos -1] != ' '){

  	    return false;    

	}

	else if ( (arr[pos - 1] < 1) && (arr[pos - 1] > 9)){

    	return false;    

	}

	else {

    	return true;    

	}

}

 

//  This function returns whether a player has won or not

//  Please enter the parameters you feel are needed for this function as they are not provided for you

bool thereIsAWin(char arr[], char piece){

	// if winning condition found then set win = true

	bool win = false;

	//  CODE HERE

    

	if (((arr[0] == piece) && (arr[1] == piece) && (arr[2] == piece)) ||

    	((arr[3] == piece) && (arr[4] == piece) && (arr[5] == piece)) ||

    	((arr[6] == piece) && (arr[7] == piece) && (arr[8] == piece)) ||

    	((arr[0] == piece) && (arr[3] == piece) && (arr[6] == piece)) ||

    	((arr[1] == piece) && (arr[4] == piece) && (arr[7] == piece)) ||

    	((arr[2] == piece) && (arr[5] == piece) && (arr[8] == piece)) ||

    	((arr[0] == piece) && (arr[4] == piece) && (arr[8] == piece)) ||

    	((arr[2] == piece) && (arr[4] == piece) && (arr[6] == piece))){

     	 

     	    win = true;   

     	}

	return win;

}

 

 

int main(){

 

	//  N is the length of the char array given

	int N = 9;

	char arr[N] = {' ',' ',' ',' ',' ',' ',' ',' ',' ' };

 

	//  Initializing the different game variables

	char pieceToMove = 'X';

	int moveNumber = 0;

	int position;

 

	cout << "Welcome to the TicTacToe game!              	\n"

     	<< "Take turns entering the move destination (1..9) \n"

     	<< "or '0' (zero) to exit."

     	<< endl;

 

 

	while(moveNumber <= 9){

    	 

    	//  DisplayBoard is already given to you parameterized please use those parameters

    	displayBoard(arr, N);

 

    	// Prompt for and get move.

    	cout << moveNumber << ". Enter the move (1..9) for " << pieceToMove << ": ";

    	cin >> position;   	// the position at which the move is made

 

    	// See if 0 was entered, indicating the desire to exit the program

    	if( position == 0) {

        	// 0 was entered. Break out of enclosing loop, to exit the program.

        	break;

    	}

    	 

    	//**** PLEASE UN-COMMENT THE CODE BELOW TO GET THE VALID MOVE WORKING WITH YOUR PARAMETERS ****

    	if(!moveIsValid( arr, position)) {

        	cout << "That move is not valid.  Retry.";

        	continue;

    	}

 

    	//****  PLEASE UNCOMMENT AND FIX THE FUNCTION WITH YOUR PARAMETERS****

    	makeMove( arr, pieceToMove, position );

 

    	// *** Add any needed parameters below to function thereIsAWin(...) *****

    	if(thereIsAWin( arr, pieceToMove )) {    	// if win was detected then the game stops

        	// After a win again display the board.

        	displayBoard(arr, N);

        	cout << endl

             	<< "Congratulations player " << pieceToMove << ". You WON!" << endl;

        	break;

    	}

 

    	// Change to the other piece for next move.

    	if( pieceToMove == 'X') {

        	pieceToMove = 'O';

    	}

    	else {

        	pieceToMove = 'X';

    	}

 

    	moveNumber++;

	}

 

	cout << "Exiting program..." << endl;

	return 0;
}
