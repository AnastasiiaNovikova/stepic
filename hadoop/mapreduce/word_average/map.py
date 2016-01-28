import sys
from collections import defaultdict

d = defaultdict(int)

for line in sys.stdin:
    for word in line.strip().split(" "):
        d[word] += 1
for k, v in d.items():
    print(k,"\t",v, sep="")    
        