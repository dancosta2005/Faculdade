#include <stdio.h>

int main() {
    int R, caso = 1;

    while (1) {
        scanf("%d", &R);
        if (R == 0) {
            break; // Finaliza quando R é 0
        }

        int somaAldo = 0, somaBeto = 0;

        for (int i = 0; i < R; i++) {
            int A, B;
            scanf("%d %d", &A, &B);
            somaAldo += A;
            somaBeto += B;
        }

        printf("Teste %d\n", caso++);
        if (somaAldo > somaBeto) {
            printf("Aldo\n");
        } else {
            printf("Beto\n");
        }
        printf("\n");
    }

    return 0;
}
