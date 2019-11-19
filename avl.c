/* avl.c
 * Implementacao das operacoes realizadas sobre o TAD que
 * representa uma arvore AVL.
 *
 * Ciro C. Trindade
 * 30/09/2019
 * 
 * Adaptado por Leonardo Amorim e Luis Durante
 * 19/12/2019
 */
 
 
#include "avl.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void rotacao_esq(avl_tree * t) {
    avl_tree p;
    p = (*t)->dir;
    (*t)->dir = p->esq;
    p->esq = *t;
    *t = p;
}


void rotacao_dir(avl_tree * t) {
    avl_tree p;
    p = (*t)->esq;
    (*t)->esq = p->dir;
    p->dir = *t;
    *t = p;
}


void balance_dir(avl_tree * t, bool * h) {
    avl_tree p1, p2;
    int b1, b2;

    switch ((*t)->bal) {
        case 1: (*t)->bal = 0;
            break;
        case 0: (*t)->bal = -1;
            *h = false;
            break;
        case -1: // rebalanceamento
            p1 = (*t)->esq;
            b1 = p1->bal;
            if (b1 <= 0) { // rotação simples
                (*t)->esq = p1->dir;
                p1->dir = *t;
                if (b1 == 0) {
                    (*t)->bal = -1;
                    p1->bal = 1;
                    *h = false;
                }
                else {
                    (*t)->bal = 0;
                    p1->bal = 0;
                }
                *t = p1;
            }
            else { // rotação dupla
                p2 = p1->dir;
                b2 = p2->bal;
                p1->dir = p2->esq;
                p2->esq = p1;
                p1->esq = p2->dir;
                p2->dir = *t;
                if(b2 == -1) (*t)->bal = 1;
                else (*t)->bal = 0;
                if(b2 == 1) p1->bal = -1;
                else p1->bal = 0;
                *t = p2;
                p2->bal = 0;
            }
    } // fim do switch
}


void balance_esq(avl_tree * t, bool * h) {
    avl_tree p1, p2;
    int b1, b2;

    switch ((*t)->bal) {
        case -1: (*t)->bal = 0;
                 break;
        case 0: (*t)->bal = 1;
                *h = false;
                break;
        case 1: // rebalanceamento
                p1 = (*t)->dir;
                b1 = p1->bal;
                if (b1 >= 0) { // rotação simples
                    (*t)->dir = p1->esq;
                    p1->esq = *t;
                    if (b1 == 0) {
                        (*t)->bal = 1;
                        p1->bal = -1;
                        *h = false;
                    }
                    else {
                        (*t)->bal = 0;
                        p1->bal = 0;
                    }
                    *t = p1;
                }
                else { // rotação dupla
                    p2 = p1->esq;
                    b2 = p2->bal;
                    p1->esq = p2->dir;
                    p2->dir = p1;
                    p1->dir = p2->esq;
                    p2->esq = *t;
                    if (b2 == 1) (*t)->bal = -1;
                    else (*t)->bal = 0;
                    if (b2 == -1) p1->bal = 1;
                    else p1->bal = 0;
                    *t = p2;
                    p2->bal = 0;
                }
    } // fim do switch
}


avl_tree get_min(avl_tree * t, bool * h) {
    avl_tree q;
    if ((*t)->esq != NULL) {
        q = get_min(&((*t)->esq),h);
        if (*h) balance_esq(t, h);
        return q;
    }
    else {
        *h = true;
        q = *t;
        *t = (*t)->dir;
        return q;
    }
}


void add_node(avl_tree * t, int codigo, double cobertura_vacinal, char * nome, bool * h) {
    if (*t == NULL) {
        if ((*t = (avl_tree) malloc(sizeof(struct avl_no))) == NULL) {
            fprintf(stderr, "Erro de alocacao de memoria!\n");
            exit(1);
        }
        *h = true;
        (*t)->dado.codigo = codigo;
        (*t)->dado.cobertura_vacinal = cobertura_vacinal;
        strcpy((*t)->dado.nome, nome);
        (*t)->esq = (*t)->dir = NULL;
        (*t)->bal = 0;
    } else if (cobertura_vacinal < (*t)->dado.cobertura_vacinal ){ // Inserir a esquerda
        add_node(&(*t)->esq, codigo, cobertura_vacinal, nome, h);
        if (*h) { // O ramo esquerdo cresceu
            switch ((*t)->bal) {
                case 1: (*t)->bal = 0;
                    *h = false;
                    break;
                case 0: (*t)->bal = -1;
                    break;
                case -1:
                    // Rebalanceamento
                    if ((*t)->esq->bal == -1) { //Rotação simples p/ direita
                        rotacao_dir(t);
                        (*t)->dir->bal = 0; //Ajusta o fator de balanceamento
                    }
                    else { // Rotação dupla para direita
                        rotacao_esq(&(*t)->esq);
                        rotacao_dir(t);
                        // Ajusta o fator de balanceamento
                        if ((*t)->bal == -1) (*t)->dir->bal = 1;
                        else (*t)->dir->bal = 0;
                        if ((*t)->bal == 1) (*t)->esq->bal = -1;
                        else (*t)->esq->bal = 0;
                    }
                    *h = false;
                    (*t)->bal = 0;
                    break;
            }
        }
    } else if (cobertura_vacinal >= (*t)->dado.cobertura_vacinal) { // Inserir a direita
        add_node(&(*t)->dir, codigo, cobertura_vacinal, nome, h);
        if (*h) { // O ramo direito cresceu
            switch ((*t)->bal) {
                case -1: (*t)->bal = 0;
                    *h = false;
                    break;
                case 0 : (*t)->bal = 1;
                    break;
                case 1: // Rebalanceamento
                    if ((*t)->dir->bal == 1) { // Rotação simples p/ esquerda
                        rotacao_esq(t);
                        // Ajusta o fator de balanceamento
                        (*t)->esq->bal = 0;
                    } else { // Rotação dupla para esquerda
                        rotacao_dir(&(*t)->dir);
                        rotacao_esq(t);
                        // Ajusta o fator de balanceamento
                        if ((*t)->bal == 1) (*t)->esq->bal = -1;
                        else (*t)->esq->bal = 0;
                        if ((*t)->bal == -1) (*t)->dir->bal = 1;
                        else (*t)->dir->bal = 0;
                    }
                    *h = false;
                    (*t)->bal = 0;
                    break;
            }
        }
    }
}

