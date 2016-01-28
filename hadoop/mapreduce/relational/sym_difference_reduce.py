import sys

last_key = None
last_mark = None
key_count = 0

for line in sys.stdin:
    key,mark = line.strip().split("\t")
    if last_key != key:
        if key_count == 1: print(last_key)
        key_count = 1
    else:
        key_count += 1
    last_key = key
    last_mark = mark
if key_count == 1: print(last_key)