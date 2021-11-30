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


void lessGreaterLists( Node *pOriginal,int d, Node *&pHeadLess, Node *&pHeadGreater){
        Node *temp=pOriginal; 
        /*while original list is not empty*/
        while(temp!=NULL){
                /*creat a new node*/
                Node *newdata=(Node*)malloc(sizeof(Node));
                newdata->pNext=NULL;
                newdata->data=temp->data;
                /*if  data is less than user input attached this node to lesser list */
                if(temp->data<d){
                        /*if less list is null make a new data head of pheadLess*/
                        if(pHeadLess==NULL){
                                pHeadLess=newdata;
                        }
                        /*else attached this new data  to end*/
                        else{
                                Node *tmp=pHeadLess;
                                /*loop till pheadless becomes null*/
                                while(tmp->pNext!=NULL){
                                        tmp=tmp->pNext;
                                }
                                tmp->pNext=newdata;  
                        }                       
                }
                else if (temp->data>d){
                        if(pHeadGreater==NULL){
                                pHeadGreater=newdata;
                        }
                        else{
                                Node *tmp=pHeadGreater;
                                while(tmp->pNext!=NULL){
                                        tmp=tmp->pNext;
                                }
                                tmp->pNext=newdata;  
                        }                       
                        
                }
                temp=temp->pNext;
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
        displayList(pHead);
        int userInput;
        cout << "\nEnter value: ";
        cin >> userInput;
        lessGreaterLists( pHead, userInput, pHeadA, pHeadB);
        displayList(pHeadA);
         displayList(pHeadB);
        return 0;
}
