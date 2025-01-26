#ifndef MOVIMENTOS_H
#define MOVIMENTOS_H

#include "xadrez.h"

bool peao_xeque(casa* c, jogo* t);
bool torre_xeque(jogo* t, casa* c);
bool bispo_xeque(jogo* t, casa* c);
bool cavalo_xeque(jogo* t, casa *c);
void movimento_peao(lista* l, casa* c, jogo* t);
void movimento_torre(lista* l, casa* c, jogo* t);
void movimento_bispo(lista* l, casa* c, jogo* t);
void movimento_cavalo(lista* l, casa* c, jogo* t);
void movimento_rei(lista* l, casa* c, jogo* t);

#endif