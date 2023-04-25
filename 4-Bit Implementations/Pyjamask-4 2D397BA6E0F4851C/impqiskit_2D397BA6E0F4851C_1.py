# from : 00FF 0F0F 3333 5555 
#F[0] = X[2];
#F[1] = X[3];
#F[2] = X[1];
#F[3] = X[0];

from qiskit import QuantumCircuit
import matplotlib.pyplot as plt
circuit = QuantumCircuit(4)

circuit.cx((3),(1))
circuit.ccx((2),(0),(1))
circuit.cx((1),(2))
circuit.x(3)
circuit.ccx((2),(1),(3))
circuit.ccx((3),(0),(2))
circuit.cx((2),(0))
circuit.ccx((3),(1),(2))
circuit.draw(output="mpl")
plt.show()
#X[0] = F[1];
#X[1] = F[0];
#X[2] = F[3];
#X[3] = F[2];

# to : 56A9 49B5 AFA0 7C26 
# T-Depth : 4
# Depth : 31
