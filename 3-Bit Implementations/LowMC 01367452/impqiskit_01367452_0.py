# from : 000F 0033 0055 
#F[0] = X[0];
#F[1] = X[1];
#F[2] = X[2];

from qiskit import QuantumCircuit
import matplotlib.pyplot as plt
circuit = QuantumCircuit(3)

circuit.ccx((2),(1),(0))
circuit.ccx((2),(0),(1))
circuit.ccx((1),(0),(2))
circuit.cx((0),(1))
circuit.cx((1),(2))
circuit.draw(output="mpl")
plt.show()
#X[0] = F[0];
#X[1] = F[1];
#X[2] = F[2];

# to : 001E 0039 006A 
# T-Depth : 3
# Depth : 23
