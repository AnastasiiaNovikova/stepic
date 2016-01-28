import sys

for line in sys.stdin:
    timestamp,user_id,url = line.strip().split("\t")
    if user_id == 'user10':
        print(line.strip())