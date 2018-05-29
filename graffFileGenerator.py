import os
from random import randint

ver=50              #ilość wierzchołków
finite=100000       #wartość oznaczająca nieskończoność<=>brak krawędzi
threshold=1        #gęstość(odwrotna)-próg szansy na wystąpienie danej krawędzi(w procentach 0 do 100)(im większy tym mniej krawędzi)
minW=1              #minimalna waga
maxW=30             #maksymalna waga
filePath="~/Qt/SDiZO2/data" #ścieżka/nazwa pliku do utworzenia

edges=0
tab=[[ 0 ]*ver for i in range(0,ver)]
for i in range(0,ver):
    for i2 in range(0,ver):
        chance=randint(0,100)
        if chance>threshold:
            tab[i][i2]=randint(minW-1,maxW)
            edges+=1
        else:
            tab[i][i2]=finite


line=edges.__str__()+" "+ver.__str__()+" 0 "+(ver-1).__str__()

os.system('rm {} -f;touch {};echo "{}" > {}'.format(filePath,filePath,line,filePath))

for i in range(0,ver):
    for i2 in range(0,ver):
        if tab[i][i2]==finite:
            continue;
        else:
            line=i.__str__()+" "+i2.__str__()+" "+tab[i][i2].__str__()
        os.system('echo "{}" >> {}'.format(line,filePath))
os.system('echo ciastko;echo -n "threshold=";echo  {};echo -n "edges=";echo {}'.format(threshold,edges))
