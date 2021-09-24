/* ---------------------------------------------
    Program 2: Great 13
        Peg puzzle, jumping pieces to try and
        leave only a single piece.

    Course: CS 141, Fall 2021. Tues 5pm lab
    System: Mac using Xcode
    Author: Dale Reed
    
    Running the program looks like:
        
        Author:  Jimmy Patel
        Class:   CS 141, Fall '21
        UIN: 656971609
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
   ---------------------------------------------
*/
#include <iostream>
#include <cctype>  	// for toupper()
using namespace std;

// Global variables for the pieces are allowed for this program,
// but will generally not be allowed in the future.
// You will likely want to declare global variables at least for the following:
//   - 13 board pieces
//   - The letter positions you are moving from, jumping over, and moving to
//   - The number of pieces on the board (to know when there is a win)
// ...

char pA, pB, pC, pD, pE, pF, pG, pH, pI, pJ, pK, pL, pM;

// ----------------------------------------------------------------------
// Display the game instructions.

void displayInstructions()
{
	cout << "Class: CS 141             \n" <<
		"Program: #2 Great 13      \n" <<
		"  \n" <<
		"Make a series of jumps until there is a single piece left in the   \n" <<
		"middle. On each move you must jump an adjacent piece into an empty \n" <<
		"square, jumping horizontally, vertically, or diagonally.           \n" <<
		"Input of 'R' resets the board back to the beginning, and input of  \n" <<
		"'X' exits the game.'   \n" <<
		endl;
}	//end displayInstructions()

// ----------------------------------------------------------------------
// Display the board, using the global variables pA..pM
void displayBoard()
{
	cout << "\n " <<
		"    Board   " << " Position \n" <<
		"       " << pA << "          A    \n" <<
		"     " << pB << " " << pC << " " << pD << "      B C D  \n" <<
		"   " << pE << " " << pF << " " << pG << " " << pH << " " << pI << "  E F G H I\n" <<
		"     " << pJ << " " << pK << " " << pL << "      J K L  \n" <<
		"       " << pM << "          M    \n" <<
		endl;
}	//end displayBoard()

void reinitializeBoard()
{
	pA = pB = pC = pD = pE = pF = pH = pI = pJ = pK = pL = pM = '#';
	pG = '.';
}



void gameLogic(int moveFrom, int jump, int moveTo, int &moveNum){
    if (moveFrom == 'E')
		{
			if (pE != '#')
			{
				cout << endl << "   *** Source must have a piece. Please retry" << endl << endl;
				moveNum -= 1;
			}
			else if (jump == 'F')
			{
				if (pF != '#')
				{
					cout << endl << "   *** Must jump a piece. Please retry" << endl << endl;
					moveNum -= 1;
				}
				else
				{
					if (moveTo == 'G')
					{
						if (pG != '.')
						{
							cout << endl << "   *** Destination must be blank. Retry" << endl << endl;
							moveNum -= 1;
						}
						else
						{
							pE = '.';
							pF = '.';
							pG = '#';
							displayBoard();
						}
					}
					else
					{
						cout << endl << "   *** Pieces must be adjacent. Please retry" << endl << endl;
						moveNum -= 1;
					}
				}
			}
			else if (jump == 'J')
			{
				if (pJ != '#')
				{
					cout << endl << "   *** Must jump a piece. Please retry" << endl << endl;
					moveNum -= 1;
				}
				else if (moveTo == 'M')
				{
					if (pM != '.')
					{
						cout << endl << "   *** Destination must be blank. Retry" << endl << endl;
						moveNum -= 1;
					}
					else
					{
						pE = '.';
						pJ = '.';
						pM = '#';
						displayBoard();
					}
				}
				else
				{
					cout << endl << "   *** Pieces must be adjacent. Please retry" << endl << endl;
					moveNum -= 1;
				}
			}
			else if (jump == 'B')
			{
				if (pB != '#')
				{
					cout << endl << "   *** Must jump a piece. Please retry" << endl << endl;
					moveNum -= 1;
				}
				else if (moveTo == 'A')
				{
					if (pA != '.')
					{
						cout << endl << "   *** Destination must be blank. Retry" << endl << endl;
						moveNum -= 1;
					}
					else
					{
						pE = '.';
						pB = '.';
						pA = '#';
						displayBoard();
					}
				}
				else
				{
					cout << endl << "   *** Pieces must be adjacent. Please retry" << endl << endl;
					moveNum -= 1;
				}
			}
			else
			{
				cout << endl << "   *** Pieces must be adjacent. Please retry" << endl << endl;
				moveNum -= 1;
			}
		}
		else if (moveFrom == 'A')
		{
			if (pA != '#')
			{
				cout << endl << "   *** Source must have a piece. Please retry" << endl << endl;
				moveNum -= 1;
			}
			else if (jump == 'C')
			{
				if (pC != '#')
				{
					cout << endl << "   *** Must jump a piece. Please retry" << endl << endl;
					moveNum -= 1;
				}
				else
				{
					if (moveTo == 'G')
					{
						if (pG != '.')
						{
							cout << endl << "   *** Destination must be blank. Retry" << endl << endl;
							moveNum -= 1;
						}
						else
						{
							pA = '.';
							pC = '.';
							pG = '#';
							displayBoard();
						}
					}
					else
					{
						cout << endl << "   *** Pieces must be adjacent. Please retry" << endl << endl;
						moveNum -= 1;
					}
				}
			}
			else if (jump == 'B')
			{
				if (pB != '#')
				{
					cout << endl << "   *** Must jump a piece. Please retry" << endl << endl;
					moveNum -= 1;
				}
				else if (moveTo == 'E')
				{
					if (pE != '.')
					{
						cout << endl << "   *** Destination must be blank. Retry" << endl << endl;
						moveNum -= 1;
					}
					else
					{
						pA = '.';
						pB = '.';
						pE = '#';
						displayBoard();
					}
				}
				else
				{
					cout << endl << "   *** Pieces must be adjacent. Please retry" << endl << endl;
					moveNum -= 1;
				}
			}
			else if (jump == 'D')
			{
				if (pD != '#')
				{
					cout << endl << "   *** Must jump a piece. Please retry" << endl << endl;
					moveNum -= 1;
				}
				else if (moveTo == 'I')
				{
					if (pI != '.')
					{
						cout << endl << "   *** Destination must be blank. Retry" << endl << endl;
						moveNum -= 1;
					}
					else
					{
						pA = '.';
						pD = '.';
						pI = '#';
						displayBoard();
					}
				}
				else
				{
					cout << endl << "   *** Pieces must be adjacent. Please retry" << endl << endl;
					moveNum -= 1;
				}
			}
			else
			{
				cout << endl << "   *** Pieces must be adjacent. Please retry" << endl << endl;
				moveNum -= 1;
			}
		}
		else if (moveFrom == 'I')
		{
			if (pI != '#')
			{
				cout << endl << "   *** Source must have a piece. Please retry" << endl << endl;
				moveNum -= 1;
			}
			else if (jump == 'H')
			{
				if (pH != '#')
				{
					cout << endl << "   *** Must jump a piece. Please retry" << endl << endl;
					moveNum -= 1;
				}
				else
				{
					if (moveTo == 'G')
					{
						if (pG != '.')
						{
							cout << endl << "   *** Destination must be blank. Retry" << endl << endl;
							moveNum -= 1;
						}
						else
						{
							pI = '.';
							pH = '.';
							pG = '#';
							displayBoard();
						}
					}
					else
					{
						cout << endl << "   *** Pieces must be adjacent. Please retry" << endl << endl;
						moveNum -= 1;
					}
				}
			}
			else if (jump == 'D')
			{
				if (pD != '#')
				{
					cout << endl << "   *** Must jump a piece. Please retry" << endl << endl;
					moveNum -= 1;
				}
				else if (moveTo == 'A')
				{
					if (pA != '.')
					{
						cout << endl << "   *** Destination must be blank. Retry" << endl << endl;
						moveNum -= 1;
					}
					else
					{
						pI = '.';
						pD = '.';
						pA = '#';
						displayBoard();
					}
				}
				else
				{
					cout << endl << "   *** Pieces must be adjacent. Please retry" << endl << endl;
					moveNum -= 1;
				}
			}
			else if (jump == 'L')
			{
				if (pL != '#')
				{
					cout << endl << "   *** Must jump a piece. Please retry" << endl << endl;
					moveNum -= 1;
				}
				else if (moveTo == 'M')
				{
					if (pM != '.')
					{
						cout << endl << "   *** Destination must be blank. Retry" << endl << endl;
						moveNum -= 1;
					}
					else
					{
						pI = '.';
						pL = '.';
						pM = '#';
						displayBoard();
					}
				}
				else
				{
					cout << endl << "   *** Pieces must be adjacent. Please retry" << endl << endl;
					moveNum -= 1;
				}
			}
			else
			{
				cout << endl << "   *** Pieces must be adjacent. Please retry" << endl << endl;
				moveNum -= 1;
			}
		}
		else if (moveFrom == 'M')
		{
			if (pM != '#')
			{
				cout << endl << "   *** Source must have a piece. Please retry" << endl << endl;
				moveNum -= 1;
			}
			else if (jump == 'K')
			{
				if (pK != '#')
				{
					cout << endl << "   *** Must jump a piece. Please retry" << endl << endl;
					moveNum -= 1;
				}
				else
				{
					if (moveTo == 'G')
					{
						if (pG != '.')
						{
							cout << endl << "   *** Destination must be blank. Retry" << endl << endl;
							moveNum -= 1;
						}
						else
						{
							pM = '.';
							pK = '.';
							pG = '#';
							displayBoard();
						}
					}
					else
					{
						cout << endl << "   *** Pieces must be adjacent. Please retry" << endl << endl;
						moveNum -= 1;
					}
				}
			}
			else if (jump == 'L')
			{
				if (pL != '#')
				{
					cout << endl << "   *** Must jump a piece. Please retry" << endl << endl;
					moveNum -= 1;
				}
				else if (moveTo == 'I')
				{
					if (pI != '.')
					{
						cout << endl << "   *** Destination must be blank. Retry" << endl << endl;
						moveNum -= 1;
					}
					else
					{
						pM = '.';
						pL = '.';
						pI = '#';
						displayBoard();
					}
				}
				else
				{
					cout << endl << "   *** Pieces must be adjacent. Please retry" << endl << endl;
					moveNum -= 1;
				}
			}
			else if (jump == 'J')
			{
				if (pJ != '#')
				{
					cout << endl << "   *** Must jump a piece. Please retry" << endl << endl;
					moveNum -= 1;
				}
				else if (moveTo == 'E')
				{
					if (pE != '.')
					{
						cout << endl << "   *** Destination must be blank. Retry" << endl << endl;
						moveNum -= 1;
					}
					else
					{
						pM = '.';
						pJ = '.';
						pE = '#';
						displayBoard();
					}
				}
				else
				{
					cout << endl << "   *** Pieces must be adjacent. Please retry" << endl << endl;
					moveNum -= 1;
				}
			}
			else
			{
				cout << endl << "   *** Pieces must be adjacent. Please retry" << endl << endl;
				moveNum -= 1;
			}
		}
		else if (moveFrom == 'M')
		{
			if (pM != '#')
			{
				cout << endl << "   *** Source must have a piece. Please retry" << endl << endl;
				moveNum -= 1;
			}
			else if (jump == 'K')
			{
				if (pK != '#')
				{
					cout << endl << "   *** Must jump a piece. Please retry" << endl << endl;
					moveNum -= 1;
				}
				else
				{
					if (moveTo == 'G')
					{
						if (pG != '.')
						{
							cout << endl << "   *** Destination must be blank. Retry" << endl << endl;
							moveNum -= 1;
						}
						else
						{
							pM = '.';
							pK = '.';
							pG = '#';
							displayBoard();
						}
					}
					else
					{
						cout << endl << "   *** Pieces must be adjacent. Please retry" << endl << endl;
						moveNum -= 1;
					}
				}
			}
			else if (jump == 'L')
			{
				if (pL != '#')
				{
					cout << endl << "   *** Must jump a piece. Please retry" << endl << endl;
					moveNum -= 1;
				}
				else if (moveTo == 'I')
				{
					if (pI != '.')
					{
						cout << endl << "   *** Destination must be blank. Retry" << endl << endl;
						moveNum -= 1;
					}
					else
					{
						pM = '.';
						pL = '.';
						pI = '#';
						displayBoard();
					}
				}
				else
				{
					cout << endl << "   *** Pieces must be adjacent. Please retry" << endl << endl;
					moveNum -= 1;
				}
			}
			else if (jump == 'J')
			{
				if (pJ != '#')
				{
					cout << endl << "   *** Must jump a piece. Please retry" << endl << endl;
					moveNum -= 1;
				}
				else if (moveTo == 'E')
				{
					if (pE != '.')
					{
						cout << endl << "   *** Destination must be blank. Retry" << endl << endl;
						moveNum -= 1;
					}
					else
					{
						pM = '.';
						pJ = '.';
						pE = '#';
						displayBoard();
					}
				}
				else
				{
					cout << endl << "   *** Pieces must be adjacent. Please retry" << endl << endl;
					moveNum -= 1;
				}
			}
			else
			{
				cout << endl << "   *** Pieces must be adjacent. Please retry" << endl << endl;
				moveNum -= 1;
			}
		}
		else if (moveFrom == 'B')
		{
			if (pB != '#')
			{
				cout << endl << "   *** Source must have a piece. Please retry" << endl << endl;
				moveNum -= 1;
			}
			else if (jump == 'C')
			{
				if (pC != '#')
				{
					cout << endl << "   *** Must jump a piece. Please retry" << endl << endl;
					moveNum -= 1;
				}
				else
				{
					if (moveTo == 'D')
					{
						if (pD != '.')
						{
							cout << endl << "   *** Destination must be blank. Retry" << endl << endl;
							moveNum -= 1;
						}
						else
						{
							pB = '.';
							pC = '.';
							pD = '#';
							displayBoard();
						}
					}
					else
					{
						cout << endl << "   *** Pieces must be adjacent. Please retry" << endl << endl;
						moveNum -= 1;
					}
				}
			}
			else if (jump == 'F')
			{
				if (pF != '#')
				{
					cout << endl << "   *** Must jump a piece. Please retry" << endl << endl;
					moveNum -= 1;
				}
				else if (moveTo == 'J')
				{
					if (pJ != '.')
					{
						cout << endl << "   *** Destination must be blank. Retry" << endl << endl;
						moveNum -= 1;
					}
					else
					{
						pB = '.';
						pF = '.';
						pJ = '#';
						displayBoard();
					}
				}
				else
				{
					cout << endl << "   *** Pieces must be adjacent. Please retry" << endl << endl;
					moveNum -= 1;
				}
			}
			else if (jump == 'G')
			{
				if (pG != '#')
				{
					cout << endl << "   *** Must jump a piece. Please retry" << endl << endl;
					moveNum -= 1;
				}
				else if (moveTo == 'L')
				{
					if (pL != '.')
					{
						cout << endl << "   *** Destination must be blank. Retry" << endl << endl;
						moveNum -= 1;
					}
					else
					{
						pB = '.';
						pG = '.';
						pL = '#';
						displayBoard();
					}
				}
				else
				{
					cout << endl << "   *** Pieces must be adjacent. Please retry" << endl << endl;
					moveNum -= 1;
				}
			}
			else
			{
				cout << endl << "   *** Pieces must be adjacent. Please retry" << endl << endl;
				moveNum -= 1;
			}
		}
		else if (moveFrom == 'D')
		{
			if (pD != '#')
			{
				cout << endl << "   *** Source must have a piece. Please retry" << endl << endl;
				moveNum -= 1;
			}
			else if (jump == 'C')
			{
				if (pC != '#')
				{
					cout << endl << "   *** Must jump a piece. Please retry" << endl << endl;
					moveNum -= 1;
				}
				else
				{
					if (moveTo == 'B')
					{
						if (pB != '.')
						{
							cout << endl << "   *** Destination must be blank. Retry" << endl << endl;
							moveNum -= 1;
						}
						else
						{
							pD = '.';
							pC = '.';
							pB = '#';
							displayBoard();
						}
					}
					else
					{
						cout << endl << "   *** Pieces must be adjacent. Please retry" << endl << endl;
						moveNum -= 1;
					}
				}
			}
			else if (jump == 'H')
			{
				if (pH != '#')
				{
					cout << endl << "   *** Must jump a piece. Please retry" << endl << endl;
					moveNum -= 1;
				}
				else if (moveTo == 'L')
				{
					if (pL != '.')
					{
						cout << endl << "   *** Destination must be blank. Retry" << endl << endl;
						moveNum -= 1;
					}
					else
					{
						pD = '.';
						pH = '.';
						pL = '#';
						displayBoard();
					}
				}
				else
				{
					cout << endl << "   *** Pieces must be adjacent. Please retry" << endl << endl;
					moveNum -= 1;
				}
			}
			else if (jump == 'G')
			{
				if (pG != '#')
				{
					cout << endl << "   *** Must jump a piece. Please retry" << endl << endl;
					moveNum -= 1;
				}
				else if (moveTo == 'J')
				{
					if (pJ != '.')
					{
						cout << endl << "   *** Destination must be blank. Retry" << endl << endl;
						moveNum -= 1;
					}
					else
					{
						pD = '.';
						pG = '.';
						pJ = '#';
						displayBoard();
					}
				}
				else
				{
					cout << endl << "   *** Pieces must be adjacent. Please retry" << endl << endl;
					moveNum -= 1;
				}
			}
			else
			{
				cout << endl << "   *** Pieces must be adjacent. Please retry" << endl << endl;
				moveNum -= 1;
			}
		}
		else if (moveFrom == 'L')
		{
			if (pL != '#')
			{
				cout << endl << "   *** Source must have a piece. Please retry" << endl << endl;
				moveNum -= 1;
			}
			else if (jump == 'H')
			{
				if (pH != '#')
				{
					cout << endl << "   *** Must jump a piece. Please retry" << endl << endl;
					moveNum -= 1;
				}
				else
				{
					if (moveTo == 'D')
					{
						if (pD != '.')
						{
							cout << endl << "   *** Destination must be blank. Retry" << endl << endl;
							moveNum -= 1;
						}
						else
						{
							pL = '.';
							pH = '.';
							pD = '#';
							displayBoard();
						}
					}
					else
					{
						cout << endl << "   *** Pieces must be adjacent. Please retry" << endl << endl;
						moveNum -= 1;
					}
				}
			}
			else if (jump == 'K')
			{
				if (pK != '#')
				{
					cout << endl << "   *** Must jump a piece. Please retry" << endl << endl;
					moveNum -= 1;
				}
				else if (moveTo == 'J')
				{
					if (pJ != '.')
					{
						cout << endl << "   *** Destination must be blank. Retry" << endl << endl;
						moveNum -= 1;
					}
					else
					{
						pL = '.';
						pK = '.';
						pJ = '#';
						displayBoard();
					}
				}
				else
				{
					cout << endl << "   *** Pieces must be adjacent. Please retry" << endl << endl;
					moveNum -= 1;
				}
			}
			else if (jump == 'G')
			{
				if (pG != '#')
				{
					cout << endl << "   *** Must jump a piece. Please retry" << endl << endl;
					moveNum -= 1;
				}
				else if (moveTo == 'B')
				{
					if (pB != '.')
					{
						cout << endl << "   *** Destination must be blank. Retry" << endl << endl;
						moveNum -= 1;
					}
					else
					{
						pL = '.';
						pG = '.';
						pB = '#';
						displayBoard();
					}
				}
				else
				{
					cout << endl << "   *** Pieces must be adjacent. Please retry" << endl << endl;
					moveNum -= 1;
				}
			}
			else
			{
				cout << endl << "   *** Pieces must be adjacent. Please retry" << endl << endl;
				moveNum -= 1;
			}
		}
		else if (moveFrom == 'J')
		{
			if (pJ != '#')
			{
				cout << endl << "   *** Source must have a piece. Please retry" << endl << endl;
				moveNum -= 1;
			}
			else if (jump == 'F')
			{
				if (pF != '#')
				{
					cout << endl << "   *** Must jump a piece. Please retry" << endl << endl;
					moveNum -= 1;
				}
				else
				{
					if (moveTo == 'B')
					{
						if (pB != '.')
						{
							cout << endl << "   *** Destination must be blank. Retry" << endl << endl;
							moveNum -= 1;
						}
						else
						{
							pJ = '.';
							pF = '.';
							pB = '#';
							displayBoard();
						}
					}
					else
					{
						cout << endl << "   *** Pieces must be adjacent. Please retry" << endl << endl;
						moveNum -= 1;
					}
				}
			}
			else if (jump == 'K')
			{
				if (pK != '#')
				{
					cout << endl << "   *** Must jump a piece. Please retry" << endl << endl;
					moveNum -= 1;
				}
				else if (moveTo == 'L')
				{
					if (pL != '.')
					{
						cout << endl << "   *** Destination must be blank. Retry" << endl << endl;
						moveNum -= 1;
					}
					else
					{
						pJ = '.';
						pK = '.';
						pL = '#';
						displayBoard();
					}
				}
				else
				{
					cout << endl << "   *** Pieces must be adjacent. Please retry" << endl << endl;
					moveNum -= 1;
				}
			}
			else if (jump == 'G')
			{
				if (pG != '#')
				{
					cout << endl << "   *** Must jump a piece. Please retry" << endl << endl;
					moveNum -= 1;
				}
				else if (moveTo == 'D')
				{
					if (pD != '.')
					{
						cout << endl << "   *** Destination must be blank. Retry" << endl << endl;
						moveNum -= 1;
					}
					else
					{
						pJ = '.';
						pG = '.';
						pD = '#';
						displayBoard();
					}
				}
				else
				{
					cout << endl << "   *** Pieces must be adjacent. Please retry" << endl << endl;
					moveNum -= 1;
				}
			}
			else
			{
				cout << endl << "   *** Pieces must be adjacent. Please retry" << endl << endl;
				moveNum -= 1;
			}
		}
		else if (moveFrom == 'F')
		{
			if (pF != '#')
			{
				cout << endl << "   *** Source must have a piece. Please retry" << endl << endl;
				moveNum -= 1;
			}
			else if (jump == 'G')
			{
				if (pG != '#')
				{
					cout << endl << "   *** Must jump a piece. Please retry" << endl << endl;
					moveNum -= 1;
				}
				else if (moveTo == 'H')
				{
					if (pH != '.')
					{
						cout << endl << "   *** Destination must be blank. Retry" << endl << endl;
						moveNum -= 1;
					}
					else
					{
						pF = '.';
						pG = '.';
						pH = '#';
						displayBoard();
					}
				}
				else
				{
					cout << endl << "   *** Pieces must be adjacent. Please retry" << endl << endl;
					moveNum -= 1;
				}
			}
			else
			{
				cout << endl << "   *** Pieces must be adjacent. Please retry" << endl << endl;
				moveNum -= 1;
			}
		}
		else if (moveFrom == 'C')
		{
			if (pC != '#')
			{
				cout << endl << "   *** Source must have a piece. Please retry" << endl << endl;
				moveNum -= 1;
			}
			else if (jump == 'G')
			{
				if (pG != '#')
				{
					cout << endl << "   *** Must jump a piece. Please retry" << endl << endl;
					moveNum -= 1;
				}
				else if (moveTo == 'K')
				{
					if (pK != '.')
					{
						cout << endl << "   *** Destination must be blank. Retry" << endl << endl;
						moveNum -= 1;
					}
					else
					{
						pC = '.';
						pG = '.';
						pK = '#';
						displayBoard();
					}
				}
				else
				{
					cout << endl << "   *** Pieces must be adjacent. Please retry" << endl << endl;
					moveNum -= 1;
				}
			}
			else
			{
				cout << endl << "   *** Pieces must be adjacent. Please retry" << endl << endl;
				moveNum -= 1;
			}
		}
		else if (moveFrom == 'H')
		{
			if (pH != '#')
			{
				cout << endl << "   *** Source must have a piece. Please retry" << endl << endl;
				moveNum -= 1;
			}
			else if (jump == 'G')
			{
				if (pG != '#')
				{
					cout << endl << "   *** Must jump a piece. Please retry" << endl << endl;
					moveNum -= 1;
				}
				else if (moveTo == 'F')
				{
					if (pF != '.')
					{
						cout << endl << "   *** Destination must be blank. Retry" << endl << endl;
						moveNum -= 1;
					}
					else
					{
						pH = '.';
						pG = '.';
						pF = '#';
						displayBoard();
					}
				}
				else
				{
					cout << endl << "   *** Pieces must be adjacent. Please retry" << endl << endl;
					moveNum -= 1;
				}
			}
			else
			{
				cout << endl << "   *** Pieces must be adjacent. Please retry" << endl << endl;
				moveNum -= 1;
			}
		}
		else if (moveFrom == 'K')
		{
			if (pK != '#')
			{
				cout << endl << "   *** Source must have a piece. Please retry" << endl << endl;
				moveNum -= 1;
			}
			else if (jump == 'G')
			{
				if (pG != '#')
				{
					cout << endl << "   *** Must jump a piece. Please retry" << endl << endl;
					moveNum -= 1;
				}
				else if (moveTo == 'C')
				{
					if (pC != '.')
					{
						cout << endl << "   *** Destination must be blank. Retry" << endl << endl;
						moveNum -= 1;
					}
					else
					{
						pK = '.';
						pG = '.';
						pC = '#';
						displayBoard();
					}
				}
				else
				{
					cout << endl << "   *** Pieces must be adjacent. Please retry" << endl << endl;
					moveNum -= 1;
				}
			}
			else
			{
				cout << endl << "   *** Pieces must be adjacent. Please retry" << endl << endl;
				moveNum -= 1;
			}
		}
		else if (moveFrom == 'G')
		{
			if (pG != '#')
			{
				cout << endl << "   *** Source must have a piece. Please retry" << endl << endl;
				moveNum -= 1;
			}
			else if (jump == 'C')
			{
				if (pC != '#')
				{
					cout << endl << "   *** Must jump a piece. Please retry" << endl << endl;
					moveNum -= 1;
				}
				else
				{
					if (moveTo == 'A')
					{
						if (pA != '.')
						{
							cout << endl << "   *** Destination must be blank. Retry" << endl << endl;
							moveNum -= 1;
						}
						else
						{
							pG = '.';
							pC = '.';
							pA = '#';
							displayBoard();
						}
					}
					else
					{
						cout << endl << "   *** Pieces must be adjacent. Please retry" << endl << endl;
						moveNum -= 1;
					}
				}
			}
			else if (jump == 'H')
			{
				if (pH != '#')
				{
					cout << endl << "   *** Must jump a piece. Please retry" << endl << endl;
					moveNum -= 1;
				}
				else if (moveTo == 'I')
				{
					if (pI != '.')
					{
						cout << endl << "   *** Destination must be blank. Retry" << endl << endl;
						moveNum -= 1;
					}
					else
					{
						pG = '.';
						pH = '.';
						pI = '#';
						displayBoard();
					}
				}
				else
				{
					cout << endl << "   *** Pieces must be adjacent. Please retry" << endl << endl;
					moveNum -= 1;
				}
			}
			else if (jump == 'F')
			{
				if (pF != '#')
				{
					cout << endl << "   *** Must jump a piece. Please retry" << endl << endl;
					moveNum -= 1;
				}
				else if (moveTo == 'E')
				{
					if (pE != '.')
					{
						cout << endl << "   *** Destination must be blank. Retry" << endl << endl;
						moveNum -= 1;
					}
					else
					{
						pG = '.';
						pF = '.';
						pE = '#';
						displayBoard();
					}
				}
				else
				{
					cout << endl << "   *** Pieces must be adjacent. Please retry" << endl << endl;
					moveNum -= 1;
				}
			}
			else if (jump == 'K')
			{
				if (pK != '#')
				{
					cout << endl << "   *** Must jump a piece. Please retry" << endl << endl;
					moveNum -= 1;
				}
				else if (moveTo == 'M')
				{
					if (pM != '.')
					{
						cout << endl << "   *** Destination must be blank. Retry" << endl << endl;
						moveNum -= 1;
					}
					else
					{
						pG = '.';
						pK = '.';
						pM = '#';
						displayBoard();
					}
				}
				else
				{
					cout << endl << "  *** Pieces must be adjacent. Please retry" << endl << endl;
					moveNum -= 1;
				}
			}
			else
			{
				cout << endl << "   *** Pieces must be adjacent. Please retry" << endl << endl;
				moveNum -= 1;
			}
		}

		moveNum += 1;
}
// ----------------------------------------------------------------------
// Main section of the program, containing the game play loop

int main()
{
	displayInstructions();

	int moveNum = 1;
	int run = 0;
	int numberOfPieces = 13;

	char moveFrom;
	char jump;
	char moveTo;

	// Set board values to the default starting position
	reinitializeBoard();

	// Game play loop
	while (true)
	{
		if (run == 0)
		{
			displayBoard();
			run += 1;
		}

		numberOfPieces -= 1;

		if (numberOfPieces != 1)
		{
			cout << moveNum << ". " <<
				"Enter positions from, jump, and to (e.g. EFG): ";

		}

		cin >> moveFrom;
		moveFrom = toupper(moveFrom);	// Fold input into upper case to simplify later comparisons

		if (numberOfPieces == 1)
		{
			cout << endl << "Congratulations, you did it!" << endl;
			break;
		}

		if (moveFrom == 'X')
		{
			cout << "Exiting" << endl;
			if (numberOfPieces != 1)
			{
				cout << endl << "Better luck next time." << endl;
			}

			break;
		}

		if (moveFrom == 'R')
		{
			cout << endl << "   *** Restarting" << endl;
			reinitializeBoard();
			displayBoard();
			moveNum = 1;
			numberOfPieces = 13;
			continue;
		}

		cin >> jump;	// Read just the first user input, handling inputs 'X' or 'R'
		cin >> moveTo;

		jump = toupper(jump);
		moveTo = toupper(moveTo);

		gameLogic(moveFrom,jump,moveTo,moveNum);
	}

	cout << "Done." << endl;
	return 0;
}

// If 'X' to exit was chosen, break out of game play loop
// ...

// If 'R' to reset the board was chosen, reinitialize everything
// display the board, and continue back up to re-run the while(...) loop
// ...

// Additionally now also read the piece-to-jump and destination inputs.
// ...

// Ensure set of pieces (from, jump, to) are adjacent.  If they aren't, then
// continue back up to re-run the while(...) loop.
// ...

// Ensure location we're moving FROM has a PlayerPiece in it. If it doesn't, then
// continue back up to re-run the while(...) loop.
// ...

// Ensure piece being jumped isn't blank. If it is, then
// continue back up to re-run the while(...) loop.
// ...

// Ensure location we're moving TO is blank. If it is not, then
// continue back up to re-run the while(...) loop.
// ...

// Make the move and display the board
// ...

//end while(numberOfPieces > 1)
// Check for a win
// ...
//end main()