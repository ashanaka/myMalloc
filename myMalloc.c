#include<stdio.h>
#include<stddef.h>

char memory[25000];

//The structure of the meta-data block to have all the data of the memory chunk to be allocated
struct metaData{
	size_t sizeOfChunk;
	int isFree;
	struct metaData *next;
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


//my malloc function to allocate memory dynamically in virtual memory
void* myMalloc(size_t sizeOfBytes){
	
	struct metaData* thisBlock;
	struct metaData* prevBlock;
	
	void* memoryAddress;
	
	//check whether the memory is initiated or not
	if(!(freeBlock->sizeOfChunk)){
		initiate();
		printf("Memory Initiated!\n");
	}	
	
	thisBlock = freeBlock;
	
	while((thisBlock->sizeOfChunk < sizeOfBytes || thisBlock->isFree == 0) && thisBlock->next != NULL){
		
		prevBlock = thisBlock;
		thisBlock = thisBlock->next;
		printf("One block is checked!\n");
	}
	
	if(thisBlock->sizeOfChunk == sizeOfBytes){	//when the required size is absolutely fit into the selected block;
		
		memoryAddress = ++thisBlock;
		thisBlock->isFree = 0;
		printf("Allocated the absolute fitting chunk!\n");
		return memoryAddress;
	}else if(thisBlock->sizeOfChunk > (sizeOfBytes + sizeof(struct metaData))){	//When the selected meta-data block has more than required space
		
		split(thisBlock, sizeOfBytes);
		memoryAddress = ++thisBlock;
		printf("The chunk was allocated by splitting an existing chunk!\n");
		return memoryAddress;
	}else{																		//when the memory has no enough space
		memoryAddress = NULL;
		printf("No enough space to allocate memory!\n");
		return memoryAddress;
	}
}

//to make free the allocated memory chunk when it's not needed
void freeChunk(void* blockAddress){
	
	struct metaData* thisBlock;
	
	if((void*)memory <= blockAddress && blockAddress <= ((void*)memory + 25000)){
		
		thisBlock = blockAddress;
		thisBlock--;
		thisBlock->isFree = 1;
		printf("The chunk was free!\n");
	}else{
		
		printf("The given address is not in virtual RAM!\n");
	}
}

