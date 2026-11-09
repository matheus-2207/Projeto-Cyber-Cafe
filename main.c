// ============================================================================
// CYBER CAFE ANOS 2000 (Baias e Consumo)
// Autor: Murylo Gabriel - RGM 47902523 (Modulos 1 e 3)
// Autor: Matheus Vendramim - RGM 47602465 (Modulos 2 e 4)
// ============================================================================
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

// Struct do cliente (Modulo 1 - Murylo)
struct Cliente {
    int idCliente;
    char nick[30];      // apelido nos jogos, uma palavra (ex: SniperBR)
    char telefone[20];
    int idade;
    int ativo;          // 1 = ativo, 0 = removido
};
struct Cliente listaClientes[50];   // vetor com ate 50 clientes
int totalClientes = 0;              // quantos clientes ja foram cadastrados

// Struct da baia (Modulo 2 - Matheus)
struct Baia {
    int idBaia;
    char nomeMaquina[20];  // ex: PC-01
    float precoHora;       // valor cobrado por hora
    int emManutencao;      // 1 = em manutencao, 0 = funcionando
    int ativo;             // 1 = ativa, 0 = removida
};
struct Baia listaBaias[50];
int totalBaias = 0;

// Struct do produto (Modulo 3 - Murylo)
struct Produto {
    int idProduto;
    char nomeProduto[30];  // nome do produto, uma palavra (ex: Coca600ml)
    float preco;           // preco de venda
    int estoque;           // quantidade disponivel
    int ativo;             // 1 = ativo, 0 = removido
};
struct Produto listaProdutos[50];
int totalProdutos = 0;

// Struct do atendimento (Modulo 4 - Matheus)
// Cada atendimento liga um cliente, uma baia e um produto consumido
struct Atendimento {
    int idAtendimento;
    int idCliente;     // quem usou (id da struct Cliente)
    int idBaia;        // qual PC usou (id da struct Baia)
    int minutosUso;    // tempo de uso da baia
    int idProduto;     // produto consumido (0 = nenhum)
    int qtdProduto;    // quantidade do produto
    float valorTotal;  // valor da baia + valor do consumo
    int ativo;         // 1 = valido, 0 = estornado
};
struct Atendimento listaAtendimentos[50];
int totalAtendimentos = 0;

// Limpa a tela do terminal (Windows usa cls, Linux/macOS usa clear)
void limparTela() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

// Espera o usuario apertar ENTER antes de continuar
void pausar() {
    printf("\nPressione ENTER para continuar...");
    getchar();   // consome o ENTER que sobrou do ultimo scanf
    getchar();   // espera o novo ENTER do usuario
}


// ----------------------------------------------------------------------------
// MODULO 1: PERSPECTIVA DE CLIENTES
// Autor: Murylo Gabriel - RGM 47902523
// ----------------------------------------------------------------------------
void moduloClientes() {
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
                if (totalClientes >= 50) {
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
                }
                pausar();
                break;
            case 2:
                printf("Digite o ID para buscar (0 = listar todos): ");
                scanf("%d", &idBusca);
                achou = 0;
                for (i = 0; i < totalClientes; i++) {
                    if (listaClientes[i].ativo == 1) {
                        if (idBusca == 0 || listaClientes[i].idCliente == idBusca) {
                            printf("ID: %d | Nick: %s | Tel: %s | Idade: %d\n",
                                   listaClientes[i].idCliente, listaClientes[i].nick,
                                   listaClientes[i].telefone, listaClientes[i].idade);
                            achou = 1;
                        }
                    }
                }
                if (achou == 0) {
                    printf("Nenhum cliente encontrado.\n");
                }
                pausar();
                break;
            case 3:
                printf("ID do cliente a editar: ");
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
                    }
                }
                if (achou == 0) {
                    printf("Cliente nao encontrado.\n");
                }
                pausar();
                break;
            case 4:
                printf("ID do cliente a remover: ");
                scanf("%d", &idBusca);
                achou = 0;
                for (i = 0; i < totalClientes; i++) {
                    if (listaClientes[i].idCliente == idBusca && listaClientes[i].ativo == 1) {
                        listaClientes[i].ativo = 0;   // remocao logica
                        printf("Cliente removido!\n");
                        achou = 1;
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

// ----------------------------------------------------------------------------
// MODULO 2: PERSPECTIVA DE BAIAS / PCs
// Autor: Matheus Vendramim - RGM 47602465
// ----------------------------------------------------------------------------
void moduloBaias() {
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
                if (totalBaias >= 50) {
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
                }
                pausar();
                break;
            case 2:
                printf("Digite o ID para buscar (0 = listar todas): ");
                scanf("%d", &idBusca);
                achou = 0;
                for (i = 0; i < totalBaias; i++) {
                    if (listaBaias[i].ativo == 1) {
                        if (idBusca == 0 || listaBaias[i].idBaia == idBusca) {
                            printf("ID: %d | Maquina: %s | R$ %.2f/h | ",
                                   listaBaias[i].idBaia, listaBaias[i].nomeMaquina,
                                   listaBaias[i].precoHora);
                            if (listaBaias[i].emManutencao == 1) {
                                printf("EM MANUTENCAO\n");
                            } else {
                                printf("Funcionando\n");
                            }
                            achou = 1;
                        }
                    }
                }
                if (achou == 0) {
                    printf("Nenhuma baia encontrada.\n");
                }
                pausar();
                break;
            case 3:
                printf("ID da baia a editar: ");
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
                    }
                }
                if (achou == 0) {
                    printf("Baia nao encontrada.\n");
                }
                pausar();
                break;
            case 4:
                printf("ID da baia a remover: ");
                scanf("%d", &idBusca);
                achou = 0;
                for (i = 0; i < totalBaias; i++) {
                    if (listaBaias[i].idBaia == idBusca && listaBaias[i].ativo == 1) {
                        listaBaias[i].ativo = 0;   // remocao logica
                        printf("Baia removida!\n");
                        achou = 1;
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

// ----------------------------------------------------------------------------
// MODULO 3: PERSPECTIVA DE PRODUTOS DO BALCAO
// Autor: Murylo Gabriel - RGM 47902523
// ----------------------------------------------------------------------------
void moduloProdutos() {
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
                if (totalProdutos >= 50) {
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
                }
                pausar();
                break;
            case 2:
                printf("Digite o ID para buscar (0 = listar todos): ");
                scanf("%d", &idBusca);
                achou = 0;
                for (i = 0; i < totalProdutos; i++) {
                    if (listaProdutos[i].ativo == 1) {
                        if (idBusca == 0 || listaProdutos[i].idProduto == idBusca) {
                            printf("ID: %d | %s | R$ %.2f | Estoque: %d\n",
                                   listaProdutos[i].idProduto, listaProdutos[i].nomeProduto,
                                   listaProdutos[i].preco, listaProdutos[i].estoque);
                            achou = 1;
                        }
                    }
                }
                if (achou == 0) {
                    printf("Nenhum produto encontrado.\n");
                }
                pausar();
                break;
            case 3:
                printf("ID do produto a editar: ");
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
                    }
                }
                if (achou == 0) {
                    printf("Produto nao encontrado.\n");
                }
                pausar();
                break;
            case 4:
                printf("ID do produto a remover: ");
                scanf("%d", &idBusca);
                achou = 0;
                for (i = 0; i < totalProdutos; i++) {
                    if (listaProdutos[i].idProduto == idBusca && listaProdutos[i].ativo == 1) {
                        listaProdutos[i].ativo = 0;   // remocao logica
                        printf("Produto removido!\n");
                        achou = 1;
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

// ----------------------------------------------------------------------------
// MODULO 4: PERSPECTIVA DE ATENDIMENTOS E RELATORIOS
// Autor: Matheus Vendramim - RGM 47602465
// ----------------------------------------------------------------------------
void moduloAtendimentosRelatorios() {
    int opcao;
    int i, j;
    int idBusca;
    int achou;
    int posCliente, posBaia, posProduto;   // posicao (indice) no vetor; -1 = nao achou
    int minutos, qtd, idProd;              // dados digitados
    int somaInt, maiorInt, idMaior;        // usados nos relatorios
    float somaFloat, maiorFloat;           // usados nos relatorios

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
        printf("0. Voltar ao Menu Principal\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                if (totalAtendimentos >= 50) {
                    printf("Limite de 50 atendimentos atingido!\n");
                    pausar();
                    break;
                }
                // --- procura o cliente ---
                printf("ID do cliente: ");
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
                printf("ID da baia: ");
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
                printf("ID do produto (0 = nenhum): ");
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
                pausar();
                break;
            case 2:
                achou = 0;
                for (i = 0; i < totalAtendimentos; i++) {
                    if (listaAtendimentos[i].ativo == 1) {
                        printf("ID: %d | Cliente: %d | Baia: %d | %d min | Produto: %d x%d | R$ %.2f\n",
                               listaAtendimentos[i].idAtendimento, listaAtendimentos[i].idCliente,
                               listaAtendimentos[i].idBaia, listaAtendimentos[i].minutosUso,
                               listaAtendimentos[i].idProduto, listaAtendimentos[i].qtdProduto,
                               listaAtendimentos[i].valorTotal);
                        achou = 1;
                    }
                }
                if (achou == 0) {
                    printf("Nenhum atendimento registrado.\n");
                }
                pausar();
                break;
            case 3:
                printf("ID do atendimento a editar: ");
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
                    }
                }
                if (achou == 0) {
                    printf("Atendimento nao encontrado.\n");
                }
                pausar();
                break;
            case 4:
                printf("ID do atendimento a estornar: ");
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
                    }
                }
                if (achou == 0) {
                    printf("Atendimento nao encontrado.\n");
                }
                pausar();
                break;
            case 5:
                maiorInt = 0;
                idMaior = 0;
                for (i = 0; i < totalBaias; i++) {
                    somaInt = 0;
                    for (j = 0; j < totalAtendimentos; j++) {
                        if (listaAtendimentos[j].ativo == 1 && listaAtendimentos[j].idBaia == listaBaias[i].idBaia) {
                            somaInt = somaInt + listaAtendimentos[j].minutosUso;
                        }
                    }
                    if (somaInt > maiorInt) {
                        maiorInt = somaInt;
                        idMaior = i;
                    }
                }
                if (maiorInt == 0) {
                    printf("Nenhum uso registrado.\n");
                } else {
                    printf("Baia mais usada: %s com %d minutos.\n", listaBaias[idMaior].nomeMaquina, maiorInt);
                }
                pausar();
                break;
            case 6:
                maiorInt = 0;
                idMaior = 0;
                for (i = 0; i < totalProdutos; i++) {
                    somaInt = 0;
                    for (j = 0; j < totalAtendimentos; j++) {
                        if (listaAtendimentos[j].ativo == 1 && listaAtendimentos[j].idProduto == listaProdutos[i].idProduto) {
                            somaInt = somaInt + listaAtendimentos[j].qtdProduto;
                        }
                    }
                    if (somaInt > maiorInt) {
                        maiorInt = somaInt;
                        idMaior = i;
                    }
                }
                if (maiorInt == 0) {
                    printf("Nenhuma venda registrada.\n");
                } else {
                    printf("Produto mais vendido: %s com %d unidades.\n", listaProdutos[idMaior].nomeProduto, maiorInt);
                }
                pausar();
                break;
            case 7:
                maiorFloat = 0;
                idMaior = 0;
                for (i = 0; i < totalClientes; i++) {
                    somaFloat = 0;
                    for (j = 0; j < totalAtendimentos; j++) {
                        if (listaAtendimentos[j].ativo == 1 && listaAtendimentos[j].idCliente == listaClientes[i].idCliente) {
                            somaFloat = somaFloat + listaAtendimentos[j].valorTotal;
                        }
                    }
                    if (somaFloat > maiorFloat) {
                        maiorFloat = somaFloat;
                        idMaior = i;
                    }
                }
                if (maiorFloat == 0) {
                    printf("Nenhum gasto registrado.\n");
                } else {
                    printf("Cliente VIP: %s gastou R$ %.2f.\n", listaClientes[idMaior].nick, maiorFloat);
                }
                pausar();
                break;
            case 8:
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


int main() {
    int opcao;   // guarda a opcao escolhida no menu principal

    setlocale(LC_ALL, "Portuguese");   // permite acentos no console

    do {
        limparTela();
        printf("\n===== CYBER CAFE ANOS 2000 =====\n");
        printf("1. Modulo de Clientes\n");
        printf("2. Modulo de Baias / PCs\n");
        printf("3. Modulo de Produtos do Balcao\n");
        printf("4. Modulo de Atendimentos e Relatorios\n");
        printf("0. Encerrar o Sistema\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                moduloClientes();
                break;
            case 2:
                moduloBaias();
                break;
            case 3:
                moduloProdutos();
                break;
            case 4:
                moduloAtendimentosRelatorios();
                break;
            case 0:
                printf("Encerrando o sistema...\n");
                break;
            default:
                printf("Opcao invalida! Tente novamente.\n");
                pausar();
        }
    } while (opcao != 0);

    return 0;
}
