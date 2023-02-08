#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct node_fila {
    char letra;
    struct node_fila *next;
}node_fila;

typedef struct fila {
    struct node_fila *inicio;
    struct node_fila *fim;
}fila;

typedef struct node_pilha {
    struct node_pilha *next;
    struct fila *fila;
}node_pilha;

typedef struct pilha {
    struct node_pilha *topo;
}pilha;

int num_filas; // Conta quantas filas tem
int conta_copos;

pilha* cria_pilha() {
    pilha *pi = (pilha*)malloc(sizeof(pilha));

    if(pi != NULL) {
        pi->topo = NULL;
    }
    return pi;
}

void insere_pilha(pilha *pi, fila *fi) {
    node_pilha *novo = (node_pilha*)malloc(sizeof(node_pilha));
    novo->next = NULL;
    novo->fila = fi;
    if(pi->topo == NULL) {
        pi->topo = novo;
    } else {
        novo->next = pi->topo;
        pi->topo = novo;
    }
}

void mostra_pilha(pilha *pi, int copos) {
    node_fila *aux_fila; 
    node_pilha *aux_pilha;
    int spaces = (ceil((-1+sqrt(1+8*copos))/2)) - 1;
    if(pi->topo == NULL) {
        printf("Pilha VAZIA");
    } else {
        aux_pilha = pi->topo;
        while(aux_pilha != NULL){ 
            aux_fila = aux_pilha->fila->inicio;
            for(int i = 0; i<spaces; i++) {
                printf(" ");
            }
            while(aux_fila != NULL) { 
                printf("%c ", aux_fila->letra); 
                aux_fila = aux_fila->next;
                conta_copos++; 
            }
            spaces--;
            num_filas++;
            aux_pilha = aux_pilha->next;
            printf("         Copos: %d", conta_copos);
            printf("\n");
            conta_copos = 0; 
        }
    }
}

fila* cria_fila() {
    //Iniciamos uma fila vazia
    fila *fi = (fila*)malloc(sizeof(fila));
    if(fi != NULL) {
        fi->inicio = NULL;
        fi->fim = NULL;
    }

    return fi;
}

void insere_fila(fila *fi, char letra) {
    node_fila *novo = (node_fila*)malloc(sizeof(node_fila));
    novo->letra = letra;
    novo->next = NULL;

    if(fi->inicio == NULL) {
        //printf("Fila vazia");
        fi->inicio = novo;
        fi->fim = novo;
    } else {
        fi->fim->next = novo;
        fi->fim = novo;
    }
}

void mostra_fila(fila *fi) {
    node_fila *aux;
    if(fi->inicio == NULL) {
        printf("FILA VAZIA");
    } else {
        aux = fi->inicio;
        while(aux != NULL) {
            printf("%c", aux->letra);
            aux = aux->next;
        }
    }
}

void mostra_copos(pilha *pi, int copos) {
    char letra = 'a';
    int copos_res;
    copos_res = copos;
    int formula_base = ceil((-1+sqrt(1+8*copos_res))/2);

    for(int i = 0; i<formula_base; i++){ 
        fila *fi = cria_fila();
        for(int j = 0; j < ceil((-1+sqrt(1+8*copos_res))/2); j++) {
            insere_fila(fi, letra);
            letra += 1;
        }
        copos_res = copos_res - ceil((-1+sqrt(1+8*copos_res))/2);
        insere_pilha(pi,fi);
    }
    mostra_pilha(pi, copos);
    printf("\nQuantidade de Filas: %d\n\n", num_filas);
    printf("\nTotal de Copos: %d", copos);
}

void main() {
    int copos;
    pilha *pi = cria_pilha();

    do {
        printf("Digite uma quantia de copos: ");
        fflush(stdout);
        scanf("%d", &copos);
    } while(copos <= 0 || copos > 26);

    mostra_copos(pi, copos);
}
