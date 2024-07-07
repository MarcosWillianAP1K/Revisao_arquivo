#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

#define nome_arq "FRASES.bin"
#define MAX 50

FILE *arq;
char palavra[MAX];
int menu;

void verificar_se_existe()
{
    arq = fopen(nome_arq, "ab");

    fclose(arq);
}

void blindagem_scanf()
{
    printf("\ndigitacao invalida\n");
    system("pause");
    system("cls||clear");
    fflush(stdin);
}

void tira_n(char nome[])
{
    int tamanho = strlen(nome);
    nome[tamanho - 1] = '\0';
}

void formatar()
{
    arq = fopen(nome_arq, "wb");

    fclose(arq);
}

void escrever()
{
    arq = fopen(nome_arq, "ab");

    fflush(stdin);
    fgets(palavra, sizeof(palavra), stdin);
    fflush(stdin);

    tira_n(palavra);

    fwrite(palavra, sizeof(palavra), 1, arq);

    fclose(arq);
}

void ler()
{
    printf("\n\n");
    // bool teste = false;
    arq = fopen(nome_arq, "rb");

    if (!fread(palavra, sizeof(palavra), 1, arq))
    {
        printf("Arquivo vazio\n");
    }

    rewind(arq);

    while (fread(palavra, sizeof(palavra), 1, arq))
    {
        // teste = true;
        printf("\n%s", palavra);
    }
    printf("\n");

    // if (teste == false)
    //{
    //     printf("Arquivo vazio\n");
    // }

    system("pause");
    fclose(arq);
}

void modificar_palavra(char palavra_modificada[], int posicao)
{
    arq = fopen(nome_arq, "rb+");

    fseek(arq, posicao, SEEK_SET);

    fwrite(palavra_modificada, sizeof(palavra), 1, arq);

    fclose(arq);
}

void buscar()
{
    char palavra_busca[MAX];

    arq = fopen(nome_arq, "rb+");

    fflush(stdin);
    fgets(palavra_busca, sizeof(palavra_busca), stdin);
    fflush(stdin);

    tira_n(palavra_busca);

    while (fread(palavra, sizeof(palavra), 1, arq))
    {
        if (strcmp(palavra, palavra_busca) == 0)
        {
            do
            {
                system("cls||clear");
                printf("%s", palavra);
                printf("\nDeseja modificala?\n1-Sim\n2-Nao\n");

                if (scanf("%d", &menu))
                {
                    switch (menu)
                    {
                    case 1:
                        fflush(stdin);
                        fgets(palavra_busca, sizeof(palavra_busca), stdin);
                        fflush(stdin);

                        tira_n(palavra_busca);

                        fseek(arq, sizeof(palavra) * -1, SEEK_CUR);

                        int posicao_atual = ftell(arq);

                        fclose(arq);

                        modificar_palavra(palavra_busca, posicao_atual);
                        return;

                        break;
                    case 2:
                        return;
                        break;

                    default:
                        blindagem_scanf();
                        break;
                    }
                }
                else
                {
                    blindagem_scanf();
                }

            } while (menu != 1 && menu != 2);
        }
    }

    fclose(arq);
    printf("\nPalavra nao encontrada\n");
    system("pause");
}

int main()
{
    verificar_se_existe();

    do
    {
        system("cls||clear");

        printf("1-Escrever\n2-Ler\n3-Formatar\n4-buscar\n5-finalizar\n");

        if (scanf("%d", &menu))
        {
            switch (menu)
            {
            case 1:
                escrever();
                break;

            case 2:
                ler();
                break;

            case 3:
                formatar();
                break;

            case 4:
                buscar();
                break;

            case 5:
                break;

            default:
                blindagem_scanf();
                break;
            }
        }
        else
        {
            blindagem_scanf();
        }

    } while (menu != 5);

    return 0;
}