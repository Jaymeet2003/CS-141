/* ---------------------------------------------
    Program 1: Gladiolus
    UIN: 656971609
    Name: Jaymeet Patel
    --------------------------------------------
*/

#include <iostream>   // for cin and cout
#include <iomanip>    // for setw. The number in setw(...) is the total of blank spaces including the printed item.
using namespace std;  // so that we don't need to preface every cin and cout with std::

// Entire program is given inside of main(), which is acceptable since this is the first program.

// defining function for gladiolus

void gladiolus(int inpVal){
    int MAXWIDTH = ((inpVal*2)+3);
    int lineSpace = (MAXWIDTH/2)+2;
    int numberOfLines,totalNumberOfSpaces,numberOfSpaces,temp;

    //printing flower

    cout<<setw(lineSpace)<<"---"<<endl;
   for(int j = 1; j< (inpVal*2)+1; j += 2){

        numberOfLines = j; //initializing number of lines to print in look by iterating

        for(int bracketPosition = 1; bracketPosition <= numberOfLines/2 +1; bracketPosition ++){
            for (int i = 0; i < MAXWIDTH; i++)
            {
                if(i == MAXWIDTH/2 - bracketPosition - 1){
                    cout<<"(";
                }else if (i== MAXWIDTH/2 + bracketPosition + 1) {
                    cout<<")";
                }else if(i == MAXWIDTH/2 && bracketPosition == numberOfLines/2+1){
                    cout<<"@"; // printing @ in the middle row of every section
                }else if (i < MAXWIDTH/2 + bracketPosition + 1){
                    cout<<" "; // spacing between the brackets
                }
                                
            }
            cout<<endl;
            
        }
        for(int bracketPosition = numberOfLines/2; bracketPosition >=1; bracketPosition --){
            for (int i = 0; i < MAXWIDTH; i++)
            {
                if(i == MAXWIDTH/2 - bracketPosition - 1){
                    cout<<"(";
                }else if (i== MAXWIDTH/2 + bracketPosition + 1) {
                    cout<<")";
                }else if (i < MAXWIDTH/2 + bracketPosition + 1){
                    cout<<" ";
                }
                                
            }
            cout<<endl;
            
        }
        cout<<setw(lineSpace)<<setfill(' ')<<"---"<<endl;
    }
    
    // printing the stem of the flower
    for(int i = 1; i <= inpVal; i ++){
            if (i %2 != 0)
            {
                cout <<setw(lineSpace-1)<<setfill(' ')<< "|" << "/"<< endl;
                cout <<setw(lineSpace-1)<<setfill(' ')<< "|" << endl;
            }else{
                cout <<setw(lineSpace-2)<<setfill(' ')<<"\\" << "|"<< endl;
                cout <<setw(lineSpace-1)<<setfill(' ')<< "|" << endl;
            }
    }
    
}

// defining function for graphic

void ownGraphic(){

        cout << setw( 8) << " ";
        // Display a line across the top
        for( int i=0; i<72; i++) {
           cout << "-";
        }
        cout << endl;
        // Display ASCII graphics for "CS 141".  Yours must be different!
        cout<< setw( 8) << " " << "         _________    _________                                                                       \n"
             << setw( 8) << " " << "             |            |         |\\    /|  |\\    /| \\     /                                    \n"
             << setw( 8) << " " << "             |            |         | \\  / |  | \\  / |  \\   /                                     \n"
             << setw( 8) << " " << "             |            |         |  \\/  |  |  \\/  |   \\ /                                    \n"
             << setw( 8) << " " << "             |            |         |      |  |      |    /                                   \n"
             << setw( 8) << " " << "             |            |         |      |  |      |   /                                 \n"
             << setw( 8) << " " << "    \\       /             |         |      |  |      |  /                                  \n"
             << setw( 8) << " " << "     \\_____/        ______|_______  |      |  |      | /                                     \n"
             << endl;
        cout << setw( 8) << " ";
        // Display a line across the bottom
        for( int i=0; i<72; i++) {
            cout << "-";
        }
        cout << endl;

}


int main() {

    // Display the menu and get the user choice
    int menuOption = 0;
    cout << "Program 1: Gladiolus            \n"
         << "Choose from among the following options:  \n"
         << "   1. Display original graphic  \n"
         << "   2. Display Gladiolus         \n"
         << "   3. Exit the program          \n"
         << "Your choice -> ";
    cin >> menuOption;
    
    // Handle menu option of 3 to exit
    if( menuOption == 3) {
        exit( 0);
    }
    // Handle menu option of 1 to display custom ASCII graphics
    else if( menuOption == 1) {
        // My own graphic.  You must create your own.

        ownGraphic(); // calling function to diaplay graphic


    } //end if( menuOption == 1)  // menu option to display custom graphic

    else if( menuOption == 2) {
        // Prompt for and get the number of flower sections.
        int numberOfSections = 0;
        cout << "Number of sections -> ";
        cin >> numberOfSections;
        
        gladiolus(numberOfSections); // calling the function
        
        
    } //end if( menuOption == 2) // menu option to display building
            
    cout << "Exiting" << endl;
    return 0;
}// end main()
