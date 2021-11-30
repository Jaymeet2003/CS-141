#include <iostream>

using namespace std;

//structure declaration
typedef struct node {
  int data;
  struct node * next;
}
Node;

Node * head = NULL;

//function to print the node value with address
void printList() {
  //declare a structure type variable and initialize with head
  Node * ptr = head;

  while (ptr != NULL) {
    //display the node address, value stored in node and the address of the next node
    if (ptr -> next)
      cout << ptr -> data << "->";
    else
      cout << ptr -> data;

    //assign the pointer to the next node
    ptr = ptr -> next;
  }
}

//function to add a new node at the beginning of the linked list
void addFirst(int data) {
  struct node * link = (struct node * ) malloc(sizeof(struct node));

  //assign the new node data field with the paramener value
  link -> data = data;
  //assigne the new node address field with the head pointer
  link -> next = head;

  //assign the head node to the new node
  head = link;
}

void addNeighbor(Node * pHead) {
  //declare a structure type variable and initialize with head
  Node * ptr = pHead;
  Node * temp = NULL;

  while (ptr != NULL) {
    //traverse the linked list
    if (ptr -> next) {
      temp = ptr -> next;
      ptr -> data = ptr -> data + temp -> data;
    }

    //assign the pointer to the next node
    ptr = ptr -> next;
  }
}

int main() {
  //insert value
  addFirst(6);
  addFirst(9);
  addFirst(3);
  addFirst(11);
  addFirst(5);
  addFirst(8);
  addFirst(2);

  //display the linked list by calling printList() function
  cout << "The linked list is: " << endl;
  printList();

  addNeighbor(head);

  cout << endl << endl << "The linked list is: " << endl;
  printList();

  return 0;

}
