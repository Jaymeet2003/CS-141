// Complete the code in class Restaurant so that the code in main()
// runs correctly and gives the indicated output for the input.
// You can look up information online, but cannot collaborate or
// communicate with any other person. Your grade will be determined by
// the results of running tests in Zybooks.
#include <vector>       // For vector
#include <iostream>     // For cin and cout
using namespace std;    // So we don't have to always preface std::cin



// Implement class Restaurant

class Meme {

public:

// Constructors (default, fully qualified, copy)

    Meme() { url = "www.meme.com"; funny = 10; }

    Meme( string url, int thefunny) {

        this->url = url;  // Besides using this-> you could alternatively

                            // use the scope resolution operator Meme::

        funny = thefunny;

    }

    // Copy constructor, where the calling object gets copies of the

    // information from the Meme sent as the parameter.

    Meme( const Meme & otherMeme) {

        // The next line could alternatively just be url = otherMeme.url;

        this->url = otherMeme.url;

        this->funny = otherMeme.funny;

    }

    

// Getters and setters

    void setUrl( string theurl)     { url = theurl;     }

    void setfunny( double thefunny) { funny = thefunny; }

    string getUrl()   { return url;   }

    double getfunny() { return funny; }

// Utility functions

void display() {

        cout << url << " how funny rating " << funny << endl;

    }

    

    private:

        string url;  // For simplicity, assume there is no space in the name

        int funny;   // 1 is low, 5 is high

}; // end class MenuItem

    

    

//------------------------------------------------------------------------------

// Display all Memes and find and return the index of the highest ranked

// Meme.  Send in the vector of all Memes to be used.

int displayAllAndGetIndexOfBestMeme( vector<Meme> allMemes)

{

    int funniest = 0;

    int indexOfTheFunniest = 0;

    

    for( int i=0; i<allMemes.size(); i++) {

        allMemes.at( i).display();

        

        int theFunniestRating = allMemes.at( i).getfunny();

        if( theFunniestRating > funniest) {


            funniest = theFunniestRating;

            indexOfTheFunniest = i;

        }

    }

    

    // Return the index in the vector of the highest rated Meme.

    return indexOfTheFunniest;

}

//-----------------------------------
// DO NOT CHANGE ANYTHING BELOW THIS LINE
int main()
{
    string newName;
    int newRating;

    vector< Meme> topMemes;   // Vector used to collect multiple memes

    //  Each test case will have it's own test number
    //  User will input numbers 1-5 corresponding with each test case
    int testNumber = 0;

    cout << "Please enter test #: ";
    cin >> testNumber;
    cout << endl;

    switch(testNumber){

        // Test number one will test for implementation of default constructor and getters and setters
        case 1:
        {
            Meme m1;
            m1.display();
            cout << ".....UPDATING NAME AND RATING....." << endl;
            m1.setUrl("www.memenation.com");
            m1.setfunny(5);
            m1.display();
        }
            break;
            // Test number two will test for implementation of parameterized constructor
        case 2:
        {
            string memeUrl;
            int fun;
            cout << "Insert Meme Name and howFunny" << endl;
            cin >> memeUrl >> fun;
            
            Meme m2(memeUrl, fun);
            m2.display();
        }

            break;
            // Test number three will test for implementation of copy constructor
        case 3:
        {
            string memeUrl2;
            int fun2;
            cout << "Insert Meme Name and howFunny" << endl;
            cin >> memeUrl2 >> fun2;


            Meme m3(memeUrl2, fun2);
            Meme m4(m3);

            if (m3.getfunny() == m4.getfunny() && (m3.getUrl()).compare(m4.getUrl()) == 0) {
                cout << "NAMES EQUAL" << endl;
            }

            cout << "Original Meme: ";
            m3.display();
            cout << "Copy Meme: ";
            m4.display();
        }
            break;
            // Test number four will test for the Get best meme
        case 4:
        {
            string memeUrl3;
            int fun3;
            cout << "Insert Meme Name and howFunny" << endl;
            cin >> memeUrl3 >> fun3;
            
            Meme mM("www.memenation.com", 2);
            Meme mW("www.goodmeme.com", 1);
            Meme mB(memeUrl3, fun3);

            topMemes.push_back(mM);
            topMemes.push_back(mW);
            topMemes.push_back(mB);

            // Display all Memes and find the one with the highest howFunny
            int indexOfHighestFunny = displayAllAndGetIndexOfBestMeme( topMemes);
            cout << "Top meme is: ";
            topMemes.at(indexOfHighestFunny).display();
        }

            break;
        default:
            cout << "Entered invalid test number.....EXITING" << endl;

    }


    return 0;
}
