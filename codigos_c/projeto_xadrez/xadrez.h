#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>

#define tam_tab 8
#define branco 0
#define preto 1
#define vazio 10
#define peao 1
#define torre 2
#define cavalo 3
#define bispo 4
#define rainha 5
#define rei 6

typedef struct casa casa;
typedef struct jogadas_possiveis lista;
typedef struct casa casa;
typedef struct jogo jogo;

lista* lista_cria();
void lista_insere(lista* l, casa* ini, casa* fim);
void lista_libera(lista* l);
void tabuleiro_ini(jogo* j);
void imprime_tabuleiro(jogo* j);
void libera_tabuleiro(jogo* j);
bool movimento_peao(casa* c, int lin, int col, jogo* t);
bool movimento_torre(casa* c, int lin, int col, jogo* t);
bool moviento_bispo(casa* c, int lin, int col, jogo* t);
bool movimento_cavalo(casa* c, int lin, int col, jogo* t);
bool movimento_rei(casa* c, int lin, int col, jogo* t);
lista* computa_jogadas(jogo* t);
void jogo_inicializa(jogo* j);
lista* lista_busca_ini(lista* l, casa* b);
lista* lista_busca_fim(lista* l, casa* b);
bool detecta_xeque(jogo* t, lista* l);
