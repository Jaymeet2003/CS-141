#include <iostream>

#include <string>

using namespace std;

 

 

/*

    

   REVERSE All BUT FIRST AND LAST

    

   1. Reverse All But First and Last  

   2. Count Number of Equal Characters  

   3. Number of Mirror Pair Comparisons  

   4. Exit  

   Enter your choice 1-4: 1

   Enter the string you would like: Bumfuzzle

   All but first and last string: Blzzufmue

 

 

   COUNT EQUAL CHARS:

    

   1. Reverse All But First and Last  

   2. Count Number of Equal Characters  

   3. Number of Mirror Pair Comparisons  

   4. Exit  

   Enter your choice 1-4: 2

   Enter the first string you would like to compare: good

   Enter the second string you would like to compare: more  

   Num equal: 1

 

 

   MIRROR PAIR COMPARISONS:

    

   1. Reverse All But First and Last  

   2. Count Number of Equal Characters  

   3. Number of Mirror Pair Comparisons  

   4. Exit  

   Enter your choice 1-4: 3

   Enter the first string you would like to compare: goodcar

   Enter the second string you would like to compare: badcar

   Num equal: 0

 

 

*/

 

//  Please insert the parameters that you think are required to finish the function declaration

//  You need to update the value sent as a parameter

void reverseAllButFirstAndLast(string& str){

   string newStr;

   newStr.push_back(str.at(0));

   for (long unsigned int i = str.size() - 2; i >= 1; --i){

  	newStr.push_back(str.at(i));

   }

   newStr.push_back(str.at(str.size() - 1));

   str = newStr;

}

 

 

//  Please enter the values into the parameters that you think will be required to finish the function

//  Returns the number of characters that are equal between two strings

int countEqualChars(string s1, string s2){

   int equal = 0;

   for (long unsigned int i = 0; i < s1.size(); ++i){

  	if (s1.at(i) == s2.at(i)) {

     	equal++;

  	}

   }

    

	//DON'T FORGET TO CHANGE THIS

	return equal;

 

}

 

//  Takes in two strings and returns the number of characters that are equal when one of the strings is reversed

int mirrorPairComparisons(string s1, string s2){

    

   string newS2;

   for (int i = s2.size() - 1; i >= 0; --i){

  	newS2.push_back(s2.at(i));

   }

   s2 = newS2;

    

   return countEqualChars(s1, s2);

 

}

 

 

int main(){

 

	int functionNumber;

 

	cout << "   1. Reverse All But First and Last \n"

     	<< "   2. Count Number of Equal Characters \n"

     	<< "   3. Number of Mirror Pair Comparisons \n"

     	<< "   4. Exit \n"

     	<< "Enter your choice 1-4: ";

	cin >> functionNumber;

 

	if(functionNumber == 4) {

    	exit(0);  // Exit the program

	}

	string s1, s2;

	switch(functionNumber) {

    	case 1: {

        	cout << "Enter the string you would like: ";

        	cin >> s1;

        	 

        	// ENTER PARAMETERS INTO FUNCTION

        	reverseAllButFirstAndLast(s1);

        	 

        	//  Print out reversed all but first and last string

        	cout << "All but first and last string: " << s1 << endl;

        	break;

    	}

    	case 2: {

        	cout << "Enter the first string you would like to compare: ";

        	cin >> s1;

 

        	cout << "Enter the second string you would like to compare: ";

        	cin >> s2;

        	 

        	// ENTER PARAMETERS INTO FUNCTION

        	int numEqual = countEqualChars(s1,s2);

        	cout << "Num equal: " << numEqual;

        	break;

    	}

 

    	case 3: {

        	cout << "Enter the first string you would like to compare: ";

        	cin >> s1;

 

        	cout << "Enter the second string you would like to compare: ";

        	cin >> s2;

        	 

        	// ENTER PARAMETERS INTO FUNCTION

        	int numMirrorEqual = mirrorPairComparisons(s1,s2);

        	cout << "Mirror Num equal: " << numMirrorEqual;

        	break;

    	}

    	default:

        	break;

	}

 

	return 0;

}

