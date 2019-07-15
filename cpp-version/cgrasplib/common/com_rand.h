#ifndef COMMON_GRASP_RANDOM
#define COMMON_GRASP_RANDOM

using namespace std;
#include <random>
#include <vector>

typedef long double Ld;
typedef vector<Ld> Vld;	

random_device rand_dev;
mt19937 rand_engine(rand_dev());
mt19937_64 rand_engine_64(rand_dev());

int Int_random(int l, int u){
	uniform_int_distribution<int> unif(l, u);
	return unif(rand_engine);
}

Ld Ld_random(Ld l, Ld u){
	uniform_real_distribution<Ld> unif(l, u);
	return unif(rand_engine_64);
}

Vld Vld_random(Vld &L, Vld &U){
	Vld X(L.size());
	for(int i=0; i<X.size(); i++)
		X[i] = Ld_random(L[i], U[i]);
	return X;
}

#endif