#ifndef PRODUTOS_H
#define PRODUTOS_H
#include <stdio.h>
#include <string.h>

#define MAX_PRODUTOS 50

struct Produto {
    int idProduto;
    char nomeProduto[30];
    float preco;
    int estoque;
    int ativo;
};

struct Produto listaProdutos[MAX_PRODUTOS];
int totalProdutos = 0;

void salvarProdutosCSV(void);
void carregarProdutosCSV(void);

void listarProdutosAtivos(void) {
    int i;
    int achou = 0;

    printf("\n===== PRODUTOS ATIVOS =====\n");

    for (i = 0; i < totalProdutos; i++) {
        if (listaProdutos[i].ativo == 1) {
            printf("ID: %d | %s | Preco: R$ %.2f | Estoque: %d\n",
                   listaProdutos[i].idProduto,
                   listaProdutos[i].nomeProduto,
                   listaProdutos[i].preco,
                   listaProdutos[i].estoque);

            achou = 1;
        }
    }

    if (achou == 0) {
        printf("Nenhum produto ativo cadastrado.\n");
    }

    printf("\n");
}

void buscarProdutosPorNome(void) {
    char termo[30];
    int i;
    int achou = 0;

    printf("Digite parte do nome ou * para listar todos: ");
    scanf("%29s", termo);

    if (strcmp(termo, "*") == 0) {
        listarProdutosAtivos();
        return;
    }

    for (i = 0; i < totalProdutos; i++) {
        if (listaProdutos[i].ativo == 1 &&
            strstr(listaProdutos[i].nomeProduto, termo) != NULL) {
            printf("ID: %d | %s | Preco: R$ %.2f | Estoque: %d\n",
                   listaProdutos[i].idProduto,
                   listaProdutos[i].nomeProduto,
                   listaProdutos[i].preco,
                   listaProdutos[i].estoque);
            achou = 1;
        }
    }

    if (achou == 0) {
        printf("Nenhum produto encontrado com esse trecho do nome.\n");
    }
}

// ----------------------------------------------------------------------------
// MODULO 3: PERSPECTIVA DE PRODUTOS DO BALCAO
// Autor: Samuel - RGM XXXXXXXX
// ----------------------------------------------------------------------------
void moduloProdutos(void) {
    int opcao;
    int i;
    int idBusca;
    int achou;

    do {
        limparTela();
        printf("\n===== MODULO DE PRODUTOS DO BALCAO =====\n");
        printf("1. Cadastrar Produto\n");
        printf("2. Listar / Buscar Produtos\n");
        printf("3. Editar Produto\n");
        printf("4. Remover Produto\n");
        printf("0. Voltar ao Menu Principal\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                if (totalProdutos >= MAX_PRODUTOS) {
                    printf("Limite de 50 produtos atingido!\n");
                } else {
                    listaProdutos[totalProdutos].idProduto = totalProdutos + 1;
                    printf("Nome do produto (uma palavra): ");
                    scanf("%s", listaProdutos[totalProdutos].nomeProduto);
                    printf("Preco: ");
                    scanf("%f", &listaProdutos[totalProdutos].preco);
                    printf("Estoque: ");
                    scanf("%d", &listaProdutos[totalProdutos].estoque);
                    listaProdutos[totalProdutos].ativo = 1;
                    printf("Produto cadastrado com ID %d!\n", listaProdutos[totalProdutos].idProduto);
                    totalProdutos++;
                    salvarProdutosCSV();
                }
                pausar();
                break;
            case 2:
                buscarProdutosPorNome();
                pausar();
                break;
            case 3:
                listarProdutosAtivos();
                printf("\nID do produto a editar: ");
                scanf("%d", &idBusca);
                achou = 0;
                for (i = 0; i < totalProdutos; i++) {
                    if (listaProdutos[i].idProduto == idBusca && listaProdutos[i].ativo == 1) {
                        printf("Novo preco: ");
                        scanf("%f", &listaProdutos[i].preco);
                        printf("Novo estoque: ");
                        scanf("%d", &listaProdutos[i].estoque);
                        printf("Produto atualizado!\n");
                        achou = 1;
                        salvarProdutosCSV();
                    }
                }
                if (achou == 0) {
                    printf("Produto nao encontrado.\n");
                }
                pausar();
                break;
            case 4:
                listarProdutosAtivos();
                printf("\nID do produto a remover: ");
                scanf("%d", &idBusca);
                achou = 0;
                for (i = 0; i < totalProdutos; i++) {
                    if (listaProdutos[i].idProduto == idBusca && listaProdutos[i].ativo == 1) {
                        listaProdutos[i].ativo = 0;   // remocao logica
                        printf("Produto removido!\n");
                        achou = 1;
                        salvarProdutosCSV();
                    }
                }
                if (achou == 0) {
                    printf("Produto nao encontrado.\n");
                }
                pausar();
                break;
            case 0:
                printf("Voltando ao Menu Principal...\n");
                break;
            default:
                printf("Opcao invalida! Tente novamente.\n");
                pausar();
        }
    } while (opcao != 0);
}

// salva a lista de produtos em um arquivo CSV

void salvarProdutosCSV(void) {
    FILE *arquivo = fopen("produtos.csv", "w");

    if (arquivo == NULL) {
        printf("Erro ao salvar produtos.csv\n");
        return;
    }

    for (int i = 0; i < totalProdutos; i++) {
        fprintf(arquivo, "%d;%s;%.2f;%d;%d\n",
                listaProdutos[i].idProduto,
                listaProdutos[i].nomeProduto,
                listaProdutos[i].preco,
                listaProdutos[i].estoque,
                listaProdutos[i].ativo);
    }

    fclose(arquivo);
}

void carregarProdutosCSV(void) {
    FILE *arquivo = fopen("produtos.csv", "r");

    if (arquivo == NULL) {
        return;
    }

    totalProdutos = 0;

    while (totalProdutos < MAX_PRODUTOS &&
           fscanf(arquivo, "%d;%29[^;];%f;%d;%d",
                  &listaProdutos[totalProdutos].idProduto,
                  listaProdutos[totalProdutos].nomeProduto,
                  &listaProdutos[totalProdutos].preco,
                  &listaProdutos[totalProdutos].estoque,
                  &listaProdutos[totalProdutos].ativo) == 5) {
        totalProdutos++;
    }

    fclose(arquivo);
}


#endif