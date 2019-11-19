/* listaord.h
 * Definição do TAD para uma lista linear encadeada adaptada
 * para um hash map.
 *
 * Ciro C. Trindade 
 * 30/out/2019 
 * 
 * Adaptado por Leonardo Amorim e Luis Durante
 * 19/12/2019
 */


#ifndef _LISTAORD_H
#define _LISTAORD_H


#include "hashmap.h"
#include <stdbool.h>


/* função que inicializa a lista encadeada ordenada */
void lst_init(map_ptr *);


/* função que insere um novo par (chave, valor) na lista */
void lst_ins(map_ptr *, map_key, map_value);


/* função que e devolve o endereço do valor, caso sua chave 
   esteja na lista, ou NULL, caso contrário */
map_value * lst_find(map_ptr, map_key);


#endif

