#include <stdio.h>
#include <string.h>

#define nome_arq "arquivo.bin"

void tira_n(char nome[])
{
    int tamanho = strlen(nome);
    nome[tamanho - 1] = '\0';
}

int main()
{
    // wb, rb, ab, wb+, rb+ , ab+

    char nome[50];
    FILE *arq;

    // fwrite, fread, fseek, rewind, ftell

    arq = fopen(nome_arq, "rb");

    while (fread(nome, sizeof(nome), 1, arq))
    {
        printf("%d\n%s\n\n", ftell(arq), nome);
    }

    fclose(arq);

    return 0;
}