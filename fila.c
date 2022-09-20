#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Fila
// FIFO (first-in, first-out - Primeiro a entrar, primeiro a sair)
// É ideal para processamento de estruturas que devem manter a procedência de entrada;

typedef struct elementoFila { // Estrutura de cada elemento da fila. Serve para colocar elementos dentro da fila.
  char *dado;
  struct elementoFila *seguinte; //Ponteiro para que aponta para a próxima struct;
} elemento;

typedef struct filaPonteiro {
  elemento *primeiro; // ponteiro aponta para o elemento que está no início
  elemento *ultimo; // ponteiro que aponta para o elemento que está no fim.
  int tamanho;
} Fila;

Fila* criaFila() {
  Fila* fila = (Fila*)malloc(sizeof(Fila));
  inicializa(fila);
  return fila;
}

void inicializa(Fila *fila) {
  fila->primeiro = NULL;
  fila->ultimo = NULL;
  fila->tamanho = 0;
}

elemento* criaElemento(char *dado) {
  elemento *novo_elemento = (elemento*)malloc(sizeof(elemento)); //Alocação de memória para o elemento.
  novo_elemento->dado = (char *)malloc(50 * sizeof(char)); //Alocação de memória para dado.
  strcpy(novo_elemento->dado, dado);
  //novo_elemento->dado = dado;
  novo_elemento->seguinte = NULL; //Supondo que a lista está vazia. 
  return novo_elemento;
}

void enqueue(Fila *fila, elemento *atual, char *dado) { // elemento *atual seria o último elemento que esta na fila.
     // o elemento novo que vou querer inserir.
  elemento *novo_elemento = criaElemento(dado);

  if(atual == NULL) { //Verifica se a estrutura está vazia.
    if(fila->tamanho == 0) {
      fila->ultimo = novo_elemento;
    } // Deixa de apontar para Null e aponte para esse novo elemento.
    novo_elemento->seguinte = fila->primeiro; // O novo elemento começa a apontar para onde o primeiro estava apontando, no caso pra Null
    fila->primeiro = novo_elemento; // O início começa a apontar para o novo elemento.
    
  } else { // Quando já tem elemento na estrutura!
    if(atual->seguinte == NULL) {
      fila->ultimo = novo_elemento; // Muda último e faz apontar para o novo elemento.
    }
    novo_elemento->seguinte = atual->seguinte; // Faz novo elemento apontar para null. Mostra que é o ultimo lugar da fila, por isso apota para null.
    atual->seguinte = novo_elemento; // Faz o ponteiro do elemento que já estava antes e que estava apontando para null, apontar agora para o novo elemento.
  }
  fila->tamanho++;
}

void dequeue(Fila *fila) {
  elemento *elemento_aremover;

  if(fila->tamanho != 0) { // Verifica se a fila está vazia, ou seja, se não tem nada a remover...
    elemento_aremover = fila->primeiro; //salva para conseguir liberar espaço em seguida.
    fila->primeiro = fila->primeiro->seguinte; // O início vai apontar para o próximo depois do que queremos remover. 
    free(elemento_aremover->dado);
    free(elemento_aremover);
    fila->tamanho--;
  }
}

void list(Fila *fila) {
  elemento *aux;
  int i;
  aux = fila->primeiro; // Inicio da fila. Primeira posição da lista.

  for(i = 0; i < fila->tamanho; i++) {
    printf("Valor = %s\n", aux->dado);
    aux = aux->seguinte;
  }
}

void main() {
  Fila *fila = criaFila();
  int op;
  char *dado = (char*)malloc(50*sizeof(char));

  do {
    printf("\nO que voce quer fazer?\n\n");
    printf("1. Adicionar elementos na fila\n");
    printf("2. Remover elementos da fila\n");
    printf("3. Listar elementos da Fila\n");
    printf("4. Sair do programa\n");

    scanf("%d", &op);
    system("cls || clear");

    switch(op) {
      case 1:
        printf("Qual o string que voce quer inserir?\n");
        scanf("%s", dado);
        enqueue(fila, fila->ultimo, dado);
        break;
      case 2:
        dequeue(fila);
        break;
      case 3:
       list(fila);
        break;
      default:
        printf("Digite uma opcao valida\n");
    }
  } while(op != 4);
}

