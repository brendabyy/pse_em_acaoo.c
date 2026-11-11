#include <stdio.h>
#include <string.h>

#define MAX 100

// Estrutura para guardar os dados da ação
typedef struct {
    int codigo;
    char escola[50];
    char tema[50];
    char nome[50];
    char data[15];
    char responsavel[50];
    int qtd_prevista;
    char situacao[20]; // "planejada", "realizada", "cancelada"
    int qtd_efetiva;
} Acao;

// Assinaturas das funções
void cadastrar(Acao v[], int *total);
void listar(Acao v[], int total);
void pesquisar(Acao v[], int total);
void atualizar(Acao v[], int total);
void resumo(Acao v[], int total);

int main() {
    Acao v[MAX];
    int total = 0;
    int opcao = 0;

    do {
        printf("\n=== PSE EM ACAO (SAUDE MENTAL) ===\n");
        printf("1. Cadastrar acao\n");
        printf("2. Listar acoes\n");
        printf("3. Pesquisar por codigo\n");
        printf("4. Atualizar situacao\n");
        printf("5. Gerar resumo\n");
        printf("0. Sair\n");
        printf("Escolha uma opcao: ");
        
        if (scanf("%d", &opcao) != 1) {
            printf("Entrada invalida!\n");
            while (getchar() != '\n');
            continue;
        }
        getchar(); // Limpa o \n do buffer

        switch(opcao) {
            case 1: cadastrar(v, &total); break;
            case 2: listar(v, total); break;
            case 3: pesquisar(v, total); break;
            case 4: atualizar(v, total); break;
            case 5: resumo(v, total); break;
            case 0: printf("Encerrando...\n"); break;
            default: printf("Opcao invalida!\n");
        }
    } while(opcao != 0);

    return 0;
}

// 1. Cadastrar Ação
void cadastrar(Acao v[], int *total) {
    int cod = 0;
    int i = 0;

    if (*total >= MAX) {
        printf("Limite de armazenamento atingido!\n");
        return;
    }

    printf("Codigo da acao: ");
    scanf("%d", &cod);
    getchar();

    // Validação de código duplicado
    for (i = 0; i < *total; i++) {
        if (v[i].codigo == cod) {
            printf("Erro: Codigo ja cadastrado!\n");
            return;
        }
    }

    v[*total].codigo = cod;

    printf("Escola: ");
    fgets(v[*total].escola, 50, stdin);
    v[*total].escola[strcspn(v[*total].escola, "\n")] = 0;

    printf("Tema: ");
    fgets(v[*total].tema, 50, stdin);
    v[*total].tema[strcspn(v[*total].tema, "\n")] = 0;

    printf("Nome da acao: ");
    fgets(v[*total].nome, 50, stdin);
    v[*total].nome[strcspn(v[*total].nome, "\n")] = 0;

    printf("Data (DD/MM/AAAA): ");
    fgets(v[*total].data, 15, stdin);
    v[*total].data[strcspn(v[*total].data, "\n")] = 0;

    printf("Responsavel: ");
    fgets(v[*total].responsavel, 50, stdin);
    v[*total].responsavel[strcspn(v[*total].responsavel, "\n")] = 0;

    printf("Quantidade prevista de participantes: ");
    scanf("%d", &v[*total].qtd_prevista);
    getchar();

    // Validação de quantidade negativa
    if (v[*total].qtd_prevista < 0) {
        printf("Erro: A quantidade nao pode ser negativa!\n");
        return;
    }

    strcpy(v[*total].situacao, "planejada");
    v[*total].qtd_efetiva = 0;

    (*total)++;
    printf("Acao cadastrada com sucesso!\n");
}

// 2. Listar Ações
void listar(Acao v[], int total) {
    int i = 0;

    if (total == 0) {
        printf("Nenhuma acao cadastrada.\n");
        return;
    }

    printf("\n--- LISTA DE ACOES ---\n");
    for (i = 0; i < total; i++) {
        printf("Codigo: %d | Escola: %s | Tema: %s | Acao: %s | Situacao: %s\n", 
               v[i].codigo, v[i].escola, v[i].tema, v[i].nome, v[i].situacao);
    }
}

// 3. Pesquisar por Código
void pesquisar(Acao v[], int total) {
    int cod = 0;
    int achou = 0;
    int i = 0;

    if (total == 0) {
        printf("Nenhuma acao cadastrada.\n");
        return;
    }

    printf("Digite o codigo para buscar: ");
    scanf("%d", &cod);
    getchar();

    for (i = 0; i < total; i++) {
        if (v[i].codigo == cod) {
            printf("\n[Acao Encontrada]\n");
            printf("Codigo: %d\n", v[i].codigo);
            printf("Escola: %s\n", v[i].escola);
            printf("Tema: %s\n", v[i].tema);
            printf("Nome: %s\n", v[i].nome);
            printf("Data: %s\n", v[i].data);
            printf("Responsavel: %s\n", v[i].responsavel);
            printf("Qtd Prevista: %d\n", v[i].qtd_prevista);
            printf("Situacao: %s\n", v[i].situacao);
            printf("Qtd Efetiva: %d\n", v[i].qtd_efetiva);
            achou = 1;
            break;
        }
    }
    if (!achou) {
        printf("Nenhum registro encontrado com este codigo.\n");
    }
}

// 4. Atualizar Situação
void atualizar(Acao v[], int total) {
    int cod = 0;
    int pos = -1;
    int i = 0;
    int op = 0;

    if (total == 0) {
        printf("Nenhuma acao cadastrada.\n");
        return;
    }

    printf("Digite o codigo da acao que deseja atualizar: ");
    scanf("%d", &cod);
    getchar();

    for (i = 0; i < total; i++) {
        if (v[i].codigo == cod) {
            pos = i;
            break;
        }
    }

    if (pos == -1) {
        printf("Erro: Acao nao encontrada.\n");
        return;
    }

    printf("Nova situacao:\n");
    printf("1 - Planejada\n");
    printf("2 - Realizada\n");
    printf("3 - Cancelada\n");
    printf("Escolha uma opcao: ");
    scanf("%d", &op);
    getchar();

    if (op == 1) {
        strcpy(v[pos].situacao, "planejada");
        v[pos].qtd_efetiva = 0;
    } else if (op == 2) {
        strcpy(v[pos].situacao, "realizada");
        printf("Digite a quantidade efetiva de participantes: ");
        scanf("%d", &v[pos].qtd_efetiva);
        getchar();
    } else if (op == 3) {
        strcpy(v[pos].situacao, "cancelada");
        v[pos].qtd_efetiva = 0;
    } else {
        printf("Opcao invalida!\n");
        return;
    }
    printf("Situacao atualizada com sucesso!\n");
}

// 5. Gerar Resumo Geral
void resumo(Acao v[], int total) {
    int planejadas = 0;
    int realizadas = 0;
    int canceladas = 0;
    int total_part = 0;
    int total_prev = 0;
    int i = 0;
    float perc = 0.0;

    for (i = 0; i < total; i++) {
        if (strcmp(v[i].situacao, "planejada") == 0) {
            planejadas++;
        } else if (strcmp(v[i].situacao, "realizada") == 0) {
            realizadas++;
            total_part += v[i].qtd_efetiva;
            total_prev += v[i].qtd_prevista;
        } else if (strcmp(v[i].situacao, "cancelada") == 0) {
            canceladas++;
        }
    }

    if (total_prev > 0) {
        perc = ((float)total_part / total_prev) * 100.0;
    }

    printf("\n=== RESUMO GERAL DO SISTEMA ===\n");
    printf("Acoes Planejadas: %d\n", planejadas);
    printf("Acoes Realizadas: %d\n", realizadas);
    printf("Acoes Canceladas: %d\n", canceladas);
    printf("Total de Participantes Efetivos: %d\n", total_part);
    printf("Percentual de Participacao: %.2f%%\n", perc);
}
