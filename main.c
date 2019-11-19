/* main.c
 * Interface e arquivo principal do projeto Cobertura Vacinal de EDII.
 *
 * Leonardo Amorim e Luis Durante
 * 19/12/2019
 */


#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#include "cv.h"


void wait_and_clear() {
    printf("Pressione qualquer tecla para continuar... ");
    getchar();
    getchar();
    system("cls || clear");
}


int main() {
    int escolha = 0;
    int n = 0;
    int i = 0;
    char codigo[256];

    avl_tree t = NULL;
    hash_map m;

    map_init(m);

    load_csv(m, &t, "cobertura_vacinal.csv");

    system("cls || clear");

    while (escolha != 4) {
        strcpy(codigo, "");
        i = 0;

        printf("Cobertura Vacinal\n\n");
        printf("1 - Exibir informacoes de uma cidade\n");
        printf("2 - Exibir as N cidades com *maior* cobertura vacinal\n");
        printf("3 - Exibir as N cidades com *menor* cobertura vacinal\n");
        printf("4 - Finalizar programa\n\n");
        printf("Insira sua escolha: ");
        scanf("%d", &escolha);

        system("cls || clear");

        switch (escolha) {
            case 1:
                printf("Insira o codigo da cidade: ");
                scanf(" %250[^\n]", codigo);

                print_city_details(m, codigo);

                wait_and_clear();

                break;

            case 2:
                printf("Insira o valor de N: ");
                scanf(" %d", &n);

                print_n_greatest(t, n, &i);

                wait_and_clear();

                break;

            case 3:
                printf("Insira o valor de N: ");
                scanf(" %d", &n);

                print_n_least(t, n, &i);

                wait_and_clear();

                break;

            case 4:
                return 0;

            default:
                printf("Opcao invalida!\n\n");
                wait_and_clear();
        }
    }
    return 0;
}

