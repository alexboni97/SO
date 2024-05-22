#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <semaphore.h>
#include <sys/types.h>
#include <unistd.h>

#define PROD        100

// Semáforos con nombre.
sem_t * sem_pares;
sem_t * sem_impares;
sem_t * sem_cons;

// Región de memoria compartida.
void * sh_mem;
int * datos;

// Consumidor
void Consumidor( void ){
  int i;

  for(i=0; i<PROD; i++){
    sem_wait( sem_cons ); 
    printf("Dato: %d\n", *datos);
    if(*datos%2)
        sem_post( sem_pares ); 
    else
        sem_post( sem_impares ); 
  }
}

void main(void){

  // Descriptor de fichero de respaldo.
  int shd;

  // Creación y apertura de fichero de respaldo.
  shd = open( "DATO", O_CREAT | O_RDONLY, 0777);
  if( shd == -1 ) {
    perror( "Error abriendo fichero compartido\n" );
    exit( -1 );
  }
  ftruncate( shd, sizeof(int) );

  // Mapeado de zona de memoria compartida.
  sh_mem = mmap(NULL, sizeof(int), PROT_READ, MAP_SHARED, shd, 0 );
  if( sh_mem == NULL ) {
    perror( "Error mapeando memoria\n" );
    exit( -1 );
  }
  datos = (int*)sh_mem;

  // Creación de semáforos con nombre.
  sem_pares = sem_open( "PARES", O_CREAT, 0700, 0 );
  if( sem_pares == NULL ) {
      perror("Error creando sem_pares\n");
      exit(-1);
  }
  sem_impares = sem_open( "IMPARES", O_CREAT, 0700, 1 );
  if( sem_impares == NULL ) {
      perror("Error creando sem_impares\n");
      exit(-1);
  }
  sem_cons = sem_open( "CONS", O_CREAT, 0700, 0 );
  if( sem_cons == NULL ) {
      perror("Error creando sem_cons\n");
      exit(-1);
  }
    
  Consumidor();

  // Cierre de recursos.
  sem_close( sem_pares );
  sem_close( sem_impares );
  sem_close( sem_cons );

  close( shd );

  // Eliminación de semáforos.
  sem_unlink( "PARES" );
  sem_unlink( "IMPARES" );
  sem_unlink( "CONS" );

  // Eliminación de fichero.
  unlink( "DATO" );
}


