#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int read(char *arg)
{
    FILE *arq;
    arq = fopen(arg, "r");

    if (arq == NULL)
    {
        printf("Erro ao abrir o arquivo");
        return 1;
    }

    while (!feof(arq))
    {
        char c, genoma[1000001];
        int qtdConjuntos, qtdGenomas, i, j;

        fscanf(arq, "%d", &qtdConjuntos);
        // printf("%d\n", qtdConjuntos);

        for (i = 0; i < qtdConjuntos; i++)
        {
            fscanf(arq, "%d", &qtdGenomas);
            // printf("%d\n", qtdGenomas);
            for (j = 0; j < qtdGenomas; j++)
            {
                fscanf(arq, "%s\n", genoma);
                printf("%s\n", genoma);
            }
        }
    }

    fclose(arq);

    return 0;
}
