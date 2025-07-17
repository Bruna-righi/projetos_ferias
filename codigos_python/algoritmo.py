def compute_lps(S):
    n = len(S)
    lps = [0] * n
    length = 0  # Comprimento do prefixo que também é sufixo
    i = 1
    
    while i < n:
        if S[i] == S[length]:
            length += 1
            lps[i] = length
            i += 1
        else:
            if length != 0:
                length = lps[length - 1]
            else:
                lps[i] = 0
                i += 1
    
    return lps

def find_smallest_repeating_substring(S):
    n = len(S)
    lps = compute_lps(S)
    
    # O tamanho do padrão repetitivo é dado por n - lps[n-1]
    pattern_length = n - lps[-1]
    
    # Verifica se S é formado por repetições desse padrão
    if n % pattern_length == 0:
        return S[:pattern_length]
    
    return S  # Caso não seja possível dividir, a string inteira é a menor unidade

# Exemplo de uso:
while True:
    try:
        S = input()
        print(find_smallest_repeating_substring(S))  # Saída esperada: "ab"
    except:
        break