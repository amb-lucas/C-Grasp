#ifndef COMMON_GRASP_PRINT
#define COMMON_GRASP_PRINT

using namespace std;
#include <vector>

typedef long double Ld;
typedef vector<Ld> Vld;

void Vld_print(Vld &V){
	printf("(");
	for(int i=0; i<V.size(); i++){
		printf("%.6Lf",V[i]);
		if(i != V.size() -1) printf(", ");
	}
	printf(")\n");
}

void Ld_print(Ld X){
	printf("%.8Lf\n",X);
}

void Sol_print(Vld &V, Ld function(Vld V)){
	printf("Solution: "); Vld_print(V);
	printf("Objective Function: "); Ld_print(function(V));
}

#endif