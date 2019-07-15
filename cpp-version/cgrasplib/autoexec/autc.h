#ifndef C_GRASP_AUTO_EXEC
#define C_GRASP_AUTO_EXEC

#include <vector>
using namespace std;

typedef long double Ld;
typedef vector<Ld> Vld;

Ld func(Vld V);
extern Vld Lower_limits, Upper_limits;
extern bool maximize;
extern Ld alfa, h_inf, h_sup, objective, objective_maximize;
extern int num_threads_cgrasp, num_threads_construct_greedy, num_threads_local_improve;
extern int max_iterations, max_iterations_without_improvement;
extern int delta_linear_search, points_to_examine;

#endif