#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#include <string.h>
#include "xadrez.h"
#include "movimentos.h"
#include "lista.h"

void swap(casa* temp_ini, casa* b, int lin, int col, lista* l, jogo* t){
    t->tabuleiro[lin][col].peca = temp_ini->peca;
    t->tabuleiro[lin][col].cor = temp_ini->cor;
    t->tabuleiro[lin][col].inicial = false;
    t->tabuleiro[temp_ini->lin][temp_ini->col].peca = vazio;
    t->tabuleiro[temp_ini->lin][temp_ini->col].inicial = false;

    if(!detecta_xeque(t)) lista_insere(l, temp_ini, b);

    t->tabuleiro[lin][col].peca = b->peca;
    t->tabuleiro[lin][col].cor = b->cor;
    t->tabuleiro[lin][col].inicial = b->inicial;
    t->tabuleiro[temp_ini->lin][temp_ini->col].peca = temp_ini->peca;
    t->tabuleiro[temp_ini->lin][temp_ini->col].inicial = temp_ini->inicial;
}

bool peao_xeque(casa* c, jogo* t){
    int lin = c->lin, col = c->col;
    if(c->cor == branco){
        //checa casa diagonal esquerda
        if(lin - 1 >= 0 && col - 1 >= 0 && lin - 1 < tam_tab && col - 1 < tam_tab){
            if(t->tabuleiro[lin - 1][col - 1].peca == rei && t->tabuleiro[lin - 1][col - 1].cor != c->cor)
                return true;
        }
        //checa diagonal direita
        if(lin - 1 >= 0 && lin - 1 < tam_tab && col + 1 < tam_tab && col + 1 >= 0){
            if(t->tabuleiro[lin-1][col+1].peca == rei && t->tabuleiro[lin-1][col+1].cor != c->cor)
                return true;
        }
    } else if(c->cor == preto){
        //checa casa diagonal esquerda
        if(lin + 1 >= 0 && col - 1 >= 0 && lin + 1 < tam_tab && col - 1 < tam_tab){
            if(t->tabuleiro[lin + 1][col - 1].peca == rei && t->tabuleiro[lin + 1][col - 1].cor != c->cor)
                return true;
        }
        //checa diagonal direita
        if(lin + 1 >= 0 && lin + 1 < tam_tab && col + 1 < tam_tab && col + 1 >= 0){
            if(t->tabuleiro[lin+1][col+1].peca == rei && t->tabuleiro[lin+1][col+1].cor != c->cor)
                return true;
        }
    }
    return false;
}

bool torre_xeque(jogo* t, casa* c){
    int lin = c->lin, col = c->col;
    //checa todas as casas abaixo da posição inicial
    for(int i = lin + 1; i < tam_tab; i++){
        if(t->tabuleiro[i][col].peca == vazio) continue;
        else if(t->tabuleiro[i][col].peca == rei && t->tabuleiro[i][col].cor != c->cor) return true;
        else break;
    }
    //checa todas as casas àcima da posição inicial
    for(int i = lin - 1; i >= 0; i--){
        if(t->tabuleiro[i][col].peca == vazio) continue;
        else if(t->tabuleiro[i][col].peca == rei && t->tabuleiro[i][col].cor != c->cor) return true;
        else break;
    }
    //checa todas as casas à direita da posição inicial
    for(int i = col + 1; i < tam_tab; i++){
        if(t->tabuleiro[lin][i].peca == vazio) continue;
        else if(t->tabuleiro[lin][i].peca == rei && t->tabuleiro[lin][i].cor != c->cor) return true;
        else break;
    }
    //checa todas as casas à esquerda
    for(int i = col - 1; i >= 0; i--){
        if(t->tabuleiro[lin][i].peca == vazio) continue;
        else if(t->tabuleiro[lin][i].peca == rei && t->tabuleiro[lin][i].cor != c->cor) return true;
        else break;
    }
    return false;
}

bool bispo_xeque(jogo* t, casa* c){
    int lin = c->lin, col = c->col;
    //checa todas as casas na diagonal principal abaixo e à direita
    for(int passo = 1; lin + passo < tam_tab && col + passo < tam_tab; passo++){
        if(t->tabuleiro[lin + passo][col + passo].peca == vazio)
            continue;
        else if(t->tabuleiro[lin + passo][col + passo].peca == rei && 
            t->tabuleiro[lin + passo][col + passo].cor != c->cor){
            return true;
        }else break;
    }
    //checa todas as casa na diagonal principal àcima e à esquerda
    for(int passo = 1; lin - passo >= 0 && col - passo >= 0; passo++){
        if(t->tabuleiro[lin - passo][col - passo].peca == vazio)
            continue;
        else if(t->tabuleiro[lin - passo][col - passo].peca == rei &&
            t->tabuleiro[lin - passo][col - passo].cor != c->cor){
            return true;
        }else break;
    }
    //checa todas as casas na diagonal secundária abaixo e à esquerda
    for(int passo = 1; lin + passo < tam_tab && col - passo >= 0; passo++){
        if(t->tabuleiro[lin + passo][col - passo].peca == vazio)
            continue;
        else if(t->tabuleiro[lin + passo][col - passo].peca == rei &&
            t->tabuleiro[lin + passo][col - passo].cor != c->cor){
            return true;
        }else break;
    }
    //checa todas as casas na diagonal secundária àcima e à direita
    for(int passo = 1; lin - passo >= 0 && col + passo < tam_tab; passo++){
        if(t->tabuleiro[lin - passo][col + passo].peca == vazio)
            continue;
        else if(t->tabuleiro[lin - passo][col + passo].peca == rei &&
            t->tabuleiro[lin - passo][col + passo].cor != c->cor){
            return true;
        }else break;
    }
    return false; 
}

bool cavalo_xeque(jogo* t, casa *c){
    int lin = c->lin, col = c->col;
    //2 p baixo, 1 p direita
    if(lin + 2 >= 0 && lin + 2 < tam_tab && col + 1 < tam_tab && col + 1 >= 0){
        if(t->tabuleiro[lin + 2][col + 1].peca == rei && t->tabuleiro[lin + 2][col + 1].cor != c->cor)
            return true;
    }
    if(lin + 2 >= 0 && lin + 2 < tam_tab && col - 1 < tam_tab && col - 1 >= 0){
        if(t->tabuleiro[lin + 2][col - 1].peca == rei && t->tabuleiro[lin + 2][col - 1].cor != c->cor)
            return true;
    }
    if(lin - 2 >= 0 && lin - 2 < tam_tab && col + 1 < tam_tab && col + 1 >= 0){
        if(t->tabuleiro[lin - 2][col + 1].peca == rei && t->tabuleiro[lin - 2][col + 1].cor != c->cor)
            return true;
    }
    if(lin - 2 >= 0 && lin - 2 < tam_tab && col - 1 < tam_tab && col - 1 >= 0){
        if(t->tabuleiro[lin - 2][col - 1].peca == rei && t->tabuleiro[lin - 2][col - 1].cor != c->cor)
            return true;
    }
    if(lin + 1 >= 0 && lin + 1 < tam_tab && col + 2 < tam_tab && col + 2 >= 0){
        if(t->tabuleiro[lin + 1][col + 2].peca == rei && t->tabuleiro[lin + 1][col + 2].cor != c->cor)
            return true;
    }
    if(lin + 1 >= 0 && lin + 1 < tam_tab && col - 2 < tam_tab && col - 2 >= 0){
        if(t->tabuleiro[lin + 1][col - 2].peca == rei && t->tabuleiro[lin + 1][col - 2].cor != c->cor)
            return true;
    }
    if(lin - 1 >= 0 && lin - 1 < tam_tab && col + 2 < tam_tab && col + 2 >= 0){
        if(t->tabuleiro[lin - 1][col + 2].peca == rei && t->tabuleiro[lin - 1][col + 2].cor != c->cor)
            return true;
    }
    if(lin - 1 >= 0 && lin - 1 < tam_tab && col - 2 < tam_tab && col - 2 >= 0){
        if(t->tabuleiro[lin - 1][col - 2].peca == rei && t->tabuleiro[lin - 1][col - 2].cor != c->cor)
            return true;
    }
    return false;
}

void movimento_peao(lista* l, casa* c, jogo* t){
    int lin = c->lin, col = c->col;
    casa* temp_ini = c;
    if(c->cor == branco){
        // Movimento simples
        lin = c->lin - 1;
        if(lin >= 0 && lin < tam_tab && col >= 0 && col < tam_tab){
            if(t->tabuleiro[lin][col].peca == vazio)
                if(!t->vez[t->jogador].xeque)
                    lista_insere(l, c, &t->tabuleiro[lin][col]);
                else swap(temp_ini, &t->tabuleiro[lin][col], lin, col, l, t);
        }
        else if(c->inicial) // Movimento duplo (Precisa checar inicial)
            lin = c->lin - 2;
            if(lin >= 0 && lin < tam_tab && col >= 0 && col < tam_tab){
                if(t->tabuleiro[lin][col].peca == vazio && t->tabuleiro[c->lin - 1][col].peca == vazio)
                    if(!t->vez[t->jogador].xeque)
                        lista_insere(l, c, &t->tabuleiro[lin][col]);
                    else swap(temp_ini, &t->tabuleiro[lin][col], lin, col, l, t);
        }
        //checa casa diagonal esquerda
        lin = c->lin - 1;
        col = c->col - 1;
        if(lin >= 0 && col >= 0 && lin < tam_tab && col < tam_tab){
            if(t->tabuleiro[lin][col].peca != vazio && t->tabuleiro[lin][col].cor != c->cor)
                if(!t->vez[t->jogador].xeque)
                    lista_insere(l, c, &t->tabuleiro[lin][col]);
                else swap(temp_ini, &t->tabuleiro[lin][col], lin, col, l, t);
        }
        //checa diagonal direita
        lin = c->lin - 1;
        col = c->col + 1;
        if(lin >= 0 && lin < tam_tab && col < tam_tab && col >= 0){
            if(t->tabuleiro[lin][col].peca != vazio && t->tabuleiro[lin][col].cor != c->cor)
                if(!t->vez[t->jogador].xeque)
                    lista_insere(l, c, &t->tabuleiro[lin][col]);
                else swap(temp_ini, &t->tabuleiro[lin][col], lin, col, l, t);
        }
    } else if(c->cor == preto){
        // Movimento simples
        lin = c->lin + 1;
        col = c->col;
        if(lin >= 0 && lin < tam_tab && col >= 0 && col < tam_tab){
            if(t->tabuleiro[lin][col].peca == vazio)
                if(!t->vez[t->jogador].xeque)
                    lista_insere(l, c, &t->tabuleiro[lin][col]);
                else swap(temp_ini, &t->tabuleiro[lin][col], lin, col, l, t);
        }
        else if(c->inicial) // Movimento duplo (Precisa checar inicial)
            lin = c->lin + 2;
            col = c->col;
            if(lin >= 0 && lin < tam_tab && col >= 0 && col < tam_tab){
                if(t->tabuleiro[lin][col].peca == vazio && t->tabuleiro[c->lin + 1][col].peca == vazio)
                    if(!t->vez[t->jogador].xeque)
                        lista_insere(l, c, &t->tabuleiro[lin][col]);
                    else swap(temp_ini, &t->tabuleiro[lin][col], lin, col, l, t);
        }
        //checa casa diagonal esquerda
        lin = c->lin + 1;
        col = c->col - 1;
        if(lin >= 0 && col >= 0 && lin < tam_tab && col < tam_tab){
            if(t->tabuleiro[lin][col].peca != vazio && t->tabuleiro[lin][col].cor != c->cor)
                if(!t->vez[t->jogador].xeque)
                    lista_insere(l, c, &t->tabuleiro[lin][col]);
                else swap(temp_ini, &t->tabuleiro[lin][col], lin, col, l, t);
        }
        //checa diagonal direita
        lin = c->lin + 1;
        col = c->col + 1;
        if(lin >= 0 && lin < tam_tab && col < tam_tab && col >= 0){
            if(t->tabuleiro[lin][col].peca != vazio && t->tabuleiro[lin][col].cor != c->cor)
                if(!t->vez[t->jogador].xeque)
                    lista_insere(l, c, &t->tabuleiro[lin][col]);
                else swap(temp_ini, &t->tabuleiro[lin][col], lin, col, l, t);
        }
    }
    //preciso fazer o 'en passant'
}

void movimento_torre(lista* l, casa* c, jogo* t){
    int lin = c->lin, col = c->col;
    casa* temp_ini = c;
    //checa todas as casas abaixo da posição inicial
    for(int i = lin + 1; i < tam_tab; i++){
        if(t->tabuleiro[i][col].peca == vazio){
            if(!t->vez[t->jogador].xeque){
                    lista_insere(l, c, &t->tabuleiro[i][col]);
                    continue;
            }
            else swap(temp_ini, &t->tabuleiro[i][col], i, col, l, t);
        }
        else if(t->tabuleiro[i][col].cor != c->cor){
            if(!t->vez[t->jogador].xeque){
                    lista_insere(l, c, &t->tabuleiro[i][col]);
            }
            else swap(temp_ini, &t->tabuleiro[i][col], i, col, l, t);
            break;
        }else break;
    }
    //checa todas as casas àcima da posição inicial
    for(int i = lin - 1; i >= 0; i--){
        if(t->tabuleiro[i][col].peca == vazio){
            if(!t->vez[t->jogador].xeque){
                    lista_insere(l, c, &t->tabuleiro[i][col]);
                    continue;
            }
            else swap(temp_ini, &t->tabuleiro[i][col], i, col, l, t);
        }
        else if(t->tabuleiro[i][col].cor != c->cor){
            if(!t->vez[t->jogador].xeque){
                    lista_insere(l, c, &t->tabuleiro[i][col]);
            }
            else swap(temp_ini, &t->tabuleiro[i][col], i, col, l, t);
            break;
        }else break;
    }
    //checa todas as casas à direita da posição inicial
    for(int i = col + 1; i < tam_tab; i++){
        if(t->tabuleiro[lin][i].peca == vazio){
            if(!t->vez[t->jogador].xeque){
                    lista_insere(l, c, &t->tabuleiro[lin][i]);
                    continue;
            }
            else swap(temp_ini, &t->tabuleiro[lin][i], lin, i, l, t);
        }
        else if(t->tabuleiro[lin][i].cor != c->cor){
            if(!t->vez[t->jogador].xeque){
                    lista_insere(l, c, &t->tabuleiro[lin][i]);
            }
            else swap(temp_ini, &t->tabuleiro[lin][i], lin, i, l, t);
            break;
        }else break;
    }
    //checa todas as casas à esquerda
    for(int i = col - 1; i >= 0; i--){
        if(t->tabuleiro[lin][i].peca == vazio){
            if(!t->vez[t->jogador].xeque){
                    lista_insere(l, c, &t->tabuleiro[lin][i]);
                    continue;
            }
            else swap(temp_ini, &t->tabuleiro[lin][i], lin, i, l, t);
        }
        else if(t->tabuleiro[lin][i].cor != c->cor){
            if(!t->vez[t->jogador].xeque){
                    lista_insere(l, c, &t->tabuleiro[lin][i]);
            }
            else swap(temp_ini, &t->tabuleiro[lin][i], lin, i, l, t);
            break;
        }else break;
    }
}

void movimento_bispo(lista* l, casa* c, jogo* t){
    int lin = c->lin, col = c->col;
    casa* temp_ini = c;
    //checa todas as casas na diagonal principal abaixo e à direita
    for(int passo = 1; lin + passo < tam_tab && col + passo < tam_tab; passo++){
        if(t->tabuleiro[lin + passo][col + passo].peca == vazio)
            if(!t->vez[t->jogador].xeque){
                    lista_insere(l, c, &t->tabuleiro[lin + passo][col + passo]);
            }
            else swap(temp_ini, &t->tabuleiro[lin + passo][col + passo], lin + passo, col + passo, l, t);
        else if(t->tabuleiro[lin + passo][col + passo].cor != c->cor){
            if(!t->vez[t->jogador].xeque){
                    lista_insere(l, c, &t->tabuleiro[lin + passo][col + passo]);
            }
            else swap(temp_ini, &t->tabuleiro[lin + passo][col + passo], lin + passo, col + passo, l, t);
            break;
        }else break;
    }
    //checa todas as casa na diagonal principal àcima e à esquerda
    for(int passo = 1; lin - passo >= 0 && col - passo >= 0; passo++){
        if(t->tabuleiro[lin - passo][col - passo].peca == vazio)
            if(!t->vez[t->jogador].xeque){
                    lista_insere(l, c, &t->tabuleiro[lin - passo][col - passo]);
            }
            else swap(temp_ini, &t->tabuleiro[lin - passo][col - passo], lin - passo, col - passo, l, t);
        else if(t->tabuleiro[lin - passo][col - passo].cor != c->cor){
            if(!t->vez[t->jogador].xeque){
                    lista_insere(l, c, &t->tabuleiro[lin - passo][col - passo]);
            }
            else swap(temp_ini, &t->tabuleiro[lin - passo][col - passo], lin - passo, col - passo, l, t);
            break;
        }else break;
    }
    //checa todas as casas na diagonal secundária abaixo e à esquerda
    for(int passo = 1; lin + passo < tam_tab && col - passo >= 0; passo++){
        if(t->tabuleiro[lin + passo][col - passo].peca == vazio)
            if(!t->vez[t->jogador].xeque){
                    lista_insere(l, c, &t->tabuleiro[lin + passo][col - passo]);
            }
            else swap(temp_ini, &t->tabuleiro[lin + passo][col - passo], lin + passo, col - passo, l, t);
        else if(t->tabuleiro[lin + passo][col - passo].cor != c->cor){
            if(!t->vez[t->jogador].xeque){
                    lista_insere(l, c, &t->tabuleiro[lin + passo][col - passo]);
            }
            else swap(temp_ini, &t->tabuleiro[lin + passo][col - passo], lin + passo, col - passo, l, t);
            break;
        }else break;
    }
    //checa todas as casas na diagonal secundária àcima e à direita
    for(int passo = 1; lin - passo >= 0 && col + passo < tam_tab; passo++){
        if(t->tabuleiro[lin - passo][col + passo].peca == vazio)
            if(!t->vez[t->jogador].xeque){
                    lista_insere(l, c, &t->tabuleiro[lin - passo][col + passo]);
            }
            else swap(temp_ini, &t->tabuleiro[lin - passo][col + passo], lin - passo, col + passo, l, t);
        else if(t->tabuleiro[lin - passo][col + passo].cor != c->cor){
            if(!t->vez[t->jogador].xeque){
                    lista_insere(l, c, &t->tabuleiro[lin - passo][col + passo]);
            }
            else swap(temp_ini, &t->tabuleiro[lin - passo][col + passo], lin - passo, col + passo, l, t);
            break;
        }else break;
    }
}

void movimento_cavalo(lista* l, casa* c, jogo* t){
    //faz o L
    int lin = c->lin, col = c->col;
    casa* temp_ini = c;
    //2 p baixo, 1 p direita
    if(lin + 2 >= 0 && lin + 2 < tam_tab && col + 1 < tam_tab && col + 1 >= 0){
        if(t->tabuleiro[lin + 2][col + 1].peca == vazio || t->tabuleiro[lin + 2][col + 1].cor != c->cor)
            if(!t->vez[t->jogador].xeque){
                    lista_insere(l, c, &t->tabuleiro[lin + 2][col + 1]);
            }
            else swap(temp_ini, &t->tabuleiro[lin + 2][col + 1], lin + 2, col + 1, l, t);
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

void movimento_rei(lista* l, casa* c, jogo* t){
    int lin = c->lin, col = c->col;
    int passo = 1;
    //movimento diagonal
    if(lin + passo >= 0 && lin + passo < tam_tab && col + passo < tam_tab && col + passo >= 0){
        if(t->tabuleiro[lin + passo][col + passo].peca == vazio || t->tabuleiro[lin + passo][col + passo].cor != c->cor)
            if(lista_busca_fim(l, &t->tabuleiro[lin + passo][col + passo]) == NULL)
                lista_insere(l, c, &t->tabuleiro[lin + passo][col + passo]);
    }
    if(lin - passo >= 0 && lin - passo < tam_tab && col + passo < tam_tab && col + passo >= 0){
        if(t->tabuleiro[lin - passo][col + passo].peca == vazio || t->tabuleiro[lin - passo][col + passo].cor != c->cor)
            if(lista_busca_fim(l, &t->tabuleiro[lin - passo][col + passo]) == NULL)
                lista_insere(l, c, &t->tabuleiro[lin - passo][col + passo]);
    }
    if(lin + passo >= 0 && lin + passo < tam_tab && col - passo < tam_tab && col - passo >= 0){
        if(t->tabuleiro[lin + passo][col - passo].peca == vazio || t->tabuleiro[lin + passo][col - passo].cor != c->cor)
            if(lista_busca_fim(l, &t->tabuleiro[lin + passo][col - passo]) == NULL)
                lista_insere(l, c, &t->tabuleiro[lin + passo][col - passo]);
    }
    if(lin - passo >= 0 && lin - passo < tam_tab && col - passo < tam_tab && col - passo >= 0){
        if(t->tabuleiro[lin - passo][col - passo].peca == vazio || t->tabuleiro[lin - passo][col - passo].cor != c->cor)
            if(lista_busca_fim(l, &t->tabuleiro[lin - passo][col - passo]) == NULL)
                lista_insere(l, c, &t->tabuleiro[lin - passo][col - passo]);
    }
    //movimento horizontal
    if(lin >= 0 && lin < tam_tab && col + passo < tam_tab && col + passo >= 0){
        if(t->tabuleiro[lin][col + passo].peca == vazio || t->tabuleiro[lin][col + passo].cor != c->cor)
            if(lista_busca_fim(l, &t->tabuleiro[lin][col + passo]) == NULL)
                lista_insere(l, c, &t->tabuleiro[lin][col + passo]);
    }
    if(lin >= 0 && lin < tam_tab && col - passo < tam_tab && col - passo >= 0){
        if(t->tabuleiro[lin][col - passo].peca == vazio || t->tabuleiro[lin][col - passo].cor != c->cor)
            if(lista_busca_fim(l, &t->tabuleiro[lin][col - passo]) == NULL)
                lista_insere(l, c, &t->tabuleiro[lin][col - passo]);
    }
    //movimento vertical
    if(lin + passo >= 0 && lin + passo < tam_tab && col >= 0 && col < tam_tab){
        if(t->tabuleiro[lin + passo][col].peca == vazio || t->tabuleiro[lin + passo][col].cor != c->cor)
            if(lista_busca_fim(l, &t->tabuleiro[lin + passo][col]) == NULL)
                lista_insere(l, c, &t->tabuleiro[lin + passo][col]);
    }
    if(lin - passo >= 0 && lin - passo < tam_tab && col >= 0 && col < tam_tab){
        if(t->tabuleiro[lin - passo][col].peca == vazio || t->tabuleiro[lin - passo][col].cor != c->cor)
            if(lista_busca_fim(l, &t->tabuleiro[lin - passo][col]) == NULL)
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