import sys

for line in sys.stdin:
    (key, values_str) = line.strip().split("\t")
    values = values_str.split(",")
    for value in values:
        print(key, ",", value, "\t", 1, sep="")
    