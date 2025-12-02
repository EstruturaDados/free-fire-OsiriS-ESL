#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ITENS 10

// ======================================================
// STRUCTS
// ======================================================

typedef struct {
    char nome[30];
    char tipo[20];
    int quantidade;
} Item;

typedef struct No {
    Item dados;
    struct No *proximo;
} No;

// ======================================================
// CONTADORES DE COMPARAÇÃO
// ======================================================
int compSequencialVetor = 0;
int compBinaria = 0;
int compSequencialLista = 0;

// ======================================================
// FUNÇÕES DO VETOR
// ======================================================
void inserirItemVetor(Item vet[], int *total);
void removerItemVetor(Item vet[], int *total);
void listarVetor(Item vet[], int total);
int buscarSequencialVetor(Item vet[], int total, char nome[]);
void ordenarVetor(Item vet[], int total);
int buscarBinariaVetor(Item vet[], int total, char nome[]);

// ======================================================
// FUNÇÕES DA LISTA ENCADEADA
// ======================================================
void inserirItemLista(No **inicio);
void removerItemLista(No **inicio);
void listarLista(No *inicio);
No *buscarSequencialLista(No *inicio, char nome[]);

// ======================================================
// MENU PRINCIPAL
// ======================================================
int main() {

    Item mochilaVetor[MAX_ITENS];
    int total = 0;

    No *mochilaLista = NULL;

    int op, modo;
    char nomeBusca[30];

    do {
        printf("\n=============== SISTEMA DE MOCHILA ===============\n");
        printf("1 - Usar mochila com VETOR\n");
        printf("2 - Usar mochila com LISTA ENCADEADA\n");
        printf("0 - Sair\n");
        printf("Escolha a estrutura: ");
        scanf("%d", &modo);
        getchar();

        if (modo == 1) {
            do {
                printf("\n--- Mochila (Vetor) ---\n");
                printf("1 - Inserir item\n");
                printf("2 - Remover item\n");
                printf("3 - Listar itens\n");
                printf("4 - Buscar sequencial\n");
                printf("5 - Ordenar vetor\n");
                printf("6 - Buscar binaria\n");
                printf("0 - Voltar\n");
                printf("Opcao: ");
                scanf("%d", &op);
                getchar();

                switch (op) {
                    case 1: inserirItemVetor(mochilaVetor, &total); break;
                    case 2: removerItemVetor(mochilaVetor, &total); break;
                    case 3: listarVetor(mochilaVetor, total); break;

                    case 4:
                        printf("Nome do item: ");
                        fgets(nomeBusca, 30, stdin);
                        nomeBusca[strcspn(nomeBusca, "\n")] = '\0';

                        compSequencialVetor = 0;
                        buscarSequencialVetor(mochilaVetor, total, nomeBusca);
                        printf("Comparacoes: %d\n", compSequencialVetor);
                        break;

                    case 5:
                        ordenarVetor(mochilaVetor, total);
                        printf("Vetor ordenado!\n");
                        break;

                    case 6:
                        printf("Nome do item: ");
                        fgets(nomeBusca, 30, stdin);
                        nomeBusca[strcspn(nomeBusca, "\n")] = '\0';

                        compBinaria = 0;
                        buscarBinariaVetor(mochilaVetor, total, nomeBusca);
                        printf("Comparacoes (binaria): %d\n", compBinaria);
                        break;
                }
            } while (op != 0);
        }

        else if (modo == 2) {
            do {
                printf("\n--- Mochila (Lista Encadeada) ---\n");
                printf("1 - Inserir item\n");
                printf("2 - Remover item\n");
                printf("3 - Listar itens\n");
                printf("4 - Buscar sequencial\n");
                printf("0 - Voltar\n");
                printf("Opcao: ");
                scanf("%d", &op);
                getchar();

                switch (op) {
                    case 1: inserirItemLista(&mochilaLista); break;
                    case 2: removerItemLista(&mochilaLista); break;
                    case 3: listarLista(mochilaLista); break;

                    case 4:
                        printf("Nome do item: ");
                        fgets(nomeBusca, 30, stdin);
                        nomeBusca[strcspn(nomeBusca, "\n")] = '\0';

                        compSequencialLista = 0;
                        buscarSequencialLista(mochilaLista, nomeBusca);
                        printf("Comparacoes: %d\n", compSequencialLista);
                        break;
                }
            } while (op != 0);
        }

    } while (modo != 0);

    return 0;
}

// ======================================================
// IMPLEMENTAÇÃO DO VETOR
// ======================================================

void inserirItemVetor(Item vet[], int *total) {
    if (*total >= MAX_ITENS) {
        printf("Mochila cheia!\n");
        return;
    }

    Item novo;
    printf("Nome: ");
    fgets(novo.nome, 30, stdin); novo.nome[strcspn(novo.nome, "\n")] = '\0';
    printf("Tipo: ");
    fgets(novo.tipo, 20, stdin); novo.tipo[strcspn(novo.tipo, "\n")] = '\0';
    printf("Quantidade: ");
    scanf("%d", &novo.quantidade); getchar();

    vet[*total] = novo;
    (*total)++;

    printf("Item adicionado!\n");
}

void removerItemVetor(Item vet[], int *total) {
    char nome[30];
    printf("Nome do item para remover: ");
    fgets(nome, 30, stdin);
    nome[strcspn(nome, "\n")] = '\0';

    for (int i = 0; i < *total; i++) {
        if (strcmp(vet[i].nome, nome) == 0) {
            for (int j = i; j < *total - 1; j++)
                vet[j] = vet[j + 1];
            (*total)--;
            printf("Item removido!\n");
            return;
        }
    }

    printf("Item nao encontrado.\n");
}

void listarVetor(Item vet[], int total) {
    printf("\n--- Mochila Vetor ---\n");
    if (total == 0) {
        printf("Vazia.\n");
        return;
    }
    for (int i = 0; i < total; i++) {
        printf("%d) %s - %s - %d\n", i + 1, vet[i].nome, vet[i].tipo, vet[i].quantidade);
    }
}

int buscarSequencialVetor(Item vet[], int total, char nome[]) {
    for (int i = 0; i < total; i++) {
        compSequencialVetor++;
        if (strcmp(vet[i].nome, nome) == 0) {
            printf("Item encontrado: %s (%s), qtd: %d\n", vet[i].nome, vet[i].tipo, vet[i].quantidade);
            return i;
        }
    }
    printf("Item nao encontrado.\n");
    return -1;
}

void ordenarVetor(Item vet[], int total) {
    Item temp;
    for (int i = 0; i < total - 1; i++) {
        for (int j = 0; j < total - 1 - i; j++) {
            if (strcmp(vet[j].nome, vet[j + 1].nome) > 0) {
                temp = vet[j];
                vet[j] = vet[j + 1];
                vet[j + 1] = temp;
            }
        }
    }
}

int buscarBinariaVetor(Item vet[], int total, char nome[]) {
    int ini = 0, fim = total - 1, meio;

    while (ini <= fim) {
        meio = (ini + fim) / 2;
        compBinaria++;

        int cmp = strcmp(vet[meio].nome, nome);

        if (cmp == 0) {
            printf("Item encontrado: %s\n", vet[meio].nome);
            return meio;
        }
        if (cmp < 0)
            ini = meio + 1;
        else
            fim = meio - 1;
    }

    printf("Item nao encontrado.\n");
    return -1;
}

// ======================================================
// IMPLEMENTAÇÃO DA LISTA ENCADEADA
// ======================================================

void inserirItemLista(No **inicio) {
    No *novo = (No*) malloc(sizeof(No));

    printf("Nome: ");
    fgets(novo->dados.nome, 30, stdin);
    novo->dados.nome[strcspn(novo->dados.nome, "\n")] = '\0';

    printf("Tipo: ");
    fgets(novo->dados.tipo, 20, stdin);
    novo->dados.tipo[strcspn(novo->dados.tipo, "\n")] = '\0';

    printf("Quantidade: ");
    scanf("%d", &novo->dados.quantidade);
    getchar();

    novo->proximo = *inicio;
    *inicio = novo;

    printf("Item inserido na lista!\n");
}

void removerItemLista(No **inicio) {
    char nome[30];
    printf("Nome do item para remover: ");
    fgets(nome, 30, stdin);
    nome[strcspn(nome, "\n")] = '\0';

    No *atual = *inicio;
    No *anterior = NULL;

    while (atual != NULL) {
        if (strcmp(atual->dados.nome, nome) == 0) {
            if (anterior == NULL)
                *inicio = atual->proximo;
            else
                anterior->proximo = atual->proximo;

            free(atual);
            printf("Item removido!\n");
            return;
        }
        anterior = atual;
        atual = atual->proximo;
    }

    printf("Item nao encontrado.\n");
}

void listarLista(No *inicio) {
    printf("\n--- Mochila Lista ---\n");
    if (inicio == NULL) {
        printf("Vazia.\n");
        return;
    }

    No *temp = inicio;
    while (temp != NULL) {
        printf("%s - %s - %d\n", temp->dados.nome, temp->dados.tipo, temp->dados.quantidade);
        temp = temp->proximo;
    }
}

No *buscarSequencialLista(No *inicio, char nome[]) {
    No *temp = inicio;

    while (temp != NULL) {
        compSequencialLista++;
        if (strcmp(temp->dados.nome, nome) == 0) {
            printf("Item encontrado: %s, qtd: %d\n", temp->dados.nome, temp->dados.quantidade);
            return temp;
        }
        temp = temp->proximo;
    }

    printf("Item nao encontrado.\n");
    return NULL;
}
