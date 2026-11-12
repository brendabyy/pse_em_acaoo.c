#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX 100
#define TAM 50

// Estrutura para guardar os dados da acao
typedef struct {
    int codigo;
    char escola[TAM];
    char tema[TAM];
    char nome[TAM];
    char data[15];
    char responsavel[TAM];
    int qtd_prevista;
    char situacao[20]; // "planejada", "realizada", "cancelada"
    int qtd_efetiva;
} Acao;

// Funcoes auxiliares
void limpar_buffer_se_preciso(char texto[]);
void ler_texto(const char *msg, char destino[], int tam);
int ler_inteiro(const char *msg, int minimo);
int data_valida(const char *d);
void ler_data(char destino[]);
int buscar_indice(Acao v[], int total, int cod);
void para_minusculo(const char *origem, char destino[], int tam);
void exibir_acao(Acao a);

// Funcoes do menu
void cadastrar(Acao v[], int *total);
void listar(Acao v[], int total);
void pesquisar(Acao v[], int total);
void pesquisar_por_texto(Acao v[], int total, int campo);
void atualizar(Acao v[], int total);
void registrar_participantes(Acao v[], int total);
void resumo(Acao v[], int total);

int main() {
    Acao v[MAX];
    int total = 0;
    int opcao = 0;

    do {
        printf("\n=== PSE EM ACAO (SAUDE MENTAL) ===\n");
        printf("1. Cadastrar acao\n");
        printf("2. Listar acoes\n");
        printf("3. Pesquisar acao\n");
        printf("4. Atualizar situacao\n");
        printf("5. Registrar participantes efetivos\n");
        printf("6. Gerar resumo\n");
        printf("0. Sair\n");
        opcao = ler_inteiro("Escolha uma opcao: ", 0);

        switch (opcao) {
            case 1: cadastrar(v, &total); break;
            case 2: listar(v, total); break;
            case 3: pesquisar(v, total); break;
            case 4: atualizar(v, total); break;
            case 5: registrar_participantes(v, total); break;
            case 6: resumo(v, total); break;
            case 0: printf("Encerrando...\n"); break;
            default: printf("Opcao invalida!\n");
        }
    } while (opcao != 0);

    return 0;
}

// ---------- FUNCOES AUXILIARES ----------

// Se a linha lida for maior que o buffer, descarta o resto para nao
// "vazar" para a proxima leitura
void limpar_buffer_se_preciso(char texto[]) {
    int c = 0;
    if (strchr(texto, '\n') == NULL) {
        while ((c = getchar()) != '\n' && c != EOF);
    }
}

// Le um texto e so aceita se NAO estiver vazio (campo obrigatorio)
void ler_texto(const char *msg, char destino[], int tam) {
    int i = 0;
    int vazio = 1;

    while (1) {
        printf("%s", msg);
        if (fgets(destino, tam, stdin) == NULL) {
            printf("\nEntrada encerrada.\n");
            exit(0);
        }
        limpar_buffer_se_preciso(destino);
        destino[strcspn(destino, "\n")] = '\0';

        vazio = 1;
        for (i = 0; destino[i] != '\0'; i++) {
            if (!isspace((unsigned char)destino[i])) {
                vazio = 0;
                break;
            }
        }

        if (vazio) {
            printf("Erro: campo obrigatorio, nao pode ficar vazio!\n");
        } else {
            return;
        }
    }
}

// Le um numero inteiro, repete ate o usuario digitar algo valido
int ler_inteiro(const char *msg, int minimo) {
    char buffer[50];
    char *fim = NULL;
    long valor = 0;

    while (1) {
        printf("%s", msg);
        if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
            printf("\nEntrada encerrada.\n");
            exit(0);
        }
        limpar_buffer_se_preciso(buffer);

        valor = strtol(buffer, &fim, 10);
        if (fim == buffer) {
            printf("Erro: digite um numero valido!\n");
            continue;
        }
        while (*fim == ' ' || *fim == '\n' || *fim == '\r') {
            fim++;
        }
        if (*fim != '\0') {
            printf("Erro: digite apenas numeros!\n");
            continue;
        }
        if (valor < minimo) {
            printf("Erro: o valor nao pode ser menor que %d!\n", minimo);
            continue;
        }
        if (valor > 1000000) {
            printf("Erro: valor muito grande!\n");
            continue;
        }
        return (int)valor;
    }
}

// Confere se a data esta no formato DD/MM/AAAA
int data_valida(const char *d) {
    int i = 0;
    if (strlen(d) != 10) {
        return 0;
    }
    for (i = 0; i < 10; i++) {
        if (i == 2 || i == 5) {
            if (d[i] != '/') {
                return 0;
            }
        } else if (!isdigit((unsigned char)d[i])) {
            return 0;
        }
    }
    return 1;
}

void ler_data(char destino[]) {
    while (1) {
        ler_texto("Data prevista (DD/MM/AAAA): ", destino, 15);
        if (data_valida(destino)) {
            return;
        }
        printf("Erro: use o formato DD/MM/AAAA (ex: 15/10/2026)!\n");
    }
}

// Retorna a posicao do codigo no vetor, ou -1 se nao existir
int buscar_indice(Acao v[], int total, int cod) {
    int i = 0;
    for (i = 0; i < total; i++) {
        if (v[i].codigo == cod) {
            return i;
        }
    }
    return -1;
}

void para_minusculo(const char *origem, char destino[], int tam) {
    int i = 0;
    for (i = 0; i < tam - 1 && origem[i] != '\0'; i++) {
        destino[i] = (char)tolower((unsigned char)origem[i]);
    }
    destino[i] = '\0';
}

void exibir_acao(Acao a) {
    printf("\n[Acao Encontrada]\n");
    printf("Codigo: %d\n", a.codigo);
    printf("Escola: %s\n", a.escola);
    printf("Tema: %s\n", a.tema);
    printf("Nome: %s\n", a.nome);
    printf("Data: %s\n", a.data);
    printf("Responsavel: %s\n", a.responsavel);
    printf("Qtd Prevista: %d\n", a.qtd_prevista);
    printf("Situacao: %s\n", a.situacao);
    printf("Qtd Efetiva: %d\n", a.qtd_efetiva);
}

// ---------- FUNCOES DO MENU ----------

// 1. Cadastrar Acao
void cadastrar(Acao v[], int *total) {
    int cod = 0;

    if (*total >= MAX) {
        printf("Limite de armazenamento atingido!\n");
        return;
    }

    cod = ler_inteiro("Codigo da acao: ", 1);

    // Validacao de codigo duplicado
    if (buscar_indice(v, *total, cod) != -1) {
        printf("Erro: Codigo ja cadastrado!\n");
        return;
    }

    v[*total].codigo = cod;
    ler_texto("Escola: ", v[*total].escola, TAM);
    ler_texto("Tema: ", v[*total].tema, TAM);
    ler_texto("Nome da acao: ", v[*total].nome, TAM);
    ler_data(v[*total].data);
    ler_texto("Responsavel: ", v[*total].responsavel, TAM);
    v[*total].qtd_prevista = ler_inteiro("Quantidade prevista de participantes: ", 0);

    strcpy(v[*total].situacao, "planejada");
    v[*total].qtd_efetiva = 0;

    (*total)++;
    printf("Acao cadastrada com sucesso!\n");
}

// 2. Listar Acoes
void listar(Acao v[], int total) {
    int i = 0;

    if (total == 0) {
        printf("Nenhuma acao cadastrada.\n");
        return;
    }

    printf("\n--- LISTA DE ACOES ---\n");
    for (i = 0; i < total; i++) {
        printf("Codigo: %d | Escola: %s | Tema: %s | Acao: %s | Data: %s | Situacao: %s\n",
               v[i].codigo, v[i].escola, v[i].tema, v[i].nome, v[i].data, v[i].situacao);
    }
}

// 3. Pesquisar (por codigo, escola ou tema)
void pesquisar(Acao v[], int total) {
    int tipo = 0;
    int cod = 0;
    int pos = -1;

    if (total == 0) {
        printf("Nenhuma acao cadastrada.\n");
        return;
    }

    printf("\nPesquisar por:\n");
    printf("1 - Codigo\n");
    printf("2 - Escola\n");
    printf("3 - Tema\n");
    tipo = ler_inteiro("Escolha uma opcao: ", 1);

    if (tipo == 1) {
        cod = ler_inteiro("Digite o codigo para buscar: ", 1);
        pos = buscar_indice(v, total, cod);
        if (pos == -1) {
            printf("Nenhum registro encontrado com este codigo.\n");
        } else {
            exibir_acao(v[pos]);
        }
    } else if (tipo == 2) {
        pesquisar_por_texto(v, total, 1);
    } else if (tipo == 3) {
        pesquisar_por_texto(v, total, 2);
    } else {
        printf("Opcao invalida!\n");
    }
}

// campo: 1 = escola, 2 = tema (busca sem diferenciar maiuscula/minuscula)
void pesquisar_por_texto(Acao v[], int total, int campo) {
    char busca[TAM];
    char busca_min[TAM];
    char campo_min[TAM];
    int achou = 0;
    int i = 0;

    if (campo == 1) {
        ler_texto("Digite a escola (ou parte do nome): ", busca, TAM);
    } else {
        ler_texto("Digite o tema (ou parte do nome): ", busca, TAM);
    }
    para_minusculo(busca, busca_min, TAM);

    for (i = 0; i < total; i++) {
        if (campo == 1) {
            para_minusculo(v[i].escola, campo_min, TAM);
        } else {
            para_minusculo(v[i].tema, campo_min, TAM);
        }

        if (strstr(campo_min, busca_min) != NULL) {
            exibir_acao(v[i]);
            achou++;
        }
    }

    if (achou == 0) {
        printf("Nenhum registro encontrado.\n");
    } else {
        printf("\nTotal de registros encontrados: %d\n", achou);
    }
}

// 4. Atualizar Situacao
void atualizar(Acao v[], int total) {
    int cod = 0;
    int pos = -1;
    int op = 0;

    if (total == 0) {
        printf("Nenhuma acao cadastrada.\n");
        return;
    }

    cod = ler_inteiro("Digite o codigo da acao que deseja atualizar: ", 1);
    pos = buscar_indice(v, total, cod);

    if (pos == -1) {
        printf("Erro: Acao nao encontrada.\n");
        return;
    }

    printf("Situacao atual: %s\n", v[pos].situacao);
    printf("Nova situacao:\n");
    printf("1 - Planejada\n");
    printf("2 - Realizada\n");
    printf("3 - Cancelada\n");
    op = ler_inteiro("Escolha uma opcao: ", 1);

    if (op == 1) {
        strcpy(v[pos].situacao, "planejada");
        v[pos].qtd_efetiva = 0;
    } else if (op == 2) {
        strcpy(v[pos].situacao, "realizada");
        v[pos].qtd_efetiva = ler_inteiro("Digite a quantidade efetiva de participantes: ", 0);
    } else if (op == 3) {
        strcpy(v[pos].situacao, "cancelada");
        v[pos].qtd_efetiva = 0;
    } else {
        printf("Opcao invalida!\n");
        return;
    }
    printf("Situacao atualizada com sucesso!\n");
}

// 5. Registrar Participantes Efetivos
void registrar_participantes(Acao v[], int total) {
    int cod = 0;
    int pos = -1;

    if (total == 0) {
        printf("Nenhuma acao cadastrada.\n");
        return;
    }

    cod = ler_inteiro("Digite o codigo da acao: ", 1);
    pos = buscar_indice(v, total, cod);

    if (pos == -1) {
        printf("Erro: Acao nao encontrada.\n");
        return;
    }

    if (strcmp(v[pos].situacao, "realizada") != 0) {
        printf("Erro: so e possivel registrar participantes de acoes realizadas.\n");
        printf("Atualize a situacao da acao para 'realizada' (opcao 4).\n");
        return;
    }

    v[pos].qtd_efetiva = ler_inteiro("Digite a quantidade efetiva de participantes: ", 0);
    printf("Participantes registrados com sucesso!\n");
}

// 6. Gerar Resumo Geral
void resumo(Acao v[], int total) {
    int planejadas = 0;
    int realizadas = 0;
    int canceladas = 0;
    int total_part = 0;
    int total_prev = 0;
    int i = 0;
    float perc = 0.0;

    if (total == 0) {
        printf("Nenhuma acao cadastrada.\n");
        return;
    }

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
    printf("Total de Acoes Cadastradas: %d\n", total);
    printf("Acoes Planejadas: %d\n", planejadas);
    printf("Acoes Realizadas: %d\n", realizadas);
    printf("Acoes Canceladas: %d\n", canceladas);
    printf("Total de Participantes Efetivos: %d\n", total_part);
    printf("Percentual de Participacao: %.2f%%\n", perc);
}

// Le um numero inteiro, repete ate o usuario digitar algo valido
int ler_inteiro(const char *msg, int minimo) {
    char buffer[50];
    char *fim = NULL;
    long valor = 0;

    while (1) {
        printf("%s", msg);
        if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
            printf("\nEntrada encerrada.\n");
            exit(0);
        }
        limpar_buffer_se_preciso(buffer);

        valor = strtol(buffer, &fim, 10);
        if (fim == buffer) {
            printf("Erro: digite um numero valido!\n");
            continue;
        }
        while (*fim == ' ' || *fim == '\n' || *fim == '\r') {
            fim++;
        }
        if (*fim != '\0') {
            printf("Erro: digite apenas numeros!\n");
            continue;
        }
        if (valor < minimo) {
            printf("Erro: o valor nao pode ser menor que %d!\n", minimo);
            continue;
        }
        if (valor > 1000000) {
            printf("Erro: valor muito grande!\n");
            continue;
        }
        return (int)valor;
    }
}

// Confere se a data esta no formato DD/MM/AAAA
int data_valida(const char *d) {
    int i = 0;
    if (strlen(d) != 10) {
        return 0;
    }
    for (i = 0; i < 10; i++) {
        if (i == 2 || i == 5) {
            if (d[i] != '/') {
                return 0;
            }
        } else if (!isdigit((unsigned char)d[i])) {
            return 0;
        }
    }
    return 1;
}

void ler_data(char destino[]) {
    while (1) {
        ler_texto("Data prevista (DD/MM/AAAA): ", destino, 15);
        if (data_valida(destino)) {
            return;
        }
        printf("Erro: use o formato DD/MM/AAAA (ex: 15/10/2026)!\n");
    }
}

// Retorna a posicao do codigo no vetor, ou -1 se nao existir
int buscar_indice(Acao v[], int total, int cod) {
    int i = 0;
    for (i = 0; i < total; i++) {
        if (v[i].codigo == cod) {
            return i;
        }
    }
    return -1;
}

void para_minusculo(const char *origem, char destino[], int tam) {
    int i = 0;
    for (i = 0; i < tam - 1 && origem[i] != '\0'; i++) {
        destino[i] = (char)tolower((unsigned char)origem[i]);
    }
    destino[i] = '\0';
}

void exibir_acao(Acao a) {
    printf("\n[Acao Encontrada]\n");
    printf("Codigo: %d\n", a.codigo);
    printf("Escola: %s\n", a.escola);
    printf("Tema: %s\n", a.tema);
    printf("Nome: %s\n", a.nome);
    printf("Data: %s\n", a.data);
    printf("Responsavel: %s\n", a.responsavel);
    printf("Qtd Prevista: %d\n", a.qtd_prevista);
    printf("Situacao: %s\n", a.situacao);
    printf("Qtd Efetiva: %d\n", a.qtd_efetiva);
}

// ---------- FUNCOES DO MENU ----------

// 1. Cadastrar Acao
void cadastrar(Acao v[], int *total) {
    int cod = 0;

    if (*total >= MAX) {
        printf("Limite de armazenamento atingido!\n");
        return;
    }

    cod = ler_inteiro("Codigo da acao: ", 1);

    // Validacao de codigo duplicado
    if (buscar_indice(v, *total, cod) != -1) {
        printf("Erro: Codigo ja cadastrado!\n");
        return;
    }

    v[*total].codigo = cod;
    ler_texto("Escola: ", v[*total].escola, TAM);
    ler_texto("Tema: ", v[*total].tema, TAM);
    ler_texto("Nome da acao: ", v[*total].nome, TAM);
    ler_data(v[*total].data);
    ler_texto("Responsavel: ", v[*total].responsavel, TAM);
    v[*total].qtd_prevista = ler_inteiro("Quantidade prevista de participantes: ", 0);

    strcpy(v[*total].situacao, "planejada");
    v[*total].qtd_efetiva = 0;

    (*total)++;
    printf("Acao cadastrada com sucesso!\n");
}

// 2. Listar Acoes
void listar(Acao v[], int total) {
    int i = 0;

    if (total == 0) {
        printf("Nenhuma acao cadastrada.\n");
        return;
    }

    printf("\n--- LISTA DE ACOES ---\n");
    for (i = 0; i < total; i++) {
        printf("Codigo: %d | Escola: %s | Tema: %s | Acao: %s | Data: %s | Situacao: %s\n",
               v[i].codigo, v[i].escola, v[i].tema, v[i].nome, v[i].data, v[i].situacao);
    }
}

// 3. Pesquisar (por codigo, escola ou tema)
void pesquisar(Acao v[], int total) {
    int tipo = 0;
    int cod = 0;
    int pos = -1;

    if (total == 0) {
        printf("Nenhuma acao cadastrada.\n");
        return;
    }

    printf("\nPesquisar por:\n");
    printf("1 - Codigo\n");
    printf("2 - Escola\n");
    printf("3 - Tema\n");
    tipo = ler_inteiro("Escolha uma opcao: ", 1);

    if (tipo == 1) {
        cod = ler_inteiro("Digite o codigo para buscar: ", 1);
        pos = buscar_indice(v, total, cod);
        if (pos == -1) {
            printf("Nenhum registro encontrado com este codigo.\n");
        } else {
            exibir_acao(v[pos]);
        }
    } else if (tipo == 2) {
        pesquisar_por_texto(v, total, 1);
    } else if (tipo == 3) {
        pesquisar_por_texto(v, total, 2);
    } else {
        printf("Opcao invalida!\n");
    }
}

// campo: 1 = escola, 2 = tema (busca sem diferenciar maiuscula/minuscula)
void pesquisar_por_texto(Acao v[], int total, int campo) {
    char busca[TAM];
    char busca_min[TAM];
    char campo_min[TAM];
    int achou = 0;
    int i = 0;

    if (campo == 1) {
        ler_texto("Digite a escola (ou parte do nome): ", busca, TAM);
    } else {
        ler_texto("Digite o tema (ou parte do nome): ", busca, TAM);
    }
    para_minusculo(busca, busca_min, TAM);

    for (i = 0; i < total; i++) {
        if (campo == 1) {
            para_minusculo(v[i].escola, campo_min, TAM);
        } else {
            para_minusculo(v[i].tema, campo_min, TAM);
        }

        if (strstr(campo_min, busca_min) != NULL) {
            exibir_acao(v[i]);
            achou++;
        }
    }

    if (achou == 0) {
        printf("Nenhum registro encontrado.\n");
    } else {
        printf("\nTotal de registros encontrados: %d\n", achou);
    }
}

// 4. Atualizar Situacao
void atualizar(Acao v[], int total) {
    int cod = 0;
    int pos = -1;
    int op = 0;

    if (total == 0) {
        printf("Nenhuma acao cadastrada.\n");
        return;
    }

    cod = ler_inteiro("Digite o codigo da acao que deseja atualizar: ", 1);
    pos = buscar_indice(v, total, cod);

    if (pos == -1) {
        printf("Erro: Acao nao encontrada.\n");
        return;
    }

    printf("Situacao atual: %s\n", v[pos].situacao);
    printf("Nova situacao:\n");
    printf("1 - Planejada\n");
    printf("2 - Realizada\n");
    printf("3 - Cancelada\n");
    op = ler_inteiro("Escolha uma opcao: ", 1);

    if (op == 1) {
        strcpy(v[pos].situacao, "planejada");
        v[pos].qtd_efetiva = 0;
    } else if (op == 2) {
        strcpy(v[pos].situacao, "realizada");
        v[pos].qtd_efetiva = ler_inteiro("Digite a quantidade efetiva de participantes: ", 0);
    } else if (op == 3) {
        strcpy(v[pos].situacao, "cancelada");
        v[pos].qtd_efetiva = 0;
    } else {
        printf("Opcao invalida!\n");
        return;
    }
    printf("Situacao atualizada com sucesso!\n");
}

// 5. Registrar Participantes Efetivos
void registrar_participantes(Acao v[], int total) {
    int cod = 0;
    int pos = -1;

    if (total == 0) {
        printf("Nenhuma acao cadastrada.\n");
        return;
    }

    cod = ler_inteiro("Digite o codigo da acao: ", 1);
    pos = buscar_indice(v, total, cod);

    if (pos == -1) {
        printf("Erro: Acao nao encontrada.\n");
        return;
    }

    if (strcmp(v[pos].situacao, "realizada") != 0) {
        printf("Erro: so e possivel registrar participantes de acoes realizadas.\n");
        printf("Atualize a situacao da acao para 'realizada' (opcao 4).\n");
        return;
    }

    v[pos].qtd_efetiva = ler_inteiro("Digite a quantidade efetiva de participantes: ", 0);
    printf("Participantes registrados com sucesso!\n");
}

// 6. Gerar Resumo Geral
void resumo(Acao v[], int total) {
    int planejadas = 0;
    int realizadas = 0;
    int canceladas = 0;
    int total_part = 0;
    int total_prev = 0;
    int i = 0;
    float perc = 0.0;

    if (total == 0) {
        printf("Nenhuma acao cadastrada.\n");
        return;
    }

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
    printf("Total de Acoes Cadastradas: %d\n", total);
    printf("Acoes Planejadas: %d\n", planejadas);
    printf("Acoes Realizadas: %d\n", realizadas);
    printf("Acoes Canceladas: %d\n", canceladas);
    printf("Total de Participantes Efetivos: %d\n", total_part);
    printf("Percentual de Participacao: %.2f%%\n", perc);
}
