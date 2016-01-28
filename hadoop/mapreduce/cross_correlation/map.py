import sys

for line in sys.stdin:
    words = line.strip().split(" ")
    for i in words:
        for j in words:
            if i!=j:
                print(i,",",j,"\t",1, sep="")