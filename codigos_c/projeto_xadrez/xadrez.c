#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>

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
    int lin;
    int col;
} casa;

typedef struct{
    casa **tabuleiro;
    bool fim;
    int vez;
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
    //printf("ini: p:%d %d %d\n", novo->ini->peca, novo->ini->lin + 1, novo->ini->col + 1);
    //printf("fim:     %d %d\n", novo->fim->lin + 1, novo->fim->col + 1);
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
        //inicializa as cores das pecas
        j->tabuleiro[0][i].cor = branco;
        j->tabuleiro[7][i].cor = preto;
        j->tabuleiro[0][tam_tab - i -1].cor = branco;
        j->tabuleiro[7][tam_tab - i -1].cor = preto;

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
        j->tabuleiro[0][i].peca = n;
        j->tabuleiro[7][i].peca = n;
        if(n == rainha) n++;
        j->tabuleiro[0][tam_tab - i -1].peca = n;
        j->tabuleiro[7][tam_tab - i -1].peca = n;
        n++;
    }
    n = peao;
    for(int i = 0; i < tam_tab; i++){
        j->tabuleiro[1][i].cor = branco;
        j->tabuleiro[6][i].cor = preto;
        j->tabuleiro[1][i].lin = 1;
        j->tabuleiro[6][i].lin = 6;
        j->tabuleiro[1][i].col = i;
        j->tabuleiro[6][i].col = i;
        j->tabuleiro[1][i].peca = n;
        j->tabuleiro[6][i].peca = n;
    }
    for(int i = 0; i < tam_tab; i++){
        for(int k = 2; k < tam_tab - 2; k++){
            j->tabuleiro[k][i].cor = vazio;
            j->tabuleiro[k][i].peca = 0;
            j->tabuleiro[k][i].lin = k;
            j->tabuleiro[k][i].col = i;
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
    //printf("%d\n", cont);
}

void libera_tabuleiro(jogo* j){
    for(int i = 0; i < tam_tab; i++){
        free(j->tabuleiro[i]);
    }
    free(j->tabuleiro);
    free(j);
}

bool movimento_peao(casa* c, int lin, int col, jogo* t){
    if(c->cor == preto){
        if(c->lin - 1 > 0 && lin == c->lin - 1 && col == c->col){
            if(t->tabuleiro[lin][col].peca == vazio)
                return true;
        }
        else if(c->lin - 2 > 0 && lin == c->lin - 2 && col == c->col){
            if(t->tabuleiro[lin][col].peca == vazio)
                return true;
        }
        else if(c->lin - 1 > 0 && col - 1 > 0 && lin == c->lin - 1 
        && col == c->col -1 && t->tabuleiro[lin][col].peca != vazio){
            if(t->tabuleiro[lin][col].peca != vazio && t->tabuleiro[lin][col].cor != c->cor)
                return true;
        }
        else if(c->lin - 1 > 0 && lin == c->lin - 1 && col + 1 < tam_tab
        && col == c->col + 1 && t->tabuleiro[lin][col].peca != vazio){
            if(t->tabuleiro[lin][col].peca != vazio && t->tabuleiro[lin][col].cor != c->cor)
                return true;
        }
    } else if(c->cor == branco){
        if(c->lin + 1 < tam_tab && lin == c->lin + 1 && col == c->col){
            if(t->tabuleiro[lin][col].peca == vazio)
                return true;
        }
        else if(c->lin + 2 < tam_tab && lin == c->lin + 2 && col == c->col){
            if(t->tabuleiro[lin][col].peca == vazio)
                return true;
        }
        else if(c->lin + 1 < tam_tab && c->col - 1 > 0 && lin == c->lin + 1 
        && col == c->col -1 && t->tabuleiro[lin][col].peca != vazio){
            if(t->tabuleiro[lin][col].peca != vazio && t->tabuleiro[lin][col].cor != c->cor)
                return true;
        }
        else if(c->lin + 1 < tam_tab && col + 1 < tam_tab && lin == c->lin + 1 
        && col == c->col + 1 && t->tabuleiro[lin][col].peca != vazio){
            if(t->tabuleiro[lin][col].peca != vazio && t->tabuleiro[lin][col].cor != c->cor)
                return true;
        }
    }
    return false;
}

bool movimento_torre(casa* c, int lin, int col, jogo* t){
    if(lin == c->lin || col == c->col){
        if(lin == c->lin){
            int passo = (col > c->col) ? 1 : -1;
            for(int i = c->col + passo; i != col; i += passo){
                if(t->tabuleiro[lin][i].peca != vazio)
                    return false;
            }
        }
        else if(col == c->col){
            int passo = (lin > c->lin) ? 1 : -1;
            for(int i = c->lin + passo; i != lin; i += passo){
                if(t->tabuleiro[i][col].peca != vazio)
                    return false;
            }
        }
        if(t->tabuleiro[lin][col].peca == vazio || t->tabuleiro[lin][col].cor != c->cor)
            return true;
        }
    return false;
}

bool moviento_bispo(casa* c, int lin, int col, jogo* t){
    if(lin - c->lin == col - c->col || lin - c->lin == c->col - col){
        int passo_lin = (lin > c->lin) ? 1 : -1;
        int passo_col = (col > c->col) ? 1 : -1;

        int i = c->lin + passo_lin;
        int j = c->col + passo_col;
        while(i != lin && j != col){
            if(t->tabuleiro[i][j].peca != vazio)  // Se houver alguma peça no caminho
                return false;
            i += passo_lin;
            j += passo_col;
        }
        if(t->tabuleiro[lin][col].peca == vazio || t->tabuleiro[lin][col].cor != c->cor)
            return true;
        }
    return false;
}

bool movimento_cavalo(casa* c, int lin, int col, jogo* t){
    if(c->peca == cavalo){
        if((lin == c->lin + 2 && col == c->col + 1) || (lin == c->lin + 2 && col == c->col - 1) 
        || (lin == c->lin - 2 && col == c->col + 1) || (lin == c->lin - 2 && col == c->col - 1) 
        || (lin == c->lin + 1 && col == c->col + 2) || (lin == c->lin + 1 && col == c->col - 2) 
        || (lin == c->lin - 1 && col == c->col + 2) || (lin == c->lin - 1 && col == c->col - 2)){
            if(t->tabuleiro[lin][col].peca == vazio || t->tabuleiro[lin][col].cor != c->cor)            
            return true;
        }
    }
    return false;
}

bool movimento_rei(casa* c, int lin, int col, jogo* t){
    if(c->peca == rei){
        if(abs(lin - c->lin) == 1 && abs(col - c->col) == 1){
            if(t->tabuleiro[lin][col].peca == vazio || t->tabuleiro[lin][col].cor != c->cor)
                return true;
        }
        else if(abs(lin - c->lin) == 1 && col == c->col){
            if(t->tabuleiro[lin][col].peca == vazio || t->tabuleiro[lin][col].cor != c->cor)
                return true;
        }
        else if(abs(col - c->col) == 1 && lin == c->lin){
            if(t->tabuleiro[lin][col].peca == vazio || t->tabuleiro[lin][col].cor != c->cor)
                return true;
        }
    }
    return false;
}

lista* computa_jogadas(jogo* t){
    lista* l = lista_cria();

    for(int i = 0; i < tam_tab; i++){
        for(int j = 0; j < tam_tab; j++){

            if(t->tabuleiro[i][j].peca == vazio) continue;

            for(int k = 0; k < tam_tab; k++){
                for(int m = 0; m < tam_tab; m++){
                    if(i == k && j == m) continue;
                    
                    if(t->tabuleiro[i][j].peca == peao){
                        if(movimento_peao(&t->tabuleiro[i][j], k, m, t)){
                            lista_insere(l, &t->tabuleiro[i][j], &t->tabuleiro[k][m]);
                        }
                    }

                    else if(t->tabuleiro[i][j].peca == torre){
                        if(movimento_torre(&t->tabuleiro[i][j], k, m, t)){
                            lista_insere(l, &t->tabuleiro[i][j], &t->tabuleiro[k][m]);
                        }
                    }
                    else if(t->tabuleiro[i][j].peca == bispo){
                        if(moviento_bispo(&t->tabuleiro[i][j], k, m, t)){
                            lista_insere(l, &t->tabuleiro[i][j], &t->tabuleiro[k][m]);
                        }
                    }
                    else if(t->tabuleiro[i][j].peca == cavalo){
                        if(movimento_cavalo(&t->tabuleiro[i][j], k, m, t)){
                            lista_insere(l, &t->tabuleiro[i][j], &t->tabuleiro[k][m]);
                        }
                    }
                    else if(t->tabuleiro[i][j].peca == rainha){
                        if(movimento_torre(&t->tabuleiro[i][j], k, m, t)){
                            lista_insere(l, &t->tabuleiro[i][j], &t->tabuleiro[k][m]);
                        }
                        if(moviento_bispo(&t->tabuleiro[i][j], k, m, t)){
                            lista_insere(l, &t->tabuleiro[i][j], &t->tabuleiro[k][m]);
                        }                  
                    }
                    else if(t->tabuleiro[i][j].peca == rei){
                        if(movimento_rei(&t->tabuleiro[i][j], k, m, t)){
                            lista_insere(l, &t->tabuleiro[i][j], &t->tabuleiro[k][m]);
                        }
                    }
                }
            }
        }
    }
    return l;
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
    lista* l = lista_cria();
    jogo_inicializa(t);
    tabuleiro_ini(t);
    l = computa_jogadas(t);
    imprime_tabuleiro(t);
    libera_tabuleiro(t);
    lista_libera(l);
}