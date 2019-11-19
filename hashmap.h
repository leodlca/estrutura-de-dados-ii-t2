/* hashmap.h
 * Definição do TAD hash_map
 *
 * Ciro C. Trindade 
 * 30/out/2019 
 * 
 * Adaptado por Leonardo Amorim e Luis Durante
 * 19/12/2019
 */


#ifndef _HASHMAP_H
#define _HASHMAP_H


#include <stdbool.h>


#define M 1024  // número de encaixes da tabela de hashing
#define NUM_BITS 16
#define MAX_DEF 255
#define MAX_WORD 255


typedef char map_key[MAX_WORD + 1];


typedef struct {
    char nome[256];
    double cobertura_vacinal;
} map_value;


typedef struct map_node * map_ptr;


struct map_node {
    map_key key;
    map_value * value;
    map_ptr prox;
};


typedef map_ptr hash_map[M];


/* função que inicializa o hash map */
void map_init(hash_map);


/* função que devolve o endereço do valor associado a chave no mapa, 
   caso a chave esteja contida no mapa, ou NULL, caso contrário */
map_value * map_get(hash_map, map_key);


/* função que insere a entrada (chave, valor) no mapa se mapa não possuir
   um entrada para a chave */
void map_put(hash_map, map_key, map_value);


/* função de hashing que utiliza o método do meio do quadrado */
int h(map_key);


#endif // _HASHMAP_H

