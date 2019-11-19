/* cv.c
 * Implementacao de um programa que lê um csv e armazena
 * os dados em uma arvore AVL e um Hashmap para executar
 * operações específicas em cada TAD.
 * 
 * Leonardo Amorim e Luis Durante
 * 19/12/2019
 */


#include "cv.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>


void load_csv(hash_map m, avl_tree * t, char * filename) {
    FILE * arq;

    char linha[1001];

    bool h;
    map_key key;
    char nome[256];
    double cobertura_vacinal;

    if ((arq = fopen(filename, "r")) == NULL) {
        fprintf(stderr,"Erro na abertura do arquivo %s\n", filename);
        exit(1);
    }

    while (fgets(linha, 1000, arq)) {
        map_value mv;
        avl_info ai;

        strcpy(key, strtok(linha, ";"));
        strcpy(nome, strtok(NULL, ";"));
        cobertura_vacinal = atof(strtok(NULL, ";"));

        strcpy(mv.nome, nome);
        mv.cobertura_vacinal = cobertura_vacinal;

        strcpy(ai.nome, nome);
        ai.codigo = atoi(key);
        ai.cobertura_vacinal = cobertura_vacinal;
        
        map_put(m, key, mv);
        add_node(t, atoi(key), cobertura_vacinal, nome, &h);
    }

    fclose(arq);
}


void print_n_greatest(avl_tree t, int n, int * i) {
    if (t != NULL) {
        print_n_greatest(t->dir, n, i);
        if(++(*i) <= n){
            printf("Codigo: %d\n", t->dado.codigo);
            printf("Nome: %s\n", t->dado.nome);
            printf("Cobertura Vacinal: %.3f\n\n", t->dado.cobertura_vacinal);
        }
        print_n_greatest(t->esq, n, i);
    }
}


void print_n_least(avl_tree t, int n, int * i) {
    if (t != NULL) {
        print_n_least(t->esq, n, i);
        if(++(*i) <= n){
            printf("Codigo: %d\n", t->dado.codigo);
            printf("Nome: %s\n", t->dado.nome);
            printf("Cobertura Vacinal: %.3f\n\n", t->dado.cobertura_vacinal);
        }
        print_n_least(t->dir, n, i);
    }
}


void print_city_details(hash_map m, char * codigo) {
    map_value * hi = map_get(m, codigo);

    if(hi != NULL){
        printf("\nCodigo: %s\n", codigo);
        printf("Nome: %s\n", hi->nome);
        printf("Cobertura Vacinal: %.3f\n\n", hi->cobertura_vacinal);
    } else {
        printf("\nNao existe nenhuma cidade associada a este codigo.\n\n");
    }
}

