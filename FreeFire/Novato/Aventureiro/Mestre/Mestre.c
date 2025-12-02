#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_COMPONENTES 20

// ======================================================
// STRUCT PRINCIPAL
// ======================================================

typedef struct {
    char nome[30];
    char tipo[20];
    int prioridade;  // 1 a 10
} Componente;

// ======================================================
// CONTADORES DE COMPARAÇÃO POR ALGORITMO
// ======================================================
long long compBubble = 0;
long long compInsertion = 0;
long long compSelection = 0;

// ======================================================
// FUNÇÕES DE UTILIDADE
// ======================================================

void trocar(Componente *a, Componente *b) {
    Componente temp = *a;
    *a = *b;
    *b = temp;
}

// ======================================================
// ORDENAÇÃO 1 — BUBBLE SORT (por nome)
// ======================================================

void bubbleSortNome(Componente vet[], int n) {
    compBubble = 0;

    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - 1 - i; j++) {
            compBubble++;
            if (strcmp(vet[j].nome, vet[j + 1].nome) > 0) {
                trocar(&vet[j], &vet[j + 1]);
            }
        }
    }
}

// ======================================================
// ORDENAÇÃO 2 — INSERTION SORT (por tipo)
// ======================================================

void insertionSortTipo(Componente vet[], int n) {
    compInsertion = 0;

    for (int i = 1; i < n; i++) {
        Componente chave = vet[i];
        int j = i - 1;

        while (j >= 0 && strcmp(vet[j].tipo, chave.tipo) > 0) {
            compInsertion++;
            vet[j + 1] = vet[j];
            j--;
        }
        compInsertion++;
        vet[j + 1] = chave;
    }
}

// ======================================================
// ORDENAÇÃO 3 — SELECTION SORT (por prioridade)
// ======================================================

void selectionSortPrioridade(Componente vet[], int n) {
    compSelection = 0;

    for (int i = 0; i < n - 1; i++) {
        int menor = i;

        for (int j = i + 1; j < n; j++) {
            compSelection++;
            if (vet[j].prioridade < vet[menor].prioridade) {
                menor = j;
            }
        }

        if (menor != i) {
            trocar(&vet[i], &vet[menor]);
        }
    }
}

// ======================================================
// BUSCA BINÁRIA — SOMENTE APÓS BUBBLE SORT
// ======================================================

int buscaBinariaPorNome(Componente vet[], int n, char chave[]) {
    int ini = 0, fim = n - 1;
    int comparacoes = 0;

    while (ini <= fim) {
        int meio = (ini + fim) / 2;
        comparacoes++;

        int cmp = strcmp(vet[meio].nome, chave);

        if (cmp == 0) {
            printf("\nComponente encontrado: %s (%s), prioridade %d\n",
                vet[meio].nome, vet[meio].tipo, vet[meio].prioridade);
            printf("Comparações na busca binária: %d\n", comparacoes);
            return meio;
        }

        if (cmp < 0) 
            ini = meio + 1;
        else 
            fim = meio - 1;
    }

    printf("\nComponente NÃO encontrado.\n");
    printf("Comparações: %d\n", comparacoes);
    return -1;
}

// ======================================================
// MOSTRAR COMPONENTES
// ======================================================

void mostrarComponentes(Componente vet[], int n) {
    printf("\n===== LISTA DE COMPONENTES =====\n");
    for (int i = 0; i < n; i++) {
        printf("%d) Nome: %s | Tipo: %s | Prioridade: %d\n",
               i + 1, vet[i].nome, vet[i].tipo, vet[i].prioridade);
    }
}

// ======================================================
// MEDIR TEMPO DE EXECUÇÃO DE UM ALGORITMO
// ======================================================

double medirTempo(void (*alg)(Componente[], int), Componente vet[], int n) {
    clock_t inicio = clock();
    alg(vet, n);
    clock_t fim = clock();

    return (double)(fim - inicio) / CLOCKS_PER_SEC;
}

// ======================================================
// MENU PRINCIPAL
// ======================================================

int main() {
    Componente torre[MAX_COMPONENTES];
    int total = 0;
    int op;
    char chave[30];

    do {
        printf("\n================ MÓDULO FINAL: TORRE DE FUGA ================\n");
        printf("1 - Cadastrar componente\n");
        printf("2 - Exibir componentes\n");
        printf("3 - Ordenar por NOME (Bubble Sort)\n");
        printf("4 - Ordenar por TIPO (Insertion Sort)\n");
        printf("5 - Ordenar por PRIORIDADE (Selection Sort)\n");
        printf("6 - Buscar componente por nome (Busca Binária)\n");
        printf("0 - Sair\n");
        printf("Escolha: ");
        scanf("%d", &op);
        getchar();

        switch (op) {
            case 1:
                if (total >= MAX_COMPONENTES) {
                    printf("Limite máximo atingido!\n");
                    break;
                }

                printf("Nome: ");
                fgets(torre[total].nome, 30, stdin);
                torre[total].nome[strcspn(torre[total].nome, "\n")] = '\0';

                printf("Tipo: ");
                fgets(torre[total].tipo, 20, stdin);
                torre[total].tipo[strcspn(torre[total].tipo, "\n")] = '\0';

                printf("Prioridade (1–10): ");
                scanf("%d", &torre[total].prioridade);
                getchar();

                total++;
                break;

            case 2:
                mostrarComponentes(torre, total);
                break;

            case 3: {
                double tempo = medirTempo(bubbleSortNome, torre, total);
                printf("\nOrdenado por NOME usando Bubble Sort!\n");
                printf("Comparações: %lld\n", compBubble);
                printf("Tempo: %.6f segundos\n", tempo);
                break;
            }

            case 4: {
                double tempo = medirTempo(insertionSortTipo, torre, total);
                printf("\nOrdenado por TIPO usando Insertion Sort!\n");
                printf("Comparações: %lld\n", compInsertion);
                printf("Tempo: %.6f segundos\n", tempo);
                break;
            }

            case 5: {
                double tempo = medirTempo(selectionSortPrioridade, torre, total);
                printf("\nOrdenado por PRIORIDADE usando Selection Sort!\n");
                printf("Comparações: %lld\n", compSelection);
                printf("Tempo: %.6f segundos\n", tempo);
                break;
            }

            case 6:
                printf("Nome do componente-chave para busca: ");
                fgets(chave, 30, stdin);
                chave[strcspn(chave, "\n")] = '\0';

                buscaBinariaPorNome(torre, total, chave);
                break;

        }

    } while (op != 0);

    return 0;
}
