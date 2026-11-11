# PSE em Ação — Saúde Mental

Sistema em linguagem C, executado no terminal, para registrar e acompanhar ações de saúde mental e atenção psicossocial nas escolas, no contexto do **Programa Saúde na Escola (PSE)**.

Projeto desenvolvido para a **AEP (Atividade de Estudo Programada) — 2º Semestre de 2026**, UNICESUMAR.

## Integrantes

| Nome | RA |
|------|----|
| Brenda Correa | 26010283-2 |
| Luna Halabi | 26009440-2 |
| Penélope Faryniuk de Sousa | 26004706-2 |

## Objetivo do sistema

Apoiar e organizar as ações de saúde mental realizadas nas escolas, facilitando o trabalho da equipe pedagógica e de saúde. O sistema permite cadastrar ações, acompanhar sua situação (planejada, realizada ou cancelada), registrar o número de participantes efetivos e gerar um resumo geral com o percentual de participação.

## Funcionalidades

1. **Cadastrar ação:** código, escola, tema, nome da ação, data prevista, responsável e quantidade prevista de participantes (toda ação nasce como "planejada").
2. **Listar ações:** exibe todas as ações cadastradas.
3. **Pesquisar ação:** busca por código, escola ou tema.
4. **Atualizar situação:** altera a ação para planejada, realizada ou cancelada.
5. **Registrar participantes efetivos:** informa quantas pessoas participaram de uma ação realizada.
6. **Gerar resumo:** total de ações por situação, total de participantes efetivos e percentual de participação.

### Validações

- Bloqueio de códigos duplicados
- Campos obrigatórios não podem ficar vazios
- Quantidades negativas não são aceitas
- Entradas inválidas (letras no lugar de números) são tratadas sem travar o programa
- Data no formato DD/MM/AAAA
- Limite de armazenamento de 100 ações

## Estrutura do repositório

```
.
├── README.md
└── src/
    └── pse_em_acao.c
```

## Como compilar e executar

É necessário ter um compilador C instalado (por exemplo, GCC).

**1. Clone o repositório**

```bash
git clone https://github.com/brendabyy/pse_em_acaoo.c.git
cd pse_em_acaoo.c
```

**2. Compile**

```bash
gcc src/pse_em_acao.c -o pse_em_acao
```

**3. Execute**

- Linux / macOS:
  ```bash
  ./pse_em_acao
  ```
- Windows (Prompt de Comando ou PowerShell):
  ```bash
  pse_em_acao.exe
  ```

> Também é possível abrir o arquivo `src/pse_em_acao.c` em uma IDE como Code::Blocks ou Dev-C++, compilar e executar por ela.

## Exemplo de uso

```
=== PSE EM ACAO (SAUDE MENTAL) ===
1. Cadastrar acao
2. Listar acoes
3. Pesquisar acao
4. Atualizar situacao
5. Registrar participantes efetivos
6. Gerar resumo
0. Sair
Escolha uma opcao: 1
Codigo da acao: 1
Escola: Escola Maria
Tema: Saude Mental
Nome da acao: Roda de conversa
Data prevista (DD/MM/AAAA): 15/10/2026
Responsavel: Ana
Quantidade prevista de participantes: 40
Acao cadastrada com sucesso!
```

## Links

- Repositório: https://github.com/brendabyy/pse_em_acaoo.c
