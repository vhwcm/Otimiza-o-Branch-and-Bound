Otimização — Branch and Bound
1. Introdução

O trabalho consiste em modelar e implementar, utilizando Branch and Bound, o problema Leilão Virtual, descrito na Seção 2.

A resolução do problema — incluindo sua descrição, modelagem e implementação — deve ser apresentada em um texto claro no formato de artigo em PDF. Além disso, deve ser realizada uma análise utilizando duas funções limitantes (bounds) diferentes:

uma fornecida pelo professor (Seção 3);
outra escolhida pelos alunos, que deve apresentar desempenho superior à fornecida.

A função limitante desenvolvida pelos alunos deve ser a padrão da implementação. A função fornecida pelo professor deve ser selecionada por meio da opção de linha de comando -a.

O texto deve conter:

nome dos autores;
introdução ao problema;
modelagem e justificativa de sua correção;
detalhes da implementação (incluindo exemplos de uso);
análise comparativa das funções limitantes.

Nessa análise, devem ser comparados:

número de nós gerados na árvore de busca;
tempo de execução;

utilizando os relatórios gerados pelo programa. Outras métricas também podem ser utilizadas.

Todas as referências utilizadas devem ser citadas corretamente.

Para facilitar a análise, o programa deve permitir ativar ou desativar os cortes por viabilidade e por otimalidade:

opção -f: desativa os cortes por viabilidade;
opção -o: desativa os cortes por otimalidade.

É permitido utilizar bibliotecas para estruturas de dados (listas, conjuntos, etc.), mas não para implementar o algoritmo principal de resolução.

O programa deve compilar e executar nas servidoras do DINF.

O trabalho deve ser entregue com um Makefile, de modo que o comando:

make

gere o executável chamado:

abey
Resumo dos requisitos do texto

O relatório deve conter:

identificação dos autores;
explicação do problema;
modelagem;
análise das funções limitantes;
detalhes da implementação.
Requisitos da implementação

O programa:

deve gerar um executável chamado abey;
deve utilizar, por padrão:
cortes por viabilidade ativos;
cortes por otimalidade ativos;
função limitante criada pelos autores;
com a opção -f, deve desativar os cortes por viabilidade;
com a opção -o, deve desativar os cortes por otimalidade;
com a opção -a, deve utilizar a função limitante fornecida pelo professor;
deve gerar um relatório na saída de erro (stderr) contendo:
número de nós da árvore;
tempo de execução (sem considerar leitura e escrita de dados).
Arquivos para entrega

Deve ser entregue um arquivo compactado (.tar.gz) contendo:

relatório em PDF;
arquivos-fonte (podem estar em subdiretórios);
Makefile;
exemplos utilizados na análise (podem estar em subdiretórios).
Forma de entrega

O trabalho deve ser enviado por e-mail para:

BCC1: andre@inf.ufpr.br
BCC2: murilo@inf.ufpr.br

Assunto do e-mail:

Otimização-trabalho 2

(exatamente como escrito acima).

O trabalho pode ser realizado em equipes de até 3 alunos.

2. O Problema: Leilão Virtual

No fim do século passado, em 1995, foi fundada uma empresa de leilão virtual que se tornou precursora do comércio eletrônico.

Vamos imaginar que possuímos nossa própria empresa de leilões virtuais, chamada abey. Diferentemente das plataformas tradicionais, nossa empresa busca reduzir desigualdades, evitando que pessoas com grande poder aquisitivo adquiram todos os produtos, mesmo que isso resulte em menor lucro.

Em um evento de leilão existem:

p produtos à venda (uma unidade de cada);
c clientes.

Cada cliente faz uma oferta para cada produto.

Assuma que:

todas as ofertas são maiores que os preços mínimos;
uma oferta igual a zero significa que o cliente não deseja aquele produto.
Objetivo

Desejamos que:

cada cliente compre no máximo um produto;
o valor arrecadado seja máximo.
2.1 Formato de Entrada e Saída

A entrada e a saída devem utilizar:

entrada padrão (stdin);
saída padrão (stdout).

Os números podem estar separados por:

espaços;
tabulações;
quebras de linha.
Entrada

A entrada é composta por:

dois inteiros p e c;
seguidos de p linhas contendo as ofertas dos clientes.

Formato:

p c

o1,1 o1,2 ... o1,c
o2,1 o2,2 ... o2,c
...
op,1 op,2 ... op,c

Onde:

oi,j representa a oferta do cliente j pelo produto i.
Saída

A saída deve listar as ofertas aceitas.

Cada linha contém:

produto cliente

Ao final, em uma linha separada, deve ser impresso o valor total arrecadado.

2.2 Exemplos

Observação: o número de nós e o tempo de execução foram omitidos, pois dependem da modelagem e da função limitante utilizada.

2.2.1 Exemplo simples com p = 2 e c = 2
Entrada
2 2
1 2
2 1
Saída
1 2
2 1
4
2.2.2 Exemplo simples com p = 2 e c = 3
Entrada
2 3
10 1 2
20 2 1
Saída
1 3
2 1
22
3. Função Limitante Fornecida

Dados:

A: conjunto de arremates já realizados, contendo pares (i,j);
P: conjunto de produtos ainda não vendidos;
C: conjunto de clientes que ainda não compraram.

A função limitante fornecida é:

B
dada
	​

(A,P,C)=∑
(i,j)∈A
	​

o
i,j
	​

+∣P∣⋅max{o
i,j
	​

∣i∈P, j∈C}

Ou seja:

soma-se o valor dos arremates já realizados;
encontra-se a maior oferta disponível entre os produtos restantes e clientes ainda livres;
multiplica-se essa oferta pelo número de produtos restantes.

Assim obtém-se um limite superior para o valor máximo que ainda pode ser alcançado.

4. Dicas

Para implementar o algoritmo de Branch and Bound, é necessário definir uma estratégia de ramificação.

Idealmente (embora não seja obrigatório), essa estratégia deve gerar apenas soluções parciais viáveis.

Lembre-se de que, em um problema de maximização, uma função limitante deve sempre fornecer um valor maior ou igual ao valor ótimo do subproblema correspondente. Isso garante que nenhuma solução ótima seja eliminada durante os cortes por otimalidade.