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



void displayList(Node *head)
{
        Node *temp=head;
        while(temp->pNext!=NULL){
                printf("%d->",temp->data); 
                temp=temp->pNext;    
        }
        printf("%d\n",temp->data); 
        
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
}

int main(){
        Node *pHead = NULL;
        Node *pTemp;
        Node *pHeadA = NULL; 
        Node *pHeadB = NULL; 
        Node *head=NULL;
        int data[]={2,8,5,11,3,9,6};
        int length=sizeof(data)/sizeof(data[0]);
        for(int i=0;i<length;i++){
            insert(&pHead,data[i]);
        }
        evenOddSum( pHead, evenSum, oddSum);
        return 0;
}
