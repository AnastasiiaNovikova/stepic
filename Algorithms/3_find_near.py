def bin_search(a, elem):
    begin = 0
    end = len(a)
    mid = 0
    while begin < end:
        mid = (begin+end)//2
        if a[mid] == elem:
            break
        elif elem < a[mid]:
            end = mid
        else:
            begin = mid+1
    return mid

a_n = int(input())
a = list(map(int, input().split(" ")))
b_n = int(input())
b = list(map(int, input().split(" ")))

result = 0
for i in range(0, len(b)):
    index = bin_search(a, b[i])

    if b[i] == a[index]:
        result = index
    #elif index == len(a):
    #    result = index - 1
    elif index == 0:
        if abs(a[index + 1] - b[i]) < abs(a[index] - b[i]):
            result = index + 1
        else:
            result = index
    elif index > 0:
        if abs(a[index - 1] - b[i]) < abs(a[index] - b[i]):
            result = index - 1
        else:
            result = index

    print(result, end=" ")



