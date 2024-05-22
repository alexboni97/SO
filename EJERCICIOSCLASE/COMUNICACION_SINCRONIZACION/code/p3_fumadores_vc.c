#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#define TABACO      0
#define CERILLAS    1
#define PAPEL       2

unsigned char ingr[]={0,0,0};
unsigned char *ingr_str[]={"tabaco", "cerillas", "papel"};


pthread_mutex_t ingr_mutex;
pthread_cond_t ingr_cond;

void Producir(char * ingredientes){
    char a, b;
    a = random()%3;
    do{
        b=random()%3;
    } while (a == b);
    ingredientes[a]=1;
    ingredientes[b]=1;
    printf("Agente: produzco %s y %s.\n", ingr_str[a], ingr_str[b]);
}

void Fumar(char *Ingr1, char *Ingr2){
  printf("He conseguido %s y %s, me pongo a fumar...\n", Ingr1, Ingr2);
  sleep(random()%3);
  printf("Termine!\n");
}

void *Agente(void *data) {
  unsigned char *ingrs=data;
  while (1) {
    pthread_mutex_lock(&ingr_mutex);
    while (ingr[TABACO] || ingr[PAPEL] || ingr[CERILLAS])
      pthread_cond_wait(&ingr_cond, &ingr_mutex);
    Producir(ingr);
    pthread_cond_broadcast(&ingr_cond);
    pthread_mutex_unlock(&ingr_mutex);
  }
}

void *Fumador(void *data) {
  unsigned char *ind=data;
  while (1) {
    pthread_mutex_lock(&ingr_mutex);
    // Tengo los ingredientes que quiero?
    while(!ingr[ind[0]] || !ingr[ind[1]])
      pthread_cond_wait(&ingr_cond, &ingr_mutex);
    ingr[ind[0]] = 0;
    ingr[ind[1]] = 0;
    pthread_cond_broadcast(&ingr_cond);
    pthread_mutex_unlock(&ingr_mutex);
    Fumar(ingr_str[ind[0]],ingr_str[ind[1]]);
  }
}

int main(int argc, char *argv[]) {
  pthread_t pTh_agente, pTh_fum1, pTh_fum2, pTh_fum3;
  unsigned char ingr1[]={TABACO,CERILLAS};
  unsigned char ingr2[]={TABACO,PAPEL};
  unsigned char ingr3[]={CERILLAS,PAPEL};

  srand(time(NULL));
  
  pthread_mutex_init(&ingr_mutex,  NULL);
  pthread_cond_init(&ingr_cond,    NULL);

  pthread_create(&pTh_agente, NULL, Agente,  NULL);
  pthread_create(&pTh_fum1,   NULL, Fumador, ingr1);
  pthread_create(&pTh_fum2,   NULL, Fumador, ingr2);
  pthread_create(&pTh_fum3,   NULL, Fumador, ingr3);

  pthread_join(pTh_agente,   NULL);
  pthread_join(pTh_fum1, NULL);
  pthread_join(pTh_fum2, NULL);
  pthread_join(pTh_fum3, NULL);
  
  pthread_mutex_destroy(&ingr_mutex);
  pthread_cond_destroy(&ingr_cond);
  
  exit(0);
}
