#include <stdio.h>
#include <string.h>
// THE CACHE
struct LINE{
    char valid;
    int tag;
    char data[32];
};

struct SET{
    struct LINE line[1];
};

struct CACHE {
    struct SET set[8];
} cache;

// GLOBALDATA
// increment these in your function
unsigned hit_count  = 0;
unsigned miss_count = 0;
unsigned read_data_count = 0;

// SYSTEM BUS 
// call Read_Data_From_Ram to update this
char system_bus[32];



// READ DATA FROM RAM
// this function copies 32 character from the text file to
// the system_bus array aligned with the system bus
// (we will not test this with input larger than the text file)
void Read_Data_From_Ram(unsigned address) {
    address >>= 5; address <<= 5; // get align the data
    read_data_count++;
    FILE *file;
    file = fopen("alice_in_wonderland.txt", "r");
    fseek(file, address, SEEK_SET);
    for (int i = 0; i<32; i++) system_bus[i] = fgetc(file);
    return;
}


// COMPLETE THE FOLLOWING FUNCTION 
//
// this code should check to see if the data in the cache is valid and the tag matches
// if so it should return the char matching the address and increment the hit count
//
// if not it should read the data from the system bus copy it into the cache and 
// increment the miss count and return the char matching the address
// 
char Read_Data_From_Cache(unsigned address){
    
    int setNum = (address >> 5) % 8; //8 sets, 3 bits to represent which set you are choosing
    int addrTag = address >> 8; //remove 8 bits used for data + set 
    int dataAddr = address % 32; //32 bits for the data, 5 bits to represent its location

    struct LINE line = cache.set[setNum].line[0];
    if (line.valid == 1) { //data inside is valid, check if tag is correct
        if (line.tag == addrTag) { //address tags match as well, return value
            hit_count++; //we had a hit, increment + indicate
            return line.data[dataAddr];
        }
        else {
            miss_count++; //data was not present, so we had a cache miss
            Read_Data_From_Ram(address); //load the data we need into the system bus
            for(int i = 0; i < 32; i++){
			cache.set[setNum].line->data[i] = system_bus[i];
		} //copy data from system bus over to the proper line
            cache.set[setNum].line->tag = addrTag; //reset tag to match current data
            return cache.set[setNum].line->data[dataAddr];
        }
    }
    miss_count++; //data was not present, so we had a cache miss
    Read_Data_From_Ram(address);
    for(int i = 0; i < 32; i++){
		cache.set[setNum].line->data[i] = system_bus[i];
	}
    cache.set[setNum].line->tag = addrTag; //reset tag to match current data
    cache.set[setNum].line->valid = 1; //set tag to valid
    return cache.set[setNum].line->data[dataAddr];
}


int main() {
    // INITIALIZE CACHE
    for (int i = 0; i<8; i++) cache.set[i].line[0].valid = 0;
    
    // READ SOME DATA
    char c;
    c = Read_Data_From_Cache(0); printf("data = %c : hit count = %-3u : miss count = %-3u : read data count = %-3u\n", c, hit_count, miss_count,read_data_count );
    c = Read_Data_From_Cache(1); printf("data = %c : hit count = %-3u : miss count = %-3u : read data count = %-3u\n", c, hit_count, miss_count,read_data_count );
    c = Read_Data_From_Cache(2); printf("data = %c : hit count = %-3u : miss count = %-3u : read data count = %-3u\n", c, hit_count, miss_count,read_data_count );
    c = Read_Data_From_Cache(3); printf("data = %c : hit count = %-3u : miss count = %-3u : read data count = %-3u\n", c, hit_count, miss_count,read_data_count );
    c = Read_Data_From_Cache(4); printf("data = %c : hit count = %-3u : miss count = %-3u : read data count = %-3u\n", c, hit_count, miss_count,read_data_count );

    c = Read_Data_From_Cache(48); printf("data = %c : hit count = %-3u : miss count = %-3u : read data count = %-3u\n", c, hit_count, miss_count,read_data_count );
    c = Read_Data_From_Cache(49); printf("data = %c : hit count = %-3u : miss count = %-3u : read data count = %-3u\n", c, hit_count, miss_count,read_data_count );
    c = Read_Data_From_Cache(50); printf("data = %c : hit count = %-3u : miss count = %-3u : read data count = %-3u\n", c, hit_count, miss_count,read_data_count );
    c = Read_Data_From_Cache(51); printf("data = %c : hit count = %-3u : miss count = %-3u : read data count = %-3u\n", c, hit_count, miss_count,read_data_count );
    c = Read_Data_From_Cache(52); printf("data = %c : hit count = %-3u : miss count = %-3u : read data count = %-3u\n", c, hit_count, miss_count,read_data_count );
    c = Read_Data_From_Cache(53); printf("data = %c : hit count = %-3u : miss count = %-3u : read data count = %-3u\n", c, hit_count, miss_count,read_data_count );
    c = Read_Data_From_Cache(54); printf("data = %c : hit count = %-3u : miss count = %-3u : read data count = %-3u\n", c, hit_count, miss_count,read_data_count );
    c = Read_Data_From_Cache(55); printf("data = %c : hit count = %-3u : miss count = %-3u : read data count = %-3u\n", c, hit_count, miss_count,read_data_count );
    c = Read_Data_From_Cache(56); printf("data = %c : hit count = %-3u : miss count = %-3u : read data count = %-3u\n", c, hit_count, miss_count,read_data_count );
    c = Read_Data_From_Cache(57); printf("data = %c : hit count = %-3u : miss count = %-3u : read data count = %-3u\n", c, hit_count, miss_count,read_data_count );
    c = Read_Data_From_Cache(58); printf("data = %c : hit count = %-3u : miss count = %-3u : read data count = %-3u\n", c, hit_count, miss_count,read_data_count );
    c = Read_Data_From_Cache(59); printf("data = %c : hit count = %-3u : miss count = %-3u : read data count = %-3u\n", c, hit_count, miss_count,read_data_count );
    c = Read_Data_From_Cache(60); printf("data = %c : hit count = %-3u : miss count = %-3u : read data count = %-3u\n", c, hit_count, miss_count,read_data_count );
    c = Read_Data_From_Cache(61); printf("data = %c : hit count = %-3u : miss count = %-3u : read data count = %-3u\n", c, hit_count, miss_count,read_data_count );
    c = Read_Data_From_Cache(62); printf("data = %c : hit count = %-3u : miss count = %-3u : read data count = %-3u\n", c, hit_count, miss_count,read_data_count );
    c = Read_Data_From_Cache(63); printf("data = %c : hit count = %-3u : miss count = %-3u : read data count = %-3u\n", c, hit_count, miss_count,read_data_count );
    c = Read_Data_From_Cache(64); printf("data = %c : hit count = %-3u : miss count = %-3u : read data count = %-3u\n", c, hit_count, miss_count,read_data_count );
    c = Read_Data_From_Cache(65); printf("data = %c : hit count = %-3u : miss count = %-3u : read data count = %-3u\n", c, hit_count, miss_count,read_data_count );
    c = Read_Data_From_Cache(66); printf("data = %c : hit count = %-3u : miss count = %-3u : read data count = %-3u\n", c, hit_count, miss_count,read_data_count );
    c = Read_Data_From_Cache(67); printf("data = %c : hit count = %-3u : miss count = %-3u : read data count = %-3u\n", c, hit_count, miss_count,read_data_count );
    c = Read_Data_From_Cache(68); printf("data = %c : hit count = %-3u : miss count = %-3u : read data count = %-3u\n", c, hit_count, miss_count,read_data_count );
    c = Read_Data_From_Cache(69); printf("data = %c : hit count = %-3u : miss count = %-3u : read data count = %-3u\n", c, hit_count, miss_count,read_data_count );
    c = Read_Data_From_Cache(70); printf("data = %c : hit count = %-3u : miss count = %-3u : read data count = %-3u\n", c, hit_count, miss_count,read_data_count );
    // WRITE A LOT MORE TESTS

    return 0;
}

