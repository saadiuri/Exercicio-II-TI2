#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

// Função para remover caracteres indesejados de uma string
void cleanString(char *str)
{
    char garbage[] = {'\'', '[', ']'};
    int garbageSize = sizeof(garbage) / sizeof(garbage[0]);
    int index = 0;

    for (int i = 0; str[i]; i++)
    {
        int isGarbage = 0;
        for (int j = 0; j < garbageSize; j++)
        {
            if (str[i] == garbage[j])
            {
                isGarbage = 1;
                break;
            }
        }
        if (!isGarbage)
        {
            str[index++] = str[i];
        }
    }

    str[index] = '\0';
}

// Estrutura para lista ligada de strings
typedef struct StringList
{
    char *string;
    struct StringList *next;
} StringList;

// Função para criar uma nova lista ligada
StringList *newStringList()
{
    StringList *list = (StringList *)malloc(sizeof(StringList));
    if (list == NULL)
    {
        fprintf(stderr, "Erro ao alocar memória para StringList.\n");
        exit(1);
    }
    list->string = NULL;
    list->next = NULL;
    return list;
}

// Função para adicionar uma string à lista
void addStringToList(StringList **head, char *string)
{
    if (*head == NULL)
    {
        // Se a lista estiver vazia, cria o primeiro nó
        *head = newStringList();
        (*head)->string = string;
        (*head)->next = NULL;
    }
    else
    {
        // Se a lista não estiver vazia, adiciona um novo nó no final
        StringList *current = *head;

        // Percorre a lista até o último elemento
        while (current->next != NULL)
        {
            current = current->next;
        }

        // Adiciona um novo nó no final
        current->next = newStringList();
        current->next->string = string;
    }
}

// Função para converter uma lista ligada em uma string separada por vírgulas
char *stringListToString(StringList *head)
{
    StringList *current = head;

    if (current == NULL)
    {
        return strdup(""); // Retorna uma string vazia
    }

    // Calcula o tamanho necessário
    size_t total_length = 0;
    while (current != NULL)
    {
        total_length += strlen(current->string) + 2; // +2 para ", " ou '\0'
        current = current->next;
    }

    char *str = (char *)malloc(total_length);
    if (str == NULL)
    {
        fprintf(stderr, "Erro ao alocar memória para stringListToString.\n");
        exit(1);
    }
    str[0] = '\0'; // Inicializa a string vazia

    current = head;
    while (current != NULL)
    {
        strcat(str, current->string);
        if (current->next != NULL)
        {
            strcat(str, ", ");
        }
        current = current->next;
    }

    return str;
}

// Função para criar uma lista ligada a partir de uma string separada por vírgulas
StringList *stringListFromString(char *str)
{
    StringList *list = NULL;
    char *token = strtok(str, ",");
    while (token != NULL)
    {
        // Remover espaços em branco iniciais e finais
        while (*token == ' ')
            token++;
        char *end = token + strlen(token) - 1;
        while (end > token && (*end == ' ' || *end == '\n' || *end == '\r'))
        {
            *end = '\0';
            end--;
        }

        addStringToList(&list, strdup(token)); // Duplicar a string para evitar problemas de memória
        token = strtok(NULL, ",");
    }
    return list;
}

// Estrutura para data
typedef struct Date
{
    int dia;
    int mes;
    int ano;
} Date;

// Função para converter uma data em string
char *dateToString(Date date)
{
    char *str = (char *)malloc(11 * sizeof(char)); // "dd-mm-yyyy" + '\0' = 11 caracteres
    if (str == NULL)
    {
        fprintf(stderr, "Erro ao alocar memória para dateToString.\n");
        exit(1);
    }

    sprintf(str, "%02d-%02d-%04d", date.dia, date.mes, date.ano);

    return str;
}

// Função para converter uma string em data
Date stringToDate(char *str)
{
    Date date;

    if (strchr(str, '-') != NULL)
    {
        // Formato de data é "dd-mm-yyyy"
        sscanf(str, "%d-%d-%d", &date.dia, &date.mes, &date.ano);
    }
    else if (strchr(str, '/') != NULL)
    {
        // Formato de data é "dd/mm/yyyy"
        sscanf(str, "%d/%d/%d", &date.dia, &date.mes, &date.ano);
    }
    else
    {
        // Formato desconhecido, inicializa com zeros
        date.dia = 0;
        date.mes = 0;
        date.ano = 0;
    }

    return date;
}

// Estrutura para Pokémon
typedef struct Pokemon
{
    char *id;
    char *generation;
    char *name;
    char *description;
    char *type1;
    char *type2;
    StringList *abilities;
    float weight_kg;
    float height_m;
    int capture_rate;
    bool is_legendary;
    Date capture_date;
} Pokemon;

// Funções Getter e Setter para cada campo

// id
char *getId(Pokemon *pokemon)
{
    return pokemon->id;
}

void setId(Pokemon *pokemon, char *id)
{
    pokemon->id = strdup(id);
}

// generation
char *getGeneration(Pokemon *pokemon)
{
    return pokemon->generation;
}

void setGeneration(Pokemon *pokemon, char *generation)
{
    pokemon->generation = strdup(generation);
}

// name
char *getName(Pokemon *pokemon)
{
    return pokemon->name;
}

void setName(Pokemon *pokemon, char *name)
{
    pokemon->name = strdup(name);
}

// description
char *getDescription(Pokemon *pokemon)
{
    return pokemon->description;
}

void setDescription(Pokemon *pokemon, char *description)
{
    pokemon->description = strdup(description);
}

// type1
char *getType1(Pokemon *pokemon)
{
    return pokemon->type1;
}

void setType1(Pokemon *pokemon, char *type1)
{
    pokemon->type1 = strdup(type1);
}

// type2
char *getType2(Pokemon *pokemon)
{
    return pokemon->type2;
}

void setType2(Pokemon *pokemon, char *type2)
{
    pokemon->type2 = strdup(type2);
}

// abilities
StringList *getAbilities(Pokemon *pokemon)
{
    return pokemon->abilities;
}

void setAbilities(Pokemon *pokemon, StringList *abilities)
{
    pokemon->abilities = abilities;
}

// weight_kg
float getWeightKg(Pokemon *pokemon)
{
    return pokemon->weight_kg;
}

void setWeightKg(Pokemon *pokemon, float weight_kg)
{
    pokemon->weight_kg = weight_kg;
}

// height_m
float getHeightM(Pokemon *pokemon)
{
    return pokemon->height_m;
}

void setHeightM(Pokemon *pokemon, float height_m)
{
    pokemon->height_m = height_m;
}

// capture_rate
int getCaptureRate(Pokemon *pokemon)
{
    return pokemon->capture_rate;
}

void setCaptureRate(Pokemon *pokemon, int capture_rate)
{
    pokemon->capture_rate = capture_rate;
}

// is_legendary
bool getIsLegendary(Pokemon *pokemon)
{
    return pokemon->is_legendary;
}

void setIsLegendary(Pokemon *pokemon, bool is_legendary)
{
    pokemon->is_legendary = is_legendary;
}

void setIsLegendaryString(Pokemon *pokemon, char *is_legendaryStr)
{
    pokemon->is_legendary = (strcmp(is_legendaryStr, "TRUE") == 0 || strcmp(is_legendaryStr, "VERDADEIRO") == 0);
}

// capture_date
Date getCaptureDate(Pokemon *pokemon)
{
    return pokemon->capture_date;
}

void setCaptureDateDate(Pokemon *pokemon, Date capture_date)
{
    pokemon->capture_date = capture_date;
}

void setCaptureDateString(Pokemon *pokemon, char *capture_dateStr)
{
    pokemon->capture_date = stringToDate(capture_dateStr);
}

// Função para criar um novo Pokémon
Pokemon novoPokemon(
    char *id,
    char *generation,
    char *name,
    char *description,
    char *type1,
    char *type2,
    char *abilitiesStr,
    float weight_kg,
    float height_m,
    int capture_rate,
    char *is_legendaryStr,
    char *capture_dateStr)
{
    Pokemon p;

    setId(&p, id);
    setGeneration(&p, generation);
    setName(&p, name);
    setDescription(&p, description);
    setType1(&p, type1);
    setType2(&p, type2);

    StringList *abilities = stringListFromString(abilitiesStr);
    setAbilities(&p, abilities);

    p.weight_kg = weight_kg;
    p.height_m = height_m;
    p.capture_rate = capture_rate;
    setIsLegendaryString(&p, is_legendaryStr);
    setCaptureDateString(&p, capture_dateStr);

    return p;
}

// Função para imprimir um Pokémon
void imprimirPokemon(Pokemon *pokemon)
{
    printf("[%s ## ", getId(pokemon));
    printf("%s ## ", getGeneration(pokemon));
    printf("%s ## ", getName(pokemon));
    printf("%s ## ", getDescription(pokemon));
    printf("%s ## ", getType1(pokemon));
    printf("%s ## ", getType2(pokemon));
    printf("{%s} ## ", stringListToString(getAbilities(pokemon)));
    printf("%.2f ## ", getWeightKg(pokemon));
    printf("%.2f ## ", getHeightM(pokemon));
    printf("%d ## ", getCaptureRate(pokemon));
    printf("%s ## ", getIsLegendary(pokemon) ? "TRUE" : "FALSE");
    printf("%s]\n", dateToString(getCaptureDate(pokemon)));
}

// Função para imprimir uma lista de Pokémon
void imprimirPersonagens(Pokemon personagens[], int n)
{
    for (int i = 0; i < n; i++)
    {
        imprimirPokemon(&personagens[i]);
    }
}

int main()
{
    // Definir o caminho para o CSV
    char *path = "/tmp/pokemon.csv";
    FILE *file = fopen(path, "r");
    if (file == NULL)
    {
        fprintf(stderr, "Erro ao abrir o arquivo %s\n", path);
        return 1;
    }

    Pokemon personagens[1000]; // Ajuste o tamanho conforme necessário
    int n = 0;

    char line[1024]; // Aumente o tamanho se necessário
    // Ler a primeira linha de cabeçalho
    if (fgets(line, sizeof(line), file) == NULL)
    {
        fprintf(stderr, "Arquivo CSV está vazio.\n");
        fclose(file);
        return 1;
    }

    while (fgets(line, sizeof(line), file) != NULL)
    {
        // Remover o caractere de nova linha no final
        line[strcspn(line, "\r\n")] = 0;

        char *token = line;
        char *id = strsep(&token, ",");
        char *generation = strsep(&token, ",");
        char *name = strsep(&token, ",");
        char *description = strsep(&token, ",");
        char *type1 = strsep(&token, ",");
        char *type2 = strsep(&token, ",");
        char *abilitiesStr = strsep(&token, ",");
        char *weightKgStr = strsep(&token, ",");
        char *heightMStr = strsep(&token, ",");
        char *captureRateStr = strsep(&token, ",");
        char *isLegendaryStr = strsep(&token, ",");
        char *captureDateStr = strsep(&token, ",");

        // Verificar se todos os campos foram lidos corretamente
        if (id == NULL || generation == NULL || name == NULL || description == NULL ||
            type1 == NULL || type2 == NULL || abilitiesStr == NULL || weightKgStr == NULL ||
            heightMStr == NULL || captureRateStr == NULL || isLegendaryStr == NULL ||
            captureDateStr == NULL)
        {
            fprintf(stderr, "Linha com formato inválido: %s\n", line);
            continue;
        }

        // Conversões
        float weight_kg = atof(weightKgStr);
        float height_m = atof(heightMStr);
        int capture_rate = atoi(captureRateStr);

        // Criar o Pokémon
        Pokemon p = novoPokemon(
            id,
            generation,
            name,
            description,
            type1,
            type2,
            abilitiesStr,
            weight_kg,
            height_m,
            capture_rate,
            isLegendaryStr,
            captureDateStr);

        personagens[n++] = p;

        if (n >= 1000)
        { // Evitar exceder o tamanho do array
            fprintf(stderr, "Número máximo de personagens alcançado.\n");
            break;
        }
    }
    fclose(file);

    // Selecionar Pokémon por ID
    Pokemon pSelecionados[1000];
    int tam = 0;
    char idBusca[50];
    // printf("Digite os IDs dos Pokémon (Digite 'FIM' para encerrar):\n");
    scanf("%s", idBusca);
    while (strcmp(idBusca, "FIM") != 0)
    {
        // Buscar Pokémon pelo ID
        bool encontrado = false;
        for (int i = 0; i < n; i++)
        {
            if (strcmp(idBusca, personagens[i].id) == 0)
            {
                pSelecionados[tam++] = personagens[i];
                encontrado = true;
                break;
            }
        }

        if (!encontrado)
        {
            printf("Pokémon com ID %s não encontrado.\n", idBusca);
        }

        scanf("%s", idBusca);
    }

    // Ordenar personagens pelo nome usando Bubble Sort
    for (int i = 0; i < tam - 1; i++)
    {
        for (int j = i + 1; j < tam; j++)
        {
            if (strcmp(pSelecionados[i].name, pSelecionados[j].name) > 0)
            {
                Pokemon temp = pSelecionados[i];
                pSelecionados[i] = pSelecionados[j];
                pSelecionados[j] = temp;
            }
        }
    }

    // Buscar nomes usando Busca Binária
    char nomeBusca[100];
    // printf("Digite os nomes dos Pokémon para buscar (Digite 'FIM' para encerrar):\n");
    scanf(" %[^\r\n]", nomeBusca);
    while (strcmp(nomeBusca, "FIM") != 0)
    {
        int inicio = 0;
        int fim = tam - 1;
        bool encontrado = false;

        while (inicio <= fim)
        {
            int meio = inicio + (fim - inicio) / 2;
            int cmp = strcmp(nomeBusca, pSelecionados[meio].name);

            if (cmp == 0)
            {
                encontrado = true;
                break;
            }
            else if (cmp < 0)
            {
                fim = meio - 1;
            }
            else
            {
                inicio = meio + 1;
            }
        }

        if (encontrado)
            printf("SIM\n");
        else
            printf("NAO\n");

        scanf(" %[^\r\n]", nomeBusca);
    }

    // Imprimir os Pokémon selecionados
    /* printf("Pokémons Selecionados:\n");
     imprimirPersonagens(pSelecionados, tam);

     // Liberação de memória (Opcional, mas recomendado)
     for (int i = 0; i < n; i++) {
         free(personagens[i].id);
         free(personagens[i].generation);
         free(personagens[i].name);
         free(personagens[i].description);
         free(personagens[i].type1);
         free(personagens[i].type2);

         // Liberar habilidades
         StringList *current = personagens[i].abilities;
         while (current != NULL) {
             StringList *temp = current;
             current = current->next;
             free(temp->string);
             free(temp);
         }

         // free(personagens[i].capture_dateStr); // Se tiver sido alocado dinamicamente
     }

     for (int i = 0; i < tam; i++) {
         free(pSelecionados[i].id);
         free(pSelecionados[i].generation);
         free(pSelecionados[i].name);
         free(pSelecionados[i].description);
         free(pSelecionados[i].type1);
         free(pSelecionados[i].type2);

         // Liberar habilidades
         StringList *current = pSelecionados[i].abilities;
         while (current != NULL) {
             StringList *temp = current;
             current = current->next;
             free(temp->string);
             free(temp);
         }

         // free(pSelecionados[i].capture_dateStr); // Se tiver sido alocado dinamicamente
     }*/

    return 0;
}
