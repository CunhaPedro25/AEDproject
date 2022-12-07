import os 
from sys import path

root = "."
filesPy = []
fileType = '.c'
filesDirs = ''
seperator = ' '

for path, subdirs, files in os.walk(root):
    for name in files:
        relativeFilePath = os.path.join(path, name)
        if relativeFilePath[-2:] == '.c': 
            filesPy.append(os.path.join(path, name))

filesPy.remove("./main.c")

for file in filesPy:
    filesDirs = seperator.join(filesPy)

command = f"gcc main.c {filesDirs} -o app"
print(command)
os.system(command)
