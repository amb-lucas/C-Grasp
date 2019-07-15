
from random import randrange as random_int
from random import uniform as random_double

def random_vld(L, U):
	X = []
	for i in range(len(L)):
		X.append(random_double(L[i], U[i]))
	return X

import numpy as np
def random_vld_np(L, U):
	X = np.random.rand(len(L), 1) * (U-L) + L
	return X
