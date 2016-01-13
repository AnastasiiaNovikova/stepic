def bin_search(a, elem):
    begin = 0
    end = len(a)
    mid = 0
    while begin < end:
        mid = (begin+end)//2
        if elem <= a[mid]:
            end = mid
        else:
            begin = mid+1

    return begin


def find_nearest(a, elem):
    index = bin_search(a, elem)

    if index == 0:
        result = index
    elif index < len(a) and (a[index] == elem or abs(a[index - 1] - elem) > abs(a[index] - elem)):
        result = index
    else:
        result = index - 1

    return result


def main():
    a_n = int(input())
    a = list(map(int, input().split(" ")))
    b_n = int(input())
    b = list(map(int, input().split(" ")))

    for i in range(0, len(b)):
        result = find_nearest(a, b[i])
        print(result, end=" ")


if __name__ == "__main__":
    main()



