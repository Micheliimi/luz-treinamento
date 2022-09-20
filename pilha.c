#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Pilha

typedef struct elementoPilha {
  char *dado; // Se fosse inteiro, não precisaria de alocar dinâmicamente e nem alocar espaço.
  struct elementoPilha *seguinte;
} Elemento;

typedef struct pilhaPonteiro {
  Elemento *topo; // ponteiro aponta para o elemento que está no início
  int tamanho;
} Pilha;

void inicializa(Pilha *pilha) {
  pilha->topo = NULL;
  pilha->tamanho = 0;
}

Pilha* criaPilha() {
  Pilha* pilha = (Pilha*)malloc(sizeof(Pilha));
  inicializa(pilha);
  return pilha;
}

Elemento* criaElemento(char *dado) {
 Elemento *novo_elemento = (Elemento*)malloc(sizeof(Elemento)); //Alocação de memória para o elemento.
  novo_elemento->dado = (char *)malloc(50 * sizeof(char)); //Alocação de memória para dado.
  strcpy(novo_elemento->dado, dado);
  return novo_elemento;
}

void push_pilha(Pilha *pilha, char* dado) {
  Elemento *novo_elemento = criaElemento(dado);
  novo_elemento->seguinte = pilha->topo;
  pilha->topo = novo_elemento;
  pilha->tamanho++;
}

void pop_pilha(Pilha *pilha) {
  Elemento *remove_elemento;
  if(pilha->tamanho != 0) {
    remove_elemento = pilha->topo; // Põe elememento do topo e salvando num aux para desalocar a memória!
    pilha->topo = pilha->topo->seguinte; // Faz topo apontar para o seguinte do elemento a remover
    free(remove_elemento->dado);
    free(remove_elemento); // Remover memória da estrutura!
    pilha->tamanho--;
  }
}

void list(Pilha *pilha) {
  Elemento *aux;
  int i;
  aux = pilha->topo; // Inicio da fila. Primeira posição da lista.

  for(i = 0; i < pilha->tamanho; i++) {
    printf("Valor = %s\n", aux->dado);
    aux = aux->seguinte;
  }
}

void main() {
  Pilha *pilha = criaPilha();
  int op;
  
  char *dado = (char*)malloc(50*sizeof(char));

  do {
    printf("\nO que voce quer fazer?\n\n");
    printf("1. Adicionar elementos na pilha\n");
    printf("2. Remover elementos da pilha\n");
    printf("3. Listar elementos da pilha\n");
    printf("4. Sair do programa\n");

    scanf("%d", &op);
    system("cls || clear");

    switch(op) {
      case 1:
        printf("Qual o string que voce quer inserir?\n");
        scanf("%s", dado);
        push_pilha(pilha, dado);
        break;
      case 2:
        pop_pilha(pilha);
        break;
      case 3:
       list(pilha);
        break;
      default:
        printf("Digite uma opcao valida\n");
    }
  } while(op != 4);
}