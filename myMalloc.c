#include<stdio.h>
#include<stddef.h>

char memory[25000];

//The structure of the meta-data block to have all the data of the memory chunk to be allocated
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


//Split function for allocating a first-fit memory block between two allocated memory blocks
void split(struct metaData* firstFitSlot, size_t sizeOfChunk){
	struct metaData* newBlock = (void*)(firstFitSlot + sizeOfChunk + sizeof(struct metaData));
	
	newBlock->isFree = 1;
	newBlock->sizeOfChunk = firstFitSlot->sizeOfChunk - sizeOfChunk - sizeof(struct metaData);
	newBlock->next = firstFitSlot->next;
	
	firstFitSlot->next = newBlock;
	firstFitSlot->sizeOfChunk = sizeOfChunk;
	firstFitSlot->isFree = 0;
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
