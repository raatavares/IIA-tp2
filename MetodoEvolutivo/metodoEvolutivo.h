//
// Created by ricar on 06/01/2023.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define _CRT_SECURE_NO_WARNINGS 1
#define MAX_OBJ 1000

struct info
{
    // Tamanho da popula��o
    int     popsize;
    // Probabilidade de muta��o
    float   pm;
    // Probabilidade de recombina��o
    float   pr;
    // Tamanho do torneio para sele��o do pai da pr�xima gera��o
    int     tsize;
    // Constante para avalia��o com penaliza��o
    float   ro;
    // N�mero de objetos que se podem colocar na mochila
    int     numGenes;
    // Capacidade da mochila
    int     capacity;
    // N�mero de gera��es
    int     numGenerations;
};

// Individuo (solu��o)
typedef struct individual chrom, *pchrom;

struct individual
{
    // Solu��o (objetos que est�o dentro da mochila)
    int     p[MAX_OBJ];
    // Valor da qualidade da solu��o
    float   fitness;
    // 1 se for uma solu��o v�lida e 0 se n�o for
    int     valido;
};


int flip();
struct info init_data(char *filename, int mat[][2]);
pchrom init_pop(struct info d);
chrom get_best(pchrom pop, struct info d, chrom best);
void write_best(chrom x, struct info d);
float eval_individual(int sol[], struct info d, int mat[][2], int *v);

void evaluate(pchrom pop, struct info d, int mat[][2]);

void tournament(pchrom pop, struct info d, pchrom parents);
void genetic_operators(pchrom parents, struct info d, pchrom offspring);