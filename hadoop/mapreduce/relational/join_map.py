import sys
from collections import defaultdict

urls = defaultdict(list)
queries = defaultdict(list)
users =  set()

for line in sys.stdin:
    key, val = line.strip().split('\t')
    mod, str = val.split(':')
    if (mod == 'url'): urls[key].append(str)
    else: queries[key].append(str)
    users.add(key)
    
for user in users:
    for url in urls[user]:
        for query in queries[user]:
            print(user,query,url,sep='\t')
    
    