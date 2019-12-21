from Parser import Parse
import subprocess
#Add path to your preffered ide here enclosed in quotes
IDEPath = '"C:\Program Files\Sublime Text 3\sublime_text.exe"'
subprocess.Popen("%s %s" % (IDEPath, "Competetive.cpp"))

while True:
    command = input("Enter X to Exit \nEnter C to Produce final code file \nEnter Anything else to Compile and run program : ")
    if command == 'X':
        break
    elif command == 'C':
        #Produce final output file by copying additional dependencies to file
        pass
    Parse()
