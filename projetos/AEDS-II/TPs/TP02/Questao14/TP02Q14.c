#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_LINE 1024
#define MAX_FIELD 100
#define MAX_POKEMONS 1000

typedef struct
{
    int id;
    int generation;
    char name[MAX_FIELD];
    char description[MAX_FIELD];
    char type1[MAX_FIELD];
    char type2[MAX_FIELD];
    char abilities[MAX_FIELD];
    float weight_kg;
    float height_m;
    int capture_rate;
    bool is_legendary;
    char capture_date[MAX_FIELD];
} Pokemon;

// Função para remover espaços em branco no início e no fim da string
char *trim(char *str)
{
    char *end;

    // Remover espaços do início
    while (*str == ' ' || *str == '\t' || *str == '\n' || *str == '\r')
        str++;

    if (*str == 0) // Todos os espaços
        return str;

    // Remover espaços do fim
    end = str + strlen(str) - 1;
    while (end > str && (*end == ' ' || *end == '\t' || *end == '\n' || *end == '\r'))
        end--;

    // Escrever novo terminador
    *(end + 1) = 0;

    return str;
}

// Função para remover os colchetes de uma string, se presentes
void strip_brackets(char *str)
{
    int len = strlen(str);
    if (len >= 2 && str[0] == '[' && str[len - 1] == ']')
    {
        // Remover o primeiro e o último caractere
        memmove(str, str + 1, len - 2);
        str[len - 2] = '\0';
    }
}

// Função para dividir a linha CSV em campos, considerando aspas
int parse_csv_line(char *line, char fields[][MAX_FIELD])
{
    int field_count = 0;
    int i = 0;
    int len = strlen(line);
    bool in_quotes = false;
    int start = 0;

    for (i = 0; i <= len; i++)
    {
        if (line[i] == '"' && (i == 0 || line[i - 1] != '\\'))
        {
            in_quotes = !in_quotes;
        }
        if ((line[i] == ',' && !in_quotes) || line[i] == '\0')
        {
            int end = i;
            // Extrair o campo
            int j, k = 0;
            for (j = start; j < end; j++)
            {
                if (line[j] != '"')
                { // Remover aspas
                    fields[field_count][k++] = line[j];
                }
            }
            fields[field_count][k] = '\0';
            // Trim
            char *trimmed = trim(fields[field_count]);
            strcpy(fields[field_count], trimmed);
            field_count++;
            start = i + 1;
        }
    }

    return field_count;
}

// Função para buscar Pokémon por ID
Pokemon *buscar_pokemon_por_id(Pokemon pokemons[], int total, int id)
{
    for (int i = 0; i < total; i++)
    {
        if (pokemons[i].id == id)
        {
            return &pokemons[i];
        }
    }
    return NULL;
}

// Função de comparação para Radix Sort: retorna positivo se p1 > p2, negativo se p1 < p2, zero se iguais
int comparar_pokemons_radix(Pokemon p1, Pokemon p2)
{
    int cmp = strcmp(p1.abilities, p2.abilities);
    if (cmp != 0)
        return cmp;
    else
        return strcmp(p1.name, p2.name);
}

// Função de troca
void trocar_pokemon(Pokemon *a, Pokemon *b)
{
    Pokemon temp = *a;
    *a = *b;
    *b = temp;
}

// Função para encontrar o comprimento máximo das habilidades
int encontrar_max_len(Pokemon array[], int n)
{
    int max = 0;
    for (int i = 0; i < n; i++)
    {
        int len = strlen(array[i].abilities);
        if (len > max)
            max = len;
    }
    return max;
}

// Função de Counting Sort adaptada para strings no Radix Sort
void counting_sort_radix(Pokemon array[], int n, int digit)
{
    int count[256] = {0}; // ASCII
    Pokemon output[n];

    // Contagem dos caracteres no dígito atual
    for (int i = 0; i < n; i++)
    {
        int idx;
        if (strlen(array[i].abilities) < digit)
            idx = 0; // Posição vazia considerada como menor
        else
            idx = array[i].abilities[strlen(array[i].abilities) - digit];
        count[idx]++;
    }

    // Acumular contagens
    for (int i = 1; i < 256; i++)
    {
        count[i] += count[i - 1];
    }

    // Construir o array de saída
    for (int i = n - 1; i >= 0; i--)
    {
        int idx;
        if (strlen(array[i].abilities) < digit)
            idx = 0;
        else
            idx = array[i].abilities[strlen(array[i].abilities) - digit];
        output[count[idx] - 1] = array[i];
        count[idx]--;
    }

    // Copiar para o array original
    for (int i = 0; i < n; i++)
    {
        array[i] = output[i];
    }
}

// Implementação completa do Radix Sort para strings no atributo abilities
void radix_sort(Pokemon array[], int n)
{
    int max_len = encontrar_max_len(array, n);
    for (int digit = 1; digit <= max_len; digit++)
    {
        counting_sort_radix(array, n, digit);
    }
}

// Implementação do Bubble Sort para ordenação secundária por nome (opcional)
void bubble_sort_name(Pokemon array[], int n)
{
    bool swapped;
    for (int i = 0; i < n - 1; i++)
    {
        swapped = false;
        for (int j = 0; j < n - i - 1; j++)
        {
            if (strcmp(array[j].name, array[j + 1].name) > 0)
            {
                trocar_pokemon(&array[j], &array[j + 1]);
                swapped = true;
            }
        }
        if (!swapped)
            break;
    }
}

// Função para formatar as habilidades com aspas individuais
void format_abilities(char *formatted, char *abilities)
{
    char temp[MAX_FIELD];
    strcpy(temp, abilities); // Copiar as habilidades para uma string temporária
    char *token = strtok(temp, ",");
    formatted[0] = '\0'; // Inicializar a string formatada

    while (token != NULL)
    {
        char *trimmed = trim(token); // Remover espaços em branco
        strcat(formatted, "'");
        strcat(formatted, trimmed);
        strcat(formatted, "', ");
        token = strtok(NULL, ",");
    }

    // Remover a última vírgula e espaço
    int len = strlen(formatted);
    if (len >= 2)
        formatted[len - 2] = '\0';
}

// Função para imprimir um Pokémon no formato especificado
void imprimir_pokemon(Pokemon p, FILE *log_file)
{
    char tipos_formatados[2 * MAX_FIELD];
    if (strlen(p.type2) > 0)
    {
        sprintf(tipos_formatados, "['%s', '%s']", p.type1, p.type2);
    }
    else
    {
        sprintf(tipos_formatados, "['%s']", p.type1);
    }

    char habilidades_formatadas[2 * MAX_FIELD];
    if (strlen(p.abilities) > 0)
    {
        format_abilities(habilidades_formatadas, p.abilities);
    }
    else
    {
        strcpy(habilidades_formatadas, "'N/A'");
    }

    // Construir a string final
    char output[MAX_LINE];
    sprintf(output, "[#%d -> %s: %s Pokémon - %s - [%s] - %.1fkg - %.1fm - %d%% - %s - %d gen] - %s",
            p.id,
            p.name,
            p.description,
            tipos_formatados,
            habilidades_formatadas,
            p.weight_kg,
            p.height_m,
            p.capture_rate,
            p.is_legendary ? "true" : "false",
            p.generation,
            p.capture_date);

    // Imprimir na saída padrão
    printf("%s\n", output);

    // Escrever no arquivo de log
    fprintf(log_file, "%s\n", output);
}

int main()
{
    char csvPath[] = "/tmp/pokemon.csv"; // Caminho do arquivo CSV
    FILE *file = fopen(csvPath, "r");
    if (file == NULL)
    {
        printf("Erro ao abrir o arquivo %s\n", csvPath);
        return 1;
    }

    char line[MAX_LINE];
    char fields[12][MAX_FIELD];
    Pokemon pokemons[MAX_POKEMONS];
    int total_pokemons = 0;

    // Ler o cabeçalho
    if (fgets(line, sizeof(line), file) == NULL)
    {
        printf("Arquivo CSV vazio.\n");
        fclose(file);
        return 1;
    }

    // Ler cada linha do CSV
    while (fgets(line, sizeof(line), file) != NULL && total_pokemons < MAX_POKEMONS)
    {
        // Remover a nova linha
        line[strcspn(line, "\n")] = 0;

        // Parse da linha
        int num_fields = parse_csv_line(line, fields);
        if (num_fields != 12)
        {
            printf("Erro ao processar linha: %s\n", line);
            continue;
        }

        // Preencher a estrutura Pokemon
        pokemons[total_pokemons].id = atoi(fields[0]);
        pokemons[total_pokemons].generation = atoi(fields[1]);
        strcpy(pokemons[total_pokemons].name, fields[2]);
        strcpy(pokemons[total_pokemons].description, fields[3]);
        strcpy(pokemons[total_pokemons].type1, fields[4]);
        strcpy(pokemons[total_pokemons].type2, fields[5]);
        strcpy(pokemons[total_pokemons].abilities, fields[6]);

        // Remover os colchetes das habilidades
        strip_brackets(pokemons[total_pokemons].abilities);

        pokemons[total_pokemons].weight_kg = atof(fields[7]);
        pokemons[total_pokemons].height_m = atof(fields[8]);
        pokemons[total_pokemons].capture_rate = atoi(fields[9]);
        pokemons[total_pokemons].is_legendary = (strcmp(fields[10], "1") == 0) ? true : false;
        strcpy(pokemons[total_pokemons].capture_date, fields[11]);

        total_pokemons++;
    }

    fclose(file);

    // Seleção de Pokémons por ID
    Pokemon selected_pokemons[MAX_POKEMONS];
    int selected_count = 0;

    // printf("Digite os IDs dos Pokémon (Digite 'FIM' para encerrar):\n");
    while (1)
    {
        char input[MAX_FIELD];
        scanf("%s", input);
        if (strcmp(input, "FIM") == 0)
            break;
        int id = atoi(input);
        Pokemon *p = buscar_pokemon_por_id(pokemons, total_pokemons, id);
        if (p != NULL)
        {
            selected_pokemons[selected_count++] = *p;
        }
        else
        {
            printf("Pokémon com ID %d não encontrado.\n", id);
        }
    }

    // Ordenar os Pokémons selecionados pelo abilities usando Radix Sort
    radix_sort(selected_pokemons, selected_count);

    // Abrir o arquivo de log
    FILE *log_file = fopen("radixsort.txt", "w");
    if (log_file == NULL)
    {
        printf("Erro ao criar o arquivo de log.\n");
        return 1;
    }

    // Imprimir os Pokémons selecionados ordenados e escrever no log
    // printf("Pokémons Selecionados Ordenados:\n");
    for (int i = 0; i < selected_count; i++)
    {
        imprimir_pokemon(selected_pokemons[i], log_file);
    }

    fclose(log_file);

    return 0;
}
