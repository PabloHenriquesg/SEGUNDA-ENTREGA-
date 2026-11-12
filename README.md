# PSE em Ação — Segunda entrega da AEP 2026.2

**Sistema de Planejamento e Acompanhamento de Ações de Saúde na Escola**  
UniCesumar — AEP 2026.2

## Sobre o projeto

Esta é a segunda etapa do projeto PSE em Ação, dando continuidade à proposta desenvolvida na primeira entrega. O planejamento foi transformado em uma aplicação funcional de terminal, desenvolvida em linguagem C, com documentação de uso e especificação dos casos de uso.

## Funcionalidades

1. Cadastrar ações do Programa Saúde na Escola.
2. Listar ações cadastradas.
3. Pesquisar por código, escola ou tema.
4. Atualizar a situação para Planejada, Realizada ou Cancelada.
5. Registrar a quantidade efetiva de participantes de uma ação realizada.
6. Gerar resumo geral das ações e da participação.

## Validações e regras

- Código positivo e único.
- Campos obrigatórios.
- Data válida no formato `DD/MM/AAAA`.
- Quantidades não negativas.
- Limite de 100 ações por execução.
- Participação efetiva somente para ações com situação **Realizada**.
- Utilizar apenas dados fictícios e coletivos; não cadastrar dados pessoais ou clínicos de estudantes.
- Os dados são mantidos em memória e se perdem ao encerrar o programa.

## Compilação e execução

É necessário ter GCC instalado.

**Windows (MinGW/GCC), no PowerShell:**

```bash
gcc -std=c99 -Wall -Wextra -Wpedantic -O2 src/main.c -o pse_em_acao.exe
.\pse_em_acao.exe
```

**Linux:**

```bash
gcc -std=c99 -Wall -Wextra -Wpedantic -O2 src/main.c -o pse_em_acao
./pse_em_acao
```

## Estrutura do repositório

```text
SEGUNDA-ENTREGA-/
├── README.md
├── src/
│   └── main.c
└── docs/
    ├── manual_usuario.md
    └── casos_de_uso.md
```

## Documentação

- [Manual do usuário](docs/manual_usuario.md): instruções de compilação, execução e utilização.
- [Casos de uso](docs/casos_de_uso.md): ator principal, pré-condições, fluxos principais, alternativos e pós-condições.

## Integrantes

- Pablo Henrique Sousa Gouveia
- João Pedro Lima Pereira
- João Pedro de Almeida Campos
