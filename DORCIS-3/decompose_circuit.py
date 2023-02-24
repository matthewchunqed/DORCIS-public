import re

target_file = "impqiskit_01367452_0.py"

#Note: This tool provides a full decomposition as per the specifications given in the paper. 

#Open file
with open(target_file, "r") as f:

    # Read file into a string
    text = f.read()
    #Count how many ancilla lines needed
    if(text.count("ccx") > 0):
        ancillas = 4
    else:
        ancillas = 0
    text = text.replace("(3)", "("+str(3+ancillas)+")")
    i = 0
    index = 0
    replacementCount = text.count("ccx")
    while i <= replacementCount:
        #circuit.ccx((3),(0),(2))
        firstLine = text[text.find("ccx", index) + 5]
        secondLine = text[text.find("ccx", index) + 9]
        thirdLine = text[text.find("ccx", index) + 13]
        #print(firstLine)
        #print(secondLine)
        #print(thirdLine)
        text = text.replace("circuit.ccx(("+str(firstLine)+"),("+str(secondLine)+"),("+str(thirdLine)+"))",
        "circuit.initialize(0,3)\ncircuit.initialize(0,4)\ncircuit.initialize(0,5)\ncircuit.initialize(0,6)\ncircuit.h("+str(thirdLine)+")\ncircuit.cx("+str(firstLine)+","+str(3)+")\ncircuit.cx("+str(secondLine)+","+str(4)+")\ncircuit.cx("+str(thirdLine)+","+str(5)+")\ncircuit.cx("+str(3)+","+str(6)+")\ncircuit.cx("+str(firstLine)+","+str(4)+")\ncircuit.cx("+str(thirdLine)+","+str(6)+")\ncircuit.cx("+str(5)+","+str(3)+")\ncircuit.t("+str(firstLine)+")\ncircuit.t("+str(secondLine)+")\ncircuit.t("+str(thirdLine)+")\ncircuit.t("+str(3)+")\ncircuit.tdg("+str(4)+")\ncircuit.tdg("+str(5)+")\ncircuit.tdg("+str(6)+")\ncircuit.cx("+str(5)+","+str(3)+")\ncircuit.cx("+str(thirdLine)+","+str(6)+")\ncircuit.cx("+str(firstLine)+","+str(4)+")\ncircuit.cx("+str(3)+","+str(6)+")\ncircuit.cx("+str(thirdLine)+","+str(5)+")\ncircuit.cx("+str(secondLine)+","+str(4)+")\ncircuit.cx("+str(firstLine)+","+str(3)+")\ncircuit.cx("+str(secondLine)+","+str(5)+")\ncircuit.h("+str(thirdLine)+")", 1)
        text = text.replace("#note that this is the non-decomposed depth","",1)
        i += 1
        #print()
#Replace all .ccx()

#Write
with open("decomposed_" + target_file, "w") as f:
    f.write(text)