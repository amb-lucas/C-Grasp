
from .common.comrandom.crandom import *
from .common.comparams.params import *
from .ccgrasp.lineSearch.linesearch import *
from .ccgrasp.localImprove.localimprove import *
from .ccgrasp.constructGreedyRandom.constructgreedyrandom import *

def CGrasp(funct, L, U,
	alfa = default_alfa,
	h_inf = default_h_inf,
	h_sup = default_h_sup,
	max_iterations = default_max_iterations,
	max_iterations_without_improvement = default_max_iterations_without_improvement,
	objective = default_objective,
	delta_linear_search = default_delta_linear_search,
	points_to_examine = default_points_to_examine,
	ConstructGreedyRandomized = def_ConstructGreedyRandomized,
	LineSearch = def_LineSearch,
	LocalImprove = def_LocalImprove):

	if h_sup == -1 or h_inf == -1:
		avg = 0;
		for i in range(len(L)):
			avg += U[i]-L[i]

		avg /= len(L)
		h_inf = avg/1000
		h_sup = avg*10

	Xm = random_vld(L, U)
	ObjF = funct(Xm)

	iterMelhor = max_iterations_without_improvement
	iter = 0

	while iter < max_iterations and iterMelhor > 0 and ObjF > objective:
			
		iter += 1

		X = random_vld(L, U)
		Obji = funct(X)
		h = h_sup

		while h >= h_inf:

			X = ConstructGreedyRandomized(X, funct, L, U, h, alfa, delta_linear_search, LineSearch)
			X = LocalImprove(X, funct, L, U, h, points_to_examine)

			ObjDepois = funct(X)

			if Obji <= ObjDepois:
				h = h/2
			else:
				Obji = ObjDepois

		Obji = funct(X)

		if Obji < ObjF:
			ObjF = Obji
			Xm = X
			iterMelhor = max_iterations_without_improvement
		else:
			iterMelhor -= 1

	return Xm
