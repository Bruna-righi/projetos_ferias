#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#include <string.h>
#include "xadrez.h"
#include "lista.h"
#include "movimentos.h"

bool empate_por_mov(jogo* t, bool reseta){
    if(reseta){
        t->empate = 0;
    }
    else t->empate++;
    if(t->empate >= 100){
        t->fim = true;
        printf("Empate! Você esgotou seus movimentos!");
    }
}

// todas as peças estão colocadas nas posições iniciais corretas
void tabuleiro_ini(jogo* j){
    int n = torre;
    for(int i = 0; i < tam_tab/2; i++){

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
        j->tabuleiro[0][i].peca = n;
        j->tabuleiro[7][i].peca = n;
        if(n == rainha) n++;
        j->tabuleiro[0][tam_tab - i -1].peca = n;
        j->tabuleiro[7][tam_tab - i -1].peca = n;
        n++;

        //condição inicial
        j->tabuleiro[0][i].inicial = true;
        j->tabuleiro[7][i].inicial = true;
        j->tabuleiro[0][tam_tab - i -1].inicial = true;
        j->tabuleiro[7][tam_tab - i -1].inicial = true;
    }
    strcpy(j->unicodes[branco][peao], peao_b);
    strcpy(j->unicodes[branco][torre], torre_b);
    strcpy(j->unicodes[branco][cavalo], cavalo_b);
    strcpy(j->unicodes[branco][bispo], bispo_b);
    strcpy(j->unicodes[branco][rainha], rainha_b);
    strcpy(j->unicodes[branco][rei], rei_b);
    strcpy(j->unicodes[preto][peao], peao_p);
    strcpy(j->unicodes[preto][torre], torre_p);
    strcpy(j->unicodes[preto][cavalo], cavalo_p);
    strcpy(j->unicodes[preto][bispo], bispo_p);
    strcpy(j->unicodes[preto][rainha], rainha_p);
    strcpy(j->unicodes[preto][rei], rei_p);
    n = peao;
    for(int i = 0; i < tam_tab; i++){
        j->tabuleiro[1][i].cor = preto;
        j->tabuleiro[6][i].cor = branco;
        //removendo os peões temporariamente para testar o movimento

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
            else printf(" %s ", j->unicodes[j->tabuleiro[i][k].cor][j->tabuleiro[i][k].peca]);
            printf(RESET);
        }
        printf("\n");
    }
    //printf("%d\n", cont);
}

void libera_tabuleiro(jogo* j){
    for(int i = 0; i < 2; i++){
        for(int k = 0; k < 7; k++){
            free(j->unicodes[i][k]);
        }
    }
    for(int i = 0; i < 2; i++){
        free(j->unicodes[i]);
    }
    free(j->unicodes);
    free(j->tabuleiro);
    free(j->u_jog);
    free(j);
}

lista* computa_jogadas(jogo* t){
    //cria uma nova lista para as jogadas possíveis
    lista* l = lista_cria();

    //percorre todo o tabuleiro, testando todas as opções possíveis
    for(int i = 0; i < tam_tab; i++){
        for(int j = 0; j < tam_tab; j++){

            //se a casa for vazia (não há peças para movimentar) ou a peça não é do jogador deste turno, skip
            if(t->tabuleiro[i][j].peca == vazio) continue;
            if(t->tabuleiro[i][j].cor != t->vez[t->jogador].c) continue;
            
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
                movimento_bispo(l, &t->tabuleiro[i][j], t);
            }

            //se a peça é um cavalo, adicona os movimentos de cavalo
            else if(t->tabuleiro[i][j].peca == cavalo){
                movimento_cavalo(l, &t->tabuleiro[i][j], t);
            }

            //se a peça é uma rainha, testa para bispo e torre
            else if(t->tabuleiro[i][j].peca == rainha){
                movimento_torre(l, &t->tabuleiro[i][j], t);
                movimento_bispo(l, &t->tabuleiro[i][j], t);                
            }
        }
    }
    // depois de computados todos os outros movimentos, testa os movimentos do rei
    for(int i = 0; i < tam_tab; i++){
        for(int j = 0; j < tam_tab; j++){

            if(t->tabuleiro[i][j].peca == vazio) continue;
            if(t->tabuleiro[i][j].cor != t->vez[t->jogador].c) continue;
            if(t->tabuleiro[i][j].peca != rei) continue;

            // o movimento do rei só é possível se n colocar o rei em xeque
            // tenho que testar na função "movimento_rei" se o movimento coloca o rei em xeque
            movimento_rei(l, &t->tabuleiro[i][j], t);

        }
    }

    return l;
}

void jogo_inicializa(jogo* j){
    j->unicodes = (char***) malloc(sizeof(char***)*2);
    for(int i = 0; i < 2; i++){
        j->unicodes[i] = (char**) malloc(sizeof(char**)*7);
    }
    for(int i = 0; i < 2; i++){
        for(int k = 0;  k < 7; k++){
            j->unicodes[i][k] = (char*) malloc(sizeof(char*)*5);
        }
    }

    // valores iniciais das variáveis do jogo
    j->fim = false;
    j->vez[0].c = branco;
    j->vez[1].c = preto;
    j->vez[0].xeque = false;
    j->vez[1].xeque = false;
    j->empate = 0;
    j->jogador = branco; // branco começa
    j->u_jog = malloc(sizeof(ultima_jogada));
    j->u_jog->ini = NULL;
    j->u_jog->fim = NULL;
}

// preciso alterar ainda
bool detecta_xeque(jogo* t){
    for(int i = 0; i < tam_tab; i++){
        for(int j = 0; j < tam_tab; j++){
            if(t->tabuleiro[i][j].peca == vazio) continue;
            if(t->tabuleiro[i][j].cor != t->vez[t->jogador].c) continue;
            if(t->tabuleiro[i][j].peca == rei) continue;
            casa* c = &t->tabuleiro[i][j];
            switch(c->peca){
                case rainha:
                    if(bispo_xeque(t, c) || torre_xeque(t, c)) return true;
                    break;
                case peao:
                    if(peao_xeque(c, t)) return true;
                    break;
                case cavalo:
                    if(cavalo_xeque(t, c)) return true;
                    break;
                case bispo:
                    if(bispo_xeque(t, c)) return true;
                    break;
                case torre:
                    if(torre_xeque(t, c)) return true;
                    break;
            }
        }
    }
    
    return false;
}

bool le_jogada(jogo *t){

    // cria uma lista de jogadas possíveis para cada jogador (branco ou preto) de acordo com a vez
    lista* l = computa_jogadas(t);

    bool reseta = false;

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
    if(lista_busca(l, &t->tabuleiro[lin_ini][col_i], &t->tabuleiro[lin_fim][col_f]) == NULL){
        printf("Jogada inválida\n");
        //reseta a lista
        lista_libera(l);
        return false;
    }
    if(t->tabuleiro[lin_fim][col_f].peca != vazio) reseta = true;
    if(t->tabuleiro[lin_ini][col_i].peca == peao) reseta = true;
    t->tabuleiro[lin_fim][col_f].peca = t->tabuleiro[lin_ini][col_i].peca;

    t->tabuleiro[lin_fim][col_f].cor = t->vez[t->jogador].c;
    t->tabuleiro[lin_ini][col_i].peca = vazio;
    t->tabuleiro[lin_ini][col_i].cor = vazio;
    t->tabuleiro[lin_ini][col_i].inicial = false;
    t->tabuleiro[lin_fim][col_f].inicial = false;

    //checar o en passant
    if(t->u_jog->ini != NULL){
        //en_passant(t, &t->tabuleiro[lin_ini][col_i], &t->tabuleiro[lin_fim][col_f]);
    }
    //mudar a ultima jogada
    t->u_jog->ini = &t->tabuleiro[lin_ini][col_i];
    t->u_jog->fim = &t->tabuleiro[lin_fim][col_f];

    if(detecta_xeque(t)){
        printf("Xeque\n");
        t->vez[t->jogador].xeque = true;
        // preciso colocar uma função para lidar com a situação de xeque
    }else{
        t->vez[t->jogador].xeque = false;
    }

    //muda a vez e reseta a lista
    if(t->jogador == branco) t->jogador = preto;
    else t->jogador = branco;
    
    lista_libera(l);
    if(empate_por_mov(t, reseta)) return true;
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
        //system("clear");
    }
    imprime_tabuleiro(t);
    libera_tabuleiro(t);
    lista_libera(l);
}