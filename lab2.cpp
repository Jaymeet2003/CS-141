// Jaymeet Patel (656971609)


#include <iostream>

using namespace std;

void diamond(int inpVal)
{
	int spaceBetween = inpVal - 1;
	for (int i = 0; i < inpVal; i++)
	{
		for (int j = 0;j < spaceBetween; j++)
			cout << " ";

		for (int j = 0; j <= i; j++)
			cout << "* ";

		cout << endl;
		spaceBetween--;
	}
	spaceBetween = 0;

	for (int i = inpVal; i > 0; i--)
	{

		for (int j = 0; j < spaceBetween; j++)
			cout << " ";

		for (int j = 0;j < i;j++)
			cout << "* ";

		cout << endl;
		spaceBetween++;
	}
}

void square(int inpVal){
    for (int i = 1; i <= inpVal; i++)
        {
            for(int j=1; j <= inpVal; j++){
                cout<<"*";
            }
            cout<<endl;
        }
}

void triangle(int inpVal){
     for (int i = 0; i <= inpVal; i+=2)
        {
            for(int j=0; j<=i; j++){
                cout<<"*";
            }
            cout<<endl;
        }
}

int main()
{
    int menuOption = 0;
    int theSize;

    cout << "Welcome to pattern maker." << "\n"
        << "Enter the pattern type (1: Square, 2: Triangle, 3: Diamond): ";
   cin >> menuOption; 
   cout << "Enter an odd integer for the size: ";
   cin >> theSize;
   cout << endl;

   switch( menuOption) {
      case 1: square(theSize); break;
      case 2: triangle(theSize); break;
      case 3: diamond(theSize); break;
      default: cout << "Invalid option chosen.  Exiting..." << endl;
               exit( -1);
               break;
   }
    cout<<"Done.";
	return 0;
}
