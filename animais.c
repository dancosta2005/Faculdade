#include <stdio.h>
#include <string.h>

int main() {
    char ossos[15], familia[15], alimentacao[15];
    
    // Leitura das entradas
    scanf("%s", ossos);
    scanf("%s", familia);
    scanf("%s", alimentacao);
    
    // Comparação das strings
    if (strcmp(ossos, "vertebrado") == 0) {
        if (strcmp(familia, "ave") == 0) {
            if (strcmp(alimentacao, "carnivoro") == 0) {
                printf("aguia\n");
            } else if (strcmp(alimentacao, "onivoro") == 0) {
                printf("pomba\n");
            }
        } else if (strcmp(familia, "mamifero") == 0) {
            if (strcmp(alimentacao, "onivoro") == 0) {
                printf("homem\n");
            } else if (strcmp(alimentacao, "herbivoro") == 0) {
                printf("vaca\n");
            }
        }
    } else if (strcmp(ossos, "invertebrado") == 0) {
        if (strcmp(familia, "inseto") == 0) {
            if (strcmp(alimentacao, "hematofago") == 0) {
                printf("pulga\n");
            } else if (strcmp(alimentacao, "herbivoro") == 0) {
                printf("lagarta\n");
            }
        } else if (strcmp(familia, "anelideo") == 0) {
            if (strcmp(alimentacao, "hematofago") == 0) {
                printf("sanguessuga\n");
            } else if (strcmp(alimentacao, "onivoro") == 0) {
                printf("minhoca\n");
            }
        }
    }
    
    return 0;
}
