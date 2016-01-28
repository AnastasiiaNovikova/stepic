import sys

last_key = None
key_count = 0

for line in sys.stdin:
    key,val = line.strip().split("\t")
    if last_key != key:
        if key_count > 0: print(last_key)
        key_count = 0
    else:
        key_count += 1
    last_key = key
if key_count > 0: print(last_key)