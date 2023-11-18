import re

#This tool decomposes .c implementation files into Qiskit circuits.

target_file = "implementation_B5F0729D481CEA36_0.c"
#Saves name of target file with and without extensions.
target_file_name = target_file.replace("implementation_", "impqiskit_")
if(target_file[-2:] == ".c"):
    target_file_name = target_file_name[:-2]

#Open file
with open(target_file, "r") as f:

    # Read file into a string
    text = f.read()
 
    #Comment out the measurement info lines.
    text = text.replace("F[0] = X", "\nfrom qiskit import QuantumCircuit\nimport matplotlib.pyplot as plt\ncircuit = QuantumCircuit(3)\n\n#F[0] = X")
    text = text.replace("F[1] = X", "#F[1] = X")
    text = text.replace("F[2] = X", "#F[2] = X")
    text = text.replace("X[0] = F", "\nprint(circuit.depth())\n#note that this is the non-decomposed depth\ncircuit.draw(output=\"mpl\")\nplt.show()\n\n#X[0] = F")
    text = text.replace("X[1] = F", "#X[1] = F")
    text = text.replace("X[2] = F", "#X[2] = F")

    #Convert .c comments to .py comments
    text = text.replace("//", "#")

    #Remove the "F[i] = " in the gate lines.
    text = re.compile(r'.{7}(CNOT1)').sub(r'\1', text)
    text = re.compile(r'.{7}(CCNOT2)').sub(r'\1', text)
    text = re.compile(r'.{7}(RNOT1)').sub(r'\1', text)

    #Replace the .c gates with qiskit gates
    text = re.compile(r'RNOT1\(F\[(\d+)\]\)').sub(r'circuit.x(\1)', text)
    text = re.compile(r'CNOT1\(F\[(\d+)\], F\[(\d+)\]\)').sub(r'circuit.cx(\1, \2)', text)
    text = re.compile(r'CCNOT2\(F\[(\d+)\], F\[(\d+)\], F\[(\d+)\]\)').sub(r'circuit.ccx(\1, \2, \3)', text)

    #Remove semicolons
    text = text.replace(";", "")

#Write to a file
with open(target_file_name + ".py", "w") as f:
    f.write(text)