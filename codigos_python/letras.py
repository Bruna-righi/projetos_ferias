n = int(input())

vogais = set(['a', 'e', 'i', 'o', 'u', 'A', 'E', 'I', 'O', 'U'])
flag = False

for i in range(n):
    hocuspocus = map(str, input().split())
    for i in hocuspocus:
        flag = False
        if len(i) <= 5:
            if i[-1] in vogais and i[0] not in vogais:
                flag = True
                continue
        elif i[0] in vogais and i[-1] in vogais:
            flag = True
            continue
        if len(i) == 1:
            flag = True
            continue
        if flag == False:
            print("NAO")
            break
    else:
        print("SIM")
