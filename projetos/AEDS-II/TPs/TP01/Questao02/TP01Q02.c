#include <stdio.h>
#include <stdbool.h>
#include <string.h>

bool isPalindromo(char texto[])
{
    bool Resultado;

    int tam = strlen(texto) - 1;

    for (int i = 0; i <= tam; i++)
    {
        if (texto[i] != texto[tam - i])
            Resultado = false;
    }

    return true;
}

void Resultado()
{
    char texto[1000];

    scanf(" %[^\n\r]", texto);

    while (strcmp(texto, "FIM"))
    {
        if (isPalindromo(texto))
            printf("SIM\n");
        else
            printf("NAO\n");

        scanf(" %[^\n\r]", texto);
    }
}

int main()
{
    Resultado();
    return 0;
}