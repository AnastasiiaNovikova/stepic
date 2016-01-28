import sys
import re

rWords = re.compile(u'\w+', re.UNICODE)

for line in sys.stdin:
    key, val = line.strip().split(':', maxsplit=1)
    for word in  re.findall(rWords, val):
        print('{0}#{1}'.format(word,key), 1, sep='\t')