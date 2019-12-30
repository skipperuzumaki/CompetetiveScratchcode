from Parser import Parse
from Linker import Link
import subprocess
#Add path to your preffered ide here enclosed in quotes
IDEPath = '"C:\Program Files\Sublime Text 3\sublime_text.exe"'
subprocess.Popen("%s %s" % (IDEPath, "Competetive.cpp"))

while True:
    command = input("Enter X to Exit \nEnter C to Produce final code file \nEnter Anything else to Compile and run program : ")
    if command.upper() == 'X':
        break
    elif command.upper() == 'C':
        Link()
        continue
    Parse()
