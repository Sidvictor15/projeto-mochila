#include <stdio.h>
#include <string.h>

#define MAX_ITENS 10
#define TAM_NOME 50
#define TAM_TIPO 20

// Estrutura para armazenar os itens
typedef struct {
    char nome[TAM_NOME];
    char tipo[TAM_TIPO];
    int quantidade;
} Item;

// Função para exibir o cabeçalho
void cabecalho(int qtdItens) {
    printf("\n=====================================\n");
    printf("  MOCHILA DE SOBREVIVENCIA - CODIGO DA ILHA\n");
    printf("=====================================\n");
    printf("Itens na Mochila: %d/%d\n", qtdItens, MAX_ITENS);
}

// Ordenar itens por nome (Bubble Sort simples)
void ordenarMochila(Item mochila[], int qtdItens) {
    for (int i = 0; i < qtdItens - 1; i++) {
        for (int j = 0; j < qtdItens - i - 1; j++) {
            if (strcmp(mochila[j].nome, mochila[j + 1].nome) > 0) {
                Item temp = mochila[j];
                mochila[j] = mochila[j + 1];
                mochila[j + 1] = temp;
            }
        }
    }
}

// Função para exibir os itens da mochila
void listarItens(Item mochila[], int qtdItens) {
    cabecalho(qtdItens);

    if (qtdItens == 0) {
        printf("\nA mochila está vazia!\n");
        return;
    }

    ordenarMochila(mochila, qtdItens);

    printf("\n%-15s | %-10s | %-10s\n", "NOME", "TIPO", "QUANTIDADE");
    printf("--------------------------------------------------\n");

    for (int i = 0; i < qtdItens; i++) {
        printf("%-15s | %-10s | %d\n",
               mochila[i].nome,
               mochila[i].tipo,
               mochila[i].quantidade);
    }
    printf("--------------------------------------------------\n");
}

// Função de busca binária por nome
int buscaBinariaPorNome(Item mochila[], int qtdItens, char nome[]) {
    int inicio = 0, fim = qtdItens - 1;

    while (inicio <= fim) {
        int meio = (inicio + fim) / 2;
        int cmp = strcmp(mochila[meio].nome, nome);

        if (cmp == 0) {
            return meio; // encontrado
        }
        if (cmp < 0) {
            inicio = meio + 1;
        } else {
            fim = meio - 1;
        }
    }
    return -1; // não encontrado
}

// Função para remover item da mochila
void removerItem(Item mochila[], int *qtdItens) {
    if (*qtdItens == 0) {
        printf("\nA mochila está vazia, nada para remover!\n");
        return;
    }

    char nome[TAM_NOME];
    printf("\nDigite o nome do item que deseja remover: ");
    fgets(nome, TAM_NOME, stdin);
    nome[strcspn(nome, "\n")] = '\0';

    ordenarMochila(mochila, *qtdItens);
    int pos = buscaBinariaPorNome(mochila, *qtdItens, nome);

    if (pos == -1) {
        printf("\nItem '%s' não encontrado!\n", nome);
    } else {
        for (int i = pos; i < *qtdItens - 1; i++) {
            mochila[i] = mochila[i + 1];
        }
        (*qtdItens)--;
        printf("\nItem '%s' removido com sucesso!\n", nome);
    }
}

// Função para buscar item por nome
void buscarItem(Item mochila[], int qtdItens) {
    if (qtdItens == 0) {
        printf("\nA mochila está vazia!\n");
        return;
    }

    char nome[TAM_NOME];
    printf("\nDigite o nome do item que deseja buscar: ");
    fgets(nome, TAM_NOME, stdin);
    nome[strcspn(nome, "\n")] = '\0';

    ordenarMochila(mochila, qtdItens);
    int pos = buscaBinariaPorNome(mochila, qtdItens, nome);

    if (pos == -1) {
        printf("\nItem '%s' não encontrado na mochila.\n", nome);
    } else {
        printf("\nItem encontrado!\n");
        printf("Nome: %s | Tipo: %s | Quantidade: %d\n",
               mochila[pos].nome,
               mochila[pos].tipo,
               mochila[pos].quantidade);
    }
}

int main() {
    Item mochila[MAX_ITENS];
    int qtdItens = 0;
    int opcao;

    do {
        cabecalho(qtdItens);
        printf("\n1 - Adicionar Item (Loot)\n");
        printf("2 - Remover Item\n");
        printf("3 - Listar Itens na Mochila\n");
        printf("4 - Buscar Item por Nome\n");
        printf("0 - Sair\n");
        printf("Opcao: ");
        scanf("%d", &opcao);
        getchar();

        if (opcao == 1) {
            if (qtdItens >= MAX_ITENS) {
                printf("A mochila está cheia!\n");
                continue;
            }

            Item novo;
            printf("\n--- Adicionar Novo Item ---\n");
            printf("Nome do item: ");
            fgets(novo.nome, TAM_NOME, stdin);
            novo.nome[strcspn(novo.nome, "\n")] = '\0';

            printf("Tipo do item (arma, municao, cura, etc.): ");
            fgets(novo.tipo, TAM_TIPO, stdin);
            novo.tipo[strcspn(novo.tipo, "\n")] = '\0';

            printf("Quantidade: ");
            scanf("%d", &novo.quantidade);
            getchar();

            mochila[qtdItens] = novo;
            qtdItens++;

            printf("\nItem '%s' adicionado com sucesso!\n", novo.nome);
        }
        else if (opcao == 2) {
            removerItem(mochila, &qtdItens);
        }
        else if (opcao == 3) {
            listarItens(mochila, qtdItens);
        }
        else if (opcao == 4) {
            buscarItem(mochila, qtdItens);
        }

        if (opcao != 0) {
            printf("\nPressione Enter para continuar...");
            getchar();
        }
    } while (opcao != 0);

    printf("\nPrograma encerrado!\n");
    return 0;
}
