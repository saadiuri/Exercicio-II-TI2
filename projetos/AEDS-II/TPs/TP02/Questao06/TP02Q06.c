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

// Função para trocar dois Pokémons
void trocar(Pokemon *a, Pokemon *b)
{
    Pokemon temp = *a;
    *a = *b;
    *b = temp;
}

// Função de Seleção Recursiva para ordenar por nome
void selecao_recursiva(Pokemon array[], int n, int start)
{
    if (start >= n - 1)
        return;

    // Encontrar o índice do menor elemento a partir de 'start'
    int min_idx = start;
    for (int i = start + 1; i < n; i++)
    {
        if (strcmp(array[i].name, array[min_idx].name) < 0)
        {
            min_idx = i;
        }
    }

    // Trocar o menor encontrado com o elemento na posição 'start'
    if (min_idx != start)
    {
        trocar(&array[start], &array[min_idx]);
    }

    // Chamada recursiva para o próximo elemento
    selecao_recursiva(array, n, start + 1);
}

// Função para imprimir um Pokémon no formato especificado
void imprimir_pokemon(Pokemon p, FILE *log_file)
{
    char types1[MAX_FIELD];
    char types2[MAX_FIELD];
    strcpy(types1, p.type1);
    if (strlen(p.type2) > 0)
    {
        strcpy(types2, p.type2);
    }
    else
    {
        strcpy(types2, "N/A");
    }

    // Imprimir na saída padrão
    printf("[#%d -> %s: %s Pokémon - [%s, %s] - [%s] - %.1fkg - %.1fm - %d%% - %s - %d gen] - %s\n",
           p.id,
           p.name,
           p.description,
           types1,
           types2,
           p.abilities,
           p.weight_kg,
           p.height_m,
           p.capture_rate,
           p.is_legendary ? "true" : "false",
           p.generation,
           p.capture_date);

    // Escrever no arquivo de log
    fprintf(log_file, "[#%d -> %s: %s Pokémon - [%s, %s] - [%s] - %.1fkg - %.1fm - %d%% - %s - %d gen] - %s\n",
            p.id,
            p.name,
            p.description,
            types1,
            types2,
            p.abilities,
            p.weight_kg,
            p.height_m,
            p.capture_rate,
            p.is_legendary ? "true" : "false",
            p.generation,
            p.capture_date);
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

    // Ordenar os Pokémons selecionados pelo nome usando Seleção Recursiva
    selecao_recursiva(selected_pokemons, selected_count, 0);

    // Abrir o arquivo de log
    FILE *log_file = fopen("selecaoRecursiva.txt", "w");
    if (log_file == NULL)
    {
        printf("Erro ao criar o arquivo de log.\n");
        return 1;
    }

    // Imprimir os Pokémons selecionados e escrever no log
    for (int i = 0; i < selected_count; i++)
    {
        imprimir_pokemon(selected_pokemons[i], log_file);
    }

    fclose(log_file);

    return 0;
}
