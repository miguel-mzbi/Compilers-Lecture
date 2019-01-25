import sys
import re

patternFunction = re.compile("^[0-9a-fA-F]{16} <[a-zA-Z_]+>:$")
patternInstructions = re.compile("^ [a-fA-F0-9]+:[ \t]+[0-9a-fA-F ]+[ \t]+[a-zA-Z]+")
functionsFound = []
instructionsFound = {}

def getData(lines):
    for line in lines:
        if patternFunction.match(line):
            function = line.strip().split(" ")
            address = function[0]
            funcName = function[1].replace("<", "").replace(">", "").replace(":", "")
            functionsFound.append([funcName, address])
        elif patternInstructions.match(line):
            instruction = line.split("\t")[2].strip().split(" ")[0]
            if instruction in instructionsFound:
                instructionsFound[instruction] += 1
            else:
                instructionsFound[instruction] = 1

    print("Hi, this is the output of the analysis:")
    print("  You have %d functions:" % (len(functionsFound)))
    for entry in functionsFound:
        print("    %s: Located at %s" % (entry[0].ljust(25), entry[1]))
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