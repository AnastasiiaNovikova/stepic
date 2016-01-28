import sys
from collections import defaultdict

for line in sys.stdin:
    words = line.strip().split(" ")
    for i in words:
        d = defaultdict(int)
        for j in words:
            if i!=j:
                d[j] += 1
        stripe = ','.join(['{0}:{1}'.format(k,v) for (k,v) in d.items()])
        print (i,stripe,sep='\t')