import random
import string

def gerar_string_repetida(sequencia, repeticoes):
    return sequencia * repeticoes

def gerar_sequencia_aleatoria(tamanho):
    caracteres = string.ascii_letters
    return ''.join(random.choice(caracteres) for _ in range(tamanho))


s = int(input())
tamanho = [100, 500, 1000, 1500, 2000, 2500, 3000, 3500, 4000, 4500, 5000, 5500, 6000, 6500, 7000, 7500]
repeticoes = [10, 5, 4, 2]
t = tamanho[s]

for n in range(5):
    for i in repeticoes:
        sequencia = gerar_sequencia_aleatoria(t//i)
        resultado = gerar_string_repetida(sequencia, i)
        print(resultado)  # Saída: abcabcabc