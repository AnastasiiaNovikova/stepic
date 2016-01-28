import sys

last_key = None

for line in sys.stdin:
    (key, value) = line.strip().split("\t")
    if key != last_key:
        print(key)
    last_key = key
    