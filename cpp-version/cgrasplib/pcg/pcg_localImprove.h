#ifndef PC_GRASP_LOCALIMPROVE
#define PC_GRASP_LOCALIMPROVE

using namespace std;
#include <vector>
#include "omp.h"
#include "../common/com_rand.h"

void defLocalImprove(Vld &X, Ld function(Vld V),
	Vld &L, Vld &U, Ld H, int MaxPointsToExamine, int nThreads){

	Vld Y = X;
	Ld Fobj = function(Y);

	#pragma omp parallel for num_threads(nThreads)
	for(int j=0; j<MaxPointsToExamine; j++){

		Vld V = Vld_random(L, U);
		Ld sz = 0;

		for(int i=0; i<V.size(); i++){
			V[i] -= Y[i];
			sz += V[i]*V[i];
		}
		
		sz = sqrt(sz);

		for(int i=0; i<V.size(); i++){
			V[i] = Y[i]+(V[i]*H/sz);
			if(V[i] < L[i]) V[i] = L[i];
			else if(V[i] > U[i]) V[i] = U[i];
		}

		Ld Fobi = function(V);

		#pragma omp critical(localimprove)
		{
			if(Fobi < Fobj){
				Fobj = Fobi;
				X = V;
			}
		}
	}
}

#endif