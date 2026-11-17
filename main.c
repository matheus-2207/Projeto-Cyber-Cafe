// ============================================================================
// CYBER CAFE ANOS 2000 (Baias e Consumo)
// Autor: Murylo Gabriel - RGM 47902523 (Modulo 1)
// Autor: Matheus Vendramim - RGM 47602465 (Modulo 2)
// Autor: Samuel - RGM XXXXXXXX (Modulo 3 e Modulo 4)
// ============================================================================
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

void limparTela(void);
void pausar(void);

#include "clientes.h"
#include "baias.h"
#include "produtos.h"
#include "atendimento.h"

// Limpa a tela do terminal (Windows usa cls, Linux/macOS usa clear)
void limparTela(void) {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

// Espera o usuario apertar ENTER antes de continuar
void pausar(void) {
    printf("\nPressione ENTER para continuar...");
    getchar();   // consome o ENTER que sobrou do ultimo scanf
    getchar();   // espera o novo ENTER do usuario
}

int main(void) {
    int opcao;   // guarda a opcao escolhida no menu principal

    setlocale(LC_ALL, "Portuguese");   // permite acentos no console
    carregarClientesCSV();
    carregarBaiasCSV();
    carregarProdutosCSV();
    carregarAtendimentosCSV();

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