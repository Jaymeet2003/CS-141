// TicTacToe.cpp   
// for CS 141 lab 3

#include <iostream>
using namespace std;


char p1,p2,p3,p4,p5,p6,p7,p8,p9;
int win;
char pieceToMove;           
int position;

//Running display board should print out the board and the pieces if move has been made
//Running the code without making any move should look like:
//   -------
//   | | | |   1  2  3
//   -------
//   | | | |   4  5  6
//   -------
//   | | | |   7  8  9
//   -------
//
// Running the code after making the move should display the peice on the board:
//   -------
//   |X| | |   1  2  3
//   -------
//   | | | |   4  5  6
//   -------
//   | | | |   7  8  9
//   -------

void displayBoard(){
   cout<<"------- "<<endl;

    
    cout<<"|"<<p1<<"|"<<p2<<"|"<<p3<<"|   ";
    cout<<"1  "<<"2  "<<"3"<<endl;

    cout<<"------- "<<endl;

    cout<<"|"<<p4<<"|"<<p5<<"|"<<p6<<"|   ";
    cout<<"4  "<<"5  "<<"6"<<endl;

    cout<<"------- "<<endl;

    cout<<"|"<<p7<<"|"<<p8<<"|"<<p9<<"|   ";
    cout<<"7  "<<"8  "<<"9"<<endl;

    cout<<"------- "<<endl;
   }

// This function allows the player to make a move.
//the function should be able to place the correct character at the position
//entered by user.

void makeMove(int userInp, char pieceMove){
   	
       switch (userInp)
       {
       case 1:
           p1 = pieceMove;
           break;
        case 2:
           p2 = pieceMove;
           break;
        case 3:
           p3 = pieceMove;
           break;
        case 4:
           p4 = pieceMove;
           break;
        case 5:
           p5 = pieceMove;
           break;
        case 6:
           p6 = pieceMove;
           break;
        case 7:
           p7 = pieceMove;
           break;
        case 8:
           p8 = pieceMove;
           break;
        case 9:
           p9 = pieceMove;
           break;
       
       default:
       cout<<"Invalid Move!"<<endl;
           break;
       }

}


//this function checks the board after every move 
// for a winning condition.
//For eg. the winning condition could be poistion 1,2,3 having the same character.
//if winning condition is found set the global varaible win to be 1
void checkBoard(){
    // row 1 check
    if(p1 == 'X' && p2 == 'X' && p3 == 'X'){
        displayBoard();
        cout<<endl<<"Congratulations player X. You WON!"<<endl;
        win = 1;
    }else if(p1 == 'O' && p2 == 'O' && p3 == 'O'){
        displayBoard();
        cout<<endl<<"Congratulations player O. You WON!"<<endl;
        win = 1;
    }
    
    
    // row 2 check
    if(p4 == 'X' && p5 == 'X' && p6 == 'X'){
        displayBoard();
        cout<<endl<<"Congratulations player X. You WON!"<<endl;
        win = 1;
    }else if(p4 == 'O' && p5 == 'O' && p6 == 'O'){
        displayBoard();
        cout<<endl<<"Congratulations player O. You WON!"<<endl;
        win = 1;
    }
    
    // row 3 check
    if(p7 == 'X' && p8 == 'X' && p9 == 'X'){
        displayBoard();
        cout<<endl<<"Congratulations player X. You WON!"<<endl;
        win = 1;
    }else if(p7 == 'O' && p8 == 'O' && p9 == 'O'){
        displayBoard();
        cout<<endl<<"Congratulations player O. You WON!"<<endl;
        win = 1;
    }
    
    // column 1 check
    if(p1 == 'X' && p4 == 'X' && p7 == 'X'){
        displayBoard();
        cout<<endl<<"Congratulations player X. You WON!"<<endl;
        win = 1;
    }else if(p1 == 'O' && p4 == 'O' && p7 == 'O'){
        displayBoard();
        cout<<endl<<"Congratulations player O. You WON!"<<endl;
        win = 1;
    }
    
    // column 2 check
    if(p2 == 'X' && p5 == 'X' && p8 == 'X'){
        displayBoard();
        cout<<endl<<"Congratulations player X. You WON!"<<endl;
        win = 1;
    }else if(p2 == 'O' && p5 == 'O' && p8 == 'O'){
        displayBoard();
        cout<<endl<<"Congratulations player O. You WON!"<<endl;
        win = 1;
    }
    
    
    // column 3 check
    if(p3 == 'X' && p6 == 'X' && p9 == 'X'){
        displayBoard();
        cout<<endl<<"Congratulations player X. You WON!"<<endl;
        win = 1;
    }else if(p9 == 'O' && p6 == 'O' && p9 == 'O'){
        displayBoard();
        cout<<endl<<"Congratulations player O. You WON!"<<endl;
        win = 1;
    }
    
    // diagonal 1 check
    if(p1 == 'X' && p5 == 'X' && p9 == 'X'){
        displayBoard();
        cout<<endl<<"Congratulations player X. You WON!"<<endl;
        win = 1;
    }else if(p1 == 'O' && p5 == 'O' && p9 == 'O'){
        displayBoard();
        cout<<endl<<"Congratulations player O. You WON!"<<endl;
        win = 1;
    }
    
    // diagonal 2 check
    if(p3 == 'X' && p5 == 'X' && p7 == 'X'){
        displayBoard();
        cout<<endl<<"Congratulations player X. You WON!"<<endl;
        win = 1;
    }else if(p3 == 'O' && p5 == 'O' && p7 == 'O'){
        displayBoard();
        cout<<endl<<"Congratulations player O. You WON!"<<endl;
        win = 1;
    }
}

int main()
{
	// Initialize the board
	p1=p2=p3=p4=p5=p6=p7=p8=p9=' ';
	pieceToMove = 'X';           // 'X' gets the first move
	position = 0;
	int moveNumber = 1;
	win = 0;
	     
	cout << "Welcome to the TicTacToe game! " << endl
	     << "Take turns entering the position (1..9)" << endl
	     << "into which your piece will be placed. "  
		 << endl << "Enter '0' (zero) to exit." <<endl
		 << endl;
 
  displayBoard();

	// Main loop
	while( moveNumber <= 9) {      // if winning condition not found the game stops after 9 moves
		// Prompt for and get move.  
		cout << moveNumber << ". Enter the move (1..9) for " << pieceToMove << ": ";
        cout<<endl;
		cin >> position;       // the position at which the move is made
		if(position !=0){
	    	makeMove(position, pieceToMove);        // make the move to place teh character on the board
		   checkBoard();      //checks the board for winning condition
	      if(win==1){ 
            // if win was detected then the game stops
	          break;
	      }
	   
		   // the game continues if the win flag was not set to 1
		   // Change to other piece for next move.  
		   if( pieceToMove == 'X') {
			   pieceToMove = 'O';
		   }
		   else {
			   pieceToMove = 'X';
		   }

	      displayBoard();     //display the current board

		   moveNumber++;
		}
		else{
		   break;
		}
	}

	cout << "Exiting program..." << endl;
	return 1;

}// end main()
