n = int(input())
a = list(map(int, input().split(" ")))
b = list(map(int, input().split(" ")))

max_sum_index_a = len(b)-1
max_sum_index_b = len(b)-1
max_b_index = len(b)-1
max_sum = a[max_sum_index_a]+b[max_sum_index_b]

for i in reversed(range(0, len(b)-1)):
    if b[i] >= b[max_b_index]:
        max_b_index = i
    if a[i]+b[max_b_index] >= max_sum:
        max_sum_index_a = i
        max_sum_index_b = max_b_index
        max_sum = a[i]+b[max_b_index]

print(max_sum_index_a, max_sum_index_b)
