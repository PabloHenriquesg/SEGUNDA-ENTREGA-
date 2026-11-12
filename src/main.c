/*
 * PSE em Acao - Sistema de Planejamento e Acompanhamento de Acoes de Saude na Escola
 * AEP 2026.2 - ADS / Engenharia de Software - UniCesumar
 *
 * Aplicacao introdutoria em C, executada em terminal.
 * Os registros sao mantidos em memoria durante a execucao.
 * Nao armazena dados pessoais ou clinicos de estudantes.
 */

#include <ctype.h>
#include <errno.h>
#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ACOES 100
#define TAM_ESCOLA 80
#define TAM_TEMA 80
#define TAM_DATA 12
#define TAM_PUBLICO 100
#define TAM_RESPONSAVEL 80
#define TAM_ENTRADA 256

typedef enum {
    PLANEJADA = 1,
    REALIZADA = 2,
    CANCELADA = 3
} Situacao;

typedef struct {
    int codigo;
    char escola[TAM_ESCOLA];
    char tema[TAM_TEMA];
    char dataPrevista[TAM_DATA];
    char publicoAlvo[TAM_PUBLICO];
    char responsavel[TAM_RESPONSAVEL];
    int quantidadePrevista;
    Situacao situacao;
    int quantidadeEfetiva;
} Acao;

static Acao acoes[MAX_ACOES];
static int totalAcoes = 0;

/* Le uma linha completa, remove o ENTER e espacos nas extremidades. */
static int lerLinha(const char *mensagem, char *destino, size_t tamanho) {
    size_t inicio = 0;
    size_t fim;
    int caractere;

    printf("%s", mensagem);
    if (fgets(destino, (int)tamanho, stdin) == NULL) {
        return 0;
    }

    fim = strlen(destino);
    if (fim > 0 && destino[fim - 1] == '\n') {
        destino[--fim] = '\0';
    } else if (!feof(stdin)) {
        while ((caractere = getchar()) != '\n' && caractere != EOF) {
            /* Descarta o restante de uma entrada maior que o campo. */
        }
        printf("Entrada muito longa. Tente novamente.\n");
        return 0;
    }

    while (destino[inicio] != '\0' && isspace((unsigned char)destino[inicio])) {
        inicio++;
    }
    if (inicio > 0) {
        memmove(destino, destino + inicio, strlen(destino + inicio) + 1);
    }

    fim = strlen(destino);
    while (fim > 0 && isspace((unsigned char)destino[fim - 1])) {
        destino[--fim] = '\0';
    }

    return 1;
}

static int lerCampoObrigatorio(const char *mensagem, char *destino, size_t tamanho) {
    for (;;) {
        if (!lerLinha(mensagem, destino, tamanho)) {
            if (feof(stdin)) return 0;
            continue;
        }
        if (destino[0] == '\0') {
            printf("Este campo e obrigatorio. Informe um valor.\n");
            continue;
        }
        return 1;
    }
}

static int lerInteiro(const char *mensagem, int minimo, int maximo, int *valor) {
    char entrada[TAM_ENTRADA];
    char *fim;
    long numero;

    for (;;) {
        if (!lerLinha(mensagem, entrada, sizeof(entrada))) {
            if (feof(stdin)) return 0;
            continue;
        }

        errno = 0;
        numero = strtol(entrada, &fim, 10);
        while (*fim != '\0' && isspace((unsigned char)*fim)) fim++;

        if (entrada[0] == '\0' || fim == entrada || *fim != '\0' ||
            errno == ERANGE || numero < minimo || numero > maximo) {
            printf("Valor invalido. Informe um numero entre %d e %d.\n", minimo, maximo);
            continue;
        }

        *valor = (int)numero;
        return 1;
    }
}

static int anoBissexto(int ano) {
    return (ano % 400 == 0) || ((ano % 4 == 0) && (ano % 100 != 0));
}

static int validarData(const char *data) {
    int dia, mes, ano;
    int diasNoMes[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    if (strlen(data) != 10 || data[2] != '/' || data[5] != '/') return 0;
    if (!isdigit((unsigned char)data[0]) || !isdigit((unsigned char)data[1]) ||
        !isdigit((unsigned char)data[3]) || !isdigit((unsigned char)data[4]) ||
        !isdigit((unsigned char)data[6]) || !isdigit((unsigned char)data[7]) ||
        !isdigit((unsigned char)data[8]) || !isdigit((unsigned char)data[9])) return 0;

    dia = (data[0] - '0') * 10 + (data[1] - '0');
    mes = (data[3] - '0') * 10 + (data[4] - '0');
    ano = (data[6] - '0') * 1000 + (data[7] - '0') * 100 +
          (data[8] - '0') * 10 + (data[9] - '0');

    if (ano < 2000 || mes < 1 || mes > 12) return 0;
    if (anoBissexto(ano)) diasNoMes[2] = 29;
    return dia >= 1 && dia <= diasNoMes[mes];
}

static int lerData(char *destino, size_t tamanho) {
    for (;;) {
        if (!lerLinha("Data prevista (DD/MM/AAAA): ", destino, tamanho)) {
            if (feof(stdin)) return 0;
            continue;
        }
        if (!validarData(destino)) {
            printf("Data invalida. Use uma data existente no formato DD/MM/AAAA.\n");
            continue;
        }
        return 1;
    }
}

static int indicePorCodigo(int codigo) {
    int i;
    for (i = 0; i < totalAcoes; i++) {
        if (acoes[i].codigo == codigo) return i;
    }
    return -1;
}

/* Pesquisa sem diferenciar letras maiusculas/minusculas ASCII. */
static int contemTexto(const char *texto, const char *termo) {
    char textoNormalizado[ TAM_PUBLICO + TAM_RESPONSAVEL + 4 ];
    char termoNormalizado[TAM_ENTRADA];
    size_t i;

    if (strlen(texto) >= sizeof(textoNormalizado) || strlen(termo) >= sizeof(termoNormalizado)) {
        return 0;
    }
    for (i = 0; texto[i] != '\0'; i++) {
        textoNormalizado[i] = (char)tolower((unsigned char)texto[i]);
    }
    textoNormalizado[i] = '\0';
    for (i = 0; termo[i] != '\0'; i++) {
        termoNormalizado[i] = (char)tolower((unsigned char)termo[i]);
    }
    termoNormalizado[i] = '\0';
    return strstr(textoNormalizado, termoNormalizado) != NULL;
}

static const char *nomeSituacao(Situacao situacao) {
    switch (situacao) {
        case PLANEJADA: return "Planejada";
        case REALIZADA: return "Realizada";
        case CANCELADA: return "Cancelada";
        default: return "Indefinida";
    }
}

static void exibirAcao(const Acao *acao) {
    printf("\n----------------------------------------\n");
    printf("Codigo: %d\n", acao->codigo);
    printf("Escola: %s\n", acao->escola);
    printf("Tema: %s\n", acao->tema);
    printf("Data prevista: %s\n", acao->dataPrevista);
    printf("Publico-alvo: %s\n", acao->publicoAlvo);
    printf("Responsavel: %s\n", acao->responsavel);
    printf("Quantidade prevista: %d\n", acao->quantidadePrevista);
    printf("Situacao: %s\n", nomeSituacao(acao->situacao));
    if (acao->situacao == REALIZADA) {
        printf("Participantes efetivos: %d\n", acao->quantidadeEfetiva);
    }
    printf("----------------------------------------\n");
}

static void cadastrarAcao(void) {
    Acao nova;

    printf("\n=== CADASTRO DE ACAO DO PSE ===\n");
    if (totalAcoes >= MAX_ACOES) {
        printf("Limite de armazenamento atingido (%d acoes).\n", MAX_ACOES);
        return;
    }

    if (!lerInteiro("Codigo (numero positivo): ", 1, 2147483647, &nova.codigo)) return;
    if (indicePorCodigo(nova.codigo) != -1) {
        printf("Ja existe uma acao cadastrada com esse codigo. Cadastro cancelado.\n");
        return;
    }
    if (!lerCampoObrigatorio("Escola: ", nova.escola, sizeof(nova.escola))) return;
    if (!lerCampoObrigatorio("Tema: ", nova.tema, sizeof(nova.tema))) return;
    if (!lerData(nova.dataPrevista, sizeof(nova.dataPrevista))) return;
    if (!lerCampoObrigatorio("Publico-alvo: ", nova.publicoAlvo, sizeof(nova.publicoAlvo))) return;
    if (!lerCampoObrigatorio("Responsavel: ", nova.responsavel, sizeof(nova.responsavel))) return;
    if (!lerInteiro("Quantidade prevista de participantes: ", 0, 1000000,
                    &nova.quantidadePrevista)) return;

    nova.situacao = PLANEJADA;
    nova.quantidadeEfetiva = 0;
    acoes[totalAcoes] = nova;
    totalAcoes++;

    printf("Acao cadastrada com sucesso! Situacao inicial: Planejada.\n");
}

static void listarAcoes(void) {
    int i;
    printf("\n=== ACOES CADASTRADAS ===\n");
    if (totalAcoes == 0) {
        printf("Nenhuma acao cadastrada.\n");
        return;
    }
    for (i = 0; i < totalAcoes; i++) exibirAcao(&acoes[i]);
    printf("Total de registros: %d\n", totalAcoes);
}

static void pesquisarAcoes(void) {
    int opcao, codigo, i, encontrados = 0;
    char termo[TAM_ENTRADA];

    if (totalAcoes == 0) {
        printf("Nenhuma acao cadastrada para pesquisa.\n");
        return;
    }

    printf("\n=== PESQUISAR ACOES ===\n");
    printf("1 - Por codigo\n2 - Por escola\n3 - Por tema\n");
    if (!lerInteiro("Escolha: ", 1, 3, &opcao)) return;

    if (opcao == 1) {
        if (!lerInteiro("Codigo: ", 1, 2147483647, &codigo)) return;
        i = indicePorCodigo(codigo);
        if (i >= 0) {
            exibirAcao(&acoes[i]);
            encontrados = 1;
        }
    } else {
        const char *campo = (opcao == 2) ? "Escola para pesquisar: " : "Tema para pesquisar: ";
        if (!lerCampoObrigatorio(campo, termo, sizeof(termo))) return;
        for (i = 0; i < totalAcoes; i++) {
            const char *valor = (opcao == 2) ? acoes[i].escola : acoes[i].tema;
            if (contemTexto(valor, termo)) {
                exibirAcao(&acoes[i]);
                encontrados++;
            }
        }
    }

    if (encontrados == 0) printf("Nenhuma acao encontrada com o criterio informado.\n");
    else printf("Pesquisa concluida: %d registro(s) encontrado(s).\n", encontrados);
}

static void atualizarSituacao(void) {
    int codigo, indice, opcao, quantidade;

    printf("\n=== ATUALIZAR SITUACAO ===\n");
    if (!lerInteiro("Codigo da acao: ", 1, 2147483647, &codigo)) return;
    indice = indicePorCodigo(codigo);
    if (indice == -1) {
        printf("Acao nao encontrada.\n");
        return;
    }

    printf("Situacao atual: %s\n", nomeSituacao(acoes[indice].situacao));
    printf("1 - Planejada\n2 - Realizada\n3 - Cancelada\n");
    if (!lerInteiro("Nova situacao: ", 1, 3, &opcao)) return;

    if (opcao == REALIZADA) {
        if (!lerInteiro("Quantidade efetiva de participantes: ", 0, 1000000, &quantidade)) return;
        acoes[indice].quantidadeEfetiva = quantidade;
    } else {
        acoes[indice].quantidadeEfetiva = 0;
    }
    acoes[indice].situacao = (Situacao)opcao;
    printf("Situacao atualizada para %s.\n", nomeSituacao(acoes[indice].situacao));
}

static void registrarParticipacao(void) {
    int codigo, indice, quantidade;

    printf("\n=== REGISTRAR PARTICIPACAO EFETIVA ===\n");
    if (!lerInteiro("Codigo da acao: ", 1, 2147483647, &codigo)) return;
    indice = indicePorCodigo(codigo);
    if (indice == -1) {
        printf("Acao nao encontrada.\n");
        return;
    }
    if (acoes[indice].situacao != REALIZADA) {
        printf("A participacao efetiva so pode ser registrada para uma acao com situacao Realizada.\n");
        return;
    }
    if (!lerInteiro("Quantidade efetiva de participantes: ", 0, 1000000, &quantidade)) return;
    acoes[indice].quantidadeEfetiva = quantidade;
    printf("Participacao efetiva atualizada com sucesso.\n");
}

static void gerarResumo(void) {
    int i, planejadas = 0, realizadas = 0, canceladas = 0;
    long long previstos = 0, efetivos = 0;

    for (i = 0; i < totalAcoes; i++) {
        previstos += acoes[i].quantidadePrevista;
        switch (acoes[i].situacao) {
            case PLANEJADA: planejadas++; break;
            case REALIZADA:
                realizadas++;
                efetivos += acoes[i].quantidadeEfetiva;
                break;
            case CANCELADA: canceladas++; break;
            default: break;
        }
    }

    printf("\n========== RESUMO GERAL DO PSE EM ACAO ==========\n");
    printf("Total de acoes cadastradas: %d\n", totalAcoes);
    printf("Acoes planejadas: %d\n", planejadas);
    printf("Acoes realizadas: %d\n", realizadas);
    printf("Acoes canceladas: %d\n", canceladas);
    printf("Total de participantes previstos: %lld\n", previstos);
    printf("Total de participantes efetivos (acoes realizadas): %lld\n", efetivos);
    printf("================================================\n");
}

static void exibirMenu(void) {
    printf("\n===============================================\n");
    printf("                 PSE EM ACAO\n");
    printf(" Sistema de Planejamento e Acompanhamento\n");
    printf("===============================================\n");
    printf("1 - Cadastrar acao\n");
    printf("2 - Listar acoes\n");
    printf("3 - Pesquisar acoes\n");
    printf("4 - Atualizar situacao da acao\n");
    printf("5 - Registrar participacao efetiva\n");
    printf("6 - Gerar resumo geral\n");
    printf("0 - Encerrar sistema\n");
}

int main(void) {
    int opcao;
    setlocale(LC_ALL, "");

    printf("PSE em Acao - AEP 2026.2\n");
    printf("Os dados utilizados devem ser ficticios e coletivos.\n");

    do {
        exibirMenu();
        if (!lerInteiro("Escolha uma opcao: ", 0, 6, &opcao)) break;

        switch (opcao) {
            case 1: cadastrarAcao(); break;
            case 2: listarAcoes(); break;
            case 3: pesquisarAcoes(); break;
            case 4: atualizarSituacao(); break;
            case 5: registrarParticipacao(); break;
            case 6: gerarResumo(); break;
            case 0: printf("Sistema encerrado. Obrigado por utilizar o PSE em Acao!\n"); break;
            default: printf("Opcao invalida.\n"); break;
        }
    } while (opcao != 0);

    return 0;
}