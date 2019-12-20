import subprocess as sp
import os

code = open("./Competetive.cpp","r")

includes = list()
i = False
namespaces = list()
n = False
Globals = list()
g = False
codes = list()
c = False

try:
    while True:
        line = code.readline()
        if '//Includes' in line:
            i = True
        elif '//Namespaces' in line:
            n = True
        elif '//Globals' in line:
            g = True
        elif 'void Code()' in line:
            c = True
        elif '//End' in line:
            i = False
            n = False
            g = False
            c = False
        elif '//ENDFILE' in line:
            break;
        if i:
            includes.append(line)
        elif n:
            namespaces.append(line)
        elif g:
            Globals.append(line)
        elif c:
            if '//time' in line:
                codes.append(line.replace('//time','Timings.push_back(high_resolution_clock::now()); //timing'))
            else:
                codes.append(line)
except:
    pass
try:
    code.close()
    codes.pop(0)
    includes.pop(0)
    namespaces.pop(0)
    Globals.pop(0)
except:
    print("essential comments incorrect")

includes = "".join(includes)
namespaces = "".join(namespaces)
Globals = "".join(Globals)
codes = "".join(codes)

f = open("Time.cpp", "r")
lines = f.readlines()
f.close()

for line in range(len(lines)):
    if '//Includes' in lines[line]:
        i = line + 1
    elif '//Namespaces' in lines[line]:
        n = line + 2
    elif '//Globals' in lines[line]:
        g = line + 3
    elif '//Code' in lines[line]:
        c = line + 4

lines.insert(i,includes)
lines.insert(n,namespaces)
lines.insert(g,Globals)
lines.insert(c,codes)

f = open("Program.cpp", "w")
lines = "".join(lines)
f.write(lines)
f.close()
            
