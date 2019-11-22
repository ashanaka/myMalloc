#include<stdio.h>
#include<stddef.h>
#include "myMalloc.h"

typedef struct node{
	int data;
	struct node *next;
};

struct node *head = NULL;

void display(){
	struct node *p;
	p = head;
	printf("Values in th linked list: ");
	while(p != NULL){
		printf("%d ", p->data);
		p = p->next;
	}
	printf("\n");
}	

void append(){
	
	struct node* temp;
	temp = (struct node*)myMalloc(sizeof(struct node));
	printf("Enter the data: ");
	scanf("%d", &temp->data);
	temp -> next = NULL;
	
	if(head == NULL){
		head = temp;
	}else{
		struct node* p;
		p = head;
		while( p->next != NULL){
			p = p->next;
		}
		p->next = temp;
	}
}

void appendAtBegin(){
	struct node* temp;
	temp = (struct node*)myMalloc(sizeof(struct node));
	printf("Enter the data: ");
	scanf("%d", &temp->data);
	temp->next = NULL;
	if(head == NULL){
		head = temp;
	}else{
		temp->next = head;
		head = temp;
	}
	
}

int length(){
	int count;
	struct node* temp;
	temp = head;
	while(temp != NULL){
		count++;
		temp = temp->next;
	}
	return count;
}

void delete(){
	int location;
	printf("Enter the location to delete: ");
	scanf("%d", &location);
	struct node* temp;
	if(location > length()){
		printf("Invalid location entered\n");
	}else if(location == 1){
		temp = head;
		head = temp->next;
		temp->next = NULL;
		freeChunk(temp);
	}else{
		struct node* p = head;
		int i=1;
		while(i < location-1){
			p = p->next;
			i++;
		}
		struct node* q = p->next;
		p->next = q->next;
		q->next = NULL;
		freeChunk(q);
	}
}


int main(){
	
	char choice;
	do{
		printf("Enter the choice: a: append, b: appent at begining, d: display, r: delete, e: exit: ");
		scanf("%s", &choice);
		switch(choice){
			case 'a':
				append();
				break;
			case 'b':
				appendAtBegin();
				break;
			case 'd':
				display();
				break;
			case 'r':
				delete();
				break;
			case 'e':
				printf("\nThank You!\n");
				
				exit(0);
				break;
			default:
				printf("Invalide choice! please try again!\n");
				break;
		}
		
	}while(choice != 'e');
	
	
	return 0;
}
