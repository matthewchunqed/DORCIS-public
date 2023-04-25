# from : 00FF 0F0F 3333 5555 
#F[0] = X[0];
#F[1] = X[3];
#F[2] = X[2];
#F[3] = X[1];

from qiskit import QuantumCircuit
import matplotlib.pyplot as plt
circuit = QuantumCircuit(4)

circuit.ccx((3),(2),(1))
circuit.cx((1),(2))
circuit.cx((0),(3))
circuit.x(2)
circuit.x(3)
circuit.ccx((3),(0),(2))
circuit.ccx((2),(1),(3))
circuit.ccx((3),(2),(0))
print(circuit.depth()) #note that this is the non-decomposed depth
circuit.draw(output="mpl")
plt.show()
#X[0] = F[1];
#X[1] = F[2];
#X[2] = F[3];
#X[3] = F[0];

# to : 5656 9A95 E21B 82EE 
# T-Depth : 4
# Depth : 30
