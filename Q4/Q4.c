#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define nome_arq "NOMES.bin"
#define max_cadastro 20

FILE *arq;

int posicao, menu;
char nome[50];

bool verificar_se_abriu(FILE *arq_aux)
{
    if (arq_aux)
    {
        return true;
    }
    else
    {
        printf("\nError ao abrir o arquivo\n");
        system("pause");
        return false;
    }
}

void verificar_se_existe()
{
    arq = fopen(nome_arq, "rb");

    if (!verificar_se_abriu(arq))
    {
        return;
    }

    if (arq)
    {
        fclose(arq);
    }
    else
    {
        arq = fopen(nome_arq, "wb");

        memset(&nome, '\0', strlen(nome) + 1);

        fwrite(nome, sizeof(nome), max_cadastro, arq);

        fclose(arq);
    }
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

void digitar_o_nome()
{
    printf("\nDigite o nome(ate 50 caracteres)\n");

    fflush(stdin);
    fgets(nome, sizeof(nome), stdin);
    fflush(stdin);

    tira_n(nome);

    fwrite(nome, sizeof(nome), 1, arq);
}

void escrever()
{
    

    do
    {
        system("cls||clear");
        printf("\nDigite a posicao(1 a %d)\n0 - para voltar\n", max_cadastro);
        if (scanf("%d", &posicao) && posicao >= 0 && posicao <= 20)
        {
            if (posicao != 0)
            {
                arq = fopen(nome_arq, "rb+");

                if (!verificar_se_abriu(arq))
                {
                    return;
                }

                fseek(arq, (sizeof(nome) * posicao) - sizeof(nome), SEEK_SET);

                fread(nome, sizeof(nome), 1, arq);

                fseek(arq, (sizeof(nome) * posicao) - sizeof(nome), SEEK_SET);

                if (nome[0] == '\0')
                {
                    digitar_o_nome();
                }
                else
                {
                    printf("\nA posicao em questao ja esta preenchida.\nDeseja modificar?\n1-Sim\n2-Nao\n");
                    if (scanf("%d", &menu))
                    {
                        if (menu == 1)
                        {
                            digitar_o_nome();
                        }
                    }
                    else
                    {
                        blindagem_scanf();
                    }
                }
                fclose(arq);
            }
        }
        else
        {
            blindagem_scanf();
        }

    } while (posicao != 0);
}

void ler()
{
    system("cls||clear");

    int contador = 1;
    bool teste = false;

    arq = fopen(nome_arq, "rb");

    if (!verificar_se_abriu(arq))
    {
        return;
    }

    while (fread(nome, sizeof(nome), 1, arq))
    {
        if (!nome[0] == '\0')
        {
            printf("Posicao: %d\nNome: %s\n\n", contador, nome);
            teste = true;
        }
        contador++;
    }

    if (teste == false)
    {
        printf("Nao a nomes registrados\n\n");
    }

    fclose(arq);
    system("pause");
}

void formatar()
{
    arq = fopen(nome_arq, "wb");

    if (!verificar_se_abriu(arq))
    {
        return;
    }

    memset(&nome, '\0', strlen(nome) + 1);

    fwrite(nome, sizeof(nome), max_cadastro, arq);

    fclose(arq);
}

void buscar()
{
    do
    {
        system("cls||clear");
        printf("\nDigite a posicao(1 a %d)\n0 - para voltar\n", max_cadastro);
        if (scanf("%d", &posicao) && posicao >= 0 && posicao <= 20)
        {
            if (posicao != 0)
            {
                arq = fopen(nome_arq, "rb+");

                if (!verificar_se_abriu(arq))
                {
                    return;
                }

                fseek(arq, (sizeof(nome) * posicao) - sizeof(nome), SEEK_SET);

                fread(nome, sizeof(nome), 1, arq);

                fseek(arq, (sizeof(nome) * posicao) - sizeof(nome), SEEK_SET);

                if (nome[0] == '\0')
                {
                    printf("\nNome vazio\n\n");
                }
                else
                {
                    printf("\nNome: %s\n\n", nome);
                }
                fclose(arq);

                system("pause");
            }
        }
        else
        {
            blindagem_scanf();
        }

    } while (posicao != 0);

}

int main()
{
    verificar_se_existe();

    do
    {
        system("cls||clear");

        printf("1-Escrever\n2-Buscar\n3-Ler\n4-Formatar\n5-finalizar\n");

        if (scanf("%d", &menu))
        {
            switch (menu)
            {
            case 1:
                escrever();
                break;

            case 2:
                buscar();
                break;

            case 3:
                ler();
                break;

            case 4:
                formatar();
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