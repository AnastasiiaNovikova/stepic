n = int(input())
a = list(map(int, input().split(" ")))
b = list(map(int, input().split(" ")))
b_orig = b[:]

max_a = a[0]
for i in range(1, len(b)):
    if max_a > a[i]:
        a[i] = max_a
    elif a[i] > max_a:
        max_a = a[i]

max_b = b[len(b)-1]
for i in reversed(range(0, len(b)-1)):
    if max_b > b[i]:
        b[i] = max_b
    elif b[i] > max_b:
        max_b = b[i]

max_index_a = 0
max_sum = a[0]+b[0]
for i in range(0, len(b)):
    if a[i] + b[i] > max_sum:
        max_sum = a[i] + b[i]
        max_index_a = i

max_index_b = max_index_a
while b_orig[max_index_b] != b[max_index_a]:
    max_index_b += 1

print(max_index_a, max_index_b)
