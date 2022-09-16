/******************************************************************************

                            Online C Compiler.
                Code, Compile, Run and Debug C program online.
Write your code in this editor and press "Run" button to compile and execute it.

*******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

void alocaEspaco(int P[], int n) 
{
  P = (int*)malloc(n * sizeof (int));
}

void geraNumeros(int P[],int n)
{
  int i;
  alocaEspaco(P, n);
  
  for (i = 0; i < n; i+= 1) {
  P[i] = (rand() % n); 
  }
}

void imprimeLista(int P[], int n)
{
  int i;
  for (i = 0; i < n; i += 1)
  {
  printf("%4d", P[i]);
  }
}

void bubbleSort(int P[], int n) ////////////////// bubbleSort
{
  int i, j, aux, continua, fim;
  fim = n;
  do{
    continua = 0;
    for(i = 0; i < fim-1; i += 1) {
      if (P[i] > P[i + 1]) {
        aux = P[i];
        P[i] = P[i + 1];
        P[i + 1] = aux;
        continua = i;
      }
    }
    fim--;
  }while(continua != 0);
  
}

void insertionSort(int P[], int n) ///////////////// insertionSort - Vai levando menor número pra esqueda.
{
  int j, i, aux;
  
    for (i = 1; i < n; i += 1) {
      // inicia pelo segundo elemento.  
    
    aux = P[i];
    
    // se j não é o primeiro elemento e j/auxi atual é menor que o número anterior, continua o for!
    //Se não, volta com o próximo i.
    for(j = i; (j > 0) && (aux < P[j - 1]); j -= 1) {
      aux = P[j];
      P[j] = P[j - 1];
      P[j - 1] = aux;
    }
  }
}

/*-----------------------------------------------------------------------------------------------*/
int particiona(int P[], int comeco, int fim) {
  int esq, dir, pivo, aux;
  
  // dir - que avança
  esq = comeco;
  pivo = P[fim]; // Último elemento da lista
  
  //Esse for exlui o pivô (dir < fim).
  for (dir = comeco; dir < fim; dir +=1) {
    if (P[dir] <= pivo) {
        aux = P[dir];
        P[dir] = P[esq];
        P[esq] = aux;
        esq += 1; // Avança posição que guarda números menores
    }
  }
    
    // Põe pivô na posição certa dele, que vai ser uma posição depois dos números menores que ele.
  aux = P[esq];
  P[esq] = P[fim];
  P[fim] = aux;
  
  //retorna índice do pivô na posição certa. Próxima partição vai excluir ele.
  return esq;
}

/* Escolhe o pivô
Passa pra esquerda dele os números menores que ele
Passa pra direita os numeros maiores
No fim poẽ pivô no lugar certo e..
Divide duas partes, escolhe novo pivô e faz o mesmo procedimento


---> Vantagens: Não precisa de Vetor Auxilar (não gasta memória extra) e 
no melhor caso, apresenta O(n log n).
---> Desvantagem: pode apresentar, no pior caso, O(n²) 
Pior caso - vetor ordenado ou quase ordenado
Ao escolher o pivô em extremidades, um lado fica vazio e outro fica n-1
Pega o lado que não ta vazio e repete
Se o vetor estivesse desordenado, em cada passo, ia ordenado mais números*/
void quickSort(int P[], int comeco, int fim) {
  int pivo;
      
  if(comeco < fim) {
    pivo = particiona(P, comeco, fim);
    quickSort(P, comeco, pivo - 1); // Não inclui o pivô
    quickSort(P, pivo + 1, fim); // Não inclui o pivô
  }
}
/*--------------------------------------------------------------------------------------------------------*/

void selectionSort(int P[], int n) ///////////////// selectionSort - Procura primeiro menor elemento e troca 
//com a posição do i, lista fica ordenada conforme i vai acrescentando e j achando o menor.
{
  int j, i, aux, minIndex;
  
  for (j = 0; j < n; j += 1) {
    minIndex = j;
    
    for(i = j; i < n; i += 1) { 
      if (P[i] < P[minIndex]) {
        minIndex = i;
      }
    }
    if (P[j] > P[minIndex]) {
      aux = P[j];
      P[j] = P[minIndex];
      P[minIndex] = aux;
    }
  }
}

void merge(int P[], int comeco, int meio, int fim) {
  int com1, com2, comAux, tam;
  int *vetAux; // Vetor Auxiliar. 

  com1 = comeco;
  com2 = meio+1;
  comAux = 0;
  tam = fim-comeco+1;

  vetAux = (int*)malloc(tam * sizeof(int));

  /*Enquanto ainda existem as duas metade para combinar... É interrompido, quando uma das metades acabam*/
  while(com1 <= meio && com2 <= fim){
    /* Comparo primeiro valor dispinível de um com primeiro valor disponível do outro.*/
    if(P[com1] < P[com2]) {
      /*Vou salvando o menor no vetor auxiliar e passando para o próximo elemento do vetor auxliar e da metade que tiver tirado o menor*/
      vetAux[comAux] = P[com1];
      com1++;
    } else {
      vetAux[comAux] = P[com2];
      com2++;
    }
    comAux++;
  }

  while(com1 <= meio){  //Caso ainda haja elementos na primeira metade, vou salvando no vetor auxiliar os números restantes
    vetAux[comAux] = P[com1];
    comAux++;
    com1++;
  }

  while(com2 <= fim) {   //Caso ainda haja elementos na segunda metade, vou salvando no vetor auxiliar os números restantes
    vetAux[comAux] = P[com2];
    comAux++;
    com2++;
  }

  for(comAux = comeco; comAux <= fim; comAux++){ //Move os elementos de volta para o vetor original
    P[comAux] = vetAux[comAux-comeco];
  }
  
  free(vetAux); //Libera memória do vetor auxiliar
}


/*
Lema: Dividir para conquistar!
Divido no meio até sobrar um elemento. Depois os elementos vão sendo combinados/megeados de forma ordenada.

O mergeSort vai trabalhar com RECURSÃO.
São modelagens de funções que, para resolver um problema
faz chamadas a si mesma, simplificando a solução quebrando a problema
em subproblemas do mesmo tipo.

Vantagens: complexidade de tempo, tanto no melhor, quanto no pior caso é de O(n log n) - No melhor caso 
ou médio, é equivalente à complexidade do quick sort;
Desvantagem: Faz uso de n unidades (O(n)) de memória auxiliar. É necessário um vetor auxiliar.
*/
void mergeSort(int P[], int comeco, int fim) {
  /* O vetor será dividido até restar um elemento*/
  int meio;
  if(comeco < fim) {
    meio = floor((comeco+fim)/2); // Precisa arrendondar
    
    
    mergeSort(P, comeco, meio);
    mergeSort(P, meio + 1, fim);
    
    merge(P, comeco, meio, fim);
  }
}


int main()
{
  int i, aux, j;
  int op;
  long int n;
  
  printf("Quantos registros vocês quer inserir no vetor?\n");
  scanf("%ld", &n);
  int *P;
  geraNumeros(P, n);
  imprimeLista(P, n);
  
  do
  {
    printf("\n\tQual método de ordenação você quer usar?\n\n");
    printf("1. Bubble Sort\n");
    printf("2. Insertion Sort\n");
    printf("3. Selection Sort\n");
    printf("4. Merge Sort\n");
    printf("5. Quick Sort\n");
    printf("6. Sair do programa\n");

    scanf("%d", &op);
    system("cls || clear");

    switch(op)
    {
      case 1:
          bubbleSort(P, n);
          imprimeLista(P, n);
          break;
      case 2:
          insertionSort(P, n);
          imprimeLista(P, n);
          break;
      case 3:
          selectionSort(P, n);
          imprimeLista(P, n);
          break;
        case 4:
          mergeSort(P, 0, n-1);
          imprimeLista(P, n);
          break;
      case 5:
          quickSort(P, 0, n-1);
          imprimeLista(P, n);
          break;

      default:
          printf("Digite uma opcao valida\n");
    }
  } while(op != 6);
}
