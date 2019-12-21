from Parser import Parse
import subprocess

SublimePath = '"C:\Program Files\Sublime Text 3\sublime_text.exe"'
subprocess.Popen("%s %s" % (SublimePath, "Competetive.cpp"))

while True:
    command = input("Enter X to Exit Enter Anything else to Compile and run program : ")
    if command == 'X':
        break
    Parse()
