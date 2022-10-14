#include "header.h"
#include <time.h> 

int main(int argc, char **argv){

	srand(time(NULL));

	map<int,int> partition;
	map<int,int> new_partition;

	// start with random partition 
	for(int i = 0; i < n; i++){
		partition[i] = i % 4;
	}

	// test candidate functions
	for(int i = 0; i < n; i++){
		new_partition = merge_partition(partition);
		new_partition = split_partition(partition);
		new_partition = switch_partition(partition);
	}
	
	return 0;
}