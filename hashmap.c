/* hashmap.c
 * Implementação das operações realizadas sobre o TAD hash_map
 *
 * Ciro C. Trindade 
 * 30/out/2019 
 * 
 * Adaptado por Leonardo Amorim e Luis Durante
 * 19/12/2019
 */


#include "hashmap.h"
#include "listaord.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>


void map_init(hash_map m){
	int i;
	for (i = 0; i < M; i++) {
		lst_init(&m[i]);
	}
}


map_value * map_get(hash_map m, map_key key){
	return lst_find(m[h(key)], key);
}


void map_put(hash_map m, map_key key, map_value val){
	lst_ins(&m[h(key)], key, val);
}


/* método do meio do quadrado para chaves alfanuméricas */
int h(map_key key){
	int i, soma = 0;
	// converte a chave para um inteiro
	for (i = 0; key[i] != '\0'; i++) {
		soma += key[i] << (i % 8);
	}
	
	// meio do quadrado
	soma *= soma;
	int x = log10(M) / log10(2);
	int desl = (NUM_BITS - x) / 2;
	soma >>= desl;
	return soma & ((int) pow(2, x) - 1);
}

