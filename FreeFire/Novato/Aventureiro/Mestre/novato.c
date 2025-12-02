#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ITENS 10

// ------------------------------------------------------------
// ESTRUTURA DO ITEM
// Representa qualquer objeto armazenado na mochila.
// ------------------------------------------------------------
typedef struct {
    char nome[30];
    char tipo[20];
    int quantidade;
} Item;

// ------------------------------------------------------------
// PROTÓTIPOS DAS FUNÇÕES
// ------------------------------------------------------------
void inserirItem(Item inventario[], int *total);
void removerItem(Item inventario[], int *total);
void listarItens(Item inventario[], int total);
void buscarItem(Item inventario[], int total);

// ------------------------------------------------------------
// FUNÇÃO PRINCIPAL
// ------------------------------------------------------------
int main() {
    Item inventario[MAX_ITENS];
    int total = 0;
    int opcao;

    do {
        printf("\n========== SISTEMA DE INVENTARIO ==========\n");
        printf("1 - Cadastrar item\n");
        printf("2 - Remover item\n");
        printf("3 - Listar itens da mochila\n");
        printf("4 - Buscar item por nome\n");
        printf("0 - Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        getchar(); // Limpa buffer

        switch(opcao) {
            case 1:
                inserirItem(inventario, &total);
                break;
            case 2:
                removerItem(inventario, &total);
                break;
            case 3:
                listarItens(inventario, total);
                break;
            case 4:
                buscarItem(inventario, total);
                break;
            case 0:
                printf("Encerrando o sistema...\n");
                break;
            default:
                printf("Opcao invalida! Tente novamente.\n");
        }

    } while(opcao != 0);

    return 0;
}

// ------------------------------------------------------------
// CADASTRO DE ITENS
// ------------------------------------------------------------
void inserirItem(Item inventario[], int *total) {

    if (*total >= MAX_ITENS) {
        printf("\nA mochila esta cheia! Remova algo antes de adicionar novos itens.\n");
        return;
    }

    Item novo;

    printf("\nNome do item: ");
    fgets(novo.nome, 30, stdin);
    novo.nome[strcspn(novo.nome, "\n")] = '\0';

    printf("Tipo do item (arma, municao, cura, ferramenta...): ");
    fgets(novo.tipo, 20, stdin);
    novo.tipo[strcspn(novo.tipo, "\n")] = '\0';

    printf("Quantidade: ");
    scanf("%d", &novo.quantidade);
    getchar();

    inventario[*total] = novo;
    (*total)++;

    printf("\nItem adicionado com sucesso!\n");

    listarItens(inventario, *total);
}

// ------------------------------------------------------------
// REMOÇÃO DE ITENS POR NOME
// ------------------------------------------------------------
void removerItem(Item inventario[], int *total) {

    if (*total == 0) {
        printf("\nA mochila esta vazia! Nada para remover.\n");
        return;
    }

    char nomeRemover[30];
    printf("\nDigite o nome do item que deseja remover: ");
    fgets(nomeRemover, 30, stdin);
    nomeRemover[strcspn(nomeRemover, "\n")] = '\0';

    for (int i = 0; i < *total; i++) {
        if (strcmp(inventario[i].nome, nomeRemover) == 0) {

            for (int j = i; j < *total - 1; j++) {
                inventario[j] = inventario[j + 1];
            }

            (*total)--;

            printf("\nItem '%s' removido da mochila!\n", nomeRemover);
            listarItens(inventario, *total);
            return;
        }
    }

    printf("\nItem nao encontrado na mochila!\n");
}

// ------------------------------------------------------------
// LISTAGEM COMPLETA DO INVENTÁRIO
// ------------------------------------------------------------
void listarItens(Item inventario[], int total) {

    printf("\n========== ITENS NA MOCHILA ==========\n");

    if (total == 0) {
        printf("A mochila esta vazia!\n");
        return;
    }

    for (int i = 0; i < total; i++) {
        printf("\nItem %d:\n", i + 1);
        printf("Nome: %s\n", inventario[i].nome);
        printf("Tipo: %s\n", inventario[i].tipo);
        printf("Quantidade: %d\n", inventario[i].quantidade);
    }
}

// ------------------------------------------------------------
// BUSCA SEQUENCIAL DE ITEM POR NOME
// ------------------------------------------------------------
void buscarItem(Item inventario[], int total) {

    if (total == 0) {
        printf("\nA mochila esta vazia! Nada para buscar.\n");
        return;
    }

    char nomeBusca[30];
    printf("\nDigite o nome do item para buscar: ");
    fgets(nomeBusca, 30, stdin);
    nomeBusca[strcspn(nomeBusca, "\n")] = '\0';

    for (int i = 0; i < total; i++) {
        if (strcmp(inventario[i].nome, nomeBusca) == 0) {
            printf("\nItem encontrado!\n");
            printf("Nome: %s\n", inventario[i].nome);
            printf("Tipo: %s\n", inventario[i].tipo);
            printf("Quantidade: %d\n", inventario[i].quantidade);
            return;
        }
    }

    printf("\nItem nao encontrado!\n");
}
