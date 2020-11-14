#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <thread>
#include <math.h>
#include <sys/time.h>
#include <time.h>
#include <cstring>
#include <mutex>

typedef long long ll;

unsigned numThreads;
ll numElementos, counter = 0; //shared global variable
pthread_mutex_t mutex;

typedef struct {
  ll start, end;
} th_data;


double MyClock() {
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return (tv.tv_sec * 1000000) + tv.tv_usec;
}

int  ehPrimo(ll n) {
    int numDiv = 0, max_div = ceil(sqrt(n));
    if(n <= 1 or n % 2 == 0)        return 0;
    for (ll d = 1; d <= max_div ; d+=2) {
         if (n % d == 0){
              numDiv++;
         }
    }
    return numDiv == 1;
}
        

void *mythread(void *args){
    th_data *th = (th_data *)args;
    ll c = 0;
    //Cada thread conta os valores do intervalo
    for(ll i= (th->start); i<= (th->end); i++){
        if(ehPrimo(2*i*i-1)) c++;
    }
	pthread_mutex_lock(&mutex); 
	counter= counter + c;
	pthread_mutex_unlock(&mutex);
    return NULL;
}
                                                                    
int main(int argc, char *argv[]) {
    double inicio = MyClock();

    // Valida os argumentos
    if (argc != 3 || sscanf(argv[1], "%u", &numThreads) != 1 || sscanf(argv[2], "%lld", &numElementos) != 1) {
        printf("usage: %s <numThreads> <numElementos>\n", argv[0]);
        return 1;
    }

    if (numElementos < 0)
        printf("Tamanho invalido\n");

    srand(0);

    
    pthread_t threads[numThreads];
    th_data th[numThreads];
    
    pthread_mutex_init(&mutex, NULL);

    int i;
    for(i=0; i<numThreads; i++) {
        th[i].start = i*(numElementos/numThreads);
        th[i].end = (i+1)*(numElementos/numThreads) -1;
        if(i == numThreads-1)      th[i].end = numElementos;
        //printf("Thread %d = %d - %d\n",i+1,th[i].start,th[i].end);
        pthread_create(&(threads[i]), NULL, mythread, (void *) &th[i]);
    }
    for(i=0; i<numThreads; i++) {
        pthread_join(threads[i], NULL);
    }

    pthread_mutex_destroy(&mutex);

    printf("Tempo: %.5lf\n", (MyClock()-inicio)/CLOCKS_PER_SEC); //segundos

    printf("Resposta: %lld\n",counter);
    return 0;
}