# Concorrente_Atv1
Luiz Eduardo Azevedo Brasil - 122117785
Atividade 1 da matéria programação concorrente.

Para verificar a atividade é necessário executar os seguintes comandos:

gcc -o gera_entrada gerada_entrada.c -Wall
gcc -o gera_saida gerada_saida.c -Wall

./gera_entrada <numero_de_elementos_do_vetor> <nome_do_arquivo_de_saida>
./gera_saida <nome_do_arquivo_de_entrada> <numero_de_threads>

Foi possível constatar com os 5 testes que o erro relativo é proporcional ao número de 
elementos no vetor do arquivo de entrada e inversamente proporcional ao número de threads.

Fato esse observado quando o teste1 possui erro 0 quando executado com 10 threads, o teste2 
possui erro a partir da 7º casa decimal e o teste5 possui erro a partir da 4º casa decimal 
quando executado com 10 threads e 7º casa quando executado com 10000 threads.

Faz sentido, visto que mais threads executam somas menores, portanto menos erro acumulado 
em somas consecutivas de floats.
