#ifndef BAIAS_H
#define BAIAS_H
#include <stdio.h>
#include <string.h>

#define MAX_BAIAS 50

struct Baia {
    int idBaia;
    char nomeMaquina[20];
    float precoHora;
    int emManutencao;
    int ativo;
};

struct Baia listaBaias[MAX_BAIAS];
int totalBaias = 0;

void salvarBaiasCSV(void);
void carregarBaiasCSV(void);

void listarBaiasAtivas(void) {
    int i;
    int achou = 0;
    printf("\n===== BAIAS ATIVAS =====\n");
    for (i = 0; i < totalBaias; i++) {
        if (listaBaias[i].ativo == 1) {
            printf("ID: %d | Maquina: %s\n", listaBaias[i].idBaia, listaBaias[i].nomeMaquina);
            achou = 1;
        }
    }
    if (achou == 0) printf("Nenhuma baia ativa cadastrada.\n");
    printf("\n");
}

void buscarBaiasPorNome(void) {
    char termo[20];
    int i;
    int achou = 0;

    printf("Digite parte do nome da baia ou * para listar todas: ");
    scanf("%19s", termo);

    if (strcmp(termo, "*") == 0) {
        listarBaiasAtivas();
        return;
    }

    for (i = 0; i < totalBaias; i++) {
        if (listaBaias[i].ativo == 1 &&
            strstr(listaBaias[i].nomeMaquina, termo) != NULL) {
            printf("ID: %d | %s | Preco por hora: R$ %.2f | Em manutencao: %s\n",
                   listaBaias[i].idBaia,
                   listaBaias[i].nomeMaquina,
                   listaBaias[i].precoHora,
                   listaBaias[i].emManutencao == 1 ? "Sim" : "Nao");
            achou = 1;
        }
    }

    if (achou == 0) {
        printf("Nenhuma baia encontrada com esse trecho do nome.\n");
    }
}

// ----------------------------------------------------------------------------
// MODULO 2: PERSPECTIVA DE BAIAS / PCs
// Autor: Matheus Vendramim - RGM 47602465
// ----------------------------------------------------------------------------


void moduloBaias(void) {
    int opcaoBaia;
    int i;
    int idBusca;
    int achou;

    do {
        limparTela();
        printf("\n--- [MODULO 2: GESTAO DE BAIAS / PCs] ---\n");
        printf("1. Cadastrar Nova Baia\n");
        printf("2. Listar / Buscar Baias\n");
        printf("3. Editar Baia (Preco ou Manutencao)\n");
        printf("4. Remover Baia\n");
        printf("0. Voltar ao Menu Principal\n");
        printf("Escolha uma acao: ");
        scanf("%d", &opcaoBaia);

        switch (opcaoBaia) {
            case 1:
                if (totalBaias >= MAX_BAIAS) {
                    printf("Limite de 50 baias atingido!\n");
                } else {
                    listaBaias[totalBaias].idBaia = totalBaias + 1;
                    printf("Nome da maquina (ex: PC-01): ");
                    scanf("%s", listaBaias[totalBaias].nomeMaquina);
                    printf("Preco por hora: ");
                    scanf("%f", &listaBaias[totalBaias].precoHora);
                    listaBaias[totalBaias].emManutencao = 0;
                    listaBaias[totalBaias].ativo = 1;
                    printf("Baia cadastrada com ID %d!\n", listaBaias[totalBaias].idBaia);
                    totalBaias++;
                    salvarBaiasCSV();
                }
                pausar();
                break;
            case 2:
                buscarBaiasPorNome();
                pausar();
                break;
            case 3:
                listarBaiasAtivas();
                printf("\nID da baia a editar: ");
                scanf("%d", &idBusca);
                achou = 0;
                for (i = 0; i < totalBaias; i++) {
                    if (listaBaias[i].idBaia == idBusca && listaBaias[i].ativo == 1) {
                        printf("Novo preco por hora: ");
                        scanf("%f", &listaBaias[i].precoHora);
                        printf("Em manutencao? (1 = sim, 0 = nao): ");
                        scanf("%d", &listaBaias[i].emManutencao);
                        printf("Baia atualizada!\n");
                        achou = 1;
                        salvarBaiasCSV();
                    }
                }
                if (achou == 0) {
                    printf("Baia nao encontrada.\n");
                }
                pausar();
                break;
            case 4:
                listarBaiasAtivas();
                printf("\nID da baia a remover: ");
                scanf("%d", &idBusca);
                achou = 0;
                for (i = 0; i < totalBaias; i++) {
                    if (listaBaias[i].idBaia == idBusca && listaBaias[i].ativo == 1) {
                        listaBaias[i].ativo = 0;   // remocao logica
                        printf("Baia removida!\n");
                        achou = 1;
                        salvarBaiasCSV();
                    }
                }
                if (achou == 0) {
                    printf("Baia nao encontrada.\n");
                }
                pausar();
                break;
            case 0:
                printf("\nRetornando ao menu principal...\n");
                break;
            default:
                printf("\n[ERRO] Opcao invalida no Modulo de Baias!\n");
                pausar();
        }
    } while (opcaoBaia != 0);
}

// salvar baias.csv

void salvarBaiasCSV(void) {
    FILE *arquivo = fopen("baias.csv", "w");

    if (arquivo == NULL) {
        printf("Erro ao salvar baias.csv\n");
        return;
    }

    for (int i = 0; i < totalBaias; i++) {
        fprintf(arquivo, "%d;%s;%.2f;%d;%d\n",
                listaBaias[i].idBaia,
                listaBaias[i].nomeMaquina,
                listaBaias[i].precoHora,
                listaBaias[i].emManutencao,
                listaBaias[i].ativo);
    }

    fclose(arquivo);
}

void carregarBaiasCSV(void) {
    FILE *arquivo = fopen("baias.csv", "r");

    if (arquivo == NULL) {
        return;
    }

    totalBaias = 0;

    while (totalBaias < MAX_BAIAS &&
           fscanf(arquivo, "%d;%19[^;];%f;%d;%d",
                  &listaBaias[totalBaias].idBaia,
                  listaBaias[totalBaias].nomeMaquina,
                  &listaBaias[totalBaias].precoHora,
                  &listaBaias[totalBaias].emManutencao,
                  &listaBaias[totalBaias].ativo) == 5) {
        totalBaias++;
    }

    fclose(arquivo);
}

#endif