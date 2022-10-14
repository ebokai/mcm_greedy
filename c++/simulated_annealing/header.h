#include <map>
#include <iostream>
#include <algorithm>

using namespace std;

// PARAMETERS =========================
const int max_an_steps = 1000;
const int n = 20;
// ====================================

// FUNCTION DEFS ======================
int max_comm(map<int,int> partition);
map<int, int> merge_partition(map<int,int> partition);
map<int, int> split_partition(map<int,int> partition);
map<int, int> switch_partition(map<int,int> partition);
double evidence(map<int,int> partition, map<uint32_t, int> data);
// ====================================