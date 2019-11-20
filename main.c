#include <stdio.h>
#include <stdlib.h>

#include "reader.h"

int main(int argc, char **argv)
{
    int failed;

    failed = read(argv[1]);

    if (failed)
    {
        printf("Erro ao processar o arquivo");
        return 1;
    }

    return 0;
}