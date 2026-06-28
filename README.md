# Otimização — Branch and Bound: Leilão Virtual

Este repositório contém a modelagem e implementação em C++ do problema **Leilão Virtual** utilizando a técnica de **Branch and Bound**. O projeto faz parte da disciplina de Otimização do Departamento de Informática da Universidade Federal do Paraná (DINF/UFPR).

---

## 📌 Sumário
1. [Sobre o Problema](#-sobre-o-problema)
2. [Estrutura do Repositório](#-estrutura-do-repositório)
3. [Como Compilar e Executar](#-como-compilar-e-executar)
4. [Parâmetros de Execução](#-parâmetros-de-execução)
5. [Funções Limitantes (Bounds)](#-funções-limitantes-bounds)
6. [⚠️ Status do Desenvolvimento e Compilação](#%EF%B8%8F-status-do-desenvolvimento-e-compilação)
7. [📋 Enunciado Original do Trabalho](#-enunciado-original-do-trabalho)

---

## 💼 Sobre o Problema
O **Leilão Virtual** consiste em maximizar a receita obtida na venda de produtos sob restrições sociais de equidade:
*   Existem $p$ produtos únicos à venda e $c$ clientes interessados.
*   Cada cliente faz uma oferta para cada produto.
*   Cada cliente pode adquirir **no máximo um** produto.
*   O objetivo é maximizar o valor arrecadado total.

### Exemplo de Entrada e Saída
**Entrada (`stdin`):**
```text
2 3
10 1 2
20 2 1
```
*(2 produtos, 3 clientes. As linhas seguintes representam a matriz de ofertas dos clientes pelos produtos).*

**Saída (`stdout`):**
```text
1 3
2 1
22
```
*(O produto 1 é vendido ao cliente 3 por $2; o produto 2 ao cliente 1 por $20. Total arrecadado: 22).*

---

## 📁 Estrutura do Repositório
*   **[main.cpp](file:///home/morpho/Otimizacao-Branch-and-Bound/main.cpp)**: Código-fonte principal com o algoritmo de ramificação e poda (Branch and Bound).
*   **[teste.cpp](file:///home/morpho/Otimizacao-Branch-and-Bound/teste.cpp)**: Código auxiliar para testar o parser de argumentos de linha de comando.
*   **[Makefile](file:///home/morpho/Otimizacao-Branch-and-Bound/Makefile)**: Script para automação do build (compilação).
*   **[entradas/](file:///home/morpho/Otimizacao-Branch-and-Bound/entradas)**: Diretório contendo instâncias de teste de diferentes tamanhos (pequenas, médias e grandes).

---

## ⚙️ Como Compilar e Executar

### Pré-requisitos
*   Compilador `g++` com suporte a **C++17** ou superior.
*   Ferramenta `make` instalada.

### Compilação
Use o [Makefile](file:///home/morpho/Otimizacao-Branch-and-Bound/Makefile) disponível na raiz do projeto:

```bash
# Compila o projeto e gera o executável 'abey'
make

# Remove os arquivos de objetos temporários (.o)
make clean

# Remove os arquivos de objetos e o executável 'abey'
make purge
```

### Execução
O programa lê os dados diretamente da entrada padrão (`stdin`) e escreve o resultado na saída padrão (`stdout`):

```bash
./abey < entradas/pequeno_2x2.txt
```

---

## 🎛️ Parâmetros de Execução
O executável permite ligar e desligar os cortes e selecionar as funções limitantes através de flags:

| Flag | Descrição |
| :---: | :--- |
| `-f` | Desativa os **cortes por viabilidade** (ativos por padrão). |
| `-o` | Desativa os **cortes por otimalidade** (ativos por padrão). |
| `-a` | Utiliza a **função limitante fornecida pelo professor** (Seção 3 do enunciado). |
| `-m` | Utiliza a função limitante alternativa. |

Se nenhuma opção for fornecida, o programa executa com todos os cortes ativos e a função limitante otimizada desenvolvida pelo grupo.

---

## 📉 Funções Limitantes (Bounds)
As funções limitantes são usadas para estimar o limite superior do valor que pode ser obtido a partir de uma solução parcial.

1.  **Função do Professor (`-a`):**
    $$B_{\text{professor}}(A, P, C) = \sum_{(i,j) \in A} o_{i,j} + |P| \cdot \max \{ o_{i,j} \mid i \in P, j \in C \}$$
    *Soma os valores dos arremates já definidos e adiciona a maior oferta restante multiplicada pelo número de produtos que ainda faltam vender.*

2.  **Função Otimizada (Padrão):**
    $$B_{\text{otimizada}}(A, P, C) = \sum_{(i,j) \in A} o_{i,j} + \sum_{i \in P} \max_{j \in C} \{ o_{i,j} \}$$
    *Soma as maiores ofertas possíveis para cada produto restante individualmente, relaxando apenas a restrição de que o mesmo cliente não pode arrematar mais de um produto.*

---

## ⚠️ Status do Desenvolvimento e Compilação
Atualmente, o arquivo **[main.cpp](file:///home/morpho/Otimizacao-Branch-and-Bound/main.cpp)** está em fase de desenvolvimento e apresenta vários erros sintáticos e estruturais que impedem a compilação com o `make`.

### Principais pontos de correção pendentes no código:
1.  **Erro de Sintaxe (Template de Vetor):**
    *   *Linha 56:* Falta o fechamento da tag do template `vector<pair<int, int>>`:
        ```cpp
        vector<pair<int, int> vetorProdutoClienteFinal; // Incorreto
        vector<pair<int, int>> vetorProdutoClienteFinal; // Correto
        ```
2.  **Inconsistência de Assinatura:**
    *   *Linha 7:* `branchAndBound` é declarada com 4 parâmetros:
        ```cpp
        void branchAndBound (vector<int> vetorProdutoClienteFinal, vector<int> ofertaClientes, int nClientes, int nProdutos);
        ```
    *   *Linha 63:* É definida com 5 parâmetros (e tipos diferentes de `vetorProdutoClienteFinal` e `ofertaClientes` em relação à chamada da linha 59).
3.  **Variáveis não Declaradas / Parâmetros Faltantes:**
    *   A variável `precoProdutos` é declarada localmente dentro da `main`, mas é referenciada em outras funções como `px` sem ter sido passada como parâmetro.
    *   Uso de variáveis não declaradas como `valorAtual`.
    *   Checagens condicionais `if (funcaoLimitanteNossa)` que tentam tratar funções como variáveis booleanas antes de sua definição ou sem a sintaxe apropriada.
4.  **Incompatibilidade de Tipos no `set`:**
    *   *Linha 99:* `clienteProdutoComprado.erase(cliente);` falha porque o conjunto armazena pares (`pair<int,int>`), mas a remoção é tentada passando um `int`.

---

## 📋 Enunciado Original do Trabalho

<details>
<summary>Clique para visualizar os requisitos completos do trabalho</summary>

### 1. Introdução

O trabalho consiste em modelar e implementar, utilizando Branch and Bound, o problema Leilão Virtual, descrito na Seção 2.

A resolução do problema — incluindo sua descrição, modelagem e implementação — deve ser apresentada em um texto claro no formato de artigo em PDF. Além disso, deve ser realizada uma análise utilizando duas funções limitantes (bounds) diferentes:

*   uma fornecida pelo professor (Seção 3);
*   outra escolhida pelos alunos, que deve apresentar desempenho superior à fornecida.

A função limitante desenvolvida pelos alunos deve ser a padrão da implementação. A função fornecida pelo professor deve ser selecionada por meio da opção de linha de comando `-a`.

O texto deve conter:
*   nome dos autores;
*   introdução ao problema;
*   modelagem e justificativa de sua correção;
*   detalhes da implementação (incluindo exemplos de uso);
*   análise comparativa das funções limitantes.

Nessa análise, devem ser comparados:
*   número de nós gerados na árvore de busca;
*   tempo de execução;

utilizando os relatórios gerados pelo programa. Outras métricas também podem ser utilizadas.

Todas as referências utilizadas devem ser citadas corretamente.

Para facilitar a análise, o programa deve permitir ativar ou desativar os cortes por viabilidade e por otimalidade:
*   opção `-f`: desativa os cortes por viabilidade;
*   opção `-o`: desativa os cortes por otimalidade.

É permitido utilizar bibliotecas para estruturas de dados (listas, conjuntos, etc.), mas não para implementar o algoritmo principal de resolução.

O programa deve compilar e executar nas servidoras do DINF.

O trabalho deve ser entregue com um Makefile, de modo que o comando `make` gere o executável chamado `abey`.

#### Resumo dos requisitos do texto
O relatório deve conter:
*   identificação dos autores;
*   explicação do problema;
*   modelagem;
*   análise das funções limitantes;
*   detalhes da implementação.

#### Requisitos da implementação
O programa:
*   deve gerar um executável chamado `abey`;
*   deve utilizar, por padrão:
    *   cortes por viabilidade ativos;
    *   cortes por otimalidade ativos;
    *   função limitante criada pelos autores;
*   com a opção `-f`, deve desativar os cortes por viabilidade;
*   com a opção `-o`, deve desativar os cortes por otimalidade;
*   com a opção `-a`, deve utilizar a função limitante fornecida pelo professor;
*   deve gerar um relatório na saída de erro (`stderr`) contendo:
    *   número de nós da árvore;
    *   tempo de execução (sem considerar leitura e escrita de dados).

#### Arquivos para entrega
Deve ser entregue um arquivo compactado (`.tar.gz`) contendo:
*   relatório em PDF;
*   arquivos-fonte (podem estar em subdiretórios);
*   Makefile;
*   exemplos utilizados na análise (podem estar em subdiretórios).

#### Forma de entrega
O trabalho deve ser enviado por e-mail para:
*   BCC1: `andre@inf.ufpr.br`
*   BCC2: `murilo@inf.ufpr.br`

Assunto do e-mail: `Otimizacao-trabalho 2` (exatamente como escrito acima).

O trabalho pode ser realizado em equipes de até 3 alunos.

---

### 2. O Problema: Leilão Virtual

No fim do século passado, em 1995, foi fundada uma empresa de leilão virtual que se tornou precursora do comércio eletrônico.

Vamos imaginar que possuímos nossa própria empresa de leilões virtuais, chamada **abey**. Diferentemente das plataformas tradicionais, nossa empresa busca reduzir desigualdades, evitando que pessoas com grande poder aquisitivo adquiram todos os produtos, mesmo que isso resulte em menor lucro.

Em um evento de leilão existem:
*   $p$ produtos à venda (uma unidade de cada);
*   $c$ clientes.

Cada cliente faz uma oferta para cada produto.

Assuma que:
*   todas as ofertas são maiores que os preços mínimos;
*   uma oferta igual a zero significa que o cliente não deseja aquele produto.

#### Objetivo
Desejamos que:
*   cada cliente compre no máximo um produto;
*   o valor arrecadado seja máximo.

#### 2.1 Formato de Entrada e Saída
A entrada e a saída devem utilizar:
*   entrada padrão (`stdin`);
*   saída padrão (`stdout`).

Os números podem estar separados por espaços, tabulações ou quebras de linha.

**Entrada:**
A entrada é composta por:
*   dois inteiros $p$ e $c$;
*   seguidos de $p$ linhas contendo as ofertas dos clientes.

Formato:
```text
p c
o1,1 o1,2 ... o1,c
o2,1 o2,2 ... o2,c
...
op,1 op,2 ... op,c
```
Onde $o_{i,j}$ representa a oferta do cliente $j$ pelo produto $i$.

**Saída:**
A saída deve listar as ofertas aceitas. Cada linha contém:
```text
produto cliente
```
Ao final, em uma linha separada, deve ser impresso o valor total arrecadado.

#### 2.2 Exemplos
*Observação: o número de nós e o tempo de execução foram omitidos, pois dependem da modelagem e da função limitante utilizada.*

##### 2.2.1 Exemplo simples com $p = 2$ e $c = 2$
**Entrada:**
```text
2 2
1 2
2 1
```
**Saída:**
```text
1 2
2 1
4
```

##### 2.2.2 Exemplo simples com $p = 2$ e $c = 3$
**Entrada:**
```text
2 3
10 1 2
20 2 1
```
**Saída:**
```text
1 3
2 1
22
```

---

### 3. Função Limitante Fornecida

Dados:
*   $A$: conjunto de arremates já realizados, contendo pares $(i,j)$;
*   $P$: conjunto de produtos ainda não vendidos;
*   $C$: conjunto de clientes que ainda não compraram.

A função limitante fornecida é:
$$B_{\text{dada}}(A, P, C) = \sum_{(i,j) \in A} o_{i,j} + |P| \cdot \max \{ o_{i,j} \mid i \in P, j \in C \}$$

Ou seja:
1.  soma-se o valor dos arremates já realizados;
2.  encontra-se a maior oferta disponível entre os produtos restantes e clientes ainda livres;
3.  multiplica-se essa oferta pelo número de produtos restantes.

Assim obtém-se um limite superior para o valor máximo que ainda pode ser alcançado.

---

### 4. Dicas

*   Para implementar o algoritmo de Branch and Bound, é necessário definir uma estratégia de ramificação.
*   Idealmente (embora não seja obrigatório), essa estratégia deve gerar apenas soluções parciais viáveis.
*   Lembre-se de que, em um problema de maximização, uma função limitante deve sempre fornecer um valor maior ou igual ao valor ótimo do subproblema correspondente. Isso garante que nenhuma solução ótima seja eliminada durante os cortes por otimalidade.

</details>