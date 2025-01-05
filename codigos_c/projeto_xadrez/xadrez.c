#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define tam_tab 8
#define branco 0
#define preto 1
#define vazio 0
#define peao 1
#define torre 2
#define bispo 3
#define cavalo 4
#define rainha 5
#define rei 6

typedef struct casa casa;

typedef struct jogadas_possiveis{
    casa* ini;
    casa* fim;
    struct jogadas_possiveis* prox;
} lista;

typedef struct casa{
    int peca;
    int cor;
} casa;

typedef struct{
    casa **tabuleiro;
    bool fim;
    int vez;
} jogo;

/*void jogo_nao_acabou(jogo** j);
void tela_ganhou(int jogador);

void acha_ameacas(int lin, int col, jogo** j, int tipo){
    switch(tipo){
        if(peao)
    }
}

void jogo_nao_acabou(jogo** j){
    if((*j)->fim == 1){
        tela_ganhou((*j)->vez);
        return;
    }
    for(int i = 0; i < tam_tab; i++){
        for(int k = 0; k < tam_tab; k++){

        }
    }

}

void jogo_faz_jogada(jogo** j){
    printf("Vez do jogador %d:", (*j)->vez);
    char* c = malloc(sizeof(char)*6);
    fgets(c, 6, stdin);
    c[6] = '\0';
    int tipo = (*j)->tabuleiro[c[0]-48][c[1]-97].p->tipo;
    (*j)->tabuleiro[c[0]-48][c[1]-97].p->tipo = vazio;
    acha_ameacas(c[0]-48, c[1]-97, j, tipo);
}*/

lista* lista_cria(){
    lista* l = malloc(sizeof(lista));
    l->ini = NULL;
    l->fim = NULL;
    l->prox = NULL;
    return l;
}

void lista_insere(lista* l, casa* ini, casa* fim){
    lista* novo = lista_cria();
    novo->ini = ini;
    novo->fim = fim;
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
    free(l);
}


// todas as peças estão colocadas nas posições iniciais corretas
void tabuleiro_ini(jogo* j){
    int n = 2;
    for(int i = 0; i < tam_tab/2; i++){
        j->tabuleiro[0][i].peca = n;
        j->tabuleiro[7][i].peca = n;
        if(n == rainha) n++;
        j->tabuleiro[0][tam_tab - i -1].peca = n;
        j->tabuleiro[7][tam_tab - i -1].peca = n;
        n++;
    }
    n = 1;
    for(int i = 0; i < tam_tab; i++){
        j->tabuleiro[1][i].peca = n;
        j->tabuleiro[6][i].peca = n;
    }
    for(int i = 0; i < tam_tab; i++){
        for(int k = 2; k < tam_tab - 2; k++){
            j->tabuleiro[k][i].peca = 0;
        }
    }
}

void imprime_tabuleiro(jogo* j){
    for(int i = 0; i < tam_tab; i++){
        for(int k = 0; k < tam_tab; k++){
            printf("%d| ", j->tabuleiro[i][k].peca);
        }
        printf("\n");
    }
}

void libera_tabuleiro(jogo* j){
    for(int i = 0; i < tam_tab; i++){
        free(j->tabuleiro[i]);
    }
    free(j->tabuleiro);
    free(j);
}

void jogo_inicializa(jogo* j){
    j->tabuleiro = (casa**)malloc(sizeof(casa*)*tam_tab);
    for(int i = 0; i < tam_tab; i++){
        j->tabuleiro[i] = (casa*) malloc(sizeof(casa)*tam_tab);
    }
    j->fim = 0;
    j->vez = branco;
}

int main(){
    jogo* t = malloc(sizeof(jogo));
    jogo_inicializa(t);
    tabuleiro_ini(t);
    imprime_tabuleiro(t);
    libera_tabuleiro(t);
}