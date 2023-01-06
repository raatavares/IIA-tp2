#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "main.h"
#include "TrepaColinas/algoritmo.h"
#include "TrepaColinas/utils.h"
#define DEFAULT_RUNS  10
int runs;

void inicioTrepaColinas(char* nome_fich){
    int *grafo, *sol, *best;
    int vert, i, custo, best_custo, op, iter = 100;
    float   mbf = 0.0;

    init_rand();

    grafo = init_dados(nome_fich, &vert, &iter);

    sol = malloc(sizeof(int)*vert);
    best = malloc(sizeof(int)*vert);
    if(sol == NULL || best == NULL){
        printf("Erro na alocacao de memoria");
        return;
    }
    do {
        mbf = 0.0;
        do {
            printf("\n\n--------------------------------------------------------------\n\n");
            printf("         1- Usar gera_vizinho \n");
            printf("         2- Usar gera_vizinho2 \n");
            printf("         3- Voltar \n\n");
            printf("--------------------------------------------------------------\n\n");
            printf(">>Opcao: ");
            scanf("%d", &op);
        } while (op < 1 || op > 3);
        if (op == 1) {
            for (i = 0; i < runs; i++) {
                // Gera a solucao inicial
                gera_sol_inicial(sol, vert);
                // Executa o algoritmo do trepa colinas
                custo = trepa_colinas(sol, grafo, vert, iter);
                // Mostra a solu��o encontrada na repeti��o k e o seu custo-FAZ SENTIDO
                printf("\nRepeticao %d:", i + 1);
                escreve_sol(sol, vert);
                printf("Custo final: %2d\n", custo);
                // Acumula o custo das solu��es encontradas
                mbf += custo;
                // Guarda a melhor solu��o encontrada
                if (i == 0 || best_custo < custo) {
                    best_custo = custo;
                    substitui(best, sol, vert);
                }
            }
        }
        if (op == 2) {
            for (i = 0; i < runs; i++) {
                // Gera a solucao inicial-
                gera_sol_inicial(sol, vert);
                // Executa o algoritmo do trepa colinas
                custo = trepa_colinas2(sol, grafo, vert, iter);
                // Mostra a solu��o encontrada na repeti��o k e o seu custo
                printf("\nRepeticao %d:", i + 1);
                escreve_sol(sol, vert);
                printf("Custo final: %2d\n", custo);
                // Acumula o custo das solu��es encontradas
                mbf += custo;
                // Guarda a melhor solu��o encontrada
                if (i == 0 || best_custo < custo) {
                    best_custo = custo;
                    substitui(best, sol, vert);
                }
            }
        }
        if (op != 3) {
            //Calcula e mostra a m�dia dos custos de todas as melhores solu��es encontradas
            printf("\n\nMBF: %f\n", mbf / i);
            // Mostra a melhor solu��o encontrada e o seu respectivo custo
            printf("\nMelhor solucao encontrada");
            escreve_sol(best, vert);
            printf("Custo final: %2d\n", best_custo);
        }
    }while(op != 3);
    return;
}

void inicioEvolutivo(char* nome_fich){
    return;
}

void inicioHibrido(char* nome_fich){
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
            printf("         1- Algoritmo pesquisa local (Trepa-Colinas) \n");
            printf("         2- Algoritmo evolutivo \n");
            printf("         3- Metodo hibrido \n");
            printf("         4- Sair \n\n");
            printf("--------------------------------------------------------------\n\n");
            printf(">>Opcao: ");
            scanf("%d", &op);
        }while(op<1 || op>4);
        if (op != 4) {
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
                inicioTrepaColinas(nome_fich);
            } else if (op == 2) {
                inicioEvolutivo(nome_fich);
            } else if (op == 3) {
                inicioHibrido(nome_fich);
            }
        }
    }while(op != 4);

    return 1;
}