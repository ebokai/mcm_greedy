#include "header.h"
#include <time.h> 

int main(int argc, char **argv){

	srand(time(NULL));

	int N = 0;

	map<int,int> partition;
	map<int,int> new_partition;
	map<int,int> best_partition;

	map<uint32_t, int> data = get_data(N);

	// start with random partition 
	for(int i = 0; i < n; i++){
		partition[i] = i % 4;
	}

	best_partition = partition;

	double logE = evidence(partition, data, N);
	double best_logE = logE;
	double new_logE, delta_logE;
	float p, u;
	float T = 100, T0 = 100;

	for (int run = 0; run < 50; run++){

		cout << "RUN: " << run << "====================" << endl;

		T = T0;
		partition = best_partition;
		logE = best_logE;

		for (int step = 0; step < max_steps; step++){

			int f = rand()/(RAND_MAX/3);
			switch(f){
				case 0:
				new_partition = merge_partition(partition);

				case 1:
				new_partition = split_partition(partition);

				case 2:
				new_partition = switch_partition(partition);
			}

			new_logE = evidence(new_partition, data, N);
			delta_logE = new_logE - logE;

			if (new_logE > best_logE){
				best_logE = new_logE;
				best_partition = new_partition;
				cout << best_logE << " ";
				partition_print(partition);

			}

			p = exp(delta_logE/T);
			u = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);

			if (p > u){
				partition = new_partition;
				logE = new_logE;
			}

			T = T0 * (1 - step/max_steps);

		}
	}

	
	return 0;
}