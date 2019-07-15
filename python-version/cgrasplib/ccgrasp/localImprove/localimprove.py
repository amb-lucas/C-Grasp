
from ...common.comrandom.crandom import random_vld
from math import sqrt

def def_LocalImprove(X, funct, L, U, H, points_to_examine):

	Y = []
	for x in X:
		Y.append(x)

	Fobj = funct(X)

	for j in range(points_to_examine):

		V = random_vld(L, U)
		sz = 0
		for i in range(len(V)):
			V[i] = V[i] - Y[i]
			sz += V[i]*V[i]
		sz = sqrt(sz)

		for i in range(len(V)):
			V[i] = Y[i]+(V[i]*H/sz)
			V[i] = max(V[i], L[i])
			V[i] = min(V[i], U[i])

		Fobi = funct(V)

		if Fobi < Fobj:
			Fobj = Fobi
			X = V

	return X