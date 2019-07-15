
def def_LineSearch(X, funct, L, U, H, Dim, Delta):

	ini = X[Dim]
	Val = ini
	Fobj = funct(X)

	Delta = Delta/2

	Fim = min(Val+(Delta*H), U)
	X[Dim] = max(Val-(Delta*H), L)

	while X[Dim] <= Fim:

		fobj = funct(X)

		if fobj < Fobj:
			Fobj = fobj
			Val = X[Dim]

		X[Dim] += H

	X[Dim] = ini
	return [Fobj, Val, Dim]