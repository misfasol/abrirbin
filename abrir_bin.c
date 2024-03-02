#include <stdio.h>
#include <stdlib.h>

#define COLUNAS 16

int main(int argc, char *argv[]) {
    if (argc <= 1) {
        printf("Numero de argumentos invalido.\nUsagem: ./abrir_bin <arquivo.bin>");
        exit(1);
    }

    FILE* arq = fopen(argv[1], "rb");
    if (arq == NULL) {
        printf("Arquivo nao existe, fechando aplicacao.");
        exit(1);
    }

    unsigned char byte = 0;
    unsigned char linhas[COLUNAS] = {0};
    int contador = 0;
    while (fread(&byte, sizeof(char), 1, arq) == 1) {
        if (contador % COLUNAS == 0) {
            printf("%06x:  ", contador);
        }
        printf("%02x ", byte);
        linhas[contador % COLUNAS] = byte;
        contador++;
        if (contador % COLUNAS == 0) {
            printf("   ");
            for (int i = 0; i < COLUNAS; i++) {
                if (linhas[i] >= 32 && linhas[i] <= 126) {
                    printf("%c", linhas[i]);
                } else {
                    printf(".");
                }
            }
            printf("\n");
        }
    }
    if (contador % COLUNAS != 0) {
        for (int i = 0; i < COLUNAS - (contador % COLUNAS); i++) {
            printf("   ");
        }
        printf("   ");
        for (int i = 0; i < contador % COLUNAS; i++) {
            if (linhas[i] >= 32 && linhas[i] <= 126) {
                printf("%c", linhas[i]);
            } else {
                printf(".");
            }
        }
    }

    printf("\nTamanho do arquivo: %d bytes.", contador);
    fclose(arq);

    return 0;
}