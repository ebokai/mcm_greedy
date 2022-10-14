#include "data.h"


/******************************************************************************/
/**************************   MODEL COMPLEXITY   ******************************/
/******************************************************************************/
double GeomComplexity_SubCM(unsigned int m);
// defined in complexity.cpp

/******************************************************************************/
/**************** Log-Evidence (LogE) of a sub-complete model  ****************/
/******************************************************************************/
// Compute the log-evidence of a sub-complete model based on m basis elements
// ! Kset must have been previously reduced to these m basis elements !
// This function is mainly used for call by `LogE_PartMCM`,
// but can also be used to compute the log-likelihood of a complete model
//
double LogE_SubC_forMCM(map<__int128_t, unsigned int> Kset, uint32_t m, unsigned int N)
{
  double LogE = 0;

  map<__int128_t, unsigned int>::iterator it;
  unsigned int Ncontrol = 0; // for control
  unsigned int Ks = 0;
  double logpi = log(M_PI)/2;

  for (it = Kset.begin(); it!=Kset.end(); ++it)
  {
    Ks = (it->second);  Ncontrol += Ks;
    LogE += lgamma(Ks + 0.5) - logpi;
  }
  if (Ncontrol != N) { cout << "Error Likelihood function: Ncontrol != N" << endl;  }

  return LogE - lgamma( (double)( N + (1UL << (m-1)) ) ) + lgamma( (double)((1UL << (m-1)) ) ); 
}

/******************************************************************************/
/*********  Log-Evidence (LogE) of a sub-complete part of a MCM   *************/
/******************************************************************************/
// Compute the log-evidence of the sub-complete part (of an MCM) defined by Ai.
// This function could be also used directly by the user
// to compute the log-likelihood of a sub-complete model
// Rem: the function compute the LogE as if the space were reduced to the sub-space defined by the model

double LogE_SubCM(map<__int128_t, unsigned int> Kset, __int128_t Ai, unsigned int N, bool print_bool = false)
{
  map<__int128_t, unsigned int>::iterator it;
  map<__int128_t, unsigned int> Kset_new;

  __int128_t s;        // state
  unsigned int ks=0; // number of time state s appear in the dataset

  if (print_bool)  { 
  cout << endl << "--->> Build Kset for SC Model based on " << bitset<n>(Ai) << " for MCM.." << endl;
  }
//Build Kset:
  for (it = Kset.begin(); it!=Kset.end(); ++it)
  {
    s = it->first;      // initial state s 
    ks = it->second;    // # of times s appears in the data set
    if (print_bool)  {  cout << bitset<n>(s) << " \t" ;  }

    s &= Ai;   // troncated state: take only the bits indicated by Ai
//    sig_m = bitset<m>(bitset<m>(mu).to_string()).to_ulong(); //bitset<m>(mu).to_ulong(); // mu|m
    if (print_bool)  {  cout << bitset<n>(s) << endl; }

    Kset_new[s] += ks;
    //Kset[mu_m].second.push_back(make_pair(mu, N_mu));
  }
  if (print_bool)  {  cout << endl;  }

  bitset<n> hi{ static_cast<unsigned long long>(Ai >> 64) },
      lo{ static_cast<unsigned long long>(Ai) },
      bits{ (hi << 64) | lo };

  return LogE_SubC_forMCM(Kset_new, bits.count(), N);
}

/******************************************************************************/
/****************************   LogE of a MCM   *******************************/
/******************************************************************************/
//check if *Partition* is an actual partition of the r elements, 
// i.e., that no basis element appears in more than 1 part of the partition.

bool check_partition(map<uint32_t, uint32_t> Partition)
{
  map<uint32_t, uint32_t>::iterator Part;
  uint32_t sum = 0;
  uint32_t rank = 0; 

  for (Part = Partition.begin(); Part != Partition.end(); Part++)
  {
    sum |= (*Part).second;
    rank += bitset<n>((*Part).second).count();
    //cout << bitset<n>( (*Part).second ) << " \t";
  }
  //cout << bitset<n>(sum) << endl;

  return (bitset<n>(sum).count() == rank);
}

double LogE_MCM(map<__int128_t, unsigned int> Kset, map<unsigned int, __int128_t> Partition, unsigned int N, unsigned int r = n, bool print_bool = false)
{
  //if (!check_partition(Partition)) {cout << "Error, the argument is not a partition." << endl; return 0;  }

  //else
  //{
    double LogE = 0; 
    unsigned int rank = 0;
    map<unsigned int, __int128_t>::iterator Part;

    for (Part = Partition.begin(); Part != Partition.end(); Part++)
    {
        bitset<n> hi{ static_cast<unsigned long long>((*Part).second >> 64) },
            lo{ static_cast<unsigned long long>((*Part).second) },
            bits{ (hi << 64) | lo };

      LogE += LogE_SubCM(Kset, (*Part).second, N);
      rank += bits.count();
    }  
    return LogE - ((double) (N * (n-rank))) * log(2.);
  //}
  return 0;
}

