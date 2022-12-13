import os 
from sys import path
from sys import platform

root = "."
filesPy = []
fileType = '.c'
filesDirs = ''
seperator = ' '

if platform == "linux" or platform == "linux2":
    execute = "./app"
    main = "./main.c"
elif platform == "win32":
    execute = ".\\app"
    main = ".\\main.c"


for path, subdirs, files in os.walk(root):
    for name in files:
        relativeFilePath = os.path.join(path, name)
        if relativeFilePath[-2:] == '.c' and (path.find("cmake") == -1):
            filesPy.append(os.path.join(path, name))

filesPy.remove(main)

for file in filesPy:
    filesDirs = seperator.join(filesPy)

command = f"gcc main.c {filesDirs} -o app && {execute}"
print(command)
os.system(command)
