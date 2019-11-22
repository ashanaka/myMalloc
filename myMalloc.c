#include<stdio.h>
#include<stddef.h>

char memory[25000];


struct metaData{
	size_t sizeOfChunk;
	int isFree;
	struct block *next;
};


//Creating the pointer variable to get free memory blocks
struct metaData* freeBlock = (void*)memory;

//Initiate the first metaData block
void initiate(){
	freeBlock->sizeOfChunk  = 25000-sizeof(struct metaData);
	freeBlock->isFree = 1;
	freeBlock->next = NULL;
}


//For testing purposes only
int main(){
	
	struct metaData *block = (void*)memory;
	block->isFree = 1;
	block->next = NULL;
	block->sizeOfChunk = sizeof(struct metaData);
	
	printf("%d", (block->sizeOfChunk));
	
	return 0;
}
