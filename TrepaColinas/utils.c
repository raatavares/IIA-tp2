#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "utils.h"

// Leitura do ficheiro de input
// Recebe: nome do ficheiro, numero de vertices (ptr), numero de iteracoes (ptr)
// Devolve a matriz de adjacencias
int* init_dados(char *nome, int *n, int *iter)
{
	FILE *f;
	int *p;
	int i, j, lig, lin, col;
    char    str[100];
    char nome_fich[100]="../TestFiles/";
    strcat(nome_fich, nome);

	f=fopen(nome_fich, "r");
	if(!f)
	{
		printf("Erro no acesso ao ficheiro dos dados\n");
		exit(1);
	}
	// Numero de vertices
	fscanf(f, "k %d", n);
    while(strcmp(str,"edge"))
        fscanf(f,"%s",str);
    // Numero de vertices
    fscanf(f, "%d", n);
    // Numero de liga��es
    fscanf(f, "%d", &lig);
    // Alocacao dinamica da matriz
    p = malloc(sizeof(int)*(*n)*(*n));
    if(!p){
        printf("Erro na alocacao de memoria\n");
        exit(1);
    }
	// Preenchimento da matriz
    for(i=0; i<*n; i++)
        for(j=0; j<*n; j++)
            *(p+(*n)*i+j)=0;
    for(i=0; i<lig; i++){
        fscanf(f, " e %d %d", &lin, &col);
        *(p+(*n)*(lin-1)+col-1)=1;
        *(p+(*n)*(col-1)+lin-1)=1;
    }
    printf("N: %d\n", *n);
    for(i=0; i<*n; i++){
        for(j=0; j<*n; j++)
            printf("%d ", (*(p+(*n)*i+j)));
        printf("\n");}
	fclose(f);
	return p;
}

// Gera a solucao inicial
// Parametros: solucao, numero de vertices
void gera_sol_inicial(int *sol, int v)
{
	int i, x;

	for(i=0; i<v; i++)
        sol[i]=0;
	for(i=0; i<v/2; i++)
    {
        do
			x = random_l_h(0, v-1);
        while(sol[x] != 0);
        sol[x]=1;
    }
    return;
}

// Escreve solucao
// Parametros: solucao e numero de vertices
void escreve_sol(int *sol, int vert)
{
	int i;

	printf("\nConjunto A: ");
	for(i=0; i<vert; i++)
		if(sol[i]==0)
			printf("%2d  ", i);
	printf("\nConjunto B: ");
	for(i=0; i<vert; i++)
		if(sol[i]==1)
			printf("%2d  ", i);
	printf("\n");
    return;
}

// copia vector b para a (tamanho n)
void substitui(int a[], int b[], int n)
{
    int i;
    for(i=0; i<n; i++)
        a[i]=b[i];
    return;
}

// Inicializa o gerador de numeros aleatorios
void init_rand()
{
	srand((unsigned)time(NULL));
}

// Devolve valor inteiro aleatorio entre min e max
int random_l_h(int min, int max)
{
	return min + rand() % (max-min+1);
}

// Devolve um valor real aleatorio do intervalo [0, 1]
float rand_01()
{
	return ((float)rand())/RAND_MAX;
}
