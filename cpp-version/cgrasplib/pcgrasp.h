#ifndef PC_GRASP_MAIN
#define PC_GRASP_MAIN

#include <bits/stdc++.h>

#include "common/com_rand.h"
#include "common/com_print.h"
#include "common/com_params.h"

#include "pcg/pcg_constructGreedyRand.h"
#include "pcg/pcg_localImprove.h"

using namespace std;

typedef long double Ld;
typedef vector<Ld> Vld;

// Minimização

Vld CGrasp(Ld function(Vld V), Vld &L, Vld &U,
	int num_threads_cgrasp = default_num_threads_cgrasp,
	int num_threads_construct_greedy = default_num_threads_construct_greedy,
	int num_threads_local_improve = default_num_threads_local_improve,
	Ld alfa = default_alfa, Ld h_inf = default_h_inf, Ld h_sup = default_h_sup,
	int max_iterations = default_max_iterations,
	int max_iterations_without_improvement = default_max_iterations_without_improvement,
	Ld objective = default_objective,
	int delta_linear_search = default_delta_linear_search,
	int points_to_examine = default_points_to_examine,
	decltype(defconstructGreedyRandomized) constructGreedyRandomized=defconstructGreedyRandomized,
	decltype(defLocalImprove) LocalImprove=defLocalImprove, decltype(defLineSearch) LineSearch=defLineSearch){

	if(num_threads_cgrasp > 0){
		num_threads_local_improve = num_threads_cgrasp;
		num_threads_construct_greedy = num_threads_cgrasp;
	}

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

	int iterMelhor = max_iterations_without_improvement, iter = 0;
	
	#pragma omp parallel num_threads(num_threads_cgrasp)
	{
		while(1){

			bool loop = 0;

			#pragma omp critical(cgrasp1)
			{
				if(iter<max_iterations && iterMelhor>0 && ObjF > objective){
					loop = 1;
					iter++;
				}
			}

			if(loop == 0) break;

			Vld X = Vld_random(L, U);
			Ld Obji = function(X);
			Ld h = h_sup;

			while(h > h_inf){

				constructGreedyRandomized(X, function, L, U, h, alfa, delta_linear_search, num_threads_construct_greedy, LineSearch);
				LocalImprove(X, function, L, U, h, points_to_examine, num_threads_local_improve);

				Ld ObjDepois = function(X);
				if(Obji <= ObjDepois) h = h/2;
				else Obji = ObjDepois;
			}

			Obji = function(X);

			#pragma omp critical(cgrasp1)
			{
				if(Obji < ObjF){
					ObjF = Obji;
					Xm = X;
					iterMelhor = max_iterations_without_improvement;
				}
				else iterMelhor--;
			}
		}
	}

	return Xm;
}


// Maximização

function<Ld(Vld)> param_function;

Ld param_function_max(Vld V){
	return -param_function(V);
}

Vld CGrasp_Max(Ld function(Vld V), Vld &L, Vld &U,
	int num_threads_cgrasp = default_num_threads_cgrasp,
	int num_threads_construct_greedy = default_num_threads_construct_greedy,
	int num_threads_local_improve = default_num_threads_local_improve,
	Ld alfa = default_alfa, Ld h_inf = default_h_inf, Ld h_sup = default_h_sup,
	int max_iterations = default_max_iterations,
	int max_iterations_without_improvement = default_max_iterations_without_improvement,
	Ld objective = default_objective_maximize,
	int delta_linear_search = default_delta_linear_search,
	int points_to_examine = default_points_to_examine,
	decltype(defconstructGreedyRandomized) constructGreedyRandomized=defconstructGreedyRandomized,
	decltype(defLocalImprove) LocalImprove=defLocalImprove, decltype(defLineSearch) LineSearch=defLineSearch){

	param_function = function;
	return CGrasp(param_function_max, L, U, num_threads_cgrasp, num_threads_construct_greedy,
		num_threads_local_improve, alfa, h_inf, h_sup, max_iterations, max_iterations_without_improvement,
		-objective, delta_linear_search, points_to_examine, constructGreedyRandomized, LocalImprove, LineSearch);
}

#endif