#include <iostream>

using namespace std;

struct Node

{

  int data;

  Node * pNext;

};

void minMaxAddOne(Node * pHead, int & min, int & max)

{

  Node * pTemp = pHead;

  // if list is empty

  if (pTemp == NULL) return;

  // initialize min and max to

  // first node's data

  min = pTemp -> data;

  max = pTemp -> data;

  while (pTemp)

  {

    // if current node data

    // is more than the max

    if (pTemp -> data > max)

    {

      max = pTemp -> data;

    }

    // if current node data

    // is less than the min

    if (pTemp -> data < min)

    {

      min = pTemp -> data;

    }

    // add one

    pTemp -> data += 1;

    // next node

    pTemp = pTemp -> pNext;

  }

}

// display

void displayList(Node * pHead)

{

  Node * pTemp = pHead;

  while (pTemp)

  {

    cout << pTemp -> data;

    pTemp = pTemp -> pNext;

    if (pTemp)

      cout << "->";

  }

  cout << endl;

}

int main()

{

  Node * pHead = NULL; // pointer to the head of the list

  Node * pTemp = NULL; // pointer used to get new nodes

  // you can use these nodes as per your need

  // Node *pHeadA = NULL; // List A head pointer initialized to NULL

  // Node *pHeadB = NULL; // List B head pointer initialized to NULL

  // input loop

  cout << "Enter the data(-1 to break): " << endl;

  while (true)

  {

    int temp;

    cin >> temp;

    if (temp == -1) break;

    if (pHead == NULL)

    {

      pHead = new Node();

      pHead -> data = temp;

      pHead -> pNext = NULL;

      pTemp = pHead;

    } else

    {

      pTemp -> pNext = new Node();

      pTemp = pTemp -> pNext;

      pTemp -> data = temp;

      pTemp -> pNext = NULL;

    }

  }

  int min = 0;

  int max = 0;

  minMaxAddOne(pHead, min, max);

  displayList(pHead);

  cout << "Min and max values: " << min << " " << max << endl;

}
