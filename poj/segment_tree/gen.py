import random
N = 5000
T = 30
O = 1000
print(N, T, O)
for i in range(0, O):
	if random.randint(0, 1) == 0:
		a = random.randint(1, N)
		b = random.randint(1, N)
		c = random.randint(1, T)
		print("C {0} {1} {2}".format(a, b, c))
	else:
		a = random.randint(1, N)
		b = random.randint(1, N)
		print("P {0} {1}".format(a, b))