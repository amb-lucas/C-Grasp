
from cgrasplib.cgrasp import CGrasp

def func(X):
	s = 0;
	for x in X:
		s += x*x
	return s

L = [-5, -5, -5, -5, -5, -5]
U = [5, 5, 5, 5, 5, 5]

X = CGrasp(func, L, U)

print(f'Solution: {X}')
print(f'Objective Function: {func(X)}')