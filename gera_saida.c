#include <stdio.h>
#include <stdlib.h> 
#include <pthread.h> 

long int n;
float *vet1, *vet2;
int nthreads;

void *SomaVetor (void *tid) {
  long int id = (long int) tid;
  int ini, fim, bloco;
  float soma=0, *ret;
  
  bloco = n/nthreads;
  ini = id*bloco;
  fim = ini + bloco;
  if (id==(nthreads-1)) fim = n;

  for(int i=ini; i<fim; i++) {
     soma += vet1[i]*vet2[i];
  }

  ret = (float*) malloc(sizeof(float));
  if (ret!=NULL) *ret = soma;
  else printf("--ERRO: malloc() thread\n");
  pthread_exit((void*) ret);
}

int main(int argc, char *argv[]) {
  FILE *arq;
  size_t ret; 
  double soma_ori;
  float soma_conc;
  float *soma_retorno_threads;

  pthread_t *tid_sistema;
  
  if(argc < 3) { printf("Use: %s <arquivo de entrada> <numero de threads> \n", argv[0]); exit(-1); }

  arq = fopen(argv[1], "rb");
  if(arq==NULL) { printf("--ERRO: fopen()\n"); exit(-1); }

  ret = fread(&n, sizeof(long int), 1, arq);
  if(!ret) {
     fprintf(stderr, "Erro de leitura das dimensoes da matriz arquivo \n");
     return 3;
  }

  vet1 = (float*) malloc (sizeof(float) * n);
  vet2 = (float*) malloc (sizeof(float) * n);
  if(vet1==NULL || vet2==NULL) { printf("--ERRO: malloc()\n"); exit(-1); }

  ret = fread(vet1, sizeof(float), n, arq);
  if(ret < n) {
     fprintf(stderr, "Erro de leitura dos elementos do vetor\n");
     return 4;
  }

  ret = fread(vet2, sizeof(float), n, arq);
  if(ret < n) {
     fprintf(stderr, "Erro de leitura dos elementos do vetor\n");
     return 4;
  }

  nthreads = atoi(argv[2]);
  if(nthreads>n) nthreads = n;

  tid_sistema = (pthread_t *) malloc(sizeof(pthread_t) * nthreads);
  if(tid_sistema==NULL) { printf("--ERRO: malloc()\n"); exit(-1); }

  for(long int i=0; i<nthreads; i++) {
    if (pthread_create(&tid_sistema[i], NULL, SomaVetor, (void*) i)) {
       printf("--ERRO: pthread_create()\n"); exit(-1);
    }
  }

  soma_conc=0;
  for(int i=0; i<nthreads; i++) {
     if (pthread_join(tid_sistema[i], (void *) &soma_retorno_threads)) {
        printf("--ERRO: pthread_join()\n"); exit(-1);
     }
     soma_conc += *soma_retorno_threads;
     free(soma_retorno_threads);
  }

  printf("\n");
  printf("soma_concorrente = %.26f\n", soma_conc);
  ret = fread(&soma_ori, sizeof(double), 1, arq); 
  printf("\nSoma-original = %.26lf\n", soma_ori);
  printf("\nErro relativo = %.26lf\n", (soma_ori-soma_conc)/soma_ori);

  free(vet1);
  free(vet2);
  free(tid_sistema);
  fclose(arq);
  return 0;
}
