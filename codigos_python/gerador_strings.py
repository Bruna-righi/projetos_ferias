import random
import string

def gerar_string_repetida(sequencia, repeticoes):
    return sequencia * repeticoes

def gerar_sequencia_aleatoria(tamanho):
    caracteres = string.ascii_letters
    return ''.join(random.choice(caracteres) for _ in range(tamanho))


s = int(input())
tamanho = [20000, 22000, 24000]
repeticoes = [10, 5, 4, 2]
t = tamanho[s]

for n in range(5):
    for i in repeticoes:
        sequencia = gerar_sequencia_aleatoria(t//i)
        resultado = gerar_string_repetida(sequencia, i)
        print(resultado)  # Saída: abcabcabc