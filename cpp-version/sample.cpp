
// Please make sure to use the make command according
// to the desired library
// cgrasp.h		: compile
// pcgrasp.h	: pcompile
// gpcgrasp.h	: gpcompile

#include "./cgrasplib/autoexec/autc.h"
#include "./cgrasplib/common/com_params.h"

// Define your function here
Ld func(Vld V){
	Ld s = 0;
	for(Ld v: V) s += v*v;
	return s;
}

// Define the boundaries here
Vld Lower_limits = {-10, -10, -10, -10, -10, -10, -10, -10, -10, -10, -10, -10, -10};
Vld Upper_limits = {10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10};

// Define the parameters
int max_iterations = default_max_iterations;
int max_iterations_without_improvement = default_max_iterations_without_improvement;

bool maximize = 0;
Ld objective = default_objective;

Ld alfa = default_alfa;
Ld h_inf = default_h_inf;
Ld h_sup = default_h_sup;

int delta_linear_search = default_delta_linear_search;
int points_to_examine = default_points_to_examine;

int num_threads_cgrasp = default_num_threads_cgrasp;
int num_threads_construct_greedy = default_num_threads_construct_greedy;
int num_threads_local_improve = default_num_threads_local_improve;
