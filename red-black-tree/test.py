A = int(input())
B = int(input())

def preProcess(A, B):
	X = []
	Y = []
	cnt = 0
	while A > 0:
		if A % 10 != 0:
			X.append(A % 10)
		else:
			cnt += 1
		A = A // 10

	X.sort()

	while B > 0:
		Y.append(B % 10)
		B = B // 10

	Y.reverse()

	return X, Y, cnt


X, Y, k = preProcess(A, B)

i = 0
j = 0
if X[0] < Y[0]:
	c = X[0]
	i+=1
else:
	c = Y[0]
	j+=1

while k > 0:
	c = c*10
	k-=1

while i < len(X) and j < len(Y):
	if(X[i] < Y[j]):
		c = c*10 + X[i]
		i+=1
	else:
		c = c*10 + Y[j]
		j+=1

while i < len(X):
	c = c*10 + X[i]
	i+=1

while j < len(Y):
	c = c*10 + Y[j]
	j+=1

print(c)