#ifndef C_GRASP_CONSTRUCTGREEDYRANDOM
#define C_GRASP_CONSTRUCTGREEDYRANDOM

using namespace std;
#include <vector>
#include "cg_lineSearch.h"

#include "../common/com_rand.h"
#include "../common/com_params.h"

typedef long double Ld;
typedef vector<Ld> Vld;
typedef pair<Ld, Ld> Pld;

void defconstructGreedyRandomized(Vld &X, Ld function(Vld V),
	Vld &L, Vld &U, Ld H, Ld alfa, int Delta,
	decltype(defLineSearch) LineSearch){

	vector<bool> Unfixed(X.size(), 1);
	int qtf = X.size();

	Ld ObjMin, ObjMax;

	while(qtf){

		ObjMin = INF;
		ObjMax = -INF;

		vector<pair<Pld, Ld> > Proximas;

		for(int i=0; i<X.size(); i++){
			
			if(Unfixed[i]){

				Pld P = LineSearch(X, function,
					L[i], U[i], H, i, Delta);
				Proximas.push_back({P,i});

				ObjMin = min(ObjMin, P.first);
				ObjMax = max(ObjMax, P.first);
			}
		}

		Ld Corte = ObjMin + alfa*(ObjMax-ObjMin);

		vector<Pld> Filtradas;
		for(auto u: Proximas){
			if(u.first.first <= Corte)
				Filtradas.push_back({u.second, u.first.second});
		}

		int Selecionado = Int_random(0, Filtradas.size()-1);
		X[Filtradas[Selecionado].first] = Filtradas[Selecionado].second;

		Unfixed[Filtradas[Selecionado].first] = 0;
		qtf--;
	}
}

#endif