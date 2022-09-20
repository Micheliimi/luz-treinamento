#include <stdio.h>
#include <stdlib.h>

// Lista Encadeada -> Aloca/memória de forma dinâmica e adiciona e remove elementos sob demanda.

typedef struct no {
  int valor; // valor que queremos armazenar
  struct no *proximo; // ponteiro para o próximo
} No; // nome que chamo estrutura

typedef struct {
  No *inicio;
  No *fim;
  int tamanho;
} Lista;

void inicializa(Lista *lista) {
  lista->inicio = NULL;
  lista->fim = NULL;
  lista->tamanho = 0;
}

No* criaNo(int valor) {
  No* novo = (No*)malloc(sizeof(No));

  novo->valor = valor;
  novo->proximo = NULL; //Supondo que a lista está vazia. 
  return novo;
}
  
Lista* criaLista() {
  Lista* lista = (Lista*)malloc(sizeof(Lista));
  inicializa(lista);
  return lista;
}

void inserirInicio(Lista* lista, int valor) {
  No *novo = criaNo(valor); // criar variável que vai receber nó chamado novo! Criando ponteiro!
  
  if (lista->inicio == NULL) { //Veridica se a lista está vazia ou não. Se está vazia... Senão..
    lista->inicio = novo; // É o primeiro
    lista->fim = novo; //E último
  } else {
    novo->proximo = lista->inicio; // O que estava antes no início vira o próximo
    lista->inicio = novo;
  }

  lista->tamanho++;
}

void inserirFim(Lista* lista, int valor) {
  No *novo = criaNo(valor);; // criar nó chamado novo! Criando ponteiro!
  
  if (lista->inicio == NULL) //Veridica se a lista está vazia ou não. Se está vazia... Senão..
  {
    lista->inicio = novo; // É o primeiro
    lista->fim = novo; //E último
  } else {
    lista->fim->proximo = novo; //ponteiro que aponta pro além aponte para esse novo ultimo elemento.
    lista->fim = novo;
  }
  
  lista->tamanho++; // para controlar o tamanho da lista sem ter que percorrer.
}

void removeInicio(Lista* lista) {
  //verifica se tem algo lá na lista.
  if(lista->inicio != NULL) {
    No *no = lista->inicio; //cria nó auxiliar e salva copia do primeiro elemento que estava salva
    lista->inicio = no->proximo; // põe o segundo elemento como primeiro
    lista->tamanho--; //retira no tamanho
    if(lista->inicio == NULL) // se retorna, significa que retirou todo. Caso esse retirado fosse o último!
      lista->fim = NULL;
    free(no);
  }
}

void removeQualquer(Lista *lista, int valor) // função genérica que retirar de acordo com o valor passado
{
  No *inicio = lista->inicio; //ponteiro nó auxiliar
  No *aRemover = NULL;
  
  if(inicio != NULL && lista->inicio->valor == valor) { //verifica se tem algo dentro da lista e se o primeiro valor já não é o prmeiro que está lá na lista
    aRemover = lista->inicio;
    lista->inicio = aRemover->proximo;//ponteiro aponta pra segundo nó
    if(lista->inicio == NULL) //segundo nó existe?
    {
      lista->fim = NULL;
    }
  }
  else {
    while(inicio != NULL /* fim da lista*/ && inicio->proximo /*verifica de o próximo é ultimo*/ != NULL && inicio->proximo->valor != valor /*proximo nó que contem valor é diferente do que estamos procurando*/ ) {
      inicio = inicio->proximo;
      //pra sair daqui é só quando a lista acabar ou encontrar o valor
    }
    //só entra no if se achar valor
    if(inicio != NULL && inicio->proximo != NULL) {
      aRemover = inicio->proximo; // valor encontrado!
      inicio->proximo = aRemover->proximo; //Muda apontamento para o proximo elemento
      if(inicio->proximo == NULL) // se for ultima posição
        lista->fim = NULL; // fim recebe null
    }
  }

  if(aRemover) {
    free(aRemover);
    lista->tamanho--;
  }
}

void imprime(Lista *lista) {
  No *atual = lista->inicio;
  printf("tamanho atual da lista = %d\n", lista->tamanho);
  
  while(atual != NULL) {
    printf("Valor = %d\n", atual->valor);
    atual = atual->proximo;
  }
}

int escolherValor() {
  int n;
  printf("Qual o numero que voce quer inserir ou remover?\n");
  scanf("%d", &n);
  return n;
}

void main () {
  Lista* lista = criaLista();
  int valor, i, op;
  int n;
  do {
    printf("\n\tO que voce quer fazer?\n\n");
    printf("1. Inserir no inicio\n");
    printf("2. Inserir no fim\n");
    printf("3. Remover no inicio\n");
    printf("4. Remover numero escolhido\n");
    printf("5. Imprimir lista\n");
    printf("6. Escolher numero a ser inserido ou removido\n");
    printf("7. Sair do programa\n");

    scanf("%d", &op);
    system("cls || clear");

    switch(op) {
      case 1:
        n =  escolherValor();
        inserirInicio(lista, n);
        break;
      case 2:
        n =  escolherValor();
        inserirFim(lista, n);
        break;
      case 3:
       removeInicio(lista);
        break;
      case 4:
        n =  escolherValor();
        removeQualquer(lista, n);
        break;
      case 5:
        imprime(lista);
        break;
      case 6:
        n =  escolherValor();
        break;
      default:
        printf("Digite uma opcao valida\n");
    }
  } while(op != 7);
}