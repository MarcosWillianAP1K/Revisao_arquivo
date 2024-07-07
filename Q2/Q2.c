#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#define nome_arq "FRASES.txt"
#define nome_arq_aux "AUXILIAR.txt"
#define MAX 50

FILE *arq;
char palavra[MAX];
int menu;

void verificar_se_existe()
{
    arq = fopen(nome_arq, "a");

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
    arq = fopen(nome_arq, "w");

    fclose(arq);
}

void modificar_palavra(char palavra_modificada[], char palavra_busca[])
{
    char aux[MAX];

    FILE *arq_aux = fopen(nome_arq_aux, "w");

    arq = fopen(nome_arq, "r");

    while (fgets(aux, sizeof(aux), arq))
    {
        if (strcmp(aux, palavra_busca) == 0)
        {
            fprintf(arq_aux, "%s", palavra_modificada);
        }
        else
        {
            fprintf(arq_aux, "%s", aux);
        }
    }
    fclose(arq_aux);
    fclose(arq);

    arq = fopen(nome_arq, "w");
    arq_aux = fopen(nome_arq_aux, "r");

    while (fgets(aux, sizeof(aux), arq_aux))
    {
        fprintf(arq, "%s", aux);
    }

    fclose(arq_aux);
    fclose(arq);

    remove(nome_arq_aux);
}

void buscar()
{
    char palavra_busca[MAX], palavra_modificada[MAX];

    arq = fopen(nome_arq, "r+");

    fflush(stdin);
    fgets(palavra_busca, sizeof(palavra_busca), stdin);
    fflush(stdin);

    while (fgets(palavra, sizeof(palavra), arq))
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
                        fgets(palavra_modificada, sizeof(palavra_modificada), stdin);
                        fflush(stdin);

                        fclose(arq);

                        modificar_palavra(palavra_modificada, palavra_busca);
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

void escrever()
{
    arq = fopen(nome_arq, "a");

    fflush(stdin);
    fgets(palavra, sizeof(palavra), stdin);
    fflush(stdin);

    tira_n(palavra);

    fprintf(arq, "%s\n", palavra);

    fclose(arq);
}

void ler()
{
    printf("\n\n");
                // bool teste = false;
                arq = fopen(nome_arq, "r");

                if (!fgets(palavra, sizeof(palavra), arq))
                {
                    printf("Arquivo vazio\n");
                }

                rewind(arq);

                while (fgets(palavra, sizeof(palavra), arq))
                {
                    // teste = true;
                    printf("%s", palavra);
                }

                // if (teste == false)
                //{
                //     printf("Arquivo vazio\n");
                // }

                system("pause");
                fclose(arq);
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