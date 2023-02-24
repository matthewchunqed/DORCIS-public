# from : 00FF 0F0F 3333 5555 
#F[0] = X[0];
#F[1] = X[1];
#F[2] = X[3];
#F[3] = X[2];

from qiskit import QuantumCircuit
import matplotlib.pyplot as plt
circuit = QuantumCircuit(4)

circuit.ccx((2),(1),(3))
circuit.cx((0),(1))
circuit.cx((0),(2))
circuit.x(3)
circuit.ccx((3),(0),(2))
circuit.ccx((3),(2),(1))
circuit.ccx((2),(1),(0))
circuit.x(0)
circuit.cx((1),(3))
circuit.cx((3),(0))
circuit.draw(output="mpl")
plt.show()
#X[0] = F[2];
#X[1] = F[0];
#X[2] = F[1];
#X[3] = F[3];

# to : 5563 3C59 4EB1 8778 
# T-Depth : 4
# Depth : 32
