#include <stdio.h>
#include <stdlib.h>
#include "lista.h"

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
    //printf("ini: p:%d %d %c\n", novo->ini->peca, tam_tab - novo->ini->lin, 97 + novo->ini->col);
    //printf("fim:     %d %c\n", tam_tab - novo->fim->lin, 97 + novo->fim->col);
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

lista* lista_busca(lista* l, casa* ini, casa* fim){
    // procura na lista uma jogada determinada
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
