#include<iostream>
#include<cstdlib>
using namespace std;

struct Node {
        int data;
        Node *pNext;
};

void *insert(Node **head,int userInput){
        Node *newnode;
        newnode=(Node*)malloc(sizeof(Node));
        newnode->pNext=NULL;
        newnode->data=userInput;
        if(*head==NULL){
            *head=newnode;
        }
        else{
            Node *next=*head;
            while(next->pNext!=NULL){
                    next=next->pNext;
            }
            next->pNext=newnode;
        }
}



void display(Node * pHead) {
  while (pHead != NULL) {
    cout << pHead -> data << " ";
    pHead = pHead -> pNext;
  }
  cout << endl;
}


void evenOddSum( Node *&pHead, int &evenSum, int &oddSum)
{
   Node *curr = pHead;
   evenSum = 0;
   oddSum = 0;
  
   while(curr != NULL){
       if(curr->data % 2 == 0) //even
           evenSum += curr->data;
       else
           oddSum += curr->data;
          
       curr = curr->pNext;
   }
   
   cout << "Even and odd sums are:"<< evenSum <<" "<<oddSum;
}

int main(){
        Node *pHead = NULL;
        Node *pTemp;
        Node *pHeadA = NULL; 
        Node *pHeadB = NULL; 
        Node *head=NULL;

        int evenSum,oddSum;
        cout << "Enter list numbers separated by space, followed by -1:";

        while (true)
        {       
                int data;
                cin >> data;
                if(data == -1) break;
                insert(&pHead, data);
        }
        
        cout<<"The List is:";
        display(pHead);


        evenOddSum( pHead, evenSum, oddSum);
        
        return 0;
}
