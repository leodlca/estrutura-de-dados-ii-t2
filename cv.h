/* cv.c
 * Implementacao de um programa que lê um csv e armazena
 * os dados em uma arvore AVL e um Hashmap para executar
 * operações específicas em cada TAD.
 * 
 * Leonardo Amorim e Luis Durante
 * 19/12/2019
 */


#ifndef _CV_H
#define _CV_H


#include <stdbool.h>
#include "avl.h"
#include "listaord.h"
#include "hashmap.h"


/*
 * Carrega dados contidos no CSV numa AVL Tree e num hashmap.
 */
void load_csv(hash_map, avl_tree *, char *);


/* 
 * Exibe detalhes dos `n` maiores municípios em termos de 
 * cobertura vacinal.
 */
void print_n_greatest(avl_tree, int, int *);


/* 
 * Exibe detalhes dos `n` menores municípios em termos de 
 * cobertura vacinal.
 */
void print_n_least(avl_tree, int, int *);


/* 
 * Exibe detalhes do município que possui o código passado,
 * exibe um erro caso o município esteja cadastrado.
 */
void print_city_details(hash_map, char *);


#endif

