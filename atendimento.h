#ifndef ATENDIMENTO_H
#define ATENDIMENTO_H
#include <stdio.h>

#define MAX_ATENDIMENTOS 50

struct Atendimento {
    int idAtendimento;
    int idCliente;
    int idBaia;
    int minutosUso;
    int idProduto;
    int qtdProduto;
    float valorTotal;
    int ativo;
};

struct Atendimento listaAtendimentos[MAX_ATENDIMENTOS];
int totalAtendimentos = 0;

void salvarAtendimentosCSV(void);
void carregarAtendimentosCSV(void);

void listarAtendimentosAtivos(void) {
    int i, j, k;
    int achou = 0;
    printf("\n===== ATENDIMENTOS ATIVOS =====\n");
    for (i = 0; i < totalAtendimentos; i++) {
        if (listaAtendimentos[i].ativo == 1) {
            printf("ID: %d | Cliente: ", listaAtendimentos[i].idAtendimento);
            for (j = 0; j < totalClientes; j++) {
                if (listaClientes[j].idCliente == listaAtendimentos[i].idCliente) printf("%s", listaClientes[j].nick);
            }
            printf(" | Baia: ");
            for (k = 0; k < totalBaias; k++) {
                if (listaBaias[k].idBaia == listaAtendimentos[i].idBaia) printf("%s", listaBaias[k].nomeMaquina);
            }
            printf(" | %d min | Produto: %d x%d | R$ %.2f\n", listaAtendimentos[i].minutosUso,
                   listaAtendimentos[i].idProduto, listaAtendimentos[i].qtdProduto, listaAtendimentos[i].valorTotal);
            achou = 1;
        }
    }
    if (achou == 0) printf("Nenhum atendimento ativo cadastrado.\n");
    printf("\n");
}

// ----------------------------------------------------------------------------
// RELATORIOS ANALITICOS (usados pelo Modulo 4)
// Autor: Samuel  - RGM 47459191
// ----------------------------------------------------------------------------
// Calcula qual baia acumulou mais minutos de uso.
void relatorioBaiaMaisUsada(void) {
    int i, j;
    int somaMinutos;
    int totalBaiasAtivas = 0;
    int trocaId, trocaMinutos;
    int matriz[MAX_BAIAS][2];

    /*
       Cada linha da matriz representa uma baia:
       coluna 0 = ID da baia
       coluna 1 = minutos de uso acumulados
    */
    for (i = 0; i < totalBaias; i++) {
        if (listaBaias[i].ativo == 1) {
            somaMinutos = 0;

            for (j = 0; j < totalAtendimentos; j++) {
                if (listaAtendimentos[j].ativo == 1 &&
                    listaAtendimentos[j].idBaia == listaBaias[i].idBaia) {
                    somaMinutos += listaAtendimentos[j].minutosUso;
                }
            }

            matriz[totalBaiasAtivas][0] = listaBaias[i].idBaia;
            matriz[totalBaiasAtivas][1] = somaMinutos;
            totalBaiasAtivas++;
        }
    }

    /* Bubble Sort: ordena as baias da maior para a menor utilização. */
    for (i = 0; i < totalBaiasAtivas - 1; i++) {
        for (j = 0; j < totalBaiasAtivas - 1 - i; j++) {
            if (matriz[j][1] < matriz[j + 1][1]) {
                trocaId = matriz[j][0];
                matriz[j][0] = matriz[j + 1][0];
                matriz[j + 1][0] = trocaId;

                trocaMinutos = matriz[j][1];
                matriz[j][1] = matriz[j + 1][1];
                matriz[j + 1][1] = trocaMinutos;
            }
        }
    }

    if (totalBaiasAtivas == 0 || matriz[0][1] == 0) {
        printf("Nenhum uso registrado.\n");
    } else {
        printf("Ranking de baias por minutos de uso:\n");

        for (i = 0; i < totalBaiasAtivas; i++) {
            if (matriz[i][1] > 0) {
                printf("%d. %s - %d minutos\n",
                       i + 1,
                       listaBaias[matriz[i][0] - 1].nomeMaquina,
                       matriz[i][1]);
            }
        }
    }

    pausar();
}

// Calcula qual produto teve mais unidades vendidas.
void relatorioProdutoMaisVendido(void) {
    int i, j;
    int somaUnidades;
    int totalProdutosAtivos = 0;
    int trocaId, trocaUnidades;
    int matriz[MAX_PRODUTOS][2];

    /*
       Cada linha da matriz representa um produto:
       coluna 0 = ID do produto
       coluna 1 = unidades vendidas
    */
    for (i = 0; i < totalProdutos; i++) {
        if (listaProdutos[i].ativo == 1) {
            somaUnidades = 0;

            for (j = 0; j < totalAtendimentos; j++) {
                if (listaAtendimentos[j].ativo == 1 &&
                    listaAtendimentos[j].idProduto == listaProdutos[i].idProduto) {
                    somaUnidades += listaAtendimentos[j].qtdProduto;
                }
            }

            matriz[totalProdutosAtivos][0] = listaProdutos[i].idProduto;
            matriz[totalProdutosAtivos][1] = somaUnidades;
            totalProdutosAtivos++;
        }
    }

    /* Bubble Sort: ordena da maior para a menor quantidade vendida. */
    for (i = 0; i < totalProdutosAtivos - 1; i++) {
        for (j = 0; j < totalProdutosAtivos - 1 - i; j++) {
            if (matriz[j][1] < matriz[j + 1][1]) {
                trocaId = matriz[j][0];
                matriz[j][0] = matriz[j + 1][0];
                matriz[j + 1][0] = trocaId;

                trocaUnidades = matriz[j][1];
                matriz[j][1] = matriz[j + 1][1];
                matriz[j + 1][1] = trocaUnidades;
            }
        }
    }

    if (totalProdutosAtivos == 0 || matriz[0][1] == 0) {
        printf("Nenhuma venda registrada.\n");
    } else {
        printf("Ranking de produtos por unidades vendidas:\n");

        for (i = 0; i < totalProdutosAtivos; i++) {
            if (matriz[i][1] > 0) {
                printf("%d. %s - %d unidades\n",
                       i + 1,
                       listaProdutos[matriz[i][0] - 1].nomeProduto,
                       matriz[i][1]);
            }
        }
    }

    pausar();
}

// Calcula qual cliente acumulou o maior gasto.
void relatorioClienteVIP(void) {
    int i, j;
    int totalClientesAtivos = 0;
    float somaGastos;
    float trocaId, trocaGastos;
    float matriz[MAX_CLIENTES][2];

    /*
       Cada linha da matriz representa um cliente:
       coluna 0 = ID do cliente
       coluna 1 = total gasto
    */
    for (i = 0; i < totalClientes; i++) {
        if (listaClientes[i].ativo == 1) {
            somaGastos = 0;

            for (j = 0; j < totalAtendimentos; j++) {
                if (listaAtendimentos[j].ativo == 1 &&
                    listaAtendimentos[j].idCliente == listaClientes[i].idCliente) {
                    somaGastos += listaAtendimentos[j].valorTotal;
                }
            }

            matriz[totalClientesAtivos][0] = listaClientes[i].idCliente;
            matriz[totalClientesAtivos][1] = somaGastos;
            totalClientesAtivos++;
        }
    }

    /* Bubble Sort: ordena do maior para o menor gasto. */
    for (i = 0; i < totalClientesAtivos - 1; i++) {
        for (j = 0; j < totalClientesAtivos - 1 - i; j++) {
            if (matriz[j][1] < matriz[j + 1][1]) {
                trocaId = matriz[j][0];
                matriz[j][0] = matriz[j + 1][0];
                matriz[j + 1][0] = trocaId;

                trocaGastos = matriz[j][1];
                matriz[j][1] = matriz[j + 1][1];
                matriz[j + 1][1] = trocaGastos;
            }
        }
    }

    if (totalClientesAtivos == 0 || matriz[0][1] == 0) {
        printf("Nenhum gasto registrado.\n");
    } else {
        printf("Ranking de clientes por gasto:\n");

        for (i = 0; i < totalClientesAtivos; i++) {
            if (matriz[i][1] > 0) {
                printf("%d. %s - R$ %.2f\n",
                       i + 1,
                       listaClientes[(int)matriz[i][0] - 1].nick,
                       matriz[i][1]);
            }
        }
    }

    pausar();
}

// Calcula o faturamento e a quantidade de atendimentos validos.
void relatorioFaturamento(void) {
    int i;
    int somaInt;
    float somaFloat;
    somaFloat = 0;
    somaInt = 0;
    for (i = 0; i < totalAtendimentos; i++) {
        if (listaAtendimentos[i].ativo == 1) {
            somaFloat = somaFloat + listaAtendimentos[i].valorTotal;
            somaInt++;
        }
    }
    printf("Atendimentos validos: %d\n", somaInt);
    printf("Faturamento do dia: R$ %.2f\n", somaFloat);
    pausar();
}

// ----------------------------------------------------------------------------
// MODULO 4: PERSPECTIVA DE ATENDIMENTOS E RELATORIOS
// Autor: Matheus Vendramim - RGM 47602465 (opcoes 1 a 4)
// Relatorios (opcoes 5 a 8): funcoes do Murylo Gabriel, definidas acima
// ----------------------------------------------------------------------------

void moduloAtendimentosRelatorios(void) {
    int opcao;
    int i;
    int idBusca;
    int achou;
    int posCliente, posBaia, posProduto;   // posicao (indice) no vetor; -1 = nao achou
    int minutos, qtd, idProd;              // dados digitados

    do {
        limparTela();
        printf("\n===== MODULO DE ATENDIMENTOS E RELATORIOS =====\n");
        printf("1. Registrar Atendimento (Cliente + Baia + Consumo)\n");
        printf("2. Listar Atendimentos\n");
        printf("3. Editar Atendimento\n");
        printf("4. Estornar Atendimento\n");
        printf("5. [RELATORIO] Baia mais usada (mais minutos)\n");
        printf("6. [RELATORIO] Produto mais vendido\n");
        printf("7. [RELATORIO] Cliente VIP (maior gasto)\n");
        printf("8. [RELATORIO] Faturamento do dia\n");
        printf("9. [RELATORIO] Atendimentos de um cliente\n");
        printf("0. Voltar ao Menu Principal\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                if (totalAtendimentos >= MAX_ATENDIMENTOS) {
                    printf("Limite de 50 atendimentos atingido!\n");
                    pausar();
                    break;
                }
                // --- procura o cliente ---
                listarClientesAtivos();
                printf("\nID do cliente: ");
                scanf("%d", &idBusca);
                posCliente = -1;
                for (i = 0; i < totalClientes; i++) {
                    if (listaClientes[i].idCliente == idBusca && listaClientes[i].ativo == 1) {
                        posCliente = i;
                    }
                }
                if (posCliente == -1) {
                    printf("Cliente nao encontrado.\n");
                    pausar();
                    break;
                }
                // --- procura a baia ---
                listarBaiasAtivas();
                printf("\nID da baia: ");
                scanf("%d", &idBusca);
                posBaia = -1;
                for (i = 0; i < totalBaias; i++) {
                    if (listaBaias[i].idBaia == idBusca && listaBaias[i].ativo == 1) {
                        posBaia = i;
                    }
                }
                if (posBaia == -1) {
                    printf("Baia nao encontrada.\n");
                    pausar();
                    break;
                }
                if (listaBaias[posBaia].emManutencao == 1) {
                    printf("Baia em manutencao! Escolha outra.\n");
                    pausar();
                    break;
                }
                printf("Minutos de uso: ");
                scanf("%d", &minutos);
                // --- consumo (opcional) ---
                listarProdutosAtivos();
                printf("\nID do produto (0 = nenhum): ");
                scanf("%d", &idProd);
                qtd = 0;
                posProduto = -1;
                if (idProd != 0) {
                    for (i = 0; i < totalProdutos; i++) {
                        if (listaProdutos[i].idProduto == idProd && listaProdutos[i].ativo == 1) {
                            posProduto = i;
                        }
                    }
                    if (posProduto == -1) {
                        printf("Produto nao encontrado.\n");
                        pausar();
                        break;
                    }
                    printf("Quantidade: ");
                    scanf("%d", &qtd);
                    if (qtd > listaProdutos[posProduto].estoque) {
                        printf("Estoque insuficiente! Disponivel: %d\n", listaProdutos[posProduto].estoque);
                        pausar();
                        break;
                    }
                    listaProdutos[posProduto].estoque = listaProdutos[posProduto].estoque - qtd;
                }
                // --- grava o atendimento ---
                listaAtendimentos[totalAtendimentos].idAtendimento = totalAtendimentos + 1;
                listaAtendimentos[totalAtendimentos].idCliente = listaClientes[posCliente].idCliente;
                listaAtendimentos[totalAtendimentos].idBaia = listaBaias[posBaia].idBaia;
                listaAtendimentos[totalAtendimentos].minutosUso = minutos;
                listaAtendimentos[totalAtendimentos].idProduto = idProd;
                listaAtendimentos[totalAtendimentos].qtdProduto = qtd;
                listaAtendimentos[totalAtendimentos].valorTotal = minutos / 60.0 * listaBaias[posBaia].precoHora;
                if (posProduto != -1) {
                    listaAtendimentos[totalAtendimentos].valorTotal =
                        listaAtendimentos[totalAtendimentos].valorTotal + qtd * listaProdutos[posProduto].preco;
                }
                listaAtendimentos[totalAtendimentos].ativo = 1;
                printf("Atendimento %d registrado! Total: R$ %.2f\n",
                       listaAtendimentos[totalAtendimentos].idAtendimento,
                       listaAtendimentos[totalAtendimentos].valorTotal);
                totalAtendimentos++;
                salvarAtendimentosCSV();
                salvarProdutosCSV();
                pausar();
                break;
            case 2:
                listarAtendimentosAtivos();
                pausar();
                break;
            case 3:
                listarAtendimentosAtivos();
                printf("\nID do atendimento a editar: ");
                scanf("%d", &idBusca);
                achou = 0;
                for (i = 0; i < totalAtendimentos; i++) {
                    if (listaAtendimentos[i].idAtendimento == idBusca && listaAtendimentos[i].ativo == 1) {
                        achou = 1;
                        // acha a baia e o produto desse atendimento (indices = id - 1)
                        posBaia = listaAtendimentos[i].idBaia - 1;
                        posProduto = listaAtendimentos[i].idProduto - 1;   // -1 se nao tem produto
                        printf("Novos minutos de uso: ");
                        scanf("%d", &minutos);
                        qtd = 0;
                        if (posProduto != -1) {
                            // devolve a quantidade antiga para o estoque antes de pedir a nova
                            listaProdutos[posProduto].estoque =
                                listaProdutos[posProduto].estoque + listaAtendimentos[i].qtdProduto;
                            printf("Nova quantidade (estoque: %d): ", listaProdutos[posProduto].estoque);
                            scanf("%d", &qtd);
                            if (qtd > listaProdutos[posProduto].estoque) {
                                printf("Estoque insuficiente! Mantida a quantidade antiga.\n");
                                qtd = listaAtendimentos[i].qtdProduto;
                            }
                            listaProdutos[posProduto].estoque = listaProdutos[posProduto].estoque - qtd;
                        }
                        listaAtendimentos[i].minutosUso = minutos;
                        listaAtendimentos[i].qtdProduto = qtd;
                        listaAtendimentos[i].valorTotal = minutos / 60.0 * listaBaias[posBaia].precoHora;
                        if (posProduto != -1) {
                            listaAtendimentos[i].valorTotal =
                                listaAtendimentos[i].valorTotal + qtd * listaProdutos[posProduto].preco;
                        }
                        printf("Atendimento atualizado! Novo total: R$ %.2f\n", listaAtendimentos[i].valorTotal);
                        salvarAtendimentosCSV();
                        salvarProdutosCSV();
                    }
                }
                if (achou == 0) {
                    printf("Atendimento nao encontrado.\n");
                }
                pausar();
                break;
            case 4:
                listarAtendimentosAtivos();
                printf("\nID do atendimento a estornar: ");
                scanf("%d", &idBusca);
                achou = 0;
                for (i = 0; i < totalAtendimentos; i++) {
                    if (listaAtendimentos[i].idAtendimento == idBusca && listaAtendimentos[i].ativo == 1) {
                        listaAtendimentos[i].ativo = 0;   // remocao logica (estorno)
                        posProduto = listaAtendimentos[i].idProduto - 1;
                        if (posProduto != -1) {
                            // devolve os produtos para o estoque
                            listaProdutos[posProduto].estoque =
                                listaProdutos[posProduto].estoque + listaAtendimentos[i].qtdProduto;
                        }
                        printf("Atendimento estornado!\n");
                        achou = 1;
                        salvarAtendimentosCSV();
                        salvarProdutosCSV();
                    }
                }
                if (achou == 0) {
                    printf("Atendimento nao encontrado.\n");
                }
                pausar();
                break;
            case 5:
                relatorioBaiaMaisUsada();
                break;
            case 6:
                relatorioProdutoMaisVendido();
                break;
            case 7:
                relatorioClienteVIP();
                break;
            case 8:
                relatorioFaturamento();
                break;
            case 9:
                listarClientesAtivos();
                printf("\nID do cliente para consultar atendimentos: ");
                scanf("%d", &idBusca);
                achou = 0;
                for (i = 0; i < totalAtendimentos; i++) {
                    if (listaAtendimentos[i].ativo == 1 && listaAtendimentos[i].idCliente == idBusca) {
                        printf("Atendimento ID: %d | %d min | R$ %.2f\n",
                               listaAtendimentos[i].idAtendimento, listaAtendimentos[i].minutosUso,
                               listaAtendimentos[i].valorTotal);
                        achou = 1;
                    }
                }
                if (achou == 0) printf("Nenhum atendimento ativo encontrado para esse cliente.\n");
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

// salva a lista de atendimentos em um arquivo CSV

void salvarAtendimentosCSV(void) {
    FILE *arquivo = fopen("atendimentos.csv", "w");

    if (arquivo == NULL) {
        printf("Erro ao salvar atendimentos.csv\n");
        return;
    }

    for (int i = 0; i < totalAtendimentos; i++) {
        fprintf(arquivo, "%d;%d;%d;%d;%d;%d;%.2f;%d\n",
                listaAtendimentos[i].idAtendimento,
                listaAtendimentos[i].idCliente,
                listaAtendimentos[i].idBaia,
                listaAtendimentos[i].minutosUso,
                listaAtendimentos[i].idProduto,
                listaAtendimentos[i].qtdProduto,
                listaAtendimentos[i].valorTotal,
                listaAtendimentos[i].ativo);
    }

    fclose(arquivo);
}

void carregarAtendimentosCSV(void) {
    FILE *arquivo = fopen("atendimentos.csv", "r");

    if (arquivo == NULL) {
        return;
    }

    totalAtendimentos = 0;

    while (totalAtendimentos < MAX_ATENDIMENTOS &&
           fscanf(arquivo, "%d;%d;%d;%d;%d;%d;%f;%d",
                  &listaAtendimentos[totalAtendimentos].idAtendimento,
                  &listaAtendimentos[totalAtendimentos].idCliente,
                  &listaAtendimentos[totalAtendimentos].idBaia,
                  &listaAtendimentos[totalAtendimentos].minutosUso,
                  &listaAtendimentos[totalAtendimentos].idProduto,
                  &listaAtendimentos[totalAtendimentos].qtdProduto,
                  &listaAtendimentos[totalAtendimentos].valorTotal,
                  &listaAtendimentos[totalAtendimentos].ativo) == 8) {
        totalAtendimentos++;
    }

    fclose(arquivo);
}

#endif