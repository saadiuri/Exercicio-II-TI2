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

// Função para comparar dois Pokémons
int comparar_pokemons(Pokemon p1, Pokemon p2)
{
    if (p1.weight_kg < p2.weight_kg)
        return -1;
    else if (p1.weight_kg > p2.weight_kg)
        return 1;
    else
    {
        return strcmp(p1.name, p2.name);
    }
}

// Função de Shellsort para ordenar Pokémons por weight e, em caso de empate, por name
void shellsort(Pokemon array[], int n)
{
    // Começar com um gap grande e reduzir gradualmente
    for (int gap = n / 2; gap > 0; gap /= 2)
    {
        // Fazer um insertion sort para esse gap
        for (int i = gap; i < n; i++)
        {
            Pokemon temp = array[i];
            int j = i;
            while (j >= gap && comparar_pokemons(array[j - gap], temp) > 0)
            {
                array[j] = array[j - gap];
                j -= gap;
            }
            array[j] = temp;
        }
    }
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

    // Construir a string de tipos
    char tipos_formatados[2 * MAX_FIELD];
    if (strcmp(types2, "N/A") == 0)
    {
        sprintf(tipos_formatados, "'%s'", types1);
    }
    else
    {
        sprintf(tipos_formatados, "'%s', '%s'", types1, types2);
    }

    // Construir a string de habilidades
    char habilidades_formatadas[MAX_FIELD];
    strcpy(habilidades_formatadas, p.abilities);

    // Imprimir na saída padrão
    printf("[#%d -> %s: %s Pokémon - [%s] - ['%s'] - %.1fkg - %.1fm - %d%% - %s - %d gen] - %s\n",
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

    // Escrever no arquivo de log
    fprintf(log_file, "[#%d -> %s: %s Pokémon - [%s] - ['%s'] - %.1fkg - %.1fm - %d%% - %s - %d gen] - %s\n",
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

    // Ordenar os Pokémons selecionados pelo weight usando Shellsort
    shellsort(selected_pokemons, selected_count);

    // Abrir o arquivo de log
    FILE *log_file = fopen("shellsort.txt", "w");
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
