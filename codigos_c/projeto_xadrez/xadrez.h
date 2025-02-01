#ifndef XADREZ_H
#define XADREZ_H

#include <stdbool.h>

#define ESC "\033["
#define RESET "\033[0m"
#define JUNTA ";"
#define FIM_ESC "m"
#define BACKGROUND_PRETO "48;2;30;30;30"
#define BACKGROUND_BRANCO "48;2;255;255;255"
#define COR_PRETA "38;2;0;0;0"
#define COR_BRANCA "38;2;255;255;255"
#define COR_VERMELHA "38;2;255;0;0"

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

#define peao_b "\U00002659"
#define torre_b "\U00002656"
#define cavalo_b "\U00002658"
#define bispo_b "\U00002657"
#define rainha_b "\U00002655"
#define rei_b "\U00002654"
#define peao_p "\U0000265F"
#define torre_p "\U0000265C"
#define cavalo_p "\U0000265E"
#define bispo_p "\U0000265D"
#define rainha_p "\U0000265B"
#define rei_p "\U0000265A"

typedef struct casa casa;
typedef struct jogadas_possiveis lista;
typedef struct casa casa;
typedef struct jogo jogo;

typedef struct turno{
    int c;
    bool xeque;
}turno;

typedef struct ultima_jogada{
    casa* ini;
    casa* fim;
} ultima_jogada;

struct jogadas_possiveis{
    int jogEspecial;
    casa* ini;
    casa* fim;
    struct jogadas_possiveis* prox;
};

struct casa{
    int peca;
    int cor;
    int lin;
    int col;
    bool inicial;
};

struct jogo{
    casa tabuleiro[tam_tab][tam_tab];
    char*** unicodes;
    bool fim;
    turno vez[2];
    int jogador;
    ultima_jogada* u_jog;
    int empate;
};

void tabuleiro_ini(jogo* j);
void imprime_tabuleiro(jogo* j);
void libera_tabuleiro(jogo* j);
lista* computa_jogadas(jogo* t);
void jogo_inicializa(jogo* j);
bool detecta_xeque(jogo* t);

#endif