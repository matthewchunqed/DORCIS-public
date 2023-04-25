# from : 00FF 0F0F 3333 5555 
#F[0] = X[0];
#F[1] = X[3];
#F[2] = X[1];
#F[3] = X[2];

from qiskit import QuantumCircuit
import matplotlib.pyplot as plt
circuit = QuantumCircuit(4)

circuit.cx((3),(1))
circuit.x(3)
circuit.cx((3),(2))
circuit.cx((0),(1))
circuit.ccx((3),(2),(1))
circuit.ccx((2),(0),(3))
circuit.ccx((3),(1),(0))
circuit.cx((1),(3))
circuit.cx((2),(1))
circuit.ccx((3),(0),(2))
circuit.cx((2),(3))
circuit.cx((1),(0))
circuit.draw(output="mpl")
plt.show()
#X[0] = F[0];
#X[1] = F[2];
#X[2] = F[3];
#X[3] = F[1];

# to : E16C C395 A9C3 659A 
# T-Depth : 4
# Depth : 34
