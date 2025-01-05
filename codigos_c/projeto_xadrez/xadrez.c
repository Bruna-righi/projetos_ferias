#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define tam_tab 8
#define vazio 0
#define peao 1
#define torre 2
#define bispo 3
#define cavalo 4
#define rainha 5
#define rei 6

typedef struct{
    int peca;
    bool ameacado;
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
    /*for(int i = 0; i < tam_tab; i++){
        for(int k = 0; k < tam_tab; k++){
            printf("%d| ", j->tabuleiro[i][k].peca);
        }
        printf("\n");
    }*/
}

void imprime_tabuleiro(jogo* j){

}

int main(){
    jogo* t = malloc(sizeof(jogo));
    t->tabuleiro = (casa**)malloc(sizeof(casa*)*tam_tab);
    for(int i = 0; i < tam_tab; i++){
        t->tabuleiro[i] = (casa*) malloc(sizeof(casa)*tam_tab);
    }
    tabuleiro_ini(t);
    for (int i = 0; i < tam_tab; i++) {
        free(t->tabuleiro[i]);
    }
    free(t->tabuleiro);

    //free(t);
}