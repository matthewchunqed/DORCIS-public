# from : 00FF 0F0F 3333 5555 
#F[0] = X[3];
#F[1] = X[0];
#F[2] = X[2];
#F[3] = X[1];

from qiskit import QuantumCircuit
import matplotlib.pyplot as plt
circuit = QuantumCircuit(4)

circuit.cx((3),(0))
circuit.x(3)
circuit.x(2)
circuit.ccx((3),(1),(0))
circuit.ccx((3),(2),(1))
circuit.ccx((2),(0),(3))
circuit.ccx((1),(0),(2))
circuit.x(0)
circuit.cx((0),(2))
circuit.draw(output="mpl")
plt.show()
#X[0] = F[0];
#X[1] = F[1];
#X[2] = F[3];
#X[3] = F[2];

# to : A555 C03F B878 29B3 
# T-Depth : 4
# Depth : 32
