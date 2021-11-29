/* prog3TypingTutor.cpp
    Typing tutor program prompts user to type in a set of words within a
    time limit. Words are taken randomly from either a list of commonly
    misspelled words, or from a large dictionary of words.
    
    Author: Dale Reed
    Date: 9/28/2021
    Class: CS 141, Fall 2021, UIC
    System: Xcode on iMac
*/

#include <iostream>   // For Input and Output
#include <fstream>    // For file input and output
#include <cassert>    // For the assert statement
#include <cctype>     // Allows using the tolower() function
#include <vector>     // For vectors
#include <ctime>      // Timer functions
using namespace std;

//--------------------------------------------------------------------------------
// Display name and program information
void displayIdentifyingInformation()
{
    cout << "  \n"
         << "Program: #3, Typing Tutor  \n"
         << "CS 141, Fall 2021          \n"
         << endl;
}//end displayIdentifyingInformation()


//--------------------------------------------------------------------------------
// Use binary search to look up a search word in the dictionary vector, returning
// the index if found, -1 otherwise.
long binarySearch( string searchWord,            // Word we are searching for
                   vector< string> dictionary)   // Dictionary of words as a vector
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
        cout << "     " << guessNumber++ << ". Comparing to: " << dictionary[ mid] << endl;
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
void readWordsIntoDictionary(
        vector <string> & dictionary,   // Dictionary where words will be stored
        char fileName[])                // File name where words will be read from
{
    ifstream inStream;                      // Declare an input stream for reading
    inStream.open( fileName);               // Open dictionary file
    assert( inStream.fail() == false );     // Ensure file open worked
    
    // Clear vector in case it already had some words in it
    dictionary.clear();
    
    // Keep repeating while input from the file yields a word
    string newWord;                         // Store a single input word
    while( inStream >> newWord) {           // While there is another word to be read
        // Add this new word to the end of the vector, growing it in the process
        dictionary.push_back( newWord);
    }
    
    // Close the dictionary file
    inStream.close();
} //end readWordsIntoDictionary()


//---------------------------------------------------------------------------
// Read in set of ~100 commonly misspelled words.  Each line has a common
// misspelling followed by the correct spelling.  These are read into two
// separate vectors: dictionary and correctSpellings.
void readCommonMisspelledWords(
        vector <string> & dictionary,         // Dictionary for incorrectly spelled words
        vector <string> & correctSpellings,   // Dictionary for corresponding correctly spelled words
        char fileName[])                      // File name where words will be read from
{
    ifstream inStream;                      // Declare an input stream for reading
    inStream.open( fileName);               // Open dictionary file
    assert( inStream.fail() == false );     // Ensure file open worked
    
    // Clear vectors in case they already had some words in them
    dictionary.clear();
    correctSpellings.clear();
    
    // Keep repeating while input from the file yields a word
    string incorrectWord, correctWord;      // Store the incorrect and correct words from each input line
    while( inStream >> incorrectWord >> correctWord ) {   // While there is another word pair to be read
        // Add the incorrect and correct new words to their respective vectors, growing them in the process
        dictionary.push_back( incorrectWord);
        correctSpellings.push_back( correctWord);
    }
    
    // Close the dictionary file
    inStream.close();
} //end readCommonMisspelledWords()


//---------------------------------------------------------------------------
// Calculate and display the score for this move based on the number of words
// spelled correctly/incorrectly and the length of time taken.
int calculateAndDisplayScore(
        int elapsedSeconds,             // How long the move took
        int timeLimit,                  // Expected time limit
        int wordLength,                 // Length of words (when using large dictionary)
        int howManyWords,               // How many words are being displayed to be typed
        int numberOfMisspelledWords)    // How many words were typed incorrectly
{
    int score = 0;      // Value will be computed and returned at the end
    
    // Handle bonus/penalty for time
    int timePointsAdjustment = 0;
    if( elapsedSeconds < timeLimit) {
        // Bonus for finishing under the designated number of seconds
        timePointsAdjustment = (timeLimit - elapsedSeconds) * 2;
        cout << timePointsAdjustment << " point bonus for finishing " << (timeLimit - elapsedSeconds)
             << " seconds early.";
    }
    if( elapsedSeconds > timeLimit) {
        timePointsAdjustment = -1 * (elapsedSeconds - timeLimit) * 3;
        cout << timePointsAdjustment << " points for finishing " << (elapsedSeconds - timeLimit)
             << " seconds late.";
    }
    cout << endl;

    // Calculate the number of points per word.
    int pointsPerWord = 3;          // The default, used for commonly misspelled words
    int incorrectWordDeduction = 0; // Stores deduction points for incorrectly spelled words
    if( wordLength != 0) {
        // We're using the full dictionary, not commonly misspelled words, so points per word
        // is relative to the word length.
        pointsPerWord = wordLength - 4;
    }
    // Handle score calculation based on number spelled correctly/incorrectly
    int numberOfCorrectWords = howManyWords - numberOfMisspelledWords;
    cout << "   " << numberOfCorrectWords * pointsPerWord << " points: " << numberOfCorrectWords
         << " spelled correctly x " << pointsPerWord << " points each" << endl;
    // Only display the misspellings penalty if some words were missed
    if( numberOfMisspelledWords > 0) {
        incorrectWordDeduction = pointsPerWord * 2;
        cout << "   " << numberOfMisspelledWords * incorrectWordDeduction << " point penalty: "
             << numberOfMisspelledWords << " spelled incorrectly x "
             << incorrectWordDeduction << " points each" << endl;
    }
    
    // Calculate and display score based on number of misspellings and time, as shown above
    score = (numberOfCorrectWords * pointsPerWord) -
            (numberOfMisspelledWords * incorrectWordDeduction) + timePointsAdjustment;
    cout << "   " << "Score: " << score
         << endl;
         
    return score;
} //end calculateAndDisplayScore()


//---------------------------------------------------------------------------
// Do the word test, giving a limited length of time for the user to type in
// a set of randomly selected words.
//    This same function is used both for typing randomly selected words from the
// dictionary, as well as in typing randomly selected words from the list of
// commonly misspelled words.
//    The second parameter gives the vector of correctly spelled words to compare
// against. In the case of using normal dictionary words, both parameters point to
// the same dictionary.  In the case of using commonly misspelled words, the two are
// different.
//    The last parameter is a default parameter. It is used only when using the full
// dictionary, not when using the commonly misspelled words.  It determines what
// length words will be used.  Longer words give higher scores.
void wordTest(
        vector <string> wordsToUse,           // Randomly selected words to be typed
        vector <string> dictionaryForLookups, // Dictionary to use to find correctly spelled words
        int &score,                           // Score on this run
        int wordLength = 0)                   // Default parameter, not used w/commonly misspelled words
{
    int howManyWords = 5;   // How many words to be typed
    int timeLimit = 15;     // How many seconds the user has to type in the words
    vector <string> wordsToType;
    vector <string> correctlySpelledWords;
    vector <string> userTypedWords;
    
    // Select some number of randomly selected words to be typed, displaying them and storing
    // them into a vector. Store the correctly spelled versions of each one in a parallel array.
    // We use a while loop here rather than a for loop to facilitate the use of the continue
    // statement, used when working with the full dictionary, to only choose certain length words.
    int i = 0;
    while( i<howManyWords) {
        int wordIndex = rand() % wordsToUse.size();         // Generate an index for some random word
        // Validate word length, but only when using the full dictionary and wordLength is non-zero
        if( wordLength != 0 && wordsToUse.at( wordIndex).length() != wordLength) {
            continue;   // Try again, until we find the correct length word
        }
        wordsToType.push_back( wordsToUse.at( wordIndex));  // Add this word to the list of words to be typed
        cout << wordsToUse.at( wordIndex) << " ";           // Display the word
        correctlySpelledWords.push_back( dictionaryForLookups.at( wordIndex));  // Store correct spelling
        i++;
    }
    cout << endl;
    
    // Declare a variable to hold a time, and set it to the current time
    time_t startTime = time( NULL);
    int elapsedSeconds = 0;

    // Store user-typed words.
    cout << "Type in those words within goal of " << timeLimit << " seconds: " << endl;
    string userInput;
    for( int i=0; i<howManyWords; i++) {
        cin >> userInput;
        userTypedWords.push_back( userInput);
    }
    
    // Validate spelling of each user-typed word, concatenating all misspelled
    // words for display.
    int numberOfMisspelledWords = 0;
    string outputMessage = "   Misspelled words: ";
    for( int i=0; i<howManyWords; i++) {
        if( userTypedWords.at( i).compare( correctlySpelledWords.at( i)) != 0) {
            // User-typed word was not spelled correctly
            numberOfMisspelledWords++;
            outputMessage = outputMessage + "\n       " + userTypedWords.at( i) +
                            " should be: " + correctlySpelledWords.at( i);
        }
    }
    // Display misspelled words, if any
    if( numberOfMisspelledWords > 0) {
        cout << outputMessage << endl;
    }
    else {
        cout << "   No misspelled words!" << endl;
    }
    
    // Calculate the elapsed time as the difference between the current time and the start time
    elapsedSeconds = difftime( time( NULL), startTime);
    cout << "   Elapsed time: " << elapsedSeconds << " seconds. ";
    
    score = calculateAndDisplayScore( elapsedSeconds, timeLimit, wordLength, howManyWords, numberOfMisspelledWords);
    
} //end wordTest()


//---------------------------------------------------------------------------
// Display dictionary words within some valid range.
void displayDictionaryWords( vector <string> dictionary)  // Vector to store dictionary words)
{
    cout << endl
         << "   Enter the start and end indices between 0 and " << dictionary.size() - 1 << ": ";
    int start, end;
    cin >> start >> end;

    // Sanity check
    if( start < 0 || end > dictionary.size() - 1) {
        cout << "Start or end value out of bounds.  Exiting program..." << endl;
        exit( -1);
    }

    // Display the words
    for( int i=start; i<=end; i++) {
        cout << "      " << i << ". " << dictionary.at( i) << endl;
    }
} //end displayDictionaryWords()


//---------------------------------------------------------------------------
// Main loop that reads in words, then displays and processes menu options.
int main()
{
    int menuChoice;                     // Store user input for menu option chosen
    vector <string> dictionary;         // Vector to store dictionary words
    vector <string> correctSpellings;   // Vector to store correct versions of common incorrectly spelled words
    vector <string> incorrectSpellings; // Vector to store common incorrectly spelled words
    int bestScore = 0;                  // Best score
    int score = -1;                     // Current score
    int wordLength = 5;                 // Length of words currently to display
    
    // Read in words from the dictionary and commonly misspelled words files into vectors.
    readWordsIntoDictionary( dictionary, "dictionary.txt");
    readCommonMisspelledWords( incorrectSpellings, correctSpellings, "misspelledWords.txt");
    
    // For random number generation seed the random number generator to 1, so that results
    // are predictable.  To make results different every time instead you would
    // use srand( time( NULL));   Don't do this if you want your code to match test cases!
    srand( 1);
    
    cout << "There are " << dictionary.size() << " words in the full dictionary." << endl;
    cout << "There are " << incorrectSpellings.size() << " commonly misspelled words." << endl;

    // Keep looping until user selects the option to exit
    while( true) {
        cout << endl
             << "Select a menu option:" << endl
             << "   1. Spell commonly misspelled words (timed)" << endl
             << "   2. Type random words from full dictionary (timed)" << endl
             << "   3. Display some words from one of the lists" << endl
             << "   4. Use binary search to lookup a word in full dictionary" << endl
             << "   5. Set word length to use with full dictionary" << endl
             << "   6. Exit the program" << endl
             << "Your choice --> ";
        cin >> menuChoice;
        cout << endl;
        
        // Exit if option 6 to exit was chosen
        if( menuChoice == 6) {
            cout << "Exiting program" << endl;
            break;      // Break out of enclosing infinite game-play loop
        }
        
        // Reset word length if option 5 was chosen
        if( menuChoice == 5) {
            cout << "Enter new wordLength: ";
            cin >> wordLength;
            continue;   // Loop back up to retry, with new wordlength value
        }
        
        // Binary search of a word in large dictionary was chosen
        if( menuChoice == 4) {
            string wordToLookup;
            cout << "Enter the word to lookup: ";
            cin >> wordToLookup;
            if( binarySearch( wordToLookup, dictionary) != -1) {
                cout << wordToLookup << " was found.";
            }
            else {
                cout << wordToLookup << " was NOT found.";
            }
            cout << endl;
            continue;   // Loop back up to display menu
        } //end if( menuChoice == 4)
                
        // Dictionary will store commonly misspelled words
        if( menuChoice == 1) {
            cout << "Using commonly misspelled words" << endl;
            wordTest( incorrectSpellings, correctSpellings, score);
        }
        else if( menuChoice == 2) {
            cout << "Using full dictionary" << endl;
            // Do the word test, selecting random words and comparing against correctly spelled words
            wordTest( dictionary, dictionary, score, wordLength);
            wordLength++;   // Next time use words that are 1 character longer
        }
        else if( menuChoice == 3) {
            cout << "   Displaying word list entries." << endl
                 << "   Which words do you want to display?" << endl
                 << "      A. Dictionary of all words" << endl
                 << "      B. Wrongly spelled common misspelled words" << endl
                 << "      C. Correctly spelled common misspelled words" << endl
                 << "   Your choice --> ";
            char menuInput = ' ';
            cin >> menuInput;
            menuInput = toupper( menuInput);
            switch( menuInput) {
                case 'A': displayDictionaryWords( dictionary); break;
                case 'B': displayDictionaryWords( incorrectSpellings); break;
                case 'C': displayDictionaryWords( correctSpellings); break;
                default: cout << "Invalid switch - case option chosen. Exiting...";
                         exit( -1);
                         break;
            }
        } //end if( menuChoice == 3)

        // Keep track of best score
        if( score > bestScore) {
            bestScore = score;
        }

    } //end while( true)
    
    cout << "Best score was " << bestScore << endl;
    
    return 0;
}//end main()

