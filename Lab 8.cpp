#include <iostream>


#include <string>


using namespace std;


// MAKE/INSERT THE VACATION CLASS HERE


class Vacation{


string destination;


int cost;


public:


// setters and getters of data members


void setDestination(string d)


{


destination=d;


}


void setCost(int c)


{


cost=c;


}


string getDestination()


{


return destination;


}


int getCost()


{


return cost;


}


// Method to display vacation information


void displayCost()


{


cout<<"Vacation information: "<<getDestination()<<" with cost: "<<getCost()<<endl;


}


// Default constructor


Vacation()


{


destination="NYC";


cost=3;


}


// Parameterized constructor


Vacation(string d,int c)


{


setCost(c);


setDestination(d);


}


};


int main() {


// DECLARE AN INSTANCE OF VACATION AND CALL IT V1


Vacation v1;


string destination; // Vacation destination as a single-word


int cost; // Vacation cost, used for user input


// Taking in the destination and cost parameters


cout << "Enter vacation destination and cost: ";


cin >> destination >> cost;


// SET THE DESTINATION AND COST PARAMETERS HERE


v1.setDestination(destination);


v1.setCost(cost);


// UPDATE THE VARIABLE "theDestination" to equal the actual destination of v1


string theDestination;


theDestination=v1.getDestination();


cout << "The vacation is in " << theDestination << "." << endl;


// Uncomment these lines only when implementing Stage 2


// Use v1 to call the display() function, which displays destination and cost,


//v1.displayCost();


// as shown in the sample output below


// Enter either 2 or 3 to check those test cases -1 to check neither


// To check the default constructor please enter 3 for the qualified enter 4


int testCaseCheck;


cout << "Please enter test case number: ";


cin >> testCaseCheck;


switch (testCaseCheck) {


case 2: {


// UNCOMMENT THE CODE BELOW WHEN YOU START PART 2


v1.displayCost();


break;


}


case 3: {


cout << "Second General Vacation: " << endl;


Vacation v2;


// AFTER MAKING YOUR DEFAULT CONSTRUCTOR INITIALIZE A DEFAULT VACATION


// NAME THIS VACATION v2 AND DISPLAY THE VACATION COST BY UNCOMMENTING THE CODE


v2.displayCost();


break;


}


case 4: {


cout << "Second Specific Vacation: " << endl;


string pDestination;


int pCost;


// Taking in the destination and cost parameters


cout << "Enter parameterized vacation destination and cost: ";


cin >> pDestination >> pCost;


// AFTER MAKING YOUR PARAMETERIZED CONSTRUCTOR INITIALIZE A PARAMETERIZED VACATION


// NAME THIS VACATION v3


Vacation v3(pDestination,pCost);


// ***INSERT INITIALIZED PARAMETERIZED VACATION HERE***


// Display v3 information using displayCost


// UNCOMMENT BELOW CODE TO DISPLAY v3 INFORMATION USING displayCost


v3.displayCost();


break;


}


default:


break;


}


return 0;


}

