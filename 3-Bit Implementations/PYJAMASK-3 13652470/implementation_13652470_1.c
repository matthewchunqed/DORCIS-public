// from : 000F 0033 0055 

F[0] = X[1];
F[1] = X[2];
F[2] = X[0];

F[0] = CCNOT2(F[2], F[1], F[0]);
F[1] = CNOT1(F[2], F[1]);
F[2] = RNOT1(F[2]);
F[1] = CCNOT2(F[2], F[0], F[1]);
F[2] = CCNOT2(F[1], F[0], F[2]);

X[0] = F[0];
X[1] = F[1];
X[2] = F[2];

// to : 0036 006A 00D2 
// T-Depth : 3
// Depth : 23
// Gate Count : 5
