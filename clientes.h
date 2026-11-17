#ifndef CLIENTES_H
#define CLIENTES_H
#include <stdio.h>
#include <string.h>

#define MAX_CLIENTES 50

struct Cliente {
    int idCliente;
    char nick[30];
    char telefone[20];
    int idade;
    int ativo;
};

struct Cliente listaClientes[MAX_CLIENTES];
int totalClientes = 0;

void salvarClientesCSV(void);
void carregarClientesCSV(void);

void listarClientesAtivos(void) {
    int i;
    int achou = 0;
    printf("\n===== USUARIOS ATIVOS =====\n");
    for (i = 0; i < totalClientes; i++) {
        if (listaClientes[i].ativo == 1) {
            printf("ID: %d | Nick: %s\n", listaClientes[i].idCliente, listaClientes[i].nick);
            achou = 1;
        }
    }
    if (achou == 0) printf("Nenhum cliente ativo cadastrado.\n");
    printf("\n");
}

void buscarClientesPorNick(void) {
    char termo[30];
    int i;
    int achou = 0;

    printf("Digite parte do nick ou * para listar todos: ");
    scanf("%29s", termo);

    if (strcmp(termo, "*") == 0) {
        listarClientesAtivos();
        return;
    }

    for (i = 0; i < totalClientes; i++) {
        if (listaClientes[i].ativo == 1 &&
            strstr(listaClientes[i].nick, termo) != NULL) {
            printf("ID: %d | Nick: %s | Telefone: %s | Idade: %d\n",
                   listaClientes[i].idCliente,
                   listaClientes[i].nick,
                   listaClientes[i].telefone,
                   listaClientes[i].idade);
            achou = 1;
        }
    }

    if (achou == 0) {
        printf("Nenhum cliente encontrado com esse trecho do nick.\n");
    }
}

// ----------------------------------------------------------------------------
// MODULO 1: PERSPECTIVA DE CLIENTES
// Autor: Murylo Gabriel - RGM 47902523
// ----------------------------------------------------------------------------



void moduloClientes(void) {
    int opcao;        // opcao do submenu
    int i;            // contador dos for
    int idBusca;      // id digitado pelo usuario
    int achou;        // 1 = encontrou, 0 = nao encontrou

    do {
        limparTela();
        printf("\n===== MODULO DE CLIENTES =====\n");
        printf("1. Cadastrar Cliente\n");
        printf("2. Listar / Buscar Clientes\n");
        printf("3. Editar Cliente\n");
        printf("4. Remover Cliente\n");
        printf("0. Voltar ao Menu Principal\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                if (totalClientes >= MAX_CLIENTES) {
                    printf("Limite de 50 clientes atingido!\n");
                } else {
                    listaClientes[totalClientes].idCliente = totalClientes + 1;
                    printf("Nick (uma palavra): ");
                    scanf("%s", listaClientes[totalClientes].nick);
                    printf("Telefone: ");
                    scanf("%s", listaClientes[totalClientes].telefone);
                    printf("Idade: ");
                    scanf("%d", &listaClientes[totalClientes].idade);
                    listaClientes[totalClientes].ativo = 1;
                    printf("Cliente cadastrado com ID %d!\n", listaClientes[totalClientes].idCliente);
                    totalClientes++;
                    salvarClientesCSV();
                }
                pausar();
                break;
            case 2:
                buscarClientesPorNick();
                pausar();
                break;
            case 3:
                listarClientesAtivos();
                printf("\nID do cliente a editar: ");
                scanf("%d", &idBusca);
                achou = 0;
                for (i = 0; i < totalClientes; i++) {
                    if (listaClientes[i].idCliente == idBusca && listaClientes[i].ativo == 1) {
                        printf("Novo nick: ");
                        scanf("%s", listaClientes[i].nick);
                        printf("Novo telefone: ");
                        scanf("%s", listaClientes[i].telefone);
                        printf("Nova idade: ");
                        scanf("%d", &listaClientes[i].idade);
                        printf("Cliente atualizado!\n");
                        achou = 1;
                        salvarClientesCSV();
                    }
                }
                if (achou == 0) {
                    printf("Cliente nao encontrado.\n");
                }
                pausar();
                break;
            case 4:
                listarClientesAtivos();
                printf("\nID do cliente a remover: ");
                scanf("%d", &idBusca);
                achou = 0;
                for (i = 0; i < totalClientes; i++) {
                    if (listaClientes[i].idCliente == idBusca && listaClientes[i].ativo == 1) {
                        listaClientes[i].ativo = 0;   // remocao logica
                        printf("Cliente removido!\n");
                        achou = 1;
                        salvarClientesCSV();
                    }
                }
                if (achou == 0) {
                    printf("Cliente nao encontrado.\n");
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

// csv functions

void salvarClientesCSV(void) {
    FILE *arquivo = fopen("clientes.csv", "w");

    if (arquivo == NULL) {
        printf("Erro ao salvar clientes.csv\n");
        return;
    }

    for (int i = 0; i < totalClientes; i++) {
        fprintf(arquivo, "%d;%s;%s;%d;%d\n",
                listaClientes[i].idCliente,
                listaClientes[i].nick,
                listaClientes[i].telefone,
                listaClientes[i].idade,
                listaClientes[i].ativo);
    }

    fclose(arquivo);
}

void carregarClientesCSV(void) {
    FILE *arquivo = fopen("clientes.csv", "r");

    if (arquivo == NULL) {
        return;
    }

    totalClientes = 0;

    while (totalClientes < MAX_CLIENTES &&
           fscanf(arquivo, "%d;%29[^;];%19[^;];%d;%d",
                  &listaClientes[totalClientes].idCliente,
                  listaClientes[totalClientes].nick,
                  listaClientes[totalClientes].telefone,
                  &listaClientes[totalClientes].idade,
                  &listaClientes[totalClientes].ativo) == 5) {
        totalClientes++;
    }

    fclose(arquivo);
}


#endif