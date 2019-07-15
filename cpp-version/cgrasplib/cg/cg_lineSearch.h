#ifndef C_GRASP_LINESEARCH
#define C_GRASP_LINESEARCH

using namespace std;
#include <vector>

typedef long double Ld;
typedef vector<Ld> Vld;	
typedef pair<Ld, Ld> Pld;

Pld defLineSearch(Vld X, Ld function(Vld V),
	Ld L, Ld U, Ld H, int Dim, int Delta){

	Ld Fobj = function(X);
	Ld Val = X[Dim];

	Delta >>= 1;
	Ld Fin = min(X[Dim]+(Delta*H), U);
	X[Dim] = max(X[Dim]-(Delta*H), L);

	while(X[Dim] <= Fin){

		Ld fobj = function(X);

		if(fobj < Fobj){
			Fobj = fobj;
			Val = X[Dim];
		}
	
		X[Dim] += H;
	}

	return {Fobj, Val};
}

#endif