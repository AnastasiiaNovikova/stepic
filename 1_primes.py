# put your python code here
import sys
import math


def is_prime(k):
    for i in range(2, int(math.sqrt(k))):
        if k % i == 0:
            return False
    return True


def next_prime(k):
    k += 1
    while not is_prime(k):
        k += 1
    return k

n = int(input())
cur_n = n
cur_d = 2

while cur_n != 1:
    if cur_n % cur_d == 0:
        print(cur_d, end=" ")
        cur_n /= cur_d
        continue
    cur_d = next_prime(cur_d)
