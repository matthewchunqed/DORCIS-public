// from : 00FF 0F0F 3333 5555 

F[0] = X[1];
F[1] = X[2];
F[2] = X[3];
F[3] = X[0];

F[2] = CNOT1(F[0], F[2]);
F[2] = CNOT1(F[3], F[2]);
F[3] = CCNOT2(F[2], F[1], F[3]);
F[1] = CNOT1(F[0], F[1]);
F[2] = CCNOT2(F[3], F[0], F[2]);
F[3] = RNOT1(F[3]);
F[0] = CCNOT2(F[2], F[1], F[0]);
F[1] = CCNOT2(F[3], F[0], F[1]);
F[2] = CNOT1(F[0], F[2]);
F[3] = CNOT1(F[1], F[3]);
F[1] = CCNOT2(F[3], F[2], F[1]);
F[3] = CNOT1(F[0], F[3]);
F[0] = RNOT1(F[0]);
F[3] = CNOT1(F[1], F[3]);

X[0] = F[0];
X[1] = F[1];
X[2] = F[3];
X[3] = F[2];

// to : E8D8 7D11 BE0A 4F8C 
// T-Depth : 5
// Depth : 41
