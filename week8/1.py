with open("../week9/input.txt", 'r') as file:
    input = file.readlines()
lines = list(map(str.strip, input))
dic = {}
output = open("../week9/output.txt", 'a')
for i in lines:
    key = ''
    if len(i) >= 2:
        key = i[2:]
    if i[0] == 'A':
        dic[key] = key
    elif i[0] == 'D':
        dic[key] = None
    elif i[0] == '?':
        try:
            if dic[key] is not None:
                output.write('Y\n')
            else:
                output.write('N\n')
        except KeyError:
            output.write('N\n')