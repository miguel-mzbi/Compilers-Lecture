import sys 

def convertBNF(lines):
    with open("cleanBNF.out", "w") as fileOut: 
        for line in lines:
            line = line.split(" ")
            for i, word in enumerate(line):
                if word == "→":
                    line[i] = "::="
                elif word == "|":
                    line[i] = "\n\t|"
                elif word == "\n":
                    continue
                elif word.isalpha() and word.islower():
                    line[i] = '"' + word + '"'
                else:
                    line[i] = "<" + word + ">"
            line = " ".join(line)
            fileOut.write(line)
            
if __name__ == "__main__":
    if len(sys.argv) == 2:
        with open(sys.argv[1]) as file:  
            lines = file.readlines()
            convertBNF(lines)
    else:
        print("Provide filename")