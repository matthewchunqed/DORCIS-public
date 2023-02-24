import re

target_file = "impqiskit_1302574689abcdef_0.py"

#Note: This tool, for Qiskit graphical purposes, provides a no ancilla decomposition.
#The paper uses a decomposition with ancillary lines to find minimum T-depth bounds.

#Open file
with open(target_file, "r") as f:

    # Read file into a string
    text = f.read()
    #Count how many ancilla lines needed
    ancillas = 4*text.count("ccx")
    text = text.replace("(4)", "("+str(4+ancillas)+")")
    i = 0
    index = 0
    while i < ancillas/4:
        #circuit.ccx((3),(0),(2))
        firstLine = text[text.find("ccx", index) + 5]
        secondLine = text[text.find("ccx", index) + 9]
        thirdLine = text[text.find("ccx", index) + 13]
        #print(firstLine)
        #print(secondLine)
        #print(thirdLine)
        text = text.replace("circuit.ccx(("+str(firstLine)+"),("+str(secondLine)+"),("+str(thirdLine)+"))",
        "circuit.h("+str(thirdLine)+")\ncircuit.cx("+str(firstLine)+","+str(4+(i*4))+")\ncircuit.cx("+str(secondLine)+","+str(5+(i*4))+")\ncircuit.cx("+str(thirdLine)+","+str(6+(i*4))+")\ncircuit.cx("+str(4+(i*4))+","+str(7+(i*4))+")\ncircuit.cx("+str(firstLine)+","+str(5+(i*4))+")\ncircuit.cx("+str(thirdLine)+","+str(7+(i*4))+")\ncircuit.cx("+str(6+(i*4))+","+str(4+(i*4))+")\ncircuit.t("+str(firstLine)+")\ncircuit.t("+str(secondLine)+")\ncircuit.t("+str(thirdLine)+")\ncircuit.t("+str(4+(i*4))+")\ncircuit.tdg("+str(5+(i*4))+")\ncircuit.tdg("+str(6+(i*4))+")\ncircuit.tdg("+str(7+(i*4))+")\ncircuit.cx("+str(6+(i*4))+","+str(4+(i*4))+")\ncircuit.cx("+str(thirdLine)+","+str(7+(i*4))+")\ncircuit.cx("+str(firstLine)+","+str(5+(i*4))+")\ncircuit.cx("+str(4+(i*4))+","+str(7+(i*4))+")\ncircuit.cx("+str(thirdLine)+","+str(6+(i*4))+")\ncircuit.cx("+str(secondLine)+","+str(5+(i*4))+")\ncircuit.cx("+str(firstLine)+","+str(4+(i*4))+")\ncircuit.cx("+str(secondLine)+","+str(6+(i*4))+")\ncircuit.h("+str(thirdLine)+")", 1)
        text = text.replace("#note that this is the non-decomposed depth","",1)
        #print()
        i += 1
#Replace all .ccx()

#Write
with open("decomposed_" + target_file, "w") as f:
    f.write(text)