#include <iostream>
using namespace std;

// Declare the Node structure to be used for the linked list.
// Each node should have an int for data and
// a pointer to the next node.
class Node {
public:
    int data;
    Node *pNext;
};

/*
 * PROBLEM #1
 * Write a function to traverse a list, looking for a number.
 * If found, return the position of that node on the list, else return -1.
 * Base this off of the traversal code given in class for a basic linked list.
 * You may assume the list has nodes on it.
 */
 void insert(Node **pHead,int v)
{
   //create a node node
   struct Node *node=new Node();
   node->data=v;
   node->pNext=NULL;
 
 
   if(*pHead==NULL)
   {
       *pHead=node;
   }
   else{
     
       node->pNext=*pHead;
       *pHead=node;
   }
}

int findNumber(Node *pHead, int valueToFind){
    // .....ENTER YOUR CODE HERE.....
    int pos=0;
   while(pHead!=NULL)
   {
       if(pHead->data==valueToFind)
       {
           return pos;
       }
       pos++;
       pHead=pHead->pNext;
   }


    return -1;
}

/*
 * PROBLEM #2
 * Traverse the first list, and display each element only if it is also in the second list.
 * The lists may or not be the same length.
 * You may assume the list has nodes on it.
 */
void numbersInBoth(Node *pHead, Node *pHead2){

    // .....ENTER YOUR CODE HERE.....
    //cout<<"Numbers in both lists: ";
   while(pHead!=NULL)
   {
       //take a reference of second pointer
       struct Node *temp=pHead2;
       while(temp!=NULL)
       {
           if(pHead->data==temp->data)
           {
               cout<<temp->data<<" ";
               break;
           }
           temp=temp->pNext;
       }
       pHead=pHead->pNext;
   }

}


/*
 * PROBLEM #3 EXTRA CREDIT
 * Display only the nodes that are in the same position on both lists,
 * where the two lists are not necessarily the same length
 */
void numbersInBothAndPosition(Node *pHead, Node *pHead2){

    // .....ENTER YOUR CODE HERE.....
   
   while(pHead!=NULL && pHead2!=NULL)
   {
       if(pHead->data==pHead2->data)
       {
           cout<<pHead->data<<" ";
         
       }
       pHead=pHead->pNext;
       pHead2=pHead2->pNext;
   }

}





//-----------------------------------------------------------------------
//       *** Do not change anything below this point. ***
//------------------------------------------------------------------------

int main()
{
    //  All Numbers in the list are PREPENDED
    //  START MAKING THE FIRST LIST
    Node *pHead = NULL;  // head of linked list
    cout << "Enter as many integers > 0 as you would like for the first list" << endl
         << "  followed by the value -1. " << endl
         << endl
         << "The numbers are: ";

    int number = 0;      // Used to store numbers read in
    Node *pTemp;         // used in new node creation
    while(number != -1) {
        cin >> number;
        if( number != -1) {
            pTemp = new Node;
            // Insert at head of list
            pTemp->data = number;
            pTemp->pNext = pHead;
            pHead = pTemp;
        }
    }

    //  DONE MAKING THE FIRST LIST

    //  START MAKING THE SECOND LIST
    Node *pHead2 = NULL;  // head of linked list
    cout << "Enter as many integers > 0 as you would like for the second list" << endl
         << "  followed by the value -1. " << endl
         << endl
         << "The numbers are: ";

    int number2 = 0;      // Used to store numbers read in
    Node *pTemp2;         // used in new node creation
    while(number2 != -1) {
        cin >> number2;
        if( number2 != -1) {
            pTemp2 = new Node;
            // Insert at head of list
            pTemp2->data = number2;
            pTemp2->pNext = pHead2;
            pHead2 = pTemp2;
        }
    }

    // DONE MAKING THE SECOND LIST

    //  Entering the problem choice

    int choice;
    cout << "Please enter the problem you want to attempt: ";
    cin >> choice;

    cout << endl;

    switch(choice){

        // Problem #1: Looking for a number
        case 1:
        {
            int numLook;
            cout << "Please enter the number you are looking for in list one: ";
            cin >> numLook;

            cout << "Numbers position in the list: " << findNumber(pHead, numLook);
            break;
        }

        // Problem #2: Traverse and display numbers in both
        case 2:
        {
            cout << "Numbers in both lists: ";
            numbersInBoth(pHead, pHead2);
            break;
        }

        // Problem #3: Same position both list
        case 3:
        {
            cout << "Numbers in same position for both lists: ";
            numbersInBothAndPosition(pHead, pHead2);
            break;
        }
    }



    return 0;
}//end main()
