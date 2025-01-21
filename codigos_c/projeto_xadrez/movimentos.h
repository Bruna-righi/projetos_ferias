#ifndef MOVIMENTOS_H
#define MOVIMENTOS_H

#include "xadrez.h"

void movimento_peao(lista* l, casa* c, jogo* t);
void movimento_torre(lista* l, casa* c, jogo* t);
void movimento_bispo(lista* l, casa* c, jogo* t);
void movimento_cavalo(lista* l, casa* c, jogo* t);
void movimento_rei(lista* l, casa* c, jogo* t);

#endif