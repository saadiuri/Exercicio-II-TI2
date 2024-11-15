// TP02Q01.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Definição da estrutura Pokemon
typedef struct
{
    int id;
    int generation;
    char name[100];
    char description[256];
    char **types; // Array de strings para tipos
    int num_types;
    char **abilities; // Array de strings para habilidades
    int num_abilities;
    double weight;
    double height;
    int capture_rate;
    int is_legendary;      // 0 ou 1
    char capture_date[11]; // Formato "dd/mm/yyyy"
} Pokemon;

// Função para remover espaços em branco no início e no fim de uma string
char *trim(char *str)
{
    char *end;
    // Remover espaços no início
    while (isspace((unsigned char)*str))
        str++;
    if (*str == 0) // Todos os espaços?
        return str;
    // Remover espaços no fim
    end = str + strlen(str) - 1;
    while (end > str && isspace((unsigned char)*end))
        end--;
    // Escrever novo terminador
    *(end + 1) = 0;
    return str;
}

// Função para dividir uma linha CSV em campos, respeitando vírgulas dentro de aspas
char **split_csv_line(char *line, int *num_fields)
{
    // printf("Depuração: Iniciando split_csv_line.\n"); // Depuração
    char **fields = NULL;
    int count = 0;
    char *ptr = line;
    char *start = ptr; // Inicializa start com o início da linha
    int in_quotes = 0;

    while (*ptr)
    {
        if (*ptr == '"')
        {
            in_quotes = !in_quotes;
        }
        else if (*ptr == ',' && !in_quotes)
        {
            // Encontrou uma vírgula fora de aspas
            int len = ptr - start;
            char *field = (char *)malloc(len + 1);
            if (field == NULL)
            {
                fprintf(stderr, "Erro de alocação de memória.\n");
                exit(1);
            }
            strncpy(field, start, len);
            field[len] = '\0';
            // printf("Depuração: Campo encontrado: '%s'\n", field); // Depuração
            //  Adiciona o campo ao array
            fields = (char **)realloc(fields, sizeof(char *) * (count + 1));
            if (fields == NULL)
            {
                fprintf(stderr, "Erro de realocação de memória.\n");
                exit(1);
            }
            fields[count++] = trim(field);
            start = ptr + 1;
        }
        ptr++;
    }

    // Adicionar o último campo
    if (ptr > start)
    {
        int len = ptr - start;
        char *field = (char *)malloc(len + 1);
        if (field == NULL)
        {
            fprintf(stderr, "Erro de alocação de memória.\n");
            exit(1);
        }
        strncpy(field, start, len);
        field[len] = '\0';
        // printf("Depuração: Último campo encontrado: '%s'\n", field); // Depuração
        fields = (char **)realloc(fields, sizeof(char *) * (count + 1));
        if (fields == NULL)
        {
            fprintf(stderr, "Erro de realocação de memória.\n");
            exit(1);
        }
        fields[count++] = trim(field);
    }

    *num_fields = count;
    // printf("Depuração: Número de campos encontrados: %d\n", count); // Depuração
    return fields;
}

// Função para formatar listas de strings para impressão
char *format_list(char **list, int count)
{
    if (count == 0)
    {
        char *empty = malloc(3);
        strcpy(empty, "[]");
        return empty;
    }
    // Estimar tamanho necessário
    int size = 2; // Para os colchetes
    for (int i = 0; i < count; i++)
    {
        size += strlen(list[i]) + 4; // Para as aspas e vírgula
    }
    char *formatted = malloc(size);
    strcpy(formatted, "[");
    for (int i = 0; i < count; i++)
    {
        strcat(formatted, "'");
        strcat(formatted, list[i]);
        strcat(formatted, "'");
        if (i != count - 1)
        {
            strcat(formatted, ", ");
        }
    }
    strcat(formatted, "]");
    return formatted;
}

// Função para imprimir os atributos de um Pokémon
void imprimir_pokemon(Pokemon p)
{
    char *formatted_types = format_list(p.types, p.num_types);
    char *formatted_abilities = format_list(p.abilities, p.num_abilities);

    printf("[#%d -> %s: %s - %s - %s - %.1fkg - %.1fm - %d%% - %s - %d gen] - %s\n",
           p.id,
           p.name,
           p.description,
           formatted_types,
           formatted_abilities,
           p.weight,
           p.height,
           p.capture_rate,
           p.is_legendary ? "true" : "false",
           p.generation,
           (strlen(p.capture_date) > 0) ? p.capture_date : "N/A");

    free(formatted_types);
    free(formatted_abilities);
}

// Função para ler e processar os campos de um Pokémon
void ler_pokemon(Pokemon *p, char **campos, int num_campos)
{
    // Inicializar listas
    p->types = NULL;
    p->num_types = 0;
    p->abilities = NULL;
    p->num_abilities = 0;

    // id
    if (num_campos > 0 && strlen(campos[0]) > 0)
    {
        p->id = atoi(campos[0]);
    }
    else
    {
        p->id = 0;
    }

    // generation
    if (num_campos > 1 && strlen(campos[1]) > 0)
    {
        p->generation = atoi(campos[1]);
    }
    else
    {
        p->generation = 0;
    }

    // name
    if (num_campos > 2 && strlen(campos[2]) > 0)
    {
        strncpy(p->name, campos[2], sizeof(p->name));
        p->name[sizeof(p->name) - 1] = '\0';
    }
    else
    {
        strcpy(p->name, "");
    }

    // description
    if (num_campos > 3 && strlen(campos[3]) > 0)
    {
        strncpy(p->description, campos[3], sizeof(p->description));
        p->description[sizeof(p->description) - 1] = '\0';
    }
    else
    {
        strcpy(p->description, "");
    }

    // type1
    if (num_campos > 4 && strlen(campos[4]) > 0)
    {
        p->types = (char **)realloc(p->types, sizeof(char *) * (p->num_types + 1));
        p->types[p->num_types] = strdup(campos[4]);
        p->num_types++;
    }

    // type2
    if (num_campos > 5 && strlen(campos[5]) > 0)
    {
        p->types = (char **)realloc(p->types, sizeof(char *) * (p->num_types + 1));
        p->types[p->num_types] = strdup(campos[5]);
        p->num_types++;
    }

    // abilities
    if (num_campos > 6 && strlen(campos[6]) > 0)
    {
        // Remover [ ] e ' do campo
        char *habilidades_clean = strdup(campos[6]);
        char *start = habilidades_clean;
        char *end;
        while (*start && (*start == '[' || *start == '\'' || *start == '\"'))
            start++;
        end = habilidades_clean + strlen(habilidades_clean) - 1;
        while (end > start && (*end == ']' || *end == '\'' || *end == '\"'))
        {
            *end = '\0';
            end--;
        }
        // Dividir por vírgula
        char *token = strtok(start, ",");
        while (token != NULL)
        {
            token = trim(token);
            if (strlen(token) > 0)
            {
                p->abilities = (char **)realloc(p->abilities, sizeof(char *) * (p->num_abilities + 1));
                p->abilities[p->num_abilities] = strdup(token);
                p->num_abilities++;
            }
            token = strtok(NULL, ",");
        }
        free(habilidades_clean);
    }

    // weight_kg
    if (num_campos > 7 && strlen(campos[7]) > 0)
    {
        p->weight = atof(campos[7]);
    }
    else
    {
        p->weight = 0.0;
    }

    // height_m
    if (num_campos > 8 && strlen(campos[8]) > 0)
    {
        p->height = atof(campos[8]);
    }
    else
    {
        p->height = 0.0;
    }

    // capture_rate
    if (num_campos > 9 && strlen(campos[9]) > 0)
    {
        p->capture_rate = atoi(campos[9]);
    }
    else
    {
        p->capture_rate = 0;
    }

    // is_legendary
    if (num_campos > 10 && strlen(campos[10]) > 0)
    {
        if (strcmp(campos[10], "1") == 0)
        {
            p->is_legendary = 1;
        }
        else
        {
            p->is_legendary = 0;
        }
    }
    else
    {
        p->is_legendary = 0;
    }

    // capture_date
    if (num_campos > 11 && strlen(campos[11]) > 0)
    {
        strncpy(p->capture_date, campos[11], sizeof(p->capture_date));
        p->capture_date[sizeof(p->capture_date) - 1] = '\0';
    }
    else
    {
        strcpy(p->capture_date, "");
    }
}

// Função para liberar memória alocada para um Pokémon
void liberar_pokemon(Pokemon *p)
{
    for (int i = 0; i < p->num_types; i++)
    {
        free(p->types[i]);
    }
    free(p->types);

    for (int i = 0; i < p->num_abilities; i++)
    {
        free(p->abilities[i]);
    }
    free(p->abilities);
}

int main()
{
    // Inicialização da lista dinâmica de Pokémons
    Pokemon *pokemons = NULL;
    int num_pokemons = 0;

    // Caminho do arquivo CSV
    char caminhoArquivo[256] = "pokemon.csv"; // Ajuste conforme necessário

    // Abrir o arquivo CSV
    FILE *file = fopen(caminhoArquivo, "r");
    if (file == NULL)
    {
        fprintf(stderr, "Erro ao abrir o arquivo %s\n", caminhoArquivo);
        return 1;
    }

    char linha[1024];
    int linha_atual = 0;

    // Ler o arquivo linha por linha
    while (fgets(linha, sizeof(linha), file))
    {
        // Remover a nova linha
        linha[strcspn(linha, "\n")] = '\0';

        // Ignorar a primeira linha (cabeçalho)
        if (linha_atual == 0)
        {
            linha_atual++;
            continue;
        }

        // Verificar se a linha contém apenas "FIM"
        if (strcmp(trim(linha), "FIM") == 0)
        {
            break;
        }

        // Dividir a linha em campos
        int num_campos = 0;
        char **campos = split_csv_line(linha, &num_campos);

        // Criar e preencher um Pokémon
        Pokemon p;
        ler_pokemon(&p, campos, num_campos);

        // Adicionar o Pokémon à lista
        pokemons = (Pokemon *)realloc(pokemons, sizeof(Pokemon) * (num_pokemons + 1));
        if (pokemons == NULL)
        {
            fprintf(stderr, "Erro de realocação de memória.\n");
            exit(1);
        }
        pokemons[num_pokemons++] = p;

        // Liberar a memória alocada para campos
        for (int i = 0; i < num_campos; i++)
        {
            free(campos[i]);
        }
        free(campos);
    }

    fclose(file);

    // Ler IDs da entrada padrão
    char input[100];
    while (fgets(input, sizeof(input), stdin))
    {
        // Remover a nova linha
        input[strcspn(input, "\n")] = '\0';

        // Verificar se é "FIM"
        if (strcmp(trim(input), "FIM") == 0)
        {
            break;
        }

        // Converter para inteiro
        int idProcurado = atoi(trim(input));

        // Buscar o Pokémon com o ID correspondente
        int encontrado = 0;
        for (int i = 0; i < num_pokemons; i++)
        {
            if (pokemons[i].id == idProcurado)
            {
                imprimir_pokemon(pokemons[i]);
                encontrado = 1;
                break;
            }
        }

        if (!encontrado)
        {
            printf("Pokémon com ID %d não encontrado.\n", idProcurado);
        }
    }

    // Liberar a memória alocada para Pokémons
    for (int i = 0; i < num_pokemons; i++)
    {
        liberar_pokemon(&pokemons[i]);
    }
    free(pokemons);

    return 0;
}
