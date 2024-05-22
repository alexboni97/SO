#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>

#define MAX_NUM 10

typedef enum {
    IMPARES, 
    PARES,
    CONSUMIR
} type_turno; 

type_turno turno = IMPARES;
int numero;
pthread_mutex_t mutex;
pthread_cond_t vcImpares, vcPares, vcConsumidor;

int done_pares   = 0;
int done_impares = 0;


void *Impares(void *data){
  int i;
    
  for( i=1; i <= 2*MAX_NUM; i+=2 ){
    pthread_mutex_lock(&mutex);
    while(turno != IMPARES)
      pthread_cond_wait(&vcImpares,&mutex);
    numero=i;
    pthread_cond_signal(&vcConsumidor);
    turno = CONSUMIR;
    pthread_mutex_unlock(&mutex);
  }
  done_pares = 1;
}

void *Pares(void *data){
  int i;
    
  for( i=2; i <= 2*MAX_NUM; i+=2 ){
    pthread_mutex_lock(&mutex);
    while(turno != PARES)
      pthread_cond_wait(&vcPares,&mutex);
    numero=i;
    pthread_cond_signal(&vcConsumidor);
    turno = CONSUMIR;
    pthread_mutex_unlock(&mutex);
  }
  done_impares = 1;
}

void *Consumidor(void *data){

  while(!done_impares || !done_pares){
    pthread_mutex_lock(&mutex);
    while(turno!=CONSUMIR)
      pthread_cond_wait(&vcConsumidor,&mutex);
    printf("Dato: %d\n",numero);
    
    if(numero%2){
      turno=PARES;
      pthread_cond_signal(&vcPares);
    }else{
      turno=IMPARES;
      pthread_cond_signal(&vcImpares);
    }
    pthread_mutex_unlock(&mutex);
  }
  printf("Consumidor done!!\n");
}


int main(int argc, char *argv[]) {
  pthread_t pTh_par, pTh_impar, pTh_cons;

  pthread_mutex_init(&mutex,       NULL);
  pthread_cond_init(&vcImpares,    NULL);
  pthread_cond_init(&vcPares,      NULL);
  pthread_cond_init(&vcConsumidor, NULL);

  pthread_create(&pTh_par,   NULL, Pares,      NULL);
  pthread_create(&pTh_impar, NULL, Impares,    NULL);
  pthread_create(&pTh_cons,  NULL, Consumidor, NULL);

  pthread_join(pTh_par,   NULL);
  pthread_join(pTh_impar, NULL);
  pthread_join(pTh_cons,  NULL);
  
  pthread_mutex_destroy(&mutex);
  pthread_cond_destroy(&vcImpares);
  pthread_cond_destroy(&vcPares);
  pthread_cond_destroy(&vcConsumidor);
  
  exit(0);
}