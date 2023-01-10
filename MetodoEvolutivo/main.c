#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "main.h"
#include "MetodoEvolutivo/metodoEvolutivo.h"
#include "MetodoEvolutivo/common.h"
#define DEFAULT_RUNS  100
int runs;

void inicioEvolutivo(char* nome_fich) {
    struct info EA_param;
    pchrom      pop = NULL, parents = NULL;
    chrom       best_run, best_ever;
    int         gen_actual, r, i, inv, mat[MAX_OBJ][2];
    float       mbf = 0.0;

    init_rand();

    EA_param = init_data(nome_fich, mat);
    for (r = 0; r < runs; r++)
    {
        mbf = 0.0;
        printf("Repeticao %d\n", r + 1);
        // Gera��o da popula��o inicial
        pop = init_pop(EA_param);
        // Avalia a popula��o inicial
        evaluate(pop, EA_param, mat);
        // Como ainda n�o existe, escolhe-se como melhor solu��o a primeira da popula��o (poderia ser outra qualquer)
        best_run = pop[0];
        // Encontra-se a melhor solu��o dentro de toda a popula��o
        best_run = get_best(pop, EA_param, best_run);
        // Reserva espa�o para os pais da popula��o seguinte
        parents = malloc(sizeof(chrom) * EA_param.popsize);
        // Caso n�o consiga fazer a aloca��o, envia aviso e termina o programa
        if (parents == NULL)
        {
            printf("Erro na alocacao de memoria\n");
            exit(1);
        }
        // Ciclo de optimiza��o
        gen_actual = 1;
        while (gen_actual <= EA_param.numGenerations)
        {
            // Torneio bin�rio para encontrar os progenitores (ficam armazenados no vector parents)
            tournament(pop, EA_param, parents);
            // Aplica os operadores gen�ticos aos pais (os descendentes ficam armazenados na estrutura pop)
            genetic_operators(parents, EA_param, pop);
            // Avalia a nova popula��o (a dos filhos)
            evaluate(pop, EA_param, mat);
            // Actualiza a melhor solu��o encontrada
            best_run = get_best(pop, EA_param, best_run);
            gen_actual++;
        }
        // Contagem das solu��es inv�lidas
        for (inv = 0, i = 0; i < EA_param.popsize; i++)
            if (pop[i].valido == 0)
                inv++;
        // Escreve resultados da repeti��o que terminou
        printf("\nRepeticao %d:", r);
        write_best(best_run, EA_param);
        printf("\nPercentagem Invalidos: %f\n", 100*(float)inv/EA_param.popsize);
        mbf += best_run.fitness;
        if (r == 0 || best_run.fitness > best_ever.fitness)
            best_ever = best_run;
        // Liberta a mem�ria usada
        free(parents);
        free(pop);
    }
    // Escreve resultados globais
    printf("\n\nMBF: %f\n", mbf / r);
    printf("\nMelhor solucao encontrada");
    write_best(best_ever, EA_param);
    return;
}

int main(){
    char nome_fich[100], c;
    int op;

    printf("Introducao a Inteligencia Artificial\n");
    printf("TP2 - Problema de Otimizacao");

    do{
        do{
            printf("\n\n--------------------------------------------------------------\n\n");
            printf("         1- Algoritmo evolutivo \n");
            printf("         2- Sair \n\n");
            printf("--------------------------------------------------------------\n\n");
            printf(">>Opcao: ");
            scanf("%d", &op);
        }while(op<1 || op>2);
        if (op != 2) {
            printf(">>Nome do Ficheiro: ");
            scanf("%s", nome_fich);
            do{
                printf(">>Deseja alterar o numero de execucoes(s/n)? (Omissao: 10) ");
                scanf(" %c", &c);
            }while(c != 's' && c !='n');

            if(c == 's'){
                printf(">>Insira o numero de execucoes que deseja: ");
                scanf("%d", &runs);
            }
            else
                runs = DEFAULT_RUNS;
            if(runs <= 0)
                return 1;
            if (op == 1) {
                inicioEvolutivo(nome_fich);
            }
        }
    }while(op != 2);

    return 1;
}