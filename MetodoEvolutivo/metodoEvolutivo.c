//
// Created by ricar on 06/01/2023.
//

#include "metodoEvolutivo.h"
#include "common.h"

int flip()
{
    if ((((float)rand()) / RAND_MAX) < 0.5)
        return 0;
    else
        return 1;
}

struct info init_data(char *filename, int mat[][2]){
    struct  info x;
    FILE    *f;
    int     i, j, n, lig, lin, col;
    char str[10];
    char nome_fich[100]="../TestFiles/";
    strcat(nome_fich, filename);

    f=fopen(nome_fich, "r");
    if (!f)
    {
        printf("File not found\n");
        exit(1);
    }
    // Leitura dos par�metros do problema
    x.popsize=100;
    x.pr=0.7;
    x.pm=0.001;
    x.tsize=2;
    x.numGenerations=2.5000;
    x.ro=0.0;
    x.capacity=500;
    fscanf(f, "k %d", &n);
    while(strcmp(str,"edge"))
        fscanf(f,"%s",str);
    // Numero de vertices
    fscanf(f, "%d", &x.numGenes);
    // Numero de liga��es2

    fscanf(f, "%d", &lig);

    for (i=0; i<x.numGenes; i++) {
        int p, q;
        fscanf(f, " e %d %d", &mat[i][0], &mat[i][1]);
    }
    return x;
}

pchrom init_pop(struct info d){
    int     i, j;
    pchrom  indiv;

    indiv = malloc(sizeof(chrom)*d.popsize);
    if (indiv==NULL)
    {
        printf("Erro na alocacao de memoria\n");
        exit(1);
    }
    for (i=0; i<d.popsize; i++)
    {
        for (j=0; j<d.numGenes; j++)
            indiv[i].p[j] = flip();
    }
    return indiv;
}

chrom get_best(pchrom pop, struct info d, chrom best){
    int i;

    for (i=0; i<d.popsize; i++)
    {
        if (best.fitness < pop[i].fitness)
            best=pop[i];
    }
    return best;
}

void write_best(chrom x, struct info d){
    int i;

    printf("\nBest individual: %4.1f\n", x.fitness);
    for (i=0; i<d.numGenes; i++)
        printf("%d", x.p[i]);
    putchar('\n');
}

float eval_individual(int sol[], struct info d, int mat[][2], int *v)
{
    int     i;
    float   sum_weight, sum_profit;

    sum_weight = sum_profit = 0;
    // Percorre todos os objectos
    for (i=0; i < d.numGenes; i++)
    {
        // Verifica se o objecto i esta na mochila
        if (sol[i] == 1)
        {
            // Actualiza o peso total
            sum_weight += mat[i][0];
            // Actualiza o lucro total
            sum_profit += mat[i][1];
        }
    }
    if (sum_weight > d.capacity)
    {
        // Solucao inv�lida
        *v = 0;
        return 0;
    }
    else
    {
        // Solucao v�lida
        *v = 1;
        return sum_profit;
    }
}

void evaluate(pchrom pop, struct info d, int mat[][2]){
    int i;

    for (i=0; i<d.popsize; i++)
        pop[i].fitness = eval_individual(pop[i].p, d, mat, &pop[i].valido);
}

void tournament(pchrom pop, struct info d, pchrom parents){
    int i, x1, x2;

    // Realiza popsize torneios
    for(i=0; i<d.popsize;i++)
    {
        x1 = random_l_h(0, d.popsize-1);
        do
            x2 = random_l_h(0, d.popsize-1);
        while(x1==x2);
        if(pop[x1].fitness > pop[x2].fitness)		// Problema de maximizacao
            parents[i]=pop[x1];
        else
            parents[i]=pop[x2];
    }
}

void crossover(pchrom parents, struct info d, pchrom offspring)
{
    int i, j, point;

    for (i=0; i<d.popsize; i+=2)
    {
        if (rand_01() < d.pr)
        {
            point = random_l_h(0, d.numGenes-1);
            for (j=0; j<point; j++)
            {
                offspring[i].p[j] = parents[i].p[j];
                offspring[i+1].p[j] = parents[i+1].p[j];
            }
            for (j=point; j<d.numGenes; j++)
            {
                offspring[i].p[j]= parents[i+1].p[j];
                offspring[i+1].p[j] = parents[i].p[j];
            }
        }
        else
        {
            offspring[i] = parents[i];
            offspring[i+1] = parents[i+1];
        }
    }
}

void mutation(pchrom offspring, struct info d)
{
    int i, j;

    for (i=0; i<d.popsize; i++)
        for (j=0; j<d.numGenes; j++)
            if (rand_01() < d.pm)
                offspring[i].p[j] = !(offspring[i].p[j]);
}

void genetic_operators(pchrom parents, struct info d, pchrom offspring){
    // Recombina��o com um ponto de corte
    crossover(parents, d, offspring);
    // Muta��o bin�ria
    mutation(offspring, d);
}