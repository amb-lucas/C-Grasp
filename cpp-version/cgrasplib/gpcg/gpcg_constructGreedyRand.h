#ifndef PC_GRASP_CONSTRUCTGREEDYRANDOM
#define PC_GRASP_CONSTRUCTGREEDYRANDOM

using namespace std;
#include <vector>
#include "omp.h"
#include "gpcg_lineSearch.h"

#include "../common/com_rand.h"
#include "../common/com_params.h"

typedef long double Ld;
typedef vector<Ld> Vld;
typedef pair<Ld, Ld> Pld;

void defconstructGreedyRandomized(Vld &X, Ld function(Vld V),
	Vld &L, Vld &U, Ld H, Ld alfa, int Delta, int nThreads,
	decltype(defLineSearch) LineSearch){

	vector<bool> Unfixed(X.size(), 1);
	int qtf = X.size();

	vector<Pld> Obj(nThreads); 

	while(qtf){

		for(int k=0; k<nThreads; k++){
			Obj[k].first = INF;
			Obj[k].second = -INF;
		}

		vector<vector<pair<Pld, Ld>> > Prox(nThreads);

		int i = 0;

		#pragma omp target teams distribute parallel for num_threads(nThreads)
		for(int i=0; i<X.size(); i++){

			if(Unfixed[i]){

				Pld P = LineSearch(X, function,
					L[i], U[i], H, i, Delta);

				int ID = omp_get_thread_num();
				Prox[ID].push_back({P,i});
				Obj[ID].first = min(Obj[ID].first, P.first);
				Obj[ID].second = max(Obj[ID].second, P.first);
			}
		}

		Ld ObjMin = INF;
		Ld ObjMax = -INF;
		for(int k=0; k<nThreads; k++){
			ObjMin = min(ObjMin, Obj[k].first);
			ObjMax = max(ObjMax, Obj[k].second);
		}

		Ld Corte = ObjMin + alfa*(ObjMax-ObjMin);

		vector<Pld> Filtradas;
		for(int k=0; k<nThreads; k++){
			for(auto u: Prox[k]){
				if(u.first.first <= Corte)
					Filtradas.push_back({u.second, u.first.second});
			}
		}

		int Selecionado = Int_random(0, Filtradas.size()-1);
		X[Filtradas[Selecionado].first] = Filtradas[Selecionado].second;

		Unfixed[Filtradas[Selecionado].first] = 0;
		qtf--;
	}
}

#endif