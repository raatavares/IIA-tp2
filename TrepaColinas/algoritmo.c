#include <stdio.h>
#include <stdlib.h>
#include "algoritmo.h"
#include "funcao.h"
#include "utils.h"
#include "main.h"


// Gera um vizinho
// Parametros: solucao actual, vizinho, numero de vertices
//swap two vertices
void gera_vizinho1(int a[], int b[], int n)
{
    int i, p1, p2;

    // Copia a solu��o atual para a solu��o vizinha
    for(i = 0; i < n; i++)
        b[i] = a[i];
    // Encontra aleatoriamente a posi��o de um v�rtice com valor 0
    do
        p1 = random_l_h(0, n-1);
    while(b[p1] != 0);
    // Encontra aleatoriamente a posi��o de um v�rtice com valor 1
    do
        p2 = random_l_h(0, n-1);
    while(b[p2] != 1);
    // Troca os valores dos v�rtices das posi��es encontradas
    b[p1] = 1;
    b[p2] = 0;
}

// Gera um vizinho
// Parametros: solucao actual, vizinho, numero de vertices
//swap two vertices
void gera_vizinho(int a[], int b[], int n)
{
    int i, p1, p2;

    // Copia a solu��o atual para a solu��o vizinha
    for(i = 0; i < n; i++)
        b[i] = a[i];
    // Encontra aleatoriamente a posi��o de um v�rtice com valor 0
    do
        p1 = random_l_h(0, n-1);
    while(b[p1] != 0);
    // Encontra aleatoriamente a posi��o de um v�rtice com valor 1
    do
        p2 = random_l_h(0, n-1);
    while(b[p2] != 1);
    // Troca os valores dos v�rtices das posi��es encontradas
    b[p1] = 1;
    b[p2] = 0;
}

void gera_vizinho2(int a[], int b[], int n)
{
    int i, p1, p2, p3, p4;

    // Copia a solu��o atual para a solu��o vizinha
    for(i = 0; i < n; i++)
        b[i] = a[i];
    // Encontra aleatoriamente a posi��o de um v�rtice com valor 0
    do
        p1 = random_l_h(0, n-1);
    while(b[p1] != 0);
    // Encontra aleatoriamente a posi��o de um v�rtice com valor 1
    do
        p2 = random_l_h(0, n-1);
    while(b[p2] != 1);
    // Troca os valores dos v�rtices das posi��es encontradas
    b[p1] = 1;
    b[p2] = 0;
    // Encontra aleatoriamente a posi��o de um v�rtice, que n�o seja igual a p2, com valor 0
    do
        p3 = random_l_h(0, n-1);
    while(b[p3] != 0 || p3 == p2);
    // Encontra aleatoriamente a posi��o de um v�rtice, que n�o seja igual a p1, com valor 1
    do
        p4 = random_l_h(0, n-1);
    while(b[p4] != 1 || p4 == p1);
    // Troca os valores dos v�rtices das posi��es encontradas
    b[p3] = 1;
    b[p4] = 0;
}

// Trepa colinas first-choice
// Parametros: solucao, matriz de adjacencias, numero de vertices e numero de iteracoes
// Devolve o custo da melhor solucao encontrada
int trepa_colinas(int sol[], int *mat, int vert, int num_iter, int k)
{
    int *nova_sol, custo, custo_viz, i;

	nova_sol = malloc(sizeof(int)*vert);
    if(nova_sol == NULL)
    {
        printf("Erro na alocacao de memoria");
        exit(1);
    }
	// Avalia solucao inicial
    custo = calcula_fit(sol, mat, k);
    for(i=0; i<num_iter; i++)
    {
        // Gera vizinho
		gera_vizinho(sol, nova_sol, k);
		// Avalia vizinho
		custo_viz = calcula_fit(nova_sol, mat, k);
		// Aceita vizinho se o custo diminuir (problema de minimizacao)
        if(custo_viz >= custo)
        {
			substitui(sol, nova_sol, k);
			custo = custo_viz;
        }
    }
    free(nova_sol);
    return custo;
}

int trepa_colinas2(int *sol, int *mat, int vert, int num_iter){
    int *nova_sol, custo, custo_viz, i, op;

    nova_sol = malloc(sizeof(int)*vert);
    if (nova_sol == NULL){
        printf("Erro na alocacao de memoria");
        return 0;
    }
    // Avalia solu��o inicial
    custo = calcula_fit(sol, mat, vert);
    for(i = 0; i < num_iter; i++){
        // Gera solu��o vizinha
        gera_vizinho1(sol, nova_sol, vert);
        // Avalia solu��o vizinha
        custo_viz = calcula_fit(nova_sol, mat, vert);
        // Fica com a solu��o vizinha se o custo aumentar (problema de maximiza��o) em rela��o � solu��o atual
        if (custo_viz >= custo){
            substitui(sol, nova_sol, vert);
            custo = custo_viz;
        }
    }
    free(nova_sol);
    return custo;
}
