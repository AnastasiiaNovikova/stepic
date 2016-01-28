import sys

last_key = None
terms = []

def print_terms(terms):
    for id, tf in terms:
        print(id,tf,len(terms), sep='\t')

for line in sys.stdin:
    key,val = line.strip().split("\t")
    n,tf,cnt = val.strip().split(';')
    if last_key and last_key != key:
        print_terms(terms)
        terms.clear()
    terms.append(('{0}#{1}'.format(key,n),tf))
    last_key = key
    
if last_key:
    print_terms(terms)