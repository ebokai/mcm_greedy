#include "header.h"


bool compare(const pair<int, int>&a, const pair<int, int>&b)
{
   return a.second<b.second;
}

int rand_ab(int a, int b){
	int x = rand()/(RAND_MAX/2);
	return a + x * (b - a);
}

int max_comm(map<int,int> partition){
	return max_element(partition.begin(), partition.end(), compare) -> second;
}

// MERGE PARTITIONS 
map<int, int> merge_partition(map<int,int> partition){

	int np = max_comm(partition);
	if (np < 2){return partition;}

	int p1 = 0, p2 = 0;
	int pi, p3;
	map<int, int> new_partition;

	// pick two distinct communities
	while (p1 == p2){
		p1 = rand() / (RAND_MAX/np);
		p2 = rand() / (RAND_MAX/np);
	}

	/* make sure there are no empty communities of lower index  
	so no [0,1,2,3] => [0,2,3] but [0,1,2,3] => [0,1,2]
	this allows simply using random number to pick a community in 
	the split_partition function */

	if (p2 == np){
		p3 = p1;
		p1 = p2;
	} else {
		p3 = p2;
	}

	// re-assign nodes 
	for (int i = 0; i < n; i++){
		pi = partition[i];
		if (pi == p1){
			new_partition[i] = p3;
			cout << "merged C" << p1 << " by assigning node " << i << " to C" << p3 << endl;
		} else {
			new_partition[i] = pi;
		}
	}

	return new_partition;
}

// SPLIT PARTITIONS
map<int, int> split_partition(map<int,int> partition){

	int np = max_comm(partition);
	
	// pick a random community 
	int p1 = rand()/(RAND_MAX/np);
	int pi;

	// check if community contains at least 2 nodes 	
	int np1 = 0;
	for (int i = 0; i < n; i++){
		if (partition[i] == p1){
			np1 += 1;
		}
	}

	if (np1 < 2) {return partition;}
	map<int, int> new_partition;

	// randomly assign nodes to new community 
	for (int i = 0; i < n; i++){
		pi = partition[i];
		if (pi == p1){
			new_partition[i] = rand_ab(p1, np+1);
			cout << "split C" << p1 << " by assigning node " << i << " to C" << new_partition[i] << endl;
		}
	}

	return new_partition;
}

// SWITCH NODES BETWEEN COMMS 
map<int, int> switch_partition(map<int,int> partition){

	int np = max_comm(partition);
	if (np < 2) {return partition;}

	int node = rand()/(RAND_MAX/n);
	int pn = partition[node];

	int p1 = rand()/(RAND_MAX/np);

	while (p1 == pn){
		p1 = rand()/(RAND_MAX/np);
	} 

	partition[node] = p1;

	cout << "switched node " << node << " from C" << pn << " to C" << p1 << endl;

	return partition;
}