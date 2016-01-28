import sys

last_key = None
key_count = 0

def print_key_count(key, count):
    k,v = key.split('#', maxsplit=1)
    print(k,v,count,sep='\t')

for line in sys.stdin:
    key,val = line.strip().split("\t")
    if last_key and last_key != key:
        print_key_count(last_key, key_count)
        key_count = 1
    else:
        key_count += 1
    last_key = key
if last_key:
    print_key_count(last_key, key_count)