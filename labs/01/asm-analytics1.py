import sys
import re
import pprint as pp
from collections import Counter

patternFunction = re.compile("^[0-9a-fA-F]{16} <[a-zA-Z_.@]+>:$")
patternInstructions = re.compile("^ [a-fA-F0-9]+:[ \t]+[0-9a-fA-F ]+[ \t]+[a-zA-Z]+")
functionsFound = {}
functionsLooking = ["main"]

def getData(lines):
    currentFunc = ""    
    for line in lines:
        if patternFunction.match(line):
            function = line.strip().split(" ")
            address = function[0]
            funcName = function[1].replace("<", "").replace(">", "").replace(":", "")
            currentFunc = funcName
            functionsFound[funcName] = [address, funcName, {}]

        elif patternInstructions.match(line):
            instruction = line.split("\t")[2].strip().split(" ")[0]
            if currentFunc == "main" and instruction == "callq":
                functionsLooking.append(line.split("\t")[2].strip().split(" ")[3].replace("<", "").replace(">", ""))
            if instruction in functionsFound[currentFunc][2]:
                functionsFound[currentFunc][2][instruction] += 1
            else:
                functionsFound[currentFunc][2][instruction] = 1
   
    instructionsFound = Counter({})
    print("Hi, this is the output of the analysis:")
    print("  You have %d functions (Called with callq from main):" % (len(functionsLooking)))
    for key, value in functionsFound.items():
        if key in functionsLooking:
            print("    %s: Located at %s" % (value[1].ljust(25), value[0])) 
            instructionsFound += Counter(value[2])
    print("  You have %d kinds of instructions:" % (len(instructionsFound)))
    for key, value in instructionsFound.items():
        print("    %s : Executed %s times" % (key.ljust(10), str(value).ljust(3)))

if __name__ == "__main__":
    if len(sys.argv) == 2:
        with open(sys.argv[1]) as file:  
            lines = file.readlines()
            getData(lines)
    else:
        print("Provide filename")