#include "stdio.h"


#define MAX_KEY_SIZE 3


unsigned char HASH_BUFFER[MAX_KEY_SIZE];


void Generate_HashTable_Key(int tile, unsigned char* key) 
{
	int i=0;
	
	if(tile == 0){
		key[0] = '0';
		key[1] = '\0';
	}
	else{
		for(i=0; tile>0; i++){
			key[i] = tile%10 + '0';
			tile /= 10;
		}
		key[i] = '\0';
	}
		
	if(i>MAX_KEY_SIZE){
		printf("ERROR: MAX_KEY_SIZE is exceeded in Generate_HashTable_Key. \n");
		exit(-1);
	}     
}

void test_Generate_HashTable_Key()
{
    for (int i = 0; i < 31 * 32; i++)
    {
        Generate_HashTable_Key(i, HASH_BUFFER);
        printf("%d:%s\n", i, HASH_BUFFER);
    }
}

int main()
{
    test_Generate_HashTable_Key();
}