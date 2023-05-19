######### Reversible 

def RNOT1(a):
	return not a 

def CNOT1(a, b):
	return a ^ b

def CCNOT2(a, b, c):
	return (a & b) ^ c

Z = []
for f in range(8)[::]:

	Y = [None]*3


	X = [x == '1' for x in list((bin(f)[2:]).zfill(3))]
	F = [None]*3

	############ LowMC SBox (01367452)
    ########### Copy starts
	F[0] = X[0];
	F[1] = X[1];
	F[2] = X[2];

	F[0] = CCNOT2(F[2], F[1], F[0]);
	F[1] = CCNOT2(F[2], F[0], F[1]);
	F[2] = CCNOT2(F[1], F[0], F[2]);
	F[1] = CNOT1(F[0], F[1]);
	F[2] = CNOT1(F[1], F[2]);

	X[0] = F[0];
	X[1] = F[1];
	X[2] = F[2];                                                                                  
    ########### Copy ends

	Y[:] = X[:]
	Y = (int('0b'+(''.join(map(str, map(int, Y[::])))), 2))
	
	Z.append(Y)
	

for f in range(8):
	if f not in Z:
		print ('Error, missing %x'%f)
print((''.join(map(lambda x: hex(x)[2:], Z))).upper())