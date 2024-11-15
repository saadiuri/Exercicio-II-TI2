#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME_LEN 100
#define MAX_TYPE_LEN 50
#define MAX_ABILITY_LEN 50
#define MAX_ABILITIES 3
#define MAX_TYPES 2
#define MAX_POKEMONS 100

typedef struct
{
    char id[10];
    char name[MAX_NAME_LEN];
    char classification[MAX_NAME_LEN];
    char types[MAX_TYPES][MAX_TYPE_LEN];
    char abilities[MAX_ABILITIES][MAX_ABILITY_LEN];
    float weight;
    float height;
    float catchRate;
    int shiny;
    int generation;
    int captureDate; // Usar formato YYYYMMDD para simplificar comparação de datas
} Pokemon;

// Função para comparar Pokémons por data de captura e, em caso de empate, pelo nome
int comparePokemons(const Pokemon *p1, const Pokemon *p2)
{
    if (p1->captureDate != p2->captureDate)
    {
        return p1->captureDate - p2->captureDate;
    }
    return strcmp(p1->name, p2->name);
}

// Função de ordenação parcial por inserção
void insertionSortPartial(Pokemon *pokemons, int n, int k)
{
    if (k > n)
        k = n;

    for (int i = 1; i < k; i++)
    {
        Pokemon key = pokemons[i];
        int j = i - 1;

        while (j >= 0 && comparePokemons(&pokemons[j], &key) > 0)
        {
            pokemons[j + 1] = pokemons[j];
            j = j - 1;
        }
        pokemons[j + 1] = key;
    }
}

// Função para imprimir os Pokémons ordenados
void printPokemons(Pokemon *pokemons, int n)
{
    for (int i = 0; i < n; i++)
    {
        // printf("%d\n", i + 1);
        printf("[#%s -> %s: %s Pokémon - [", pokemons[i].id, pokemons[i].name, pokemons[i].classification);

        // Imprimir tipos
        for (int j = 0; j < MAX_TYPES; j++)
        {
            if (j > 0 && strlen(pokemons[i].types[j]) > 0)
            {
                printf(", ");
            }
            printf("'%s'", pokemons[i].types[j]);
        }
        printf("] - [");

        // Imprimir habilidades
        for (int j = 0; j < MAX_ABILITIES; j++)
        {
            if (j > 0 && strlen(pokemons[i].abilities[j]) > 0)
            {
                printf(", ");
            }
            printf("'%s'", pokemons[i].abilities[j]);
        }
        printf("] - %.1fkg - %.1fm - %.0f%% - %s - %d gen] - %02d/%02d/%04d\n",
               pokemons[i].weight,
               pokemons[i].height,
               pokemons[i].catchRate,
               pokemons[i].shiny ? "true" : "false",
               pokemons[i].generation,
               pokemons[i].captureDate % 100,         // dia
               (pokemons[i].captureDate / 100) % 100, // mês
               pokemons[i].captureDate / 10000);      // ano
    }
}

// Função para converter uma string de data (dd/MM/yyyy) para formato YYYYMMDD como inteiro
int parseDate(char *dateStr)
{
    int day, month, year;
    sscanf(dateStr, "%d/%d/%d", &day, &month, &year);
    return year * 10000 + month * 100 + day;
}

int main()
{
    // Exemplo de dados de Pokémons
    Pokemon pokemons[MAX_POKEMONS] = {
        {"132", "Ditto", "Transform", {"normal"}, {"Limber", "Imposter"}, 4.0, 0.3, 35.0, 0, 1, parseDate("15/01/1996")},
        {"047", "Parasect", "Mushroom", {"bug", "grass"}, {"Effect Spore", "Dry Skin", "Damp"}, 29.5, 1.0, 75.0, 0, 1, parseDate("04/04/1996")},
        {"056", "Mankey", "Pig Monkey", {"fighting"}, {"Vital Spirit", "Anger Point", "Defiant"}, 28.0, 0.5, 190.0, 0, 1, parseDate("02/05/1996")},
        {"091", "Cloyster", "Bivalve", {"water", "ice"}, {"Shell Armor", "Skill Link", "Overcoat"}, 132.5, 1.5, 60.0, 0, 1, parseDate("05/06/1996")},
        {"137", "Porygon", "Virtual", {"normal"}, {"Trace", "Download", "Analytic"}, 36.5, 0.8, 45.0, 0, 1, parseDate("06/06/1996")},
        {"061", "Poliwhirl", "Tadpole", {"water"}, {"Water Absorb", "Damp", "Swift Swim"}, 20.0, 1.0, 120.0, 0, 1, parseDate("24/10/1996")},
        {"046", "Paras", "Mushroom", {"bug", "grass"}, {"Effect Spore", "Dry Skin", "Damp"}, 5.4, 0.3, 190.0, 0, 1, parseDate("01/11/1996")},
        {"189", "Jumpluff", "Cottonweed", {"grass", "flying"}, {"Chlorophyll", "Leaf Guard", "Infiltrator"}, 3.0, 0.8, 45.0, 0, 2, parseDate("15/05/1999")},
        {"181", "Ampharos", "Light", {"electric"}, {"Static", "Plus"}, 61.5, 1.4, 45.0, 0, 2, parseDate("25/05/1999")},
        {"252", "Treecko", "Wood Gecko", {"grass"}, {"Overgrow", "Unburden"}, 5.0, 0.5, 45.0, 0, 3, parseDate("19/01/2002")},
    };

    int numPokemons = 10;
    int k = 10; // Número de Pokémons a serem ordenados parcialmente

    // Ordenação parcial por inserção
    insertionSortPartial(pokemons, numPokemons, k);

    // Imprimir os primeiros k Pokémons ordenados
    // printf("Pokémons ordenados (primeiros %d):\n", k);
    printPokemons(pokemons, k);

    return 0;
}
