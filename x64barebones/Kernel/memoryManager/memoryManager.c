#include "memoryManager.h"

typedef struct MemoryManagerCDT {
	char *currentAddress;
	memBlock * head;
} MemoryManagerCDT;

typedef struct memBlock{
	int size;	
	int available; 		 	
	char * address;
	memBlock * next;
	memBlock * prev;
}memBlock;

MemoryManagerADT createMemoryManager(void *const restrict memoryForMemoryManager, void *const restrict firstAddress) {
	MemoryManagerADT memoryManager = (MemoryManagerADT) memoryForMemoryManager;
	memoryManager->currentAddress = firstAddress;
	memoryManager->head = NULL;

	return memoryManager;
}

void *allocMemory(MemoryManagerADT const restrict memoryManager, const size_t memoryToAllocate) {
	
	memBlock * currBlock = memoryManager->head;

	//Itero hasta que el bloque:
	//	- Este libre
	//	- Y el tamano sea mayor a lo que quiero alocar
	// 	- O no haya ningun bloque disponible.
	while(currBlock != NULL && currBlock->available == 0 && currBlock->size < memoryToAllocate){
		currBlock = currBlock-> next;
	}

	//Address a retornar
	char * address;

	//Si no hay bloque disponible, armo uno nuevo en la ultima direccion del MM
	if(currBlock == NULL){

		memBlock * newBlock = memoryManager->currentAddress;
		newBlock -> size = memoryToAllocate;
		newBlock -> available = 0;
		newBlock -> address = newBlock; 

		memBlock* iter = memoryManager->head;
	
		memoryManager->head = addBlock(memoryManager->head, newBlock);
		

		//Retorno el address + sizeof(memBlock) que le robe
		address = memoryManager->currentAddress + sizeof(memBlock);
		memoryManager->currentAddress += memoryToAllocate;

	} else{
		//Tengo un bloque disponible para asignar
		currBlock->available = 0;
		address = (currBlock->address + sizeof(memBlock));
	}

	return (void *) address;

}

memBlock * addBlock(memBlock * head, memBlock * toAdd){

	if(head != NULL){
		return toAdd;
	} else if(head->data >= toAdd->data){
		toAdd->next = head_ref;
		toAdd->prev = NULL;
		return toAdd;
	} else{
		memBlock * current = head;
		while(current->next != NULL && current->next->data < toAdd->data)
			current = current->next;
		
		toAdd->next = current->next;
		if(current->next != NULL){
			toAdd->next->prev = toAdd;
			current->next = toAdd;
		}
		toAdd->prev = toAdd;
	}


}

void freeMemory(MemoryManagerADT const restrict memoryManager, void *memoryToFree) {
	//TODO: Chequeo de error que el bloque no este

	//El address que tiene el user esta adelantado 1 memBlock

	if(memoryToFree == NULL{
		//EXPLOTAR TODO
	}

	char * address = memoryToFree - sizeof(memBlock);

	memBlock * currBlock = memoryManager->head;
	while(currBlock->address != address){
		currBlock = currBlock->next;
	}

	if(currBlock == NULL){
		//EXPLOTAR TODO
		//NO se encontro el bloque que buscaba
	}

	currBlock->available = 1;
}
