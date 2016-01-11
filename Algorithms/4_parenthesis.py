def print_error():
    print("IMPOSSIBLE")
    exit()


d = list()

input_str = str(input())
result_str = input_str

for i in range(0, len(input_str)):
    ch = input_str[i]
    if ch in ['(', '{', '[']:
        d.append(ch)
        continue
    elif ch == ')':
        if len(d) == 0:
            result_str = '(' + result_str
        else:
            pch = d.pop()
            if pch != '(':
                print_error()
    elif ch == ']':
        if len(d) == 0:
            result_str = '[' + result_str
        else:
            pch = d.pop()
            if pch != '[':
                print_error()
    elif ch == '}':
        if len(d) == 0:
            result_str = '{' + result_str
        else:
            pch = d.pop()
            if pch != '{':
                print_error()

while len(d) != 0:
    pch = d.pop()
    if pch == '(':
        result_str = result_str + ')'
    if pch == '[':
        result_str = result_str + ']'
    if pch == '{':
        result_str = result_str + '}'

print(result_str)