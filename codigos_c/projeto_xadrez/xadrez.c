#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#include <string.h>
#include "xadrez.h"

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

typedef struct jogadas_possiveis{
    int jogEspecial;
    casa* ini;
    casa* fim;
    struct jogadas_possiveis* prox;
} lista;

typedef struct casa{
    int peca;
    char* p;
    int cor;
    int lin;
    int col;
    bool inicial;
} casa;

typedef struct jogo{
    casa **tabuleiro;
    bool fim;
    int vez;
    bool xeque;
} jogo;

lista* lista_cria(){
    lista* l = malloc(sizeof(lista));
    l->ini = NULL;
    l->fim = NULL;
    l->prox = NULL;
    return l;
}

int cont = 0;

void lista_insere(lista* l, casa* ini, casa* fim){
    cont++;
    lista* novo = lista_cria();
    novo->ini = ini;
    novo->fim = fim;
    printf("ini: p:%d %d %c\n", novo->ini->peca, tam_tab - novo->ini->lin, 97 + novo->ini->col);
    printf("fim:     %d %c\n", tam_tab - novo->fim->lin, 97 + novo->fim->col);
    lista* aux = l;
    while(aux->prox != NULL){
        aux = aux->prox;
    }
    aux->prox = novo;
}

void lista_libera(lista* l){
    lista* aux = l;
    while(aux != NULL){
        lista* aux2 = aux;
        aux = aux->prox;
        free(aux2);
    }
}


// todas as peças estão colocadas nas posições iniciais corretas
void tabuleiro_ini(jogo* j){
    int n = torre;
    for(int i = 0; i < tam_tab/2; i++){
        //inicializa os espaçõs para os códigos unicode
        j->tabuleiro[0][i].p = malloc(sizeof(char)*5);
        j->tabuleiro[7][i].p = malloc(sizeof(char)*5);

        //inicializa as cores das pecas
        j->tabuleiro[0][i].cor = preto;
        j->tabuleiro[7][i].cor = branco;
        j->tabuleiro[0][tam_tab - i -1].cor = preto;
        j->tabuleiro[7][tam_tab - i -1].cor = branco;

        //inicializa as linhas e colunas das pecas
        j->tabuleiro[0][i].lin = 0;
        j->tabuleiro[7][i].lin = 7;
        j->tabuleiro[0][tam_tab - i -1].lin = 0;
        j->tabuleiro[7][tam_tab - i -1].lin = 7;
        j->tabuleiro[0][i].col = i;
        j->tabuleiro[7][i].col = i;
        j->tabuleiro[0][tam_tab - i -1].col = tam_tab - i - 1;
        j->tabuleiro[7][tam_tab - i -1].col = tam_tab - i - 1;

        //inicializa as peças
        if(n == rainha) n++;
        j->tabuleiro[0][i].peca = n;
        j->tabuleiro[7][i].peca = n;
        if(n == rei) n--;
        j->tabuleiro[0][tam_tab - i -1].peca = n;
        j->tabuleiro[7][tam_tab - i -1].peca = n;
        n++;

        //condição inicial
        j->tabuleiro[0][i].inicial = true;
        j->tabuleiro[7][i].inicial = true;
        j->tabuleiro[0][tam_tab - i -1].inicial = true;
        j->tabuleiro[7][tam_tab - i -1].inicial = true;
    }
    j->tabuleiro[0][0].p = torre_p;
    j->tabuleiro[0][1].p = cavalo_p;
    j->tabuleiro[0][2].p = bispo_p;
    j->tabuleiro[0][3].p = rainha_p;
    j->tabuleiro[0][4].p = rei_p;
    j->tabuleiro[0][5].p = bispo_p;
    j->tabuleiro[0][6].p = cavalo_p;
    j->tabuleiro[0][7].p = torre_p;
    j->tabuleiro[7][0].p = torre_b;
    j->tabuleiro[7][1].p = cavalo_b;
    j->tabuleiro[7][2].p = bispo_b;
    j->tabuleiro[7][3].p = rainha_b;
    j->tabuleiro[7][4].p = rei_b;
    j->tabuleiro[7][5].p = bispo_b;
    j->tabuleiro[7][6].p = cavalo_b;
    j->tabuleiro[7][7].p = torre_b;
    n = peao;
    for(int i = 0; i < tam_tab; i++){
        j->tabuleiro[1][i].p = malloc(sizeof(char)*5);
        j->tabuleiro[6][i].p = malloc(sizeof(char)*5);
        j->tabuleiro[1][i].cor = preto;
        j->tabuleiro[6][i].cor = branco;
        //removendo os peões temporariamente para testar o movimento

        /*j->tabuleiro[1][i].p = (j->tabuleiro[1][i].cor == branco) ? peao_b : peao_p;
        j->tabuleiro[6][i].p = (j->tabuleiro[6][i].cor == branco) ? peao_b : peao_p;*/
        j->tabuleiro[1][i].lin = 1;
        j->tabuleiro[6][i].lin = 6;
        j->tabuleiro[1][i].col = i;
        j->tabuleiro[6][i].col = i;
        j->tabuleiro[1][i].peca = vazio;
        j->tabuleiro[6][i].peca = vazio;
        /*
        j->tabuleiro[1][i].peca = n;
        j->tabuleiro[6][i].peca = n;
        */
        j->tabuleiro[1][i].inicial = true;
        j->tabuleiro[6][i].inicial = true;
    }
    for(int i = 0; i < tam_tab; i++){
        for(int k = 2; k < tam_tab - 2; k++){
            j->tabuleiro[k][i].p = malloc(sizeof(char)*5);
            j->tabuleiro[k][i].cor = vazio;
            j->tabuleiro[k][i].peca = vazio;
            j->tabuleiro[k][i].lin = k;
            j->tabuleiro[k][i].col = i;
            j->tabuleiro[k][i].inicial = false;
        }
    }
}

void imprime_tabuleiro(jogo* j){
    printf(ESC BACKGROUND_BRANCO JUNTA COR_VERMELHA FIM_ESC"\n    a  b  c  d  e  f  g  h\n" RESET);
    for(int i = 0; i < tam_tab; i++){
        printf(ESC BACKGROUND_BRANCO JUNTA COR_VERMELHA FIM_ESC"%d  " RESET, tam_tab-i);
        for(int k = 0; k < tam_tab; k++){
            if((k + i)%2 == 0){
                printf(ESC BACKGROUND_BRANCO FIM_ESC);
            }else printf(ESC BACKGROUND_PRETO FIM_ESC);

            if(j->tabuleiro[i][k].cor == branco){
                printf(ESC COR_BRANCA FIM_ESC);
            }else printf(ESC COR_PRETA FIM_ESC);

            if(j->tabuleiro[i][k].peca == vazio){
                printf("   ");
            }
            else printf(" %s ", j->tabuleiro[i][k].p);
            printf(RESET);
        }
        printf("\n");
    }
    //printf("%d\n", cont);
}

void libera_tabuleiro(jogo* j){
    for(int i = 0; i < tam_tab; i++){
        free(j->tabuleiro[i]);
    }
    free(j->tabuleiro);
    free(j);
}

void movimento_peao(lista* l, casa* c, jogo* t){
    int lin = c->lin, col = c->col;
    if(c->cor == branco){
        // Movimento simples
        if(lin - 1 >= 0 && lin - 1 < tam_tab && col >= 0 && col < tam_tab){
            if(t->tabuleiro[lin-1][col].peca == vazio)
                lista_insere(l, c, &t->tabuleiro[lin-1][col]);
        }
        else if(c->inicial) // Movimento duplo (Precisa checar inicial)
            if(lin - 2 >= 0 && lin - 2 < tam_tab && col >= 0 && col < tam_tab){
                if(t->tabuleiro[lin-2][col].peca == vazio && t->tabuleiro[lin - 1][col].peca == vazio)
                    lista_insere(l, c, &t->tabuleiro[lin-2][col]);
        }
        //checa casa diagonal esquerda
        if(lin - 1 >= 0 && col - 1 >= 0 && lin - 1 < tam_tab && col - 1 < tam_tab){
            if(t->tabuleiro[lin - 1][col - 1].peca != vazio && t->tabuleiro[lin - 1][col - 1].cor != c->cor)
                lista_insere(l, c, &t->tabuleiro[lin-1][col-1]);
        }
        //checa diagonal direita
        if(lin - 1 >= 0 && lin - 1 < tam_tab && col + 1 < tam_tab && col + 1 >= 0){
            if(t->tabuleiro[lin-1][col+1].peca != vazio && t->tabuleiro[lin-1][col+1].cor != c->cor)
                lista_insere(l, c, &t->tabuleiro[lin-1][col+1]);
        }
    } else if(c->cor == preto){
        // Movimento simples
        if(lin + 1 >= 0 && lin + 1 < tam_tab && col >= 0 && col < tam_tab){
            if(t->tabuleiro[lin+1][col].peca == vazio)
                lista_insere(l, c, &t->tabuleiro[lin-1][col]);
        }
        else if(c->inicial) // Movimento duplo (Precisa checar inicial)
            if(lin + 2 >= 0 && lin + 2 < tam_tab && col >= 0 && col < tam_tab){
                if(t->tabuleiro[lin+2][col].peca == vazio && t->tabuleiro[lin + 1][col].peca == vazio)
                    lista_insere(l, c, &t->tabuleiro[lin+2][col]);
        }
        //checa casa diagonal esquerda
        if(lin + 1 >= 0 && col - 1 >= 0 && lin + 1 < tam_tab && col - 1 < tam_tab){
            if(t->tabuleiro[lin + 1][col - 1].peca != vazio && t->tabuleiro[lin + 1][col - 1].cor != c->cor)
                lista_insere(l, c, &t->tabuleiro[lin+1][col-1]);
        }
        //checa diagonal direita
        if(lin + 1 >= 0 && lin + 1 < tam_tab && col + 1 < tam_tab && col + 1 >= 0){
            if(t->tabuleiro[lin+1][col+1].peca != vazio && t->tabuleiro[lin+1][col+1].cor != c->cor)
                lista_insere(l, c, &t->tabuleiro[lin+1][col+1]);
        }
    }
    //preciso fazer o 'en passant'
}

void movimento_torre(lista* l, casa* c, jogo* t){
    int lin = c->lin, col = c->col;
    //checa todas as casas abaixo da posição inicial
    for(int i = lin + 1; i < tam_tab; i++){
        if(t->tabuleiro[i][col].peca == vazio)
            lista_insere(l, c, &t->tabuleiro[i][col]);
        else if(t->tabuleiro[i][col].cor != c->cor){
            lista_insere(l, c, &t->tabuleiro[i][col]);
            break;
        }else break;
    }
    //checa todas as casas àcima da posição inicial
    for(int i = lin - 1; lin >= 0; lin++){
        if(t->tabuleiro[i][col].peca == vazio)
            lista_insere(l, c, &t->tabuleiro[i][col]);
        else if(t->tabuleiro[i][col].cor != c->cor){
            lista_insere(l, c, &t->tabuleiro[i][col]);
            break;
        }else break;
    }
    //checa todas as casas à direita da posição inicial
    for(int i = col + 1; i < tam_tab; i++){
        if(t->tabuleiro[lin][i].peca == vazio)
            lista_insere(l, c, &t->tabuleiro[lin][i]);
        else if(t->tabuleiro[lin][i].cor != c->cor){
            lista_insere(l, c, &t->tabuleiro[lin][i]);
            break;
        }else break;
    }
    //checa todas as casas à esquerda
    for(int i = col - 1; col >= 0; col++){
        if(t->tabuleiro[lin][i].peca == vazio)
            lista_insere(l, c, &t->tabuleiro[lin][i]);
        else if(t->tabuleiro[lin][i].cor != c->cor){
            lista_insere(l, c, &t->tabuleiro[lin][i]);
            break;
        }else break;
    }
}

void moviento_bispo(lista* l, casa* c, jogo* t){
    int lin = c->lin, col = c->col;
    //checa todas as casas na diagonal principal abaixo e à direita
    for(int passo = 1; lin + passo < tam_tab && col + passo < tam_tab; passo++){
        if(t->tabuleiro[lin + passo][col + passo].peca == vazio)
            lista_insere(l, c, &t->tabuleiro[lin + passo][col + passo]);
        else if(t->tabuleiro[lin + passo][col + passo].cor != c->cor){
            lista_insere(l, c, &t->tabuleiro[lin + passo][col + passo]);
            break;
        }else break;
    }
    //checa todas as casa na diagonal principal àcima e à esquerda
    for(int passo = 1; lin - passo >= 0 && col - passo >= 0; passo++){
        if(t->tabuleiro[lin - passo][col - passo].peca == vazio)
            lista_insere(l, c, &t->tabuleiro[lin - passo][col - passo]);
        else if(t->tabuleiro[lin - passo][col - passo].cor != c->cor){
            lista_insere(l, c, &t->tabuleiro[lin - passo][col - passo]);
            break;
        }else break;
    }
    //checa todas as casas na diagonal secundária abaixo e à esquerda
    for(int passo = 1; lin + passo < tam_tab && col - passo >= 0; passo++){
        if(t->tabuleiro[lin + passo][col - passo].peca == vazio)
            lista_insere(l, c, &t->tabuleiro[lin + passo][col - passo]);
        else if(t->tabuleiro[lin + passo][col - passo].cor != c->cor){
            lista_insere(l, c, &t->tabuleiro[lin + passo][col - passo]);
            break;
        }else break;
    }
    //checa todas as casas na diagonal secundária àcima e à direita
    for(int passo = 1; lin - passo >= 0 && col + passo >= 0; passo++){
        if(t->tabuleiro[lin - passo][col + passo].peca == vazio)
            lista_insere(l, c, &t->tabuleiro[lin - passo][col + passo]);
        else if(t->tabuleiro[lin - passo][col + passo].cor != c->cor){
            lista_insere(l, c, &t->tabuleiro[lin - passo][col + passo]);
            break;
        }else break;
    }
}

void movimento_cavalo(lista* l, casa* c, jogo* t){
    //faz o L
    int lin = c->lin, col = c->col;
    //2 p baixo, 1 p direita
    if(lin + 2 >= 0 && lin + 2 < tam_tab && col + 1 < tam_tab && col + 1 >= 0){
        if(t->tabuleiro[lin + 2][col + 1].peca == vazio || t->tabuleiro[lin + 2][col + 1].cor != c->cor)
            lista_insere(l, c, &t->tabuleiro[lin + 2][col + 1]);
    }
    if(lin + 2 >= 0 && lin + 2 < tam_tab && col - 1 < tam_tab && col - 1 >= 0){
        if(t->tabuleiro[lin + 2][col - 1].peca == vazio || t->tabuleiro[lin + 2][col - 1].cor != c->cor)
            lista_insere(l, c, &t->tabuleiro[lin + 2][col - 1]);
    }
    if(lin - 2 >= 0 && lin - 2 < tam_tab && col + 1 < tam_tab && col + 1 >= 0){
        if(t->tabuleiro[lin - 2][col + 1].peca == vazio || t->tabuleiro[lin - 2][col + 1].cor != c->cor)
            lista_insere(l, c, &t->tabuleiro[lin - 2][col + 1]);
    }
    if(lin - 2 >= 0 && lin - 2 < tam_tab && col - 1 < tam_tab && col - 1 >= 0){
        if(t->tabuleiro[lin - 2][col - 1].peca == vazio || t->tabuleiro[lin - 2][col - 1].cor != c->cor)
            lista_insere(l, c, &t->tabuleiro[lin - 2][col - 1]);
    }
    if(lin + 1 >= 0 && lin + 1 < tam_tab && col + 2 < tam_tab && col + 2 >= 0){
        if(t->tabuleiro[lin + 1][col + 2].peca == vazio || t->tabuleiro[lin + 1][col + 2].cor != c->cor)
            lista_insere(l, c, &t->tabuleiro[lin + 1][col + 2]);
    }
    if(lin + 1 >= 0 && lin + 1 < tam_tab && col - 2 < tam_tab && col - 2 >= 0){
        if(t->tabuleiro[lin + 1][col - 2].peca == vazio || t->tabuleiro[lin + 1][col - 2].cor != c->cor)
            lista_insere(l, c, &t->tabuleiro[lin + 1][col - 2]);
    }
    if(lin - 1 >= 0 && lin - 1 < tam_tab && col + 2 < tam_tab && col + 2 >= 0){
        if(t->tabuleiro[lin - 1][col + 2].peca == vazio || t->tabuleiro[lin - 1][col + 2].cor != c->cor)
            lista_insere(l, c, &t->tabuleiro[lin - 1][col + 2]);
    }
    if(lin - 1 >= 0 && lin - 1 < tam_tab && col - 2 < tam_tab && col - 2 >= 0){
        if(t->tabuleiro[lin - 1][col - 2].peca == vazio || t->tabuleiro[lin - 1][col - 2].cor != c->cor)
            lista_insere(l, c, &t->tabuleiro[lin - 1][col - 2]);
    }
}

bool movimento_rei(lista* l, casa* c, jogo* t){
    int lin = c->lin, col = c->col;
    int passo = 1;
    //movimento diagonal
    if(lin + passo >= 0 && lin + passo < tam_tab && col + passo < tam_tab && col + passo >= 0){
        if(t->tabuleiro[lin + passo][col + passo].peca == vazio || t->tabuleiro[lin + passo][col + passo].cor != c->cor)
            lista_insere(l, c, &t->tabuleiro[lin + passo][col + passo]);
    }
    if(lin - passo >= 0 && lin - passo < tam_tab && col + passo < tam_tab && col + passo >= 0){
        if(t->tabuleiro[lin - passo][col + passo].peca == vazio || t->tabuleiro[lin - passo][col + passo].cor != c->cor)
            lista_insere(l, c, &t->tabuleiro[lin - passo][col + passo]);
    }
    if(lin + passo >= 0 && lin + passo < tam_tab && col - passo < tam_tab && col - passo >= 0){
        if(t->tabuleiro[lin + passo][col - passo].peca == vazio || t->tabuleiro[lin + passo][col - passo].cor != c->cor)
            lista_insere(l, c, &t->tabuleiro[lin + passo][col - passo]);
    }
    if(lin - passo >= 0 && lin - passo < tam_tab && col - passo < tam_tab && col - passo >= 0){
        if(t->tabuleiro[lin - passo][col - passo].peca == vazio || t->tabuleiro[lin - passo][col - passo].cor != c->cor)
            lista_insere(l, c, &t->tabuleiro[lin - passo][col - passo]);
    }
    //movimento horizontal
    if(lin >= 0 && lin < tam_tab && col + passo < tam_tab && col + passo >= 0){
        if(t->tabuleiro[lin][col + passo].peca == vazio || t->tabuleiro[lin][col + passo].cor != c->cor)
            lista_insere(l, c, &t->tabuleiro[lin][col + passo]);
    }
    if(lin >= 0 && lin < tam_tab && col - passo < tam_tab && col - passo >= 0){
        if(t->tabuleiro[lin][col - passo].peca == vazio || t->tabuleiro[lin][col - passo].cor != c->cor)
            lista_insere(l, c, &t->tabuleiro[lin][col - passo]);
    }
    //movimento vertical
    if(lin + passo >= 0 && lin + passo < tam_tab && col >= 0 && col < tam_tab){
        if(t->tabuleiro[lin + passo][col].peca == vazio || t->tabuleiro[lin + passo][col].cor != c->cor)
            lista_insere(l, c, &t->tabuleiro[lin + passo][col]);
    }
    if(lin - passo >= 0 && lin - passo < tam_tab && col >= 0 && col < tam_tab){
        if(t->tabuleiro[lin - passo][col].peca == vazio || t->tabuleiro[lin - passo][col].cor != c->cor)
            lista_insere(l, c, &t->tabuleiro[lin - passo][col]);
    }
    //roque
    /*if(c->inicial){
        for(int i = col + 1; i < tam_tab; i++){
            if(t->tabuleiro[lin][i].peca != vazio) break;
            if(i == tam_tab - 1){
                if(t->tabuleiro[lin][i].inicial){
                    lista_insere(l, c, &t->tabuleiro[lin][i - 1]);
                    lista_insere(l, &t->tabuleiro[lin][i], &t->tabuleiro[lin][col + 1]);
                }
            }
        }
    }
        if(c->inicial){
        for(int i = col - 1; i > 0; i--){
            if(t->tabuleiro[lin][i].peca != vazio) break;
            if(i == tam_tab - 1){
                if(t->tabuleiro[lin][i].inicial){
                    lista_insere(l, c, &t->tabuleiro[lin][i - 1]);
                    lista_insere(l, &t->tabuleiro[lin][i], &t->tabuleiro[lin][col + 1]);
                }
            }
        }
    }
    */
}

lista* computa_jogadas(jogo* t){
    //cria uma nova lista para as jogadas possíveis
    lista* l = lista_cria();

    //percorre todo o tabuleiro, testando todas as opções possíveis
    for(int i = 0; i < tam_tab; i++){
        for(int j = 0; j < tam_tab; j++){

            //se a casa for vazia (não há peças para movimentar) ou a peça não é do jogador deste turno, skip
            if(t->tabuleiro[i][j].peca == vazio) continue;
            if(t->tabuleiro[i][j].cor != t->vez) continue;
            
            //se a peça é um peão, adiciona na lista os movimentos do peão
            if(t->tabuleiro[i][j].peca == peao){
                movimento_peao(l, &t->tabuleiro[i][j], t);
            }


            //se a peça é uma torre, adiciona os movimentos de torre
            else if(t->tabuleiro[i][j].peca == torre){
                movimento_torre(l, &t->tabuleiro[i][j], t);
            }

            //se a peça é um bispo, adiciona os movimentos de bispo
            else if(t->tabuleiro[i][j].peca == bispo){
                moviento_bispo(l, &t->tabuleiro[i][j], t);
            }

            //se a peça é um cavalo, adicona os movimentos de cavalo
            else if(t->tabuleiro[i][j].peca == cavalo){
                movimento_cavalo(l, &t->tabuleiro[i][j], t);
            }

            //se a peça é uma rainha, testa para bispo e torre
            else if(t->tabuleiro[i][j].peca == rainha){
                movimento_torre(l, &t->tabuleiro[i][j], t);
                moviento_bispo(l, &t->tabuleiro[i][j], t);                
            }
        }
    }
    // depois de computados todos os outros movimentos, testa os movimentos do rei
    for(int i = 0; i < tam_tab; i++){
        for(int j = 0; j < tam_tab; j++){

            if(t->tabuleiro[i][j].peca == vazio) continue;
            if(t->tabuleiro[i][j].cor != t->vez) continue;
            if(t->tabuleiro[i][j].peca != rei) continue;

            // o movimento do rei só é possível se n colocar o rei em xeque
            // tenho que testar na função "movimento_rei" se o movimento coloca o rei em xeque
            movimento_rei(l, &t->tabuleiro[i][j], t);

        }
    }
    return l;
}

void jogo_inicializa(jogo* j){
    //aloca a memória para o tabuleiro
    j->tabuleiro = (casa**)malloc(sizeof(casa*)*tam_tab);

    //aloca cada linha do tabuleiro
    for(int i = 0; i < tam_tab; i++){
        j->tabuleiro[i] = (casa*) malloc(sizeof(casa)*tam_tab);
    }
    // valores iniciais das variáveis do jogo
    j->fim = false;
    j->xeque = false;
    j->vez = branco; //branco começa
}

lista* lista_busca(lista* l, casa* ini, casa* fim){
    // procura na lista uma jogada com determinada casa inicial
    lista* aux = l;
    while(aux != NULL && aux->ini != ini && aux->fim != fim){
        aux = aux->prox;
    }
    if(aux == NULL) return NULL;
    else return aux;
}

lista* lista_busca_fim(lista* l, casa* b){
    lista* aux = l;
    while(aux != NULL && aux->fim != b){
        aux = aux->prox;
    }
    if(aux == NULL) return NULL;
    else return aux;
}

// preciso alterar ainda
bool detecta_xeque(jogo* t, lista* l){
    int i, j;
    for(i = 0; i < tam_tab; i++){
        for(j = 0; j < tam_tab; j++){
            if(t->tabuleiro[i][j].peca == rei && t->tabuleiro[i][j].cor != t->vez) break;
        }
    }
    if(lista_busca_fim(l, &t->tabuleiro[i][j]) != NULL){
        return true;
    }
    return false;
}

bool le_jogada(jogo *t){
    // cria uma lista de jogadas possíveis para cada jogador (branco ou preto) de acordo com a vez
    lista* l = computa_jogadas(t);
    int lin_ini, lin_fim, col_i, col_f;
    char col_ini, col_fim;
    printf("\n\tVez do jogador %s", t->vez == branco ? "branco\n" : "preto\n");
    int resultado = scanf(" %c%d %c%d", &col_ini, &lin_ini, &col_fim, &lin_fim); 

    // Verificando se o scanf foi bem-sucedido
    if (resultado != 4) {
        printf("Entrada inválida. Tente novamente.\n");
        //reseta a lista
        lista_libera(l);
        return false;
    }
    while (getchar() != '\n');
    col_i = (int)(col_ini - 'a');
    col_f = (int)(col_fim - 'a');
    lin_ini = tam_tab - lin_ini;
    lin_fim = tam_tab - lin_fim;

    printf("lin_ini: %d, col_i: %d\nlin_fim: %d, col_f: %d", lin_ini, col_i, lin_fim, col_f);
    if(col_i > 7 || col_i < 0 || col_f > 7 || col_f < 0){
        printf("Coluna inválida\n");
        //reseta a lista
        lista_libera(l);
        return false;
    }
    if(lin_ini < 0 || lin_ini > 7 || lin_fim < 0 || lin_fim > 7){
        printf("Linha inválida\n");
        //reseta a lista
        lista_libera(l);
        return false;
    }
    
    if(lista_busca_fim(l, &t->tabuleiro[lin_fim][col_f]) == NULL){
        printf("Jogada inválida: fim\n");
        //reseta a lista
        lista_libera(l);
        return false;
    }
    if(lista_busca(l, &t->tabuleiro[lin_ini][col_i], &t->tabuleiro[lin_fim][col_f]) == NULL){
        printf("Jogada inválida: ini\n");
        //reseta a lista
        lista_libera(l);
        return false;
    }
    printf("Busca realizada com sucesso!\n");
    t->tabuleiro[lin_fim][col_f].peca = t->tabuleiro[lin_ini][col_i].peca;
    strcpy(t->tabuleiro[lin_fim][col_f].p, t->tabuleiro[lin_ini][col_i].p);
    t->tabuleiro[lin_fim][col_f].cor = t->vez;
    t->tabuleiro[lin_ini][col_i].peca = vazio;
    t->tabuleiro[lin_ini][col_i].cor = vazio;
    t->tabuleiro[lin_ini][col_i].inicial = false;
    t->tabuleiro[lin_fim][col_f].inicial = false;
    // checa se esse movimento coloca o rei inimigo em xeque
    if(detecta_xeque(t, l)){
        printf("Xeque\n");
        t->xeque = true;
    }else{
        t->xeque = false;
    }
    //muda a vez e reseta a lista
    if(t->vez == branco) t->vez = preto;
    else t->vez = branco;
    
    lista_libera(l);
    return true;

}

int main(){
    jogo* t = malloc(sizeof(jogo));
    lista* l = lista_cria();
    jogo_inicializa(t);
    tabuleiro_ini(t);
    while(!t->fim){
        imprime_tabuleiro(t);
        while(!le_jogada(t));
        system("clear");
    }
    imprime_tabuleiro(t);
    libera_tabuleiro(t);
    lista_libera(l);
}