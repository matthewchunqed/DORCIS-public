# from : 000F 0033 0055 
#F[0] = X[0];
#F[1] = X[1];
#F[2] = X[2];

from qiskit import QuantumCircuit
import matplotlib.pyplot as plt
circuit = QuantumCircuit(3)

circuit.ccx((2),(0),(1))
circuit.ccx((2),(1),(0))
circuit.ccx((1),(0),(2))
circuit.cx((1),(0))
circuit.cx((0),(2))
circuit.x(0)
circuit.draw(output="mpl")
plt.show()
#X[0] = F[1];
#X[1] = F[2];
#X[2] = F[0];

# to : 0036 006A 00D2 
# T-Depth : 3
# Depth : 24
