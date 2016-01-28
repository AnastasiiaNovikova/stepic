import sys

for line in sys.stdin:
    (key, value) = line.strip().split(",")
    print(value,1,sep="\t")
    