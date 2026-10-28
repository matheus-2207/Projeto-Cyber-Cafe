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

int main() {
    int opcao;   // guarda a opcao escolhida no menu principal

    setlocale(LC_ALL, "Portuguese");   // permite acentos no console

    do {
        printf("\n===== CYBER CAFE ANOS 2000 =====\n");
        printf("1. Modulo de Clientes (Murylo)\n");
        printf("2. Modulo de Baias / PCs (Matheus)\n");
        printf("3. Modulo de Produtos do Balcao (Samuel)\n");
        printf("4. Modulo de Atendimentos e Relatorios (Equipe)\n");
        printf("0. Encerrar o Sistema\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                moduloClientes();   // abre o submenu de clientes
                break;
            case 2:
                printf("[Em construcao] Modulo de Baias / PCs.\n");
                break;
            case 3:
                printf("[Em construcao] Modulo de Produtos do Balcao.\n");
                break;
            case 4:
                printf("[Em construcao] Modulo de Atendimentos e Relatorios.\n");
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
