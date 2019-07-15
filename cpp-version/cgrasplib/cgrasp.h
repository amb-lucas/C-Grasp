#ifndef C_GRASP_MAIN
#define C_GRASP_MAIN

#include <bits/stdc++.h>

#include "common/com_rand.h"
#include "common/com_print.h"
#include "common/com_params.h"

#include "cg/cg_constructGreedyRand.h"
#include "cg/cg_localImprove.h"

using namespace std;

typedef long double Ld;
typedef vector<Ld> Vld;

// Minimização

Vld CGrasp(Ld function(Vld V), Vld &L, Vld &U, Ld alfa = default_alfa,
	Ld h_inf = default_h_inf, Ld h_sup = default_h_sup,
	int max_iterations = default_max_iterations,
	int max_iterations_without_improvement = default_max_iterations_without_improvement,
	Ld objective = default_objective,
	int delta_linear_search = default_delta_linear_search,
	int points_to_examine = default_points_to_examine,
	decltype(defconstructGreedyRandomized) constructGreedyRandomized=defconstructGreedyRandomized,
	decltype(defLocalImprove) LocalImprove=defLocalImprove, decltype(defLineSearch) LineSearch=defLineSearch){

	if(h_sup == -1 || h_inf == -1){
		Ld avg = 0;
		for(int i=0; i<L.size(); i++)
			avg += U[i]-L[i];
		avg /= L.size();
		h_inf = avg/1000;
		h_sup = avg*10;
	}

	Vld Xm = Vld_random(L, U);
	Ld ObjF = function(Xm);

	int iterMelhor = max_iterations_without_improvement;
	for(int iter = 0; iter < max_iterations && iterMelhor && ObjF > objective; iter++){

		Vld X = Vld_random(L, U);
		Ld Obji = function(X);
		Ld h = h_sup;

		while(h > h_inf){

			constructGreedyRandomized(X, function, L, U, h, alfa, delta_linear_search, LineSearch);
			LocalImprove(X, function, L, U, h, points_to_examine);

			Ld ObjDepois = function(X);
			if(Obji <= ObjDepois) h = h/2;
			else Obji = ObjDepois;
		}

		Obji = function(X);

		if(Obji < ObjF){
			ObjF = Obji;
			Xm = X;	
			iterMelhor = max_iterations_without_improvement;
		}
		else iterMelhor--;
	}

	return Xm;
}


// Maximização

function<Ld(Vld)> param_function;

Ld param_function_max(Vld V){
	return -param_function(V);
}

Vld CGrasp_Max(Ld function(Vld V), Vld &L, Vld &U, Ld alfa = default_alfa,
	Ld h_inf = default_h_inf, Ld h_sup = default_h_sup,
	int max_iterations = default_max_iterations,
	int max_iterations_without_improvement = default_max_iterations_without_improvement,
	Ld objective = default_objective_maximize,
	int delta_linear_search = default_delta_linear_search,
	int points_to_examine = default_points_to_examine,
	decltype(defconstructGreedyRandomized) constructGreedyRandomized=defconstructGreedyRandomized,
	decltype(defLocalImprove) LocalImprove=defLocalImprove, decltype(defLineSearch) LineSearch=defLineSearch){

	param_function = function;
	return CGrasp(param_function_max, L, U, alfa, h_inf, h_sup,
		max_iterations, max_iterations_without_improvement,
		-objective, delta_linear_search, points_to_examine,
		constructGreedyRandomized, LocalImprove, LineSearch);
}

#endif