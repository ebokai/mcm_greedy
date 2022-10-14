#include "header.h"

map<uint32_t, int> get_data(int &N){

	map<uint32_t, int> data;
	uint32_t state;
	string fname = "./data/HG19_k6_mu0.50_(20,4,5)_B0.55_N1000_00.dat";
	string line, subline;
	ifstream myfile(fname);

	while (getline(myfile, line)){
		subline = line.substr(0,n);
		state = bitset<n>(subline).to_ulong();
		data[state] += 1;
		N += 1;
	}

	myfile.close();

	return data;
}

void partition_print(map<int, int> partition){

	int np = max_comm(partition);

	cout << "[";

	for (int i = 0; i <= np; i++){
		cout << "[";
		for (int j = 0; j < n; j++){
			if (partition[j] == i){
				cout << " " << j << " ";
			}
		}
		cout << "]";
	}

	cout << "]" << endl;
}