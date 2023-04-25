# from : 00FF 0F0F 3333 5555 
#F[0] = X[2];
#F[1] = X[1];
#F[2] = X[0];
#F[3] = X[3];

from qiskit import QuantumCircuit
import matplotlib.pyplot as plt
circuit = QuantumCircuit(4)

circuit.cx((2),(0))
circuit.cx((0),(1))
circuit.cx((3),(2))
circuit.cx((1),(3))
circuit.ccx((3),(2),(0))
circuit.cx((0),(3))
circuit.cx((1),(2))
circuit.draw(output="mpl")
plt.show()
#X[0] = F[3];
#X[1] = F[1];
#X[2] = F[0];
#X[3] = F[2];

# to : 1BD8 3CC3 724E 6969 
# T-Depth : 1
# Depth : 11
