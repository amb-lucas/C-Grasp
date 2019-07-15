
from ...common.comparams.params import INF
from ...common.comrandom.crandom import random_int

def def_ConstructGreedyRandomized(X, funct, L, U, H, alfa, delta, LineSearch):

	Unfixed = []
	for i in range(len(L)):
		Unfixed.append(True)

	qtf = len(L)

	for qtf in range(len(L)):

		ObjMin = INF
		ObjMax = -INF

		Proximas = []

		for i in range(len(L)):

			if Unfixed[i] == True:

				P = LineSearch(X, funct, L[i], U[i], H, i, delta)
				Proximas.append(P)

				ObjMin = min(ObjMin, P[0])
				ObjMax = max(ObjMax, P[0])

		Corte = ObjMin + alfa*(ObjMax-ObjMin)

		Filtradas = []
		for u in Proximas:
			if u[0] <= Corte:
				Filtradas.append([u[1], u[2]])

		Select = random_int(len(Filtradas))
		Ref = Filtradas[Select][1]

		X[Ref] = Filtradas[Select][0]
		Unfixed[Ref] = 0

	return X