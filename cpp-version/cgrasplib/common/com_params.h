#ifndef COMMON_GRASP_PARAMETERS
#define COMMON_GRASP_PARAMETERS

typedef long double Ld;
const Ld INF = 1e32;

const Ld default_alfa = 0.25;
const Ld default_h_inf = -1;
const Ld default_h_sup = -1;
const Ld default_objective = -INF;
const Ld default_objective_maximize = INF;

const int default_num_threads_cgrasp = 3;
const int default_num_threads_construct_greedy = 4;
const int default_num_threads_local_improve = 4;

const int default_max_iterations = 600;
const int default_max_iterations_without_improvement = 30;

const int default_delta_linear_search = 20;
const int default_points_to_examine = 100;

#endif