try:
    while True:
        tumba = input()

        tam = 1
        n = len(tumba)

        for i in range(n):
            while tumba[i%tam] != tumba[i] and tam < n:
                tam += 1



# senha = []

# tumba = input()

# tam = 1

# senha.append(tumba[0])

# for i in range(len(tumba)):
#     if senha[i%tam] != tumba[i]:
#         for j in range(len(senha), i+1):
#             senha.append(tumba[j])
#             tam = tam + 1
#             if senha[i%tam] == tumba[i]: break

        # if len(senha) > len(tumba)/2:
        #     print(-1)
        #     exit(0)

        # maior_div = 0

        # for i in range(1, len(tumba)//2 + 1):
        #     if i%len(senha) == 0 and len(tumba)%i == 0:
        #         maior_div = i

        # if maior_div == 0:
        #     print(-1)
        #     exit(0)

        # maior_div = maior_div // len(senha)

        # print(''.join(senha)*maior_div)

except EOFError:
    pass