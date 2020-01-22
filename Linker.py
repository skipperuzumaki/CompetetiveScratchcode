import subprocess
import os

def Link():
    code = open("./Competetive.cpp","r")

    includes = list()
    i = False
    additional = list()
    a = False
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
            elif '//Additional' in line:
                a = True
            elif '//Namespaces' in line:
                n = True
            elif '//Globals' in line:
                g = True
            elif '//Code' in line:
                c = True
            elif '//End' in line:
                i = False
                a = False
                n = False
                g = False
                c = False
            elif '//ENDFILE' in line:
                break;
            if i:
                includes.append(line)
            elif a:
                additional.append(line)
            elif n:
                namespaces.append(line)
            elif g:
                Globals.append(line)
            elif c:
                if '//time' in line:
                    pass #codes.append(line.replace('//time','Timings.push_back(high_resolution_clock::now()); //timing'))
                else:
                    codes.append(line)
    except:
        pass
    try:
        code.close()
        codes.pop(0)
        includes.pop(0)
        additional.pop(0)
        namespaces.pop(0)
        Globals.pop(0)
    except:
        print("essential comments incorrect")

    includes = "".join(includes)
    namespaces = "".join(namespaces)
    Globals = "".join(Globals)
    codes = "".join(codes)

    f = open("Final.txt", "r")
    lines = f.readlines()
    f.close()

    addn = ''
    for i in additional:
        k = i.split('"')
        i = k[1]
        cd = open(i,'r')
        i = cd.read()
        cd.close()
        addn += i

    for line in range(len(lines)):
        if '//Includes' in lines[line]:
            i = line + 1
        elif '//Additional' in lines[line]:
            a = line + 2
        elif '//Namespaces' in lines[line]:
            n = line + 3
        elif '//Globals' in lines[line]:
            g = line + 4
        elif '//Code' in lines[line]:
            c = line + 5
    
    lines.insert(i,includes)
    lines.insert(a,addn)
    lines.insert(n,namespaces)
    lines.insert(g,Globals)
    lines.insert(c,codes)

    f = open("FinalProg.cpp", "w")
    lines = "".join(lines)
    f.write(lines)
    f.close()

    Path = '"' + os.path.abspath(__file__) + '"'
    wPath = '"' + os.path.abspath(__file__) + '\Program.cpp"'

    os.system("cd "+Path)
    os.system("g++ Finalprog.cpp 2> Output.log")
    try:
        os.remove('a.exe')
        IDEPath = '"C:\Program Files\Sublime Text 3\sublime_text.exe"'
        subprocess.Popen("%s %s" % (IDEPath, "Finalprog.cpp"))
    except:
        os.system("output.log")
