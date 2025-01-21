#ifndef LISTA_H
#define LISTA_H

#include "xadrez.h"

lista* lista_cria();
void lista_insere(lista* l, casa* ini, casa* fim);
void lista_libera(lista* l);
lista* lista_busca(lista* l, casa* ini, casa* fim);
lista* lista_busca_fim(lista* l, casa* b);

#endif