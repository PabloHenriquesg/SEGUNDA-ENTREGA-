# Manual do usuario - PSE em Acao

## 1. Objetivo

O PSE em Acao organiza informacoes coletivas sobre as acoes do Programa Saude na Escola, permitindo cadastrar, consultar e acompanhar atividades planejadas, realizadas ou canceladas.

## 2. Cuidados com os dados

Utilize somente dados ficticios e coletivos para demonstracao. Nao cadastre nomes de estudantes, diagnosticos, prontuarios, condicoes clinicas individuais ou outros dados pessoais sensiveis. O sistema nao realiza diagnostico, triagem, prescricao ou recomendacao de tratamento.

## 3. Compilacao

Na pasta do projeto, compile o arquivo `src/main.c`:

**Windows com GCC/MinGW:**

```bash
gcc -std=c99 -Wall -Wextra -Wpedantic -O2 src/main.c -o pse_em_acao.exe
```

**Linux:**

```bash
gcc -std=c99 -Wall -Wextra -Wpedantic -O2 src/main.c -o pse_em_acao
```

## 4. Execucao

No Windows, execute `pse_em_acao.exe`. No Linux, execute `./pse_em_acao`. O programa apresenta o menu principal e aguarda a escolha de uma opcao.

## 5. Opcoes do menu

| Opcao | Operacao | Descricao |
|---|---|---|
| 1 | Cadastrar acao | Registra uma nova acao coletiva do PSE. |
| 2 | Listar acoes | Exibe todos os registros da execucao atual. |
| 3 | Pesquisar acoes | Pesquisa por codigo, escola ou tema. |
| 4 | Atualizar situacao | Altera a situacao para planejada, realizada ou cancelada. |
| 5 | Registrar participacao efetiva | Informa a quantidade efetiva de participantes de uma acao realizada. |
| 6 | Gerar resumo geral | Apresenta totais de acoes e participacao prevista/efetiva. |
| 0 | Encerrar | Finaliza o programa. |

## 6. Cadastrar uma acao

Escolha `1` e informe codigo, escola, tema, data prevista, publico-alvo, responsavel e quantidade prevista. O codigo deve ser positivo e nao pode estar cadastrado. A data deve existir e seguir o formato `DD/MM/AAAA`. A quantidade prevista deve ser igual ou superior a zero. O sistema inicia a nova acao com situacao **Planejada**.

Exemplo ficticio:

- Codigo: `101`
- Escola: `Escola Municipal Exemplo`
- Tema: `Alimentacao saudavel`
- Data: `15/11/2026`
- Publico-alvo: `Estudantes do ensino fundamental` (descricao coletiva)
- Responsavel: `Equipe de Saude`
- Quantidade prevista: `30`

## 7. Listar e pesquisar

Escolha `2` para visualizar todas as acoes. Para pesquisar, escolha `3` e selecione o criterio: codigo, escola ou tema. A pesquisa por escola e tema aceita parte do texto e nao diferencia letras maiusculas/minusculas ASCII.

## 8. Atualizar situacao

Escolha `4`, informe o codigo e selecione: `1 - Planejada`, `2 - Realizada` ou `3 - Cancelada`. Ao selecionar **Realizada**, o sistema solicita a quantidade efetiva de participantes. Ao retornar uma acao para Planejada ou Cancelada, a quantidade efetiva volta a zero.

## 9. Registrar participacao efetiva

Escolha `5`, informe o codigo de uma acao com situacao **Realizada** e digite a quantidade efetiva. O sistema impede o registro enquanto a acao estiver planejada ou cancelada. A operacao pode ser utilizada para corrigir/atualizar a quantidade registrada.

## 10. Gerar resumo geral

Escolha `6`. O resumo apresenta total de acoes cadastradas, quantidade de acoes planejadas, realizadas e canceladas, soma das participacoes previstas e soma das participacoes efetivas das acoes realizadas.

## 11. Limites e encerramento

A aplicacao aceita ate 100 acoes por execucao. Quando o limite e atingido, novos cadastros sao bloqueados e uma mensagem informa a situacao. Os dados ficam somente na memoria do programa e sao perdidos ao encerrar. Para manter informacoes entre execucoes seria necessaria uma etapa futura de persistencia em arquivo ou banco de dados.