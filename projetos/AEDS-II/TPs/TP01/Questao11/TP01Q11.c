#include <stdio.h>
#include <stdbool.h>
#include <string.h>

// Função recursiva para verificar se uma string é um palíndromo
bool isPalindromoRecursivo(char *texto, int inicio, int fim)
{
    bool resultado;

    if (inicio >= fim)
    {
        resultado = true; // Caso base: Se os índices se cruzaram ou se tornaram iguais, é um palíndromo
    }
    else if (texto[inicio] != texto[fim])
    {
        resultado = false; // Se os caracteres nos índices atuais não são iguais, não é um palíndromo
    }
    else
    {
        resultado = isPalindromoRecursivo(texto, inicio + 1, fim - 1); // Chamada recursiva com os próximos índices
    }

    return resultado;
}

// Função auxiliar para iniciar a verificação de palíndromo
bool isPalindromo(char *texto)
{
    int tam = strlen(texto);
    bool resultado = isPalindromoRecursivo(texto, 0, tam - 1);
    return resultado;
}

void Resultado()
{
    char texto[1000];

    // Inicialização da string com um valor não "FIM"
    strcpy(texto, "");

    // Loop principal
    while (strcmp(texto, "FIM") != 0)
    {
        fgets(texto, sizeof(texto), stdin);

        // Remove o caractere de nova linha ('\n') do final da string
        texto[strcspn(texto, "\n")] = '\0';

        if (strcmp(texto, "FIM") != 0)
        {
            if (isPalindromo(texto))
            {
                printf("SIM\n");
            }
            else
            {
                printf("NAO\n");
            }
        }
    }
}

int main()
{
    Resultado();
    return 0;
}
