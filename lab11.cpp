#include <iostream>
#include <string.h>
#include <ctype.h>
using namespace std;


//------------------------- Sample -----------------------------
// Iteratively (non-recursively) display numbers up to some limit
void sampleIterative( int counter, int limit)
{
// Display numbers up to the limit
while( counter < limit) {
    cout << counter << " ";
    counter++;
}
cout << endl;   // display a new line
}//end sampleIterative()


// Same thing, now using recursion
void sampleRecursive( int counter, int limit)
{
// Check for the base condition
if( counter == limit) {   // this tells the recursive function when to stop
    cout << endl;
}
else {
    cout << counter << " ";
    // make the recursive call
    sampleRecursive( ++counter, limit);       // function calls itself
}
}//end sampleRecursive()


//------------------------- Problem 1 (1 point) --------------------------
// Display odd numbers less than some limit
void problemOneOddNumbersIterative( int counter, int limit)
{
// Display numbers up to the limit
while( counter < limit) {
    if( counter % 2 == 1) {
        cout << counter << " ";
    }
    counter++;
}
cout << endl;   // display a new line
}//end problemOneOddNumbersIterative()


// Same thing, now done recursively.   >>> YOU SUPPLY CODE IN THIS FUNCTION <<<
void problemOneOddNumbersRecursive( int counter, int limit)
{
   //*** WRITE YOUR CODE HERE for problem 1 ...
   
   // Check for the base condition
if( counter == limit) {   // this tells the recursive function when to stop
    cout << endl;
}
else {
    if (counter % 2 == 1){
        cout << counter << " ";
      }
    // make the recursive call
    problemOneOddNumbersRecursive( ++counter, limit);       // function calls itself
}

}//end problemOneOddNumbersRecursive()


//------------------------- Problem 2 (1 point) --------------------------
// Count the number of upper-case letters in an array
int problemTwoCountUpperIterative( long unsigned int index, string letters)
{
int counter = 0;
while( index < letters.length() ) {
    char currentChar = letters[ index]; // first character
    // If the current character is upper case, increment counter
    if( isupper( currentChar)) {
        counter++;
    }
    // advance pointer to next character
    index++;
}
return counter;
}//end problemTwoCountUpperIterative()


// Same thing, now done recursively.
  int problemTwoCountUpperRecursive(long unsigned int index, string arrayOfLetters){
 
if(index>=arrayOfLetters.size()){
return 0;
}
if(isupper(arrayOfLetters[index])){
return 1 + problemTwoCountUpperRecursive(index+1,arrayOfLetters);
}
else{
return problemTwoCountUpperRecursive(index+1,arrayOfLetters);
}
}//end problemTwoCountUpperRecursive()


//------------------------- Problem 3 (1 point extra credit) --------------------------
// Display the Fibonacci numbers up to some limit.
// Fill out problemThreeFibonacci to display the Fibonacci numbers up to a certain amount
// The Fibonacci sequence fib( n) is defined as: fib( n-1) + fib( n-2)
// The Fibonacci numbers less than 15 are: 0 1 1 2 3 5 8 13
// Write it for them, but leave out part(s)...
// Uncomment the lines shown below to get started
void problemThreeFibonacci(int fibNum1, int fibNum2, int limit)
{
// Possible cout location
int sum = fibNum1 + fibNum2;
if ((sum) > limit) { // Base case
      exit(0);
  }
  else { // Recursive case

// // Possible cout location
cout << sum << " ";
// // Does the limit change when we recursively call the function?
problemThreeFibonacci(fibNum2, sum, limit);
  }
// // Possible cout location

}//end problemThreeFibonacci()


//----------------------------------------------------------
//YOU SHOULD NOT EDIT CODE IN THE MAIN() FUNCTION
//----------------------------------------------------------
int main()
{
cout<<"\nEnter a choice:";
cout<<"\n 0. Problem 0: Display counts";
cout<<"\n 1. Problem 1: Odd Numbers";
cout<<"\n 2. Problem 2: Count Upper Case";
cout<<"\n 3. Exit\n";
int choice;
cin>> choice;
switch(choice){
    case 0:
    {
        //------------------------------------------------------
        // Problem 0:  This one is an already completed example.
        // Count to some limit using a while loop.
        // Then the recursive version does the same thing.
        // For the other functions below you will be given the iterative (non-recursive)
        // version, and will have to create the recursive version.
        int counter = 0;
        int limit;
        cout << "Sample Problem \n";
        cout << "Enter the limit: ";
        cin >> limit;
        sampleIterative( counter, limit); // Iterative (non-recursive) version
        sampleRecursive( counter, limit); // Recursive version
        break;
    }
    case 1:
    {
        //------------------------------------------------------
        // Problem 1: Display the odd numbers less than some limit
        int counter = 0;
        int limit;
        cout << "Problem 1 \n";
        cout << "Enter the limit: ";
        cin >> limit;
        problemOneOddNumbersIterative( counter, limit);
        problemOneOddNumbersRecursive( counter, limit);  // <-- you supply the code for this one
        cout << "\n\n";
        break;
    }
    case 2:
    {
        //------------------------------------------------------
        // Problem 2: Given a C string, count how many characters are upper-case
        char arrayOfLetters[ 81];
        cout << "Problem 2 \n";
        cout << "Enter a line of input with mixed-case letters: ";
        int counter = 0;
        // First get rid of carriage-return lingering on input buffer from previous question
        char c;
        cin.get( c);
        // Now read in user input
        cin.getline( arrayOfLetters, 81); // read in an entire line
        string input(arrayOfLetters);
        cout << "Number of upper-case done Iteratively is: "
              << problemTwoCountUpperIterative( 0, arrayOfLetters) << endl;
        cout << "Number of upper-case done Recursively is: "
              << problemTwoCountUpperRecursive( counter, input)  // <-- you supply the code for this one
              << endl;
        cout << endl;
        break;
    }

    case 3:
    {
        int limit;

        cout << "Problem 3 \n";
        cout << "Please enter a limit for Fibonacci: ";
        cin >> limit;

        cout << 0 << " " << 1 << " ";
        problemThreeFibonacci(0, 1, limit);

    }
}

}//end main()
