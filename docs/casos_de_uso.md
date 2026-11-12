# Casos de uso - PSE em Acao

## Ator principal

**Equipe responsavel pelo planejamento e acompanhamento das acoes do PSE.** E o usuario considerado na primeira entrega e responsavel por cadastrar, consultar e atualizar informacoes coletivas das atividades.

## UC01 - Cadastrar acao

- **Objetivo:** registrar uma nova acao coletiva do Programa Saude na Escola.
- **Ator:** equipe responsavel pelo planejamento e acompanhamento das acoes do PSE.
- **Pre-condicoes:** sistema em execucao; usuario no menu principal; capacidade de armazenamento disponivel.
- **Fluxo principal:** (1) usuario seleciona Cadastrar acao; (2) informa codigo; (3) sistema verifica se o codigo e unico; (4) usuario informa escola, tema, data prevista, publico-alvo, responsavel e quantidade prevista; (5) sistema valida campos, data e quantidade; (6) sistema registra a acao com situacao Planejada e quantidade efetiva igual a zero; (7) sistema confirma o cadastro.
- **Fluxos alternativos:** codigo ja cadastrado: sistema informa duplicidade e cancela o cadastro; campo obrigatorio vazio: sistema solicita novo valor; data inexistente ou formato incorreto: sistema solicita nova data; quantidade negativa ou invalida: sistema solicita novo valor; limite de 100 registros atingido: sistema bloqueia novo cadastro.
- **Pos-condicoes:** nova acao armazenada em memoria com situacao Planejada, ou cadastro nao realizado em caso de validacao/limite.

## UC02 - Listar acoes

- **Objetivo:** visualizar os registros existentes na execucao atual.
- **Ator:** equipe responsavel pelo planejamento e acompanhamento das acoes do PSE.
- **Pre-condicoes:** sistema em execucao.
- **Fluxo principal:** (1) usuario seleciona Listar acoes; (2) sistema verifica se ha registros; (3) sistema apresenta os dados de cada acao e o total de registros.
- **Fluxos alternativos:** se nao houver registros, o sistema informa que nenhuma acao foi cadastrada.
- **Pos-condicoes:** registros exibidos; nenhum dado e alterado.

## UC03 - Pesquisar acoes

- **Objetivo:** localizar acoes por codigo, escola ou tema.
- **Ator:** equipe responsavel pelo planejamento e acompanhamento das acoes do PSE.
- **Pre-condicoes:** existir ao menos uma acao cadastrada.
- **Fluxo principal:** (1) usuario seleciona Pesquisar acoes; (2) escolhe o criterio; (3) informa codigo ou termo de pesquisa; (4) sistema localiza e apresenta os registros correspondentes; (5) sistema informa a quantidade encontrada.
- **Fluxos alternativos:** criterio invalido: sistema solicita uma opcao entre as disponiveis; codigo/termo sem correspondencia: sistema informa que nenhum registro foi encontrado; base vazia: sistema informa que nao ha acoes para pesquisar.
- **Pos-condicoes:** resultados apresentados; nenhum registro e alterado.

## UC04 - Atualizar situacao

- **Objetivo:** alterar o estado de acompanhamento de uma acao.
- **Ator:** equipe responsavel pelo planejamento e acompanhamento das acoes do PSE.
- **Pre-condicoes:** acao cadastrada e identificavel pelo codigo.
- **Fluxo principal:** (1) usuario seleciona Atualizar situacao; (2) informa codigo; (3) sistema localiza a acao; (4) usuario escolhe Planejada, Realizada ou Cancelada; (5) se Realizada, informa a quantidade efetiva; (6) sistema atualiza os dados e confirma a operacao.
- **Fluxos alternativos:** codigo inexistente: sistema informa que a acao nao foi encontrada; opcao invalida: sistema solicita nova escolha; quantidade invalida: sistema solicita novo valor.
- **Pos-condicoes:** situacao atualizada; ao definir Planejada ou Cancelada, a quantidade efetiva e zerada.

## UC05 - Registrar participacao efetiva

- **Objetivo:** registrar ou corrigir a quantidade efetiva de participantes de uma acao realizada.
- **Ator:** equipe responsavel pelo planejamento e acompanhamento das acoes do PSE.
- **Pre-condicoes:** acao cadastrada e com situacao Realizada.
- **Fluxo principal:** (1) usuario seleciona Registrar participacao efetiva; (2) informa codigo; (3) sistema verifica existencia e situacao; (4) usuario informa quantidade efetiva nao negativa; (5) sistema atualiza a quantidade e confirma.
- **Fluxos alternativos:** codigo inexistente: sistema informa que a acao nao foi encontrada; acao ainda Planejada ou Cancelada: sistema bloqueia o registro; quantidade invalida: sistema solicita novo valor.
- **Pos-condicoes:** quantidade efetiva registrada/atualizada para a acao realizada.

## UC06 - Gerar resumo geral

- **Objetivo:** consolidar a quantidade de acoes e os totais de participacao.
- **Ator:** equipe responsavel pelo planejamento e acompanhamento das acoes do PSE.
- **Pre-condicoes:** sistema em execucao; pode haver zero ou mais acoes cadastradas.
- **Fluxo principal:** (1) usuario seleciona Gerar resumo geral; (2) sistema percorre os registros; (3) contabiliza acoes planejadas, realizadas e canceladas; (4) soma participantes previstos e participantes efetivos das acoes realizadas; (5) apresenta o resumo.
- **Fluxos alternativos:** se nao houver registros, o sistema apresenta totais iguais a zero.
- **Pos-condicoes:** resumo exibido; nenhum dado e alterado.