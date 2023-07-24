from glob import glob
import re
import pdb

for filename in glob('src/**/*.cpp', recursive=True):
    print(filename)
    file1 = open("./" + filename ,"r")
    txt = file1.read()
    file1.close()
    #pdb.set_trace()
    result = re.finditer(r"mMnator", txt)
    for match in result:
        print(match)
        #pdb.set_trace()
        point = match.span()[0]+1
        txt = txt[:point] + 'i' + txt[point+1:]
    #pdb.set_trace()
    file2 = open("./" + filename, "w")
    file2.write(txt)
    file2.close()
        #print(match)
    # txt = txt[txt.find(" min"):]
    # txt = txt[txt.find('@'):]
    # txt = txt.replace('@','')
    # txt = txt.replace('1280