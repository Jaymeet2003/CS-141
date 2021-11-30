/*
 CS 141 Midterm #1, Fall 2021, Reed/Fulton/Kidane
 
 This midterm exam consists of a single problem.  All points 
 come from your solution passing tests in Zylabs.
 
 You may not communicate with anyone else during the test.  You may
 consult your text, your notes, files archived in your account, and 
 the Web, but you may not use text messages, phone calls, chat or any
 sort of messaging service.
 
 You don't need to comment your code or worry about having meaningful 
 variable names.  We will only be grading the output of your program.  
 
 You may assume perfect input (i.e. no error checking is necessary) 
 unless we specifically state otherwise. 
 
 Some starter code is shown below:
 */
#include <iostream>
#include<string>
#include<cctype>
using namespace std;

void stringCompare(string str, string str1){
    int lettersBefore, lettersAfter=0;
    string temp;
    for(int i=0;i<str.length();i++){
        temp = str.at(i);
        if(temp <= str1){
            lettersBefore = i+1;
        }else{
            lettersAfter++;
        }
    }
    cout<<"There were "<<lettersBefore<<" letters before and "<<lettersAfter<<" after "<<str1;
}
 
int main()
{
    int numVal;
    string str,str1;
    
    cout<<"Analyzing how many letters and a comparison value:";
    cin>> numVal>>str1;
    cout<<"Enter "<<numVal<<" numbers:";
    cin>>str;
    
 
 stringCompare(str,str1);
    return 0;
}//end main()
