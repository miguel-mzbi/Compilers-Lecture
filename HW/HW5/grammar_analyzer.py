import sys

def saveProductions(productions):
    out = ""
    if "S" in productions:
        # S production
        right = productions["S"]
        out = "S →"
        for sub in right:
            for char in sub:
                out += " " + char
            out += " |"
        out = out[:-1] + "\n"

        # Other productions
        for key in productions:
            if key == "S":
                continue
            right = productions[key]
            out += key +" →"
            for sub in right:
                for char in sub:
                    out += " " + char
                out += " |"
            out = out[:-1] + "\n"
        print(out)

def reduceCGF(lines):
    terminals = []
    allSymbols = []

    # Build productions map
    productions = {}
    for line in lines:
        line = line.split()
        currentLeft = ""
        for i, char in enumerate(line):
            if char == "→":
                continue

            if char not in allSymbols and char != "|":
                allSymbols.append(char)
            
            if i == 0:
                currentLeft = char
                if currentLeft in productions:
                   continue
                else:
                    productions[currentLeft] = [[]]
            else:
                left = productions[currentLeft]
                if char == "|":
                    left.append([])
                else:
                    if char.islower() and char not in terminals:
                        terminals.append(char)
                    left[len(left)-1].append(char)
    
    # Delete unreachable productions
    reachable = ["S"]
    stack = ["S"]
    while(len(stack) > 0):
        currentLeft = stack.pop()
        if currentLeft not in productions:
            continue
        right = productions[currentLeft]
        for sect in right:
            for char in sect:
                if char.islower():
                    continue
                else:
                    if char not in reachable and char in productions:
                        reachable.append(char)
                        stack.append(char)

    productions = {key: productions[key] for key in reachable}

    # Delete non-generation productions
    nonGenerating = [x for x in allSymbols if x not in terminals]
    generating = [x for x in terminals]
    generatingFound = True
    while generatingFound:
        generatingFound = False
        for key in productions:
            right = productions[key]
            for sub in right:
                isGenerating = True
                for char in sub:
                    if char not in generating:
                        isGenerating = False
                if isGenerating and key not in generating:
                    generating.append(key)
                    generatingFound = True

    # Delete non-existent productions remaining
    newProductions = {}
    for key in generating:
        if key not in terminals:
            newProductions[key] = []
            for i, sub in enumerate(productions[key]):
                isValid = True
                for char in sub:
                    if char not in generating:
                        isValid = False
                if isValid:
                    newProductions[key].append(sub)
    
    saveProductions(newProductions)

if __name__ == "__main__":
    if len(sys.argv) == 2:
        with open(sys.argv[1]) as file:  
            lines = file.readlines()
            print("This program requires that each character be separated by a space and assumes correct input with S as start symbol. e.g:\nS → A | B\nA → a\nB → B b\nC → c\n")
            reduceCGF(lines)
    else:
        print("Provide filename")