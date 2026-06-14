# Otimiza-o-Branch-and-Bound

1 Introdu¸c˜ao
O trabalho consiste em modelar e implementar, por Branch & Bound, o
problema Leil˜ao virtual, descrito na Se¸c˜ao 2.
A resolu¸c˜ao do problema, ou seja, a descri¸c˜ao do problema, da modelagem e da implementa¸c˜ao, deve estar em um texto claro em formato de um
artigo em pdf. Al´em disso, deve ser feita uma an´alise com duas fun¸c˜oes limitantes (bounds) diferentes, sendo uma dada pelo professor (Se¸c˜ao 3) e outra
escolhida pelos alunos (que deve ser melhor que a dada). A fun¸c˜ao limitante
dos alunos deve ser a default na implementa¸c˜ao e a dada pelo professor ´e
escolhida usando uma op¸c˜ao da linha de comando (-a).
O texto deve conter o nome dos autores (alunos), uma introdu¸c˜ao com
o problema, a modelagem e sua explica¸c˜ao (de por que essa modelagem
resolve o problema), detalhes da implementa¸c˜ao (com exemplos de uso), e
uma an´alise do uso das fun¸c˜oes limitantes. Nesta an´alise devem ser feitas
e comparadas contagens de n´umero de n´os da ´arvore e tempo de execu¸c˜ao
(com relat´orio gerado pelo programa). Outras m´etricas tamb´em podem ser
usadas.
Todas as referˆencias que forem usadas devem estar citadas corretamente
no texto.
Para facilitar a an´alise, o seu programa deve ter a op¸c˜ao de fazer ou n˜ao
os cortes por viabilidade e otimalidade. Ou seja, com a op¸c˜ao de linha de
comando -f os cortes por viabilidade n˜ao devem estar ativos; e com a op¸c˜ao
de linha do comando -o os cortes por otimalidade s˜ao desligados.
Vocˆe pode usar bibliotecas para estruturas de dados (como listas, conjuntos etc), mas n˜ao para o algoritmo de resolu¸c˜ao principal do problema. O
seu programa deve compilar e executar nas servidoras do DINF.
1
O trabalho deve ser entregue com um makefile de forma que ao digitar o
comando make o execut´avel abey seja constru´ıdo.
Resumindo, o texto deve ter:
• identifica¸c˜ao;
• explica¸c˜ao do problema;
• modelagem;
• an´alise das fun¸c˜oes limitantes;
• detalhes da implementa¸c˜ao.
A implementa¸c˜ao:
• deve ter execut´avel de nome abey;
• na op¸c˜ao default todos os cortes (viabilidade e otimalidade) est˜ao ativos
e a fun¸c˜ao limitante ´e a criada pelos autores;
• com a op¸c˜ao -f na linha de comando deve desligar os cortes de viabilidade;
• com a op¸c˜ao -o na linha de comando deve desligar os cortes de otimalidade;
• com a op¸c˜ao -a na linha de comando deve usar a fun¸c˜ao limitante dada
pelo professor;
• deve gerar relat´orio (na sa´ıda de erro padr˜ao, stderr) com n´umero de
n´os da ´arvore e tempo gasto (sem contar o tempo de entrada e sa´ıda).
Vocˆe deve entregar um arquivo compactado (tar.gz) com os seguintes
arquivos no diret´orio corrente:
• texto (em pdf);
• os fontes (podem estar em subdiret´orios);
• makefile;
• exemplos usados na an´alise (podem estar em subdiret´orios).
A entrega deve ser feita por e-mail para andre@inf.ufpr.br (turma
BCC1) ou murilo@inf.ufpr.br (turma BCC2), em um arquivo compactado com todos os arquivos do trabalho, com assunto “Otimiza¸c˜ao-trabalho
2” (exatamente). O trabalho pode ser feito em equipes de at´e 3 alunos.
2
2 O problema
Leil˜ao virtual
No fim do s´eculo passado, em 1995, foi fundada uma empresa de leil˜ao
virtual que foi a precursora do com´ercio eletrˆonico. Vamos imaginar que
temos a nossa pr´opria empresa de leil˜ao virtual, chamada abey. Mas nossa
empresa tenta n˜ao contribuir com desigualdades, evitando que pessoas com
grande poder aquisitivo comprem todos os produtos, mesmo que isso signifique menos lucro.
Em um evento de leil˜ao temos p produtos `a venda (uma unidade cada),
com seus pre¸cos m´ınimos (maiores que zero). Temos tamb´em c clientes, cada
um com uma oferta para cada produto. Podemos assumir que as ofertas
sempre s˜ao maiores que os pre¸cos m´ınimos. Se a oferta de compra para
um determinado produto ´e zero, entendemos que este cliente n˜ao quer este
produto.
Queremos ent˜ao que cada cliente compre no m´aximo um produto e que o
ganho (bruto) com a venda seja m´aximo.
2.1 Formato de entrada e sa´ıda
Os formatos de entrada e sa´ıda, s˜ao descritos a seguir e devem ser usados
a entrada e a sa´ıda padr˜ao (stdin e stdout).
A entrada ´e formada de um conjunto de n´umeros inteiros. Os n´umeros
podem estar separados por 1 ou mais espa¸cos, tabs ou fim de linha.
Entrada: dois n´umeros, representando p e c, seguidos de p conjuntos de c
n´umeros representando as ofertas, o primeiro conjunto s˜ao as ofertas
de cada cliente (em ordem) para o produto 1, depois para o produto 2,
e assim para os demais produtos. Como descrito abaixo.
p c
o1,1 o1,2 · · · o1,c
o2,1 o2,2 · · · o2,c
· · ·
op,1 op,2 · · · op,c
Sa´ıda: lista com as ofertas aceitas, indicando os ´ındices dos produtos e dos
clientes. Ou seja, dois n´umeros por linha, separados por um espa¸co,
onde o primeiro ´e o ´ındice do produto e o segundo, do cliente. Ao final,
em uma linha separada, o valor total arrecadado (ganho bruto).
3
2.2 Exemplos
Note que o n´umero de n´os e o tempo gasto foram omitidos dos exemplos,
j´a que podem variar com a modelagem e a fun¸c˜ao limitante escolhida.
2.2.1 Exemplo simples com p = 2 e c = 2
Entrada:
2 2
1 2
2 1
Sa´ıda:
1 2
2 1
4
2.2.2 Exemplo simples com p = 2 e c = 3
Entrada:
2 3
10 1 2
20 2 1
Sa´ıda:
1 2
2 3
22
3 Fun¸c˜ao limitante dada
Dados os arremates j´a feitos, A, com pares (i, j) onde o produto i foi
arrematado pelo cliente j, e os conjuntos de produtos ainda por serem arrematados, P, e clientes ainda sem comprar nada, C, podemos definir a fun¸c˜ao
Bdada(A, P, C) por:
Bdada(A, P, C) = X
(i,j)∈A
oi,j + |P| max{oi,j | i ∈ P, j ∈ C}.
Ou seja, Bdada(A, P, C) ´e a soma dos valores dos arremates j´a feitos mais
o valor da oferta mais alta para um produto ainda n˜ao arrematado feita
4
por um cliente que ainda n˜ao comprou nada multiplicado pelo n´umero de
produtos que faltam.
4 Dicas
Para fazer o Branch & Bound ´e preciso escolher uma estrat´egia de ramifica¸c˜ao. Esta estrat´egia deveria (embora n˜ao seja essencial) s´o passar por
solu¸c˜oes (parciais) vi´aveis.
Lembrem que uma fun¸c˜ao limitante em um problema de maximiza¸c˜ao
deve ser sempre maior ou igual ao valor ´otimo do subproblema, para garantir
que nenhuma solu¸c˜ao ´otima seja cortada.
