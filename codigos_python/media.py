try:
    while True:
        input();

        testes = []
        for i in range(4):
            testes.append(float(input()))

        media = 0
        for n in range(4):
            media += testes[n]

        media /= 4
        print(f"{media:.3f}")

except EOFError:
    pass