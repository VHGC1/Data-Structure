#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct conta{
  char nome[100];
  char conta[10];
  char saldo[10];
  int saldo_int;
}conta;

//função para ler o numero de linhas que o arquivo tem
int numberOfLines(char url[100]){

  FILE *arq;

  char c, letra = '\n';

  int vezes = 0;

  arq = fopen(url,"r");

  //Lendo o arquivo 1 por 1
  while(fread (&c, sizeof(char), 1, arq)) {// enquanto for true vai ler o arquivo e depois contar
    if(c == letra) {
       vezes++;
    }
  } 

  fclose(arq);
  
  return vezes + 1;//retorna o numero de linhas do arquivo
}

//Ordenação por inserção
void insertionSortSaldo(struct conta *V, int N){// recebe o vetor struct e o tamanho dele
  int i, j;
  struct conta aux;

  for( i = 1; i < N; i++){
    aux = V[i];
    for( j = i; (j > 0) && ( aux.saldo_int < V[j - 1].saldo_int); j-- )
      V[j] = V[j - 1];
    V[j] = aux;
  }
}

//ordenação por seleção
void selectionSortSaldo(struct conta *V, int N){   
  int i, j, menor;
  struct conta aux;
  
  for(i = 0; i < N - 1; i++){
    menor = i;
    for(j = i + 1; j < N; j++){
      if(V[menor].saldo_int > V[j].saldo_int){
        menor = j;
        }
      if(i != menor){
        aux = V[i];
        V[i] = V[menor];
        V[menor] = aux;
      }
    }   
  }
}

int main(){

  int i = 0, op;//variavel utilizada nos laços for e variavel utilizada para o menu de opções
  
	char novo[10];//varavel que recebe o nome do novo arquivo

	char url[100];//variavel que vai receber o nome do arquivo a ser lido

	//input para selecionar o aruivo a ser lido
	printf("Entre com o nome do arquivo desejado e o tipo(com ponto):");
	scanf("%s", &url);

	int n = (numberOfLines(url))/3;//a função recebe o nome do arquivo

  struct conta contas[n];//declaração de vetor do tipo estruct conta

	FILE *file = fopen(url, "r");//abrindo arquivo no modo de leitura

  if(file == NULL){
    printf("Nao foi possivel abrir arquivo.");
  }
   
  while (!feof(file)){ //captura dos dados seguindo o modelo
    fgets(contas[i].nome, sizeof(contas[i].nome), file);
    fgets(contas[i].conta, sizeof(contas[i].conta), file);
    fgets(contas[i].saldo, sizeof(contas[i].saldo), file);
    contas[i].saldo_int = atoi(contas[i].saldo); //passando os dados do tipo char para int
    i++;
  };

  fclose(file); 

	if(file == NULL){//caso o arquivo não seja encontrado é impresso na tela 
    printf("Arquivo nao pode ser aberto.");
    getchar();
    exit(1); 
  }

  while(op != 3){
    printf("Selecione a opcao de ordenacao desejada!");
    printf("\n[ 1 ] Ordenacao por insercao\n[ 2 ] Ordenacao por selecao\n[ 3 ] Sair\n");
    printf("Opcao desejada:");
    scanf("%d", &op);

    if(op == 1){
			/*
				chamada da ordenação que recebe como parametro o struct e o tomanho do struct
			*/
      insertionSortSaldo(contas,n);
      printf("[ 1 ] Ver os dados ordenados na tela\n[ 2 ] Gerar um novo arquivo\n");
      printf("Opcao desejada: ");
      scanf("%d", &op);
      if(op == 1){
				//impressão dos valores na tela
        for(i = 0; i < n; i++){
					printf("%s%s%d\n", contas[i].nome, contas[i].conta, contas[i].saldo_int);//
        }
      }else if(op == 2){
				//entrada do nome do novo arquivo a ser gerado
        printf("Entre com o nome do novo arquivo: ");
        scanf("%s", &novo);

        printf("%s gerado!\n", novo);

        FILE *file = fopen(novo, "w");

				//impressão no arquivo das contas
        for(i = 0; i < n; i++){
          fprintf(file, "%s", contas[i].nome);
          fprintf(file, "%s", contas[i].conta);
          fprintf(file, "%d\n", contas[i].saldo_int);
        }

        fclose(file);
      }
    }

		else if(op == 2){
      selectionSortSaldo(contas, n);
      printf("[ 1 ] Ver os dados ordenados na tela\n[ 2 ] Gerar um novo arquivo\n");
      printf("Opcao desejada: ");
      scanf("%d", &op);
      if(op == 1){
        for(i = 0; i < 3; i++){
					printf("%s%s%d\n", contas[i].nome, contas[i].conta, contas[i].saldo_int);
        }
      }else if(op == 2){
        printf("Entre com o nome do novo arquivo: ");
        scanf("%s", &novo);

        printf("%s", novo);

        FILE *file = fopen(novo, "w");

        for(i = 0; i < n; i++){
          fprintf(file, "%s", contas[i].nome);
          fprintf(file, "%s", contas[i].conta);
          fprintf(file, "%d\n", contas[i].saldo_int);
        }

        fclose(file);
      }

    }
  }
  
  system("pause");
  return 0;
}


