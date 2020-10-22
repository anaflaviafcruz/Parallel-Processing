#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>

double MyClock() {
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return (tv.tv_sec * 1000000) + tv.tv_usec;
}

int **alocar_preencher (int n)
{
  int i, j, **matriz;

  matriz = (int **) calloc (n, sizeof(int *));
  
  for ( i = 0; i < n; i++ ) {
      matriz[i] = (int*) calloc (n, sizeof(int));
  }

  for (i = 0; i < n; i++) {
     for (j = 0; j < n; j++) {
        matriz[i][j] = 1;   
     }
  }

  return (matriz);
}


int somaElementos(int n, int **matriz){
  int i, j, soma=0;
  for (i = 0; i < n; i++ ) {
      for (j = 0; j < n; j++ ) {
      	soma+= matriz[i][j];
      }
  }
  return soma;
}

int main(int argc, char *argv[]){                    
   
    int N = atoi(argv[1]);
    int **matriz;
    matriz = alocar_preencher(N);
    
    double inicio = MyClock();
    int soma = somaElementos(N,matriz);
    printf("%.10lf\n", (MyClock()-inicio)/CLOCKS_PER_SEC);

    return 0;
}