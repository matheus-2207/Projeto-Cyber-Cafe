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

// 2. Perspectiva do Matheus: Baias (PCs do salao)
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
struct Produto listaProdutos[50];   // vetor com ate 50 produtos
int totalProdutos = 0;              // quantos produtos ja foram cadastrados

// Struct do atendimento
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
struct Atendimento listaAtendimentos[50];   // vetor com ate 50 atendimentos
int totalAtendimentos = 0;                  // quantos atendimentos ja foram registrados


// ----------------------------------------------------------------------------
// MODULO 1: PERSPECTIVA DE CLIENTES
// Autor: Murylo Gabriel - RGM 47902523
// ----------------------------------------------------------------------------
void moduloClientes() {
    int opcao;   // guarda a opcao escolhida no submenu

    do {
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
                printf("[Em construcao] Cadastrar: id, nick, telefone e idade.\n");
                break;
            case 2:
                printf("[Em construcao] Listar / Buscar: mostra os clientes ativos (ou busca pelo id).\n");
                break;
            case 3:
                printf("[Em construcao] Editar: altera nick, telefone e idade pelo id.\n");
                break;
            case 4:
                printf("[Em construcao] Remover: muda o campo ativo para 0 pelo id.\n");
                break;
            case 0:
                printf("Voltando ao Menu Principal...\n");
                break;
            default:
                printf("Opcao invalida! Tente novamente.\n");
        }
    } while (opcao != 0);   // repete ate o usuario escolher 0
}

// ----------------------------------------------------------------------------
// MODULO 2: PERSPECTIVA DE BAIAS / PCs
// Autor: Matheus Vendramim - RGM 47602465
// ----------------------------------------------------------------------------
void moduloBaias() {
    int opcaoBaia;
    do {
        printf("\n--- [MODULO 2: GESTAO DE BAIAS / PCs (Matheus)] ---\n");
        printf("1. Cadastrar Nova Baia\n");
        printf("2. Listar / Buscar Baias\n");
        printf("3. Editar Baia (Preco ou Manutencao)\n");
        printf("4. Remover Baia\n");
        printf("0. Voltar ao Menu Principal\n");
        printf("Escolha uma acao: ");
        scanf("%d", &opcaoBaia);

        switch (opcaoBaia) {
            case 1:
                printf("\n[Em construcao] Cadastro de Baia...\n");
                printf("Campos previstos: ID, Nome da Maquina, Preco por Hora e Manutencao.\n");
                break;
            case 2:
                printf("\n[Em construcao] Listagem e busca de Baias...\n");
                break;
            case 3:
                printf("\n[Em construcao] Edicao de Baia por ID...\n");
                break;
            case 4:
                printf("\n[Em construcao] Remocao de Baia...\n");
                break;
            case 0:
                printf("\nRetornando ao menu principal...\n");
                break;
            default:
                printf("\n[ERRO] Opcao invalida no Modulo de Baias!\n");
        }
    } while (opcaoBaia != 0);
}

// ----------------------------------------------------------------------------
// MODULO 3: PERSPECTIVA DE PRODUTOS DO BALCAO
// Autor: Murylo Gabriel - RGM 47902523
// ----------------------------------------------------------------------------
void moduloProdutos() {
    int opcao;   // guarda a opcao escolhida no submenu

    do {
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
                printf("[Em construcao] Cadastrar: id, nome, preco e estoque.\n");
                break;
            case 2:
                printf("[Em construcao] Listar / Buscar: mostra os produtos ativos (ou busca pelo id).\n");
                break;
            case 3:
                printf("[Em construcao] Editar: altera preco e estoque pelo id.\n");
                break;
            case 4:
                printf("[Em construcao] Remover: muda o campo ativo para 0 pelo id.\n");
                break;
            case 0:
                printf("Voltando ao Menu Principal...\n");
                break;
            default:
                printf("Opcao invalida! Tente novamente.\n");
        }
    } while (opcao != 0);   // repete ate o usuario escolher 0
}

// MODULO 4: PERSPECTIVA DE ATENDIMENTOS E RELATORIOS

void moduloAtendimentosRelatorios() {
    int opcao;   // guarda a opcao escolhida no submenu

    do {
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
                printf("[Em construcao] Registrar: id do cliente, id da baia, minutos e produto consumido.\n");
                break;
            case 2:
                printf("[Em construcao] Listar: mostra todos os atendimentos validos.\n");
                break;
            case 3:
                printf("[Em construcao] Editar: altera minutos ou consumo pelo id.\n");
                break;
            case 4:
                printf("[Em construcao] Estornar: muda o campo ativo para 0 pelo id.\n");
                break;
            case 5:
                printf("[Em construcao] Relatorio: baia com mais minutos de uso.\n");
                break;
            case 6:
                printf("[Em construcao] Relatorio: produto com maior quantidade vendida.\n");
                break;
            case 7:
                printf("[Em construcao] Relatorio: cliente que mais gastou.\n");
                break;
            case 8:
                printf("[Em construcao] Relatorio: soma do valor de todos os atendimentos.\n");
                break;
            case 0:
                printf("Voltando ao Menu Principal...\n");
                break;
            default:
                printf("Opcao invalida! Tente novamente.\n");
        }
    } while (opcao != 0);   // repete ate o usuario escolher 0
}


int main() {
    int opcao;   // guarda a opcao escolhida no menu principal

    setlocale(LC_ALL, "Portuguese");   // permite acentos no console

    do {
        printf("\n===== CYBER CAFE ANOS 2000 =====\n");
        printf("1. Modulo de Clientes (Murylo)\n");
        printf("2. Modulo de Baias / PCs (Matheus)\n");
        printf("3. Modulo de Produtos do Balcao (Murylo)\n");
        printf("4. Modulo de Atendimentos e Relatorios (Equipe)\n");
        printf("0. Encerrar o Sistema\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                moduloClientes();   // abre o submenu de clientes
                break;
            case 2:
                moduloBaias(); // abre o submenu de baias / PCs
                break;
             case 3:
                moduloProdutos();   // abre o submenu de produtos
                break;
            case 4:
                moduloAtendimentosRelatorios(); // abre o submenu de atendimentos e relatorios
                break;
            case 0:
                printf("Encerrando o sistema...\n");
                break;
            default:
                printf("Opcao invalida! Tente novamente.\n");
        }
    } while (opcao != 0);

    return 0;
}

