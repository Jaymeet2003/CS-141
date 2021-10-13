#include <iostream>
#include <stdlib.h>// the option to exit()
#include <vector>
#include <fstream>
#include <cassert>	// For the assert statement used to validate file open
#include <cctype>
#include <ctime>
using namespace std;
// void menu_display();

int menu_option_1(vector<string> misspelledWords, vector<string> correctWords, int score)
{
	score = 0;
	int numVal1, numVal2, numVal3, numVal4, numVal5, wrongWord, correctWord;
	string inpWord1, inpWord2, inpWord3, inpWord4, inpWord5;

	correctWord = 0;
	wrongWord = 0;

	numVal1 = rand() % 114;
	numVal2 = rand() % 114;
	numVal3 = rand() % 114;
	numVal4 = rand() % 114;
	numVal5 = rand() % 114;

	cout << "Using commonly misspelled words" << endl;
	cout << misspelledWords[numVal1] << " ";
	cout << misspelledWords[numVal2] << " ";
	cout << misspelledWords[numVal3] << " ";
	cout << misspelledWords[numVal4] << " ";
	cout << misspelledWords[numVal5] << " " << endl;
	cout << "Type in those words within goal of 15 seconds: " << endl;

	int elapsedSeconds = 0;	// Will store number of elapsed seconds

	// Declare a variable to hold a time, and set it to the current time
	time_t startTime = time(NULL);

	cin >> inpWord1;
	cin >> inpWord2;
	cin >> inpWord3;
	cin >> inpWord4;
	cin >> inpWord5;

	elapsedSeconds = difftime(time(NULL), startTime);

	int compareValue1 = correctWords.at(numVal1).compare(inpWord1);
	int compareValue2 = correctWords.at(numVal2).compare(inpWord2);
	int compareValue3 = correctWords.at(numVal3).compare(inpWord3);
	int compareValue4 = correctWords.at(numVal4).compare(inpWord4);
	int compareValue5 = correctWords.at(numVal5).compare(inpWord5);

	if (compareValue1 == 0 && compareValue2 == 0 && compareValue3 == 0 && compareValue4 == 0 && compareValue5 == 0)
	{
		cout << "No misspelled words!" << endl;
		correctWord = 5;
		wrongWord = 0;
	}
	else if (compareValue1 != 0 || compareValue2 != 0 || compareValue3 != 0 || compareValue4 != 0 || compareValue5 != 0)
	{
		cout << "Misspelled words:" << endl;

		if (compareValue1 == 0)
		{
			correctWord++;

		}
		else if (compareValue1 != 0)
		{
			++wrongWord;
			cout << " " << inpWord1 << " should be: " << correctWords[numVal1] << endl;
		}

		if (compareValue2 == 0)
		{
			correctWord++;

		}
		else if (compareValue2 != 0)
		{
			++wrongWord;
			cout << inpWord2 << " should be: " << correctWords[numVal2] << endl;
		}

		if (compareValue3 == 0)
		{
			correctWord++;

		}
		else if (compareValue3 != 0)
		{
			++wrongWord;
			cout << inpWord3 << " should be: " << correctWords[numVal3] << endl;
		}

		if (compareValue4 == 0)
		{
			correctWord++;

		}
		else if (compareValue4 != 0)
		{
			++wrongWord;
			cout << inpWord4 << " should be: " << correctWords[numVal4] << endl;
		}

		if (compareValue5 == 0)
		{
			correctWord++;

		}
		else if (compareValue5 != 0)
		{
			++wrongWord;
			cout << inpWord5 << " should be: " << correctWords[numVal5] << endl;
		}
	}

	cout << "Elapsed time: " << elapsedSeconds << " seconds.";

	if (elapsedSeconds < 15)
	{
		int x = 15 - elapsedSeconds;
		int y = x * 2;
		cout << " " << y << " point bonus for finishing " << x << " seconds early." << endl;
		score += y;
	}
	else if (elapsedSeconds > 15)
	{
		int z = elapsedSeconds - 15;
		int c = z * 3;

		cout << " " << z << " deduction for going over 15 seconds" << endl;
		score -= c;

	}

	int score1 = correctWord * 3;
	score += score1;
	cout << score1 << " points: " << correctWord << " spelled correctly x 3 points each" << endl;

	int score2 = (wrongWord) *6;
	score -= score2;
	if (wrongWord != 0)
	{
		cout << score2 << " point penalty: " << wrongWord << " spelled incorrectly x 6 points each" << endl;
	}

	cout << "Score: " << score << endl;
	return score;

}

int menu_option_2(vector<string> dictionary, int word_length, int score, int l)
{
	score = 0;
	int numVal1, numVal2, numVal3, numVal4, numVal5, t;
	int correctWord = 0;
	int wrongWord = 0;
	string inpWord1, inpWord2, inpWord3, inpWord4, inpWord5;

	numVal1 = rand() % dictionary.size();
	numVal2 = rand() % dictionary.size();
	numVal3 = rand() % dictionary.size();
	numVal4 = rand() % dictionary.size();
	numVal5 = rand() % dictionary.size();

	inpWord1 = dictionary[numVal1];
	inpWord2 = dictionary[numVal2];
	inpWord3 = dictionary[numVal3];
	inpWord4 = dictionary[numVal4];
	inpWord5 = dictionary[numVal5];

	while (inpWord1.length() != word_length)
	{
		numVal1 = rand() % 263533;
		inpWord1 = dictionary[numVal1];
	}

	while (inpWord2.length() != word_length)
	{
		numVal2 = rand() % 263533;
		inpWord2 = dictionary[numVal2];
	}

	while (inpWord3.length() != word_length)
	{
		numVal3 = rand() % 263533;
		inpWord3 = dictionary[numVal3];
	}

	while (inpWord4.length() != word_length)
	{
		numVal4 = rand() % 263533;
		inpWord4 = dictionary[numVal4];
	}

	while (inpWord5.length() != word_length)
	{
		numVal5 = rand() % 263533;
		inpWord5 = dictionary[numVal5];
	}

	cout << "Using full dictionary" << endl;
	cout << inpWord1 << " ";
	cout << inpWord2 << " ";
	cout << inpWord3 << " ";
	cout << inpWord4 << " ";
	cout << inpWord5 << " " << endl;
	cout << "Type in those words within goal of 15 seconds: " << endl;

	int elapsedSeconds = 0;	// Will store number of elapsed seconds

	// Declare a variable to hold a time, and set it to the current time
	time_t startTime = time(NULL);

	cin >> inpWord1;
	cin >> inpWord2;
	cin >> inpWord3;
	cin >> inpWord4;
	cin >> inpWord5;

	elapsedSeconds = difftime(time(NULL), startTime);

	int compareValue1 = dictionary.at(numVal1).compare(inpWord1);
	int compareValue2 = dictionary.at(numVal2).compare(inpWord2);
	int compareValue3 = dictionary.at(numVal3).compare(inpWord3);
	int compareValue4 = dictionary.at(numVal4).compare(inpWord4);
	int compareValue5 = dictionary.at(numVal5).compare(inpWord5);

	if (compareValue1 == 0 && compareValue2 == 0 && compareValue3 == 0 && compareValue4 == 0 && compareValue5 == 0)
	{
		cout << "No misspelled words!" << endl;
	}
	else
	{
		cout << "Misspelled words:" << endl;
	}

	if (compareValue1 != 0)
	{
		wrongWord++;
		cout << inpWord1 << " should be: " << dictionary[numVal1] << endl;
	}
	else
	{
		correctWord++;
	}

	if (compareValue2 != 0)
	{
		wrongWord++;
		cout << inpWord2 << " should be: " << dictionary[numVal2] << endl;
	}
	else
	{
		correctWord++;
	}

	if (compareValue3 != 0)
	{
		wrongWord++;
		cout << inpWord3 << " should be: " << dictionary[numVal3] << endl;
	}
	else
	{
		correctWord++;
	}

	if (compareValue4 != 0)
	{
		wrongWord++;
		cout << inpWord4 << " should be: " << dictionary[numVal4] << endl;
	}
	else
	{
		correctWord++;
	}

	if (compareValue5 != 0)
	{
		wrongWord++;
		cout << inpWord5 << " should be: " << dictionary[numVal5] << endl;
	}
	else
	{
		correctWord++;
	}

	cout << "Elapsed time: " << elapsedSeconds << " seconds.";
	int y = 0;
	if (elapsedSeconds < 15)
	{
		int x = 15 - elapsedSeconds;
		y = x * 2;
		cout << " " << y << " point bonus for finishing " << x << " seconds early." << endl;

	}
	else if (elapsedSeconds > 15)
	{
		int z = elapsedSeconds - 15;
		int c = z * 3;

		cout << " " << z << " deduction for going over 15 seconds" << endl;

	}

	int x = word_length - 4;
	int score1 = correctWord * x;

	cout << score1 << " points: " << correctWord << " spelled correctly x " << x << " points each" << endl;

	int score2 = x * 2;
	int score3 = score2 * wrongWord;

	if (wrongWord != 0)
	{
		cout << score3 << " point penalty: " << wrongWord << " spelled incorrectly x " << score2 << " points each" << endl;

	}

	int u = y + score1;
	score = u - score3;

	cout << "Score: " << score << endl;
	return score;

}

void menu_option_3(vector<string> dictionary, vector<string> misspelledWords, vector< string > correctWords)
{
	char your_choice;

	int start, end;

	cout << "Displaying word list entries." << endl;
	cout << "Which words do you want to display?" << endl;
	cout << " " << "A. Dictionary of all words" << endl;
	cout << " " << "B. Wrongly spelled common misspelled words" << endl;
	cout << " " << "C. Correctly spelled common misspelled words" << endl;
	cout << "Your choice --> ";
	cin >> your_choice;
	your_choice = toupper(your_choice);

	if (your_choice == 'A')
	{
		cout << "Enter the start and end indices between 0 and 263532:";
		cin >> start >> end;

		for (int i = start; i <= end; i++)
		{
			cout << i << ". " << dictionary[i] << endl;
		}
	}
	else if (your_choice == 'B')
	{
		cout << "Enter the start and end indices between 0 and 113: ";
		cin >> start >> end;

		for (int i = start; i <= end; i++)
		{
			cout << i << ". " << misspelledWords[i] << endl;
		}
	}
	else if (your_choice == 'C')
	{
		cout << "Enter the start and end indices between 0 and 113: ";
		cin >> start >> end;

		for (int i = start; i <= end; i++)
		{
			cout << i << ". " << correctWords[i] << endl;
		}
	}
}

int binary_search_func(vector<string> dictionary, string word)
{
	int lower = 0;
	int upper = 263534 - 2;
	int step = 1;

	while (lower <= upper)
	{
		int mid = lower + (upper - lower) / 2;
		int res = 1;
		if (word == (dictionary[mid]))
		{
			cout << step << ". " << "Comparing to: " << dictionary[mid] << endl;
			step++;
			res = 0;
		}

		if (res == 0)
		{
			return mid;
		}

		if (word > (dictionary[mid]))
		{
			cout << step << ". " << "Comparing to: " << dictionary[mid] << endl;
			step++;
			lower = mid + 1;
		}
		else
		{
			cout << step << ". " << "Comparing to: " << dictionary[mid] << endl;
			step++;
			upper = mid - 1;
		}
	}

	return -1;
}

void menu_option_4(vector<string> dictionary)
{
	string word;

	cout << "Enter the word to lookup: ";
	cin >> word;

	int result = binary_search_func(dictionary, word);

	if (result == -1)
	{
		cout << word << " was NOT found." << endl;
		cout << endl;
	}
	else
	{
		cout << word << " was found." << endl;
		cout << endl;
	}
}

void read_Words_Into_Dictionary(vector<string> &dictionary)
{
	// Read in dictionary into dictionary vector
	ifstream inStream;	// Declare an input stream for reading
	inStream.open("dictionary.txt");	// Open dictionary file
	assert(inStream.fail() == false);	// Ensure file open worked

	// If you had previously used vector dictionary, then you might want to clear it
	// before continuing to use it, though that is not the case here.
	dictionary.clear();

	// Keep repeating while input from the file yields a word
	string newWord;	// Store a single input word
	while (inStream >> newWord)
	{
		// While there is another word to be read
		// Add this new word to the end of the vector, growing it in the process
		dictionary.push_back(newWord);
	}

	// Close the dictionary file
	inStream.close();
}

void correct_words(vector<string> &correctWords, vector<string> &misspelledWords)
{
	// Read in dictionary into dictionary vector
	ifstream inStream;	// Declare an input stream for reading
	inStream.open("misspelledWords.txt");	// Open dictionary file
	assert(inStream.fail() == false);	// Ensure file open worked

	// If you had previously used vector dictionary, then you might want to clear it
	// before continuing to use it, though that is not the case here.
	misspelledWords.clear();

	// Keep repeating while input from the file yields a word
	string newWord;
	string letter;
	string alphabets;	// Store a single input word
	while (inStream >> newWord >> letter)
	{
		// While there is another word to be read 

		misspelledWords.push_back(newWord);
		correctWords.push_back(letter);
		// Add this new word to the end of the vector, growing it in the process
		// dictionary.push_back(newWord);
	}

	// Close the dictionary file
	inStream.close();
}

int main()
{
	srand(1);
	int i = 1;
	vector<string> misspelledWords;
	vector<string> correctWords;
	vector<string> dictionary;
	read_Words_Into_Dictionary(dictionary);
	correct_words(correctWords, misspelledWords);

	int user_choice;
	int word_length = 5;
	int score = 0;
	int t = 0;

	cout << "There are 263533 words in the full dictionary." << endl;
	cout << "There are 114 commonly misspelled words." << endl;

	while (user_choice != 6)
	{
		cout << "Select a menu option:" << endl;

		cout << " " << "1. Spell commonly misspelled words (timed)" << endl;
		cout << " " << "2. Type random words from full dictionary (timed)" << endl;
		cout << " " << "3. Display some words from one of the lists" << endl;
		cout << " " << "4. Use binary search to lookup a word in full dictionary" << endl;
		cout << " " << "5. Set word length to use with full dictionary" << endl;
		cout << " " << "6. Exit the program" << endl;
		cout << "Your choice --> ";
		cin >> user_choice;

		if (user_choice == 1)
		{
			t = menu_option_1(misspelledWords, correctWords, score);
			if (t > score)
			{
				score = t;

			}
		}
		else if (user_choice == 2)
		{
			t = menu_option_2(dictionary, word_length, score, i);
			++i;
			++word_length;
			if (t > score)
			{
				score = t;
			}
		}
		else if (user_choice == 3)
		{
			menu_option_3(dictionary, misspelledWords, correctWords);
		}
		else if (user_choice == 4)
		{
			menu_option_4(dictionary);
		}
		else if (user_choice == 5)
		{
			cout << "Enter new wordLength: ";
			cin >> word_length;
			srand(1);

		}
		else if (user_choice == 6)
		{
			cout << "Exiting program" << endl;
			cout << "Best score was " << score << endl;
			exit(0);
		}
	}

	return 0;
}
