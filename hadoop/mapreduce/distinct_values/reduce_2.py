import sys
from collections import defaultdict

d = defaultdict(int)
last = (None, None)

for line in sys.stdin:
    (val, key) = line.strip().split("\t")
    if (val, key) != last:
        d[key] += 1
    last = (val, key)
    
for key, val in d.items():
    print(key, val, sep = "\t")