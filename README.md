# Cyber Café Anos 2000 (Baias e Consumo)

Projeto P2 da disciplina **Algoritmos e Pensamento Computacional** (Prof. Rafael Duarte).

Sistema de gestão em modo console, escrito em **C**, para um cyber café dos anos 2000: os clientes alugam uma baia (PC) por tempo e consomem produtos do balcão (bebidas, salgadinhos, impressões). Tudo fica em um único arquivo `main.c`.

## Equipe

| Integrante | Perspectiva (módulo) |
|---|---|
| Murylo Gabriel (RGM 47902523) | 1. Clientes (gamers) |
| Matheus Vendramim (RGM 47602465) | 2. Baias (PCs do salão) |
| Samuel Borges | 3. Produtos do balcão |
| Os 3 integrantes (dividido) | 4. Atendimentos e relatórios |

## O que entregamos no Checkpoint 1

1. Repositório no GitHub compartilhado com a equipe e com o professor, com commits feitos ao longo da semana.
2. Uma `struct` por perspectiva no **escopo global**, com pelo menos 4 campos de tipos variados (`int`, `float`, `char[]`) e um vetor global de tamanho `[50]` para cada uma.
3. **Menu principal** no `main()` em loop contínuo (`do-while` + `switch-case`), que abre o submenu de cada perspectiva.
4. **Submenu de cada perspectiva** (uma função `void`) com as 4 operações: Cadastrar, Listar/Buscar, Editar e Remover. O `0` volta ao menu principal sem fechar o programa.
5. Cada função identificada no cabeçalho com `// Autor: Nome do Aluno`, e o código compilando sem erros no Dev-C++ / GCC.

Neste checkpoint, o importante é a arquitetura (structs, menus e divisão por integrante) estar rodando. As contas e os relatórios podem aparecer como "[Em construcao]" e ficar prontos nas próximas entregas.

## Modelagem de dados (structs)

### 1. Clientes (Murylo Gabriel)
```c
struct Cliente {
    int idCliente;
    char nick[30];      // apelido nos jogos, uma palavra (ex: SniperBR)
    char telefone[20];
    int idade;
    int ativo;          // 1 = ativo, 0 = removido
};
struct Cliente listaClientes[50];
int totalClientes = 0;
```

### 2. Baias / PCs (Matheus Vendramim)
```c
struct Baia {
    int idBaia;
    char nomeMaquina[20];  // ex: PC-01
    float precoHora;       // valor cobrado por hora
    int emManutencao;      // 1 = em manutenção, 0 = funcionando
    int ativo;             // 1 = ativa, 0 = removida
};
struct Baia listaBaias[50];
int totalBaias = 0;
```

### 3. Produtos do balcão (Samuel Borges)
```c
struct Produto {
    int idProduto;
    char nomeProduto[30];  // ex: Coca600ml
    float preco;
    int estoque;
    int ativo;             // 1 = ativo, 0 = removido
};
struct Produto listaProdutos[50];
int totalProdutos = 0;
```

### 4. Atendimentos (Equipe)
Cada atendimento é uma "comanda" que liga um cliente a uma baia e, se houver, a um produto consumido.
```c
struct Atendimento {
    int idAtendimento;
    int idCliente;     // quem usou
    int idBaia;        // qual PC usou
    int minutosUso;    // tempo de uso da baia
    int idProduto;     // produto consumido (0 = nenhum)
    int qtdProduto;
    float valorTotal;  // (minutos / 60 * precoHora) + (qtd * preco)
    int ativo;         // 1 = válido, 0 = estornado
};
struct Atendimento listaAtendimentos[50];
int totalAtendimentos = 0;
```

## Menus

**Menu principal:**
```
1. Modulo de Clientes (Murylo)
2. Modulo de Baias / PCs (Matheus)
3. Modulo de Produtos do Balcao (Samuel)
4. Modulo de Atendimentos e Relatorios (Equipe)
0. Encerrar o Sistema
```

**Submenus 1 a 3** (`moduloClientes()`, `moduloBaias()`, `moduloProdutos()`):
```
1. Cadastrar
2. Listar / Buscar
3. Editar
4. Remover
0. Voltar ao Menu Principal
```

**Submenu 4** (`moduloAtendimentosRelatorios()`):
```
1. Registrar Atendimento (Cliente + Baia + Consumo)
2. Listar Atendimentos
3. Editar Atendimento
4. Estornar Atendimento
5. [RELATORIO] Baia mais usada (mais minutos)
6. [RELATORIO] Produto mais vendido
7. [RELATORIO] Cliente VIP (maior gasto)
8. [RELATORIO] Faturamento do dia
0. Voltar ao Menu Principal
```

## Regras que a equipe segue

Pela regra do arquiteto do professor, usamos **somente o que foi ensinado em aula**, e cada integrante precisa saber explicar cada linha do próprio módulo:

- Bibliotecas: `stdio.h`, `stdlib.h` e `locale.h` (`setlocale` para acentos).
- `printf` e `scanf` com `&`. Texto é lido com `scanf("%s", ...)`, então nomes são de **uma palavra só** (ex: `SniperBR`, `PC-01`).
- `if`/`else`, `switch-case`, `for`, `while`, `do-while`, `break`.
- `struct` e vetores no escopo global, e funções `void` fora do `main()`.
- **Não usamos:** `typedef`, `malloc`, `strcpy`/`strcmp`, `fgets`, nem bibliotecas externas.
- Remover = "remoção lógica": o campo `ativo` vira `0` e o registro some das listagens.

## Como compilar e rodar

**Dev-C++:** abrir o `main.c` e apertar **F11** (compilar e executar).

**GCC (terminal):**
```
gcc main.c -o cybercafe
./cybercafe
```

## Próximas etapas

- Completar as contas e os relatórios do módulo 4.
- Aula 11: salvar e carregar os vetores em arquivos `.txt` / `.csv` com `FILE *`.
- Aula 12: ordenação (ex.: ranking de clientes por gasto).