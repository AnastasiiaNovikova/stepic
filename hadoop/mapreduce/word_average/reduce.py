import sys

last_key = None
last_val = 0
last_count = 0

for line in sys.stdin:
    (key, val) = line.strip().split("\t")
    if last_key and last_key != key:
        print(last_key,int(last_val/last_count), sep="\t")
        last_key = key
        last_count = 1
        last_val = int(val)
    else:
        last_key = key
        last_count += 1
        last_val += int(val)
if last_key:
    print(last_key,int(last_val/last_count), sep="\t")