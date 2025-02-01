for o in range(20):
    senha = []

    tumba = input()
    n = len(tumba)

    for tam in range(1, n):
        for i in range(n):
            if tumba[i%tam] != tumba[i]: break
        else: 
            print(tam)
            break