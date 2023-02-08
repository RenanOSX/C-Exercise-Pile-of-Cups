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
    pilha *pi = (pilha*)malloc(sizeof(pilha)); //Aloca memoria pra pilha

    if(pi != NULL) {
        pi->topo = NULL; //Se a pilha acabou de ser criada ela é vazia e logo seu topo também
    }
    return pi;
}

void insere_pilha(pilha *pi, fila *fi) {
    node_pilha *novo = (node_pilha*)malloc(sizeof(node_pilha)); //Aloca um node pra pilha
    novo->next = NULL; //Proximo do novo node como vazio
    novo->fila = fi; //Aponta o node da pilha pra fila
    if(pi->topo == NULL) {
        pi->topo = novo; //Ponteiro do topo aponta para o novo
    } else {
        novo->next = pi->topo; //O próximo do novo aponta pro antigo topo
        pi->topo = novo; //Topo antigo aponta pro novo
    }
}

void mostra_pilha(pilha *pi, int copos) {
    node_fila *aux_fila; //Ponteiro auxiliar que aponta pra fila
    node_pilha *aux_pilha; //Ponteiro auxiliar que sempre aponta pro topo da pilha;
    int spaces = (ceil((-1+sqrt(1+8*copos))/2)) - 1; //Define a quantia de espaços com base na altura da pilha
    if(pi->topo == NULL) {
        printf("Pilha VAZIA");
    } else {
        aux_pilha = pi->topo;
        while(aux_pilha != NULL){ //Enquanto o topo tiver coisas dentro
            aux_fila = aux_pilha->fila->inicio;
            for(int i = 0; i<spaces; i++) {
                printf(" ");
            }
            while(aux_fila != NULL) { //Enquanto o inicio da fila NÃO for vazio
                printf("%c ", aux_fila->letra); //Mostra a letra daquela fila
                aux_fila = aux_fila->next; // Vai pro proximo nó da fila
                conta_copos++; //Cada letra printada = +1 copo no contador
            }
            spaces--;
            num_filas++;
            aux_pilha = aux_pilha->next; // Vai pro proximo elemento da pilha
            printf("         Copos: %d", conta_copos);
            printf("\n");
            conta_copos = 0; //Depois de printar a linha de copos ele 0 para contar a próxima linha
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
    novo->letra = letra; //Adiciona a letra dentro do novo espaço alocado
    novo->next = NULL; //Aponta o próximo do novo elemento para NULL

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
    copos_res = copos; // Quantia restante igual o total de copos
    int formula_base = ceil((-1+sqrt(1+8*copos_res))/2);

    for(int i = 0; i<formula_base; i++){ //Repete para cada LINHA DA PILHA
        fila *fi = cria_fila();
        for(int j = 0; j < ceil((-1+sqrt(1+8*copos_res))/2); j++) { //Adiciona letras de acordo com o andar pilha
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
    pilha *pi = cria_pilha(); //Inicializa Pilha

    do {
        printf("Digite uma quantia de copos: ");
        fflush(stdout);
        scanf("%d", &copos);
    } while(copos <= 0 || copos > 26);

    mostra_copos(pi, copos);
}
