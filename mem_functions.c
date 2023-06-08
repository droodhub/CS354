#include "mem.h"                      
extern BLOCK_HEADER* first_header;
int is_Allocated(void* ptr) {
    return ((BLOCK_HEADER*)ptr)->size_alloc%2; 
}
void set_Free(void* ptr) {
    if (!is_Allocated(ptr))
        return; //if not allocated, no need to set free
    ((BLOCK_HEADER*)ptr)->size_alloc -= 1;
    return;
}
void set_Allocated(void* ptr) {
    if (is_Allocated(ptr))
        return;
    ptr += 1;
    return;
}
void* Get_Next_Pointer(void* ptr) {
    unsigned long givenAddr = (unsigned long)ptr; //addr of pointer
    int size = ((BLOCK_HEADER*)ptr)->size_alloc;
    if (size % 2) //AKA the block is allocated
        size--; //remove the +1 for allocated block
    
    givenAddr += size;//advance past the size allocated for ptr
    
    return (void*)givenAddr;
}
int Get_Padding(void* ptr) {
    BLOCK_HEADER* pointer = (BLOCK_HEADER*)ptr;
    int blockSize = pointer->size_alloc;
    int payload = pointer->payload;
    return blockSize - payload - 8;

}
// return a pointer to the payload
// if a large enough free block isn't available, return NULL
void* Mem_Alloc(int size){
    if (size <= 0)
        return NULL;
    // find a free block that's big enough
    BLOCK_HEADER* current = (BLOCK_HEADER*)first_header;
    while (current->size_alloc & 0x1 || current->size_alloc - 8 < size) { //-8 to account for header space
        if (current->size_alloc == 1) //we have reached the last header
            return NULL; // return NULL if we didn't find a block

        current = Get_Next_Pointer((void*)current); //advance to the next pointer in the heap
    }

    // allocate the block
    current->payload = size;
    current->size_alloc += 1; //+1 for the allocated bit

    if (Get_Padding((void*)current) >= 16) { //split the block
        unsigned long currentAddr = (unsigned long)current; //convert addrss to unsigned long for arithmetic purposes
	unsigned long originalAddr = (unsigned long)current;
        int originalSize = current->size_alloc; //keep track of the total block size we are splitting
        currentAddr += 8; //move past header
        currentAddr += current->payload; //move past payload
        while (currentAddr % 8) currentAddr++; //find the nearest address that satisfies minimum block size
        
        current->size_alloc = currentAddr - (unsigned long)current + 1; //+1 for allocated status


        void* nextPointer = currentAddr; //initialize pointer to remaining free block
        ((BLOCK_HEADER*)nextPointer)->payload = originalSize- (currentAddr - originalAddr) -9;
        ((BLOCK_HEADER*)nextPointer)->size_alloc = originalSize - (currentAddr - originalAddr) -1; 
    }

    unsigned long address = (unsigned long)current;
    return (void*)(address + 8);
}


// return 0 on success
// return -1 if the input ptr was invalid
int Mem_Free(void *ptr){
        
    if(!is_Allocated(ptr-8))//if not allocated, don't need to free
	return -1;

    void* headerAddress = (void*)((unsigned long)ptr - 8);
    void* current = (void*)first_header;//use this to iterate through the stack
    while(current != headerAddress){
	if(((BLOCK_HEADER*)current)->size_alloc == 1){ //we have found the last header
		return -1;}	
	current = Get_Next_Pointer(current);
    } 
    
    set_Free(headerAddress);
    ((BLOCK_HEADER*)headerAddress)->payload = ((BLOCK_HEADER*)headerAddress)->size_alloc-8;
 
    if(!is_Allocated(Get_Next_Pointer(current))){ //pointer after freed pointer is also free
		((BLOCK_HEADER*)current)->payload += ((BLOCK_HEADER*)Get_Next_Pointer(current))->payload+8;
		((BLOCK_HEADER*)current)->size_alloc += ((BLOCK_HEADER*)Get_Next_Pointer(current))->size_alloc;
    }
    //now, coalesce the block before
    current = (void*)first_header; 
    if(current == headerAddress)
	return 0; //the first header is the header of the block passed

    while(Get_Next_Pointer(current) != headerAddress && ((BLOCK_HEADER*)Get_Next_Pointer(current))->size_alloc != 1) current = Get_Next_Pointer(current);
   
    if(!is_Allocated(current)){//block is free
		((BLOCK_HEADER*)current)->payload += ((BLOCK_HEADER*)Get_Next_Pointer(current))->payload+8;
		((BLOCK_HEADER*)current)->size_alloc += ((BLOCK_HEADER*)Get_Next_Pointer(current))->size_alloc; }

      return 0;
}

