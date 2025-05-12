// Essa atividade consiste em identificar animais que foram selecionados pelo criador da atividade a partir de certas classificações biológicas, como alimentação e classe.

#include <stdio.h>
#include <string.h>

int main() {
    char ossos[15], classe[15], alimentacao[15];
    
    scanf("%s", ossos);
    scanf("%s", classe);
    scanf("%s", alimentacao);
    
    if (strcmp(ossos, "vertebrado") == 0) {
        if (strcmp(classe, "ave") == 0) {
            if (strcmp(alimentacao, "carnivoro") == 0) {
                printf("aguia\n");
            } else if (strcmp(alimentacao, "onivoro") == 0) {
                printf("pomba\n");
            }
        } else if (strcmp(classe, "mamifero") == 0) {
            if (strcmp(alimentacao, "onivoro") == 0) {
                printf("homem\n");
            } else if (strcmp(alimentacao, "herbivoro") == 0) {
                printf("vaca\n");
            }
        }
    } else if (strcmp(ossos, "invertebrado") == 0) {
        if (strcmp(classe, "inseto") == 0) {
            if (strcmp(alimentacao, "hematofago") == 0) {
                printf("pulga\n");
            } else if (strcmp(alimentacao, "herbivoro") == 0) {
                printf("lagarta\n");
            }
        } else if (strcmp(classe, "anelideo") == 0) {
            if (strcmp(alimentacao, "hematofago") == 0) {
                printf("sanguessuga\n");
            } else if (strcmp(alimentacao, "onivoro") == 0) {
                printf("minhoca\n");
            }
        }
    }
    
    return 0;
}
