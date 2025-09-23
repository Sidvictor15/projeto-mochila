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

// Função para exibir os itens da mochila
void listarItens(Item mochila[], int qtdItens) {
    cabecalho(qtdItens);

    if (qtdItens == 0) {
        printf("\nA mochila está vazia!\n");
        return;
    }

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

    int encontrado = -1;
    for (int i = 0; i < *qtdItens; i++) {
        if (strcmp(mochila[i].nome, nome) == 0) {
            encontrado = i;
            break;
        }
    }

    if (encontrado == -1) {
        printf("\nItem '%s' não encontrado!\n", nome);
    } else {
        for (int i = encontrado; i < *qtdItens - 1; i++) {
            mochila[i] = mochila[i + 1];
        }
        (*qtdItens)--;
        printf("\nItem '%s' removido com sucesso!\n", nome);
    }
}

// Função para alterar a quantidade de um item
void alterarQuantidade(Item mochila[], int qtdItens) {
    if (qtdItens == 0) {
        printf("\nA mochila está vazia!\n");
        return;
    }

    char nome[TAM_NOME];
    printf("\nDigite o nome do item que deseja alterar: ");
    fgets(nome, TAM_NOME, stdin);
    nome[strcspn(nome, "\n")] = '\0';

    int encontrado = -1;
    for (int i = 0; i < qtdItens; i++) {
        if (strcmp(mochila[i].nome, nome) == 0) {
            encontrado = i;
            break;
        }
    }

    if (encontrado == -1) {
        printf("\nItem '%s' não encontrado!\n", nome);
    } else {
        int novaQtd;
        printf("Nova quantidade para '%s': ", mochila[encontrado].nome);
        scanf("%d", &novaQtd);
        getchar();
        mochila[encontrado].quantidade = novaQtd;
        printf("\nQuantidade atualizada com sucesso!\n");
    }
}

int main() {
    Item mochila[MAX_ITENS];
    int qtdItens = 0;
    int opcao;

    do {
        cabecalho(qtdItens);
        printf("\n1 - Adicionar Novo Item\n");
        printf("2 - Listar Itens\n");
        printf("3 - Remover Item\n");
        printf("4 - Alterar Quantidade\n");
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
            listarItens(mochila, qtdItens);
        }
        else if (opcao == 3) {
            removerItem(mochila, &qtdItens);
        }
        else if (opcao == 4) {
            alterarQuantidade(mochila, qtdItens);
        }

        if (opcao != 0) {
            printf("\nPressione Enter para continuar...");
            getchar();
        }
    } while (opcao != 0);

    printf("\nPrograma encerrado!\n");
    return 0;
}
