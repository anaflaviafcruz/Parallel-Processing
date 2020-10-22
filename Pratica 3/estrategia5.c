#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>

double MyClock() {
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return (tv.tv_sec * 1000000) + tv.tv_usec;
}

int main(int argc, char *argv[]){                    
   
    int N = atoi(argv[1]);
    /* Cria as matrizes*/
    int i, j, k, r, **A, **B, **C;

    A = (int **) calloc (N, sizeof(int *));
    B = (int **) calloc (N, sizeof(int *));
    C = (int **) calloc (N, sizeof(int *));
  
    for ( i = 0; i < N; i++ ) {
      A[i] = (int*) calloc (N, sizeof(int));
      B[i] = (int*) calloc (N, sizeof(int *));
      C[i] = (int*) calloc (N, sizeof(int *));
    }

    for (i = 0; i < N; i++) {
      for (j = 0; j < N; j++) {
        A[i][j] = B[i][j] = 1;
    	C[i][j] = 0;   
      }
    }

    double inicio = MyClock(); //começa contar tempo

    //multiplicando as matrizes
    /*kij*/
    for(k=0; k < N; k++){
        for(i=0; i < N; i++){
        r=A[i][k];
        for(j=0; j< N; j++)
          C[i][j]+=r*B[k][j];
      } 
    }
    
    printf("%.15lf\n", (MyClock()-inicio)/CLOCKS_PER_SEC); //termino do tempo

    return 0;
}