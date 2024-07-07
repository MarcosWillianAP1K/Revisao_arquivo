#include <stdio.h>
#include <string.h>
#include <ctype.h>

void tira_n(char nome[])
{
    int tamanho = strlen(nome);
    nome[tamanho - 1] = '\0';
}

int main()
{
    char nome_arq[20];

    scanf("%s", nome_arq);



    FILE *arq;

    arq = fopen(nome_arq, "a");

    fclose(arq);

    char nome[50];

    arq = fopen(nome_arq, "w");

    for (int i = 0; i < 3; i++)
    {
        fflush(stdin);
        fgets(nome, sizeof(nome), stdin);
        fflush(stdin);

        int tam = strlen(nome);

        for (int j = 0; j < tam; j++)
        {
            nome[j] = toupper(nome[j]);
        }

        tira_n(nome);
        
        fprintf(arq, "%s\n", nome);
    }

    fclose(arq);

    printf("\n\n");

    char buffer[50];

    arq = fopen(nome_arq, "r");

    //!feof(arq)
    while(fgets(buffer, sizeof(buffer), arq))
    {
        printf("%s", buffer);
    }

    fclose(arq);

    return 0;
}