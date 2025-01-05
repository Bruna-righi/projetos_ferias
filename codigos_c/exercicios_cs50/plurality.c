#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX 9

struct Case{
    char* nome;
    int votos;
};

typedef struct Case candidato;

char* inicializa_string(){
    char* temp = (char*) malloc(sizeof(char)*30);
    return temp;
}

void le_votos(candidato* candidates){
    printf("Quantos votos: ");
    int n;
    char* temp = inicializa_string();
    scanf("%i", &n);
    for(int i = 0; i < n; i++){
        fgets(temp, 30, stdin);
        bool valido = false;
        for (int j = 0; j < MAX; j++){
            if(strcpm(temp, candidates[j].nome) == 0){
                candidates[j].votos++;
                valido = true;
                break;
            }
        }
        if(!valido){
            printf("Voto inválido!\n");
        }
    }
}

void winner(candidato* candidates){
    
}

int main(int argc, char* argv[]){
    if(argc < 2){
        printf("Digite pelo menos 1 candidato.\n");
        return 1;
    }
    int n_candidates = argc - 1;
    if(n_candidates > MAX){
        printf("Você ultrapassou o limite de candidatos, que é %d.\n", MAX);
        return 2;
    }
    candidato candidates[argc-1];
    //inicialização
    for(int i = 0; i < argc - 1; i++){
        candidates[i].nome = inicializa_string();
        strcpy(candidates[i].nome, argv[i+1]);
        candidates[i].votos = 0;
    }
    le_votos(candidates);
    winner(candidates);

}