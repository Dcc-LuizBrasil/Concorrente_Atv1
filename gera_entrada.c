#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX 1000

int main(int argc, char*argv[]) {
   float *vetor1, *vetor2;
   long int n;
   float elem;
   double soma=0;
   int fator=1;
   FILE * descritorArquivo;
   size_t ret;

   if(argc < 3) {
      fprintf(stderr, "Digite: %s <dimensao> <nome arquivo saida>\n", argv[0]);
      return 1;
   }
   n = atoi(argv[1]);

   vetor1 = (float*) malloc(sizeof(float) * n);
   vetor2 = (float*) malloc(sizeof(float) * n);
   if(!vetor1 || !vetor2) {
      fprintf(stderr, "Erro de alocao da memoria do vetor\n");
      return 2;
   }

   srand(time(NULL));
   for(long int i=0; i<n; i++) {
        elem = (rand() % MAX) * fator;
        vetor1[i] = elem;
        elem = (rand() % MAX) * fator;
        vetor2[i] = elem;

        soma += vetor1[i]*vetor2[i]; 
        fator*=-1;
   }

   descritorArquivo = fopen(argv[2], "wb");
   if(!descritorArquivo) {
      fprintf(stderr, "Erro de abertura do arquivo\n");
      return 3;
   }

   ret = fwrite(&n, sizeof(long int), 1, descritorArquivo);
   ret = fwrite(vetor1, sizeof(float), n, descritorArquivo);
   ret = fwrite(vetor2, sizeof(float), n, descritorArquivo);
   if(ret < n) {
      fprintf(stderr, "Erro de escrita no  arquivo\n");
      return 4;
   }

   ret = fwrite(&soma, sizeof(double), 1, descritorArquivo);

   fclose(descritorArquivo);
   free(vetor1);
   free(vetor2);
   return 0;
} 
