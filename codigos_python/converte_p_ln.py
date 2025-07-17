import math

try:
    while True:
        n = float(input()) + 1
        n = math.log2(n)
        print(f"{n:.3f}")
except EOFError:
    pass
