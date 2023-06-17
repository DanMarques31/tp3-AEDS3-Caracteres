# tp3-AEDS3-Caracteres
Compilação e Execução

O programa feito de acordo com a proposta possui um arquivo Makefile que realiza todo o procedimento de compilação e execução. Para tanto, temos as seguintes diretrizes de execução:
	
Comandos:

make clean -	Apaga a última compilação realizada.
make 	   -	Executa a compilação do programa utilizando o gcc.

A compilação irá gerar um arquivo .exe com o nome tp3. Para execução basta fazer :

./tp3 nomedoarquivo.txt <estratégia>

Estratégia 1 = Irá executar o algoritmo de casamento Força Bruta.
Estratégia 2 = Irá executar o algoritmo de casamento KMP.
Estratégia 3 = Irá executar o algoritmo de casamento BMH.

O programa irá gerar um arquivo '<nomedaentrada>.txt.out' com as respostas de cada teste do arquivo de entradas.