######### Reversible 

def RNOT1(a):
	return not a 

def CNOT1(a, b):
	return a ^ b

def CCNOT2(a, b, c):
	return (a & b) ^ c
	#return a ^ (b & c)

def CCCNOT2(a, b, c, d):
	return (a & b & c) ^ d

Z = []
for f in range(16)[::]:

	Y = [None]*4


	X = [x == '1' for x in list((bin(f)[2:]).zfill(4))]
	F = [None]*4

	############ PRINCE SBox (BF32AC916780E5D4)
    ########### Copy starts
	F[0] = X[1];
	F[1] = X[0];
	F[2] = X[2];
	F[3] = X[3];

	F[0] = CCNOT2(F[3], F[2], F[0]);
	F[1] = CNOT1(F[0], F[1]);
	F[3] = CNOT1(F[2], F[3]);
	F[2] = CCNOT2(F[1], F[0], F[2]);
	F[1] = CNOT1(F[0], F[1]);
	F[3] = CNOT1(F[2], F[3]);
	F[0] = CCNOT2(F[3], F[2], F[0]);

	X[0] = F[1];
	X[1] = F[0];
	X[2] = F[2];
	X[3] = F[3];                                                                                               
    ########### Copy ends

	Y[:] = X[:]
	Y = (int('0b'+(''.join(map(str, map(int, Y[::])))), 2))
	
	Z.append(Y)
	

for f in range(16):
	if f not in Z:
		print ('Error, missing %x'%f)
print((''.join(map(lambda x: hex(x)[2:], Z))).upper())