#include <stdio.h>
#include <stdlib.h>

// Função que realiza operações de escrita e leitura no arquivo
void arquivo()
{
    int n;
    FILE *file;

    // Passo 1: Ler o número de valores reais (n)
    if (scanf("%d", &n) != 1)
    {
        printf("Erro ao ler o número de valores.\n");
        exit(1);
    }

    // Abrir o arquivo para escrita binária
    file = fopen("valores.bin", "wb");
    if (file == NULL)
    {
        printf("Erro ao abrir o arquivo para escrita.\n");
        exit(1);
    }

    // Passo 2: Ler os valores reais e gravar no arquivo
    for (int i = 0; i < n; i++)
    {
        double valor;
        if (scanf("%lf", &valor) != 1)
        {
            printf("Erro ao ler o valor real.\n");
            fclose(file);
            exit(1);
        }
        fwrite(&valor, sizeof(double), 1, file); // Grava o número no arquivo
    }

    // Fechar o arquivo após a escrita
    fclose(file);

    // Reabrir o arquivo para leitura binária
    file = fopen("valores.bin", "rb");
    if (file == NULL)
    {
        printf("Erro ao abrir o arquivo para leitura.\n");
        exit(1);
    }

    // Passo 3: Ler os valores de trás para frente
    for (int i = n - 1; i >= 0; i--)
    {
        fseek(file, i * sizeof(double), SEEK_SET); // Move o ponteiro para a posição i
        double valor;
        fread(&valor, sizeof(double), 1, file); // Lê o número do arquivo
        printf("%g\n", valor);                  // Imprime o número lido
    }

    // Fechar o arquivo após a leitura
    fclose(file);
}

int main()
{
    arquivo(); // Chamada da função
    return 0;
}
