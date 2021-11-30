#include<iostream>
using namespace std;

typedef struct node{
    int data;
    struct node*next;
}Node;

Node * addNode(Node*list,int data){
    Node*newnode = new Node;
    newnode->data = data;
    newnode->next = NULL;
    
    if(!list){
        return newnode;
    }

    Node*current = list;
    while(current->next)
        current = current->next;
    current->next = newnode;
    return list;
}

void print(Node*list){
    while(list){
        cout << list->data << "->";
        list = list->next;
    }
    cout << "\n";
}

void splitList(Node*pOriginal, int splitValue, Node*&pHeadA, Node*&pHeadB){
    if(pOriginal -> data == splitValue){
        pHeadA = NULL;
        pHeadB = pOriginal;
        return;
    }
    Node*current = pOriginal;

    while(current&&current-> data != splitValue)
        current = current->next;
        if(current==NULL){
            cout<<splitValue<<"not found in list\n";
            return;
        } 
        pHeadA = pOriginal;
        pHeadB = current->next;
        current->next = NULL;
}

int main(){
    int userInput;
    Node* head = NULL;
    Node * HeadA = NULL;
    Node * HeadB = NULL;
    head = addNode(head,2);
    head = addNode(head,8);
    head = addNode(head,5);
    head = addNode(head,11);
    head = addNode(head,3);
    head = addNode(head,9);
    head = addNode(head,6);

    cout << "Enter value for split: ";
    cin >> userInput;

    splitList(head, userInput, HeadA, HeadB);
    print(HeadA);
    print(HeadB);
    return 0;
}
