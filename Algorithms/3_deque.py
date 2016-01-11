from collections import deque

d = deque()
n = int(input())

try:
    for i in range(0,n):
        cmd = list(map(int, input().split(sep=" ")))
        if cmd[0] == 1:
            d.appendleft(cmd[1])
        elif cmd[0] == 2:
            if cmd[1] == -1 and len(d) == 0:
                continue
            x = d.popleft()
            if x != cmd[1]:
                raise IndexError
        elif cmd[0] == 3:
            d.append(cmd[1])
        elif cmd[0] == 4:
            if cmd[1] == -1 and len(d) == 0:
                continue
            x = d.pop()
            if x != cmd[1]:
                raise IndexError
    print("YES")
except IndexError:
    print("NO")
