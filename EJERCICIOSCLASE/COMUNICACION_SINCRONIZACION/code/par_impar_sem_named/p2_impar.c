#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <semaphore.h>
#include <sys/types.h>
#include <unistd.h>

#define PROD        100

// Semáforos con nombre.
sem_t * sem_impares;
sem_t * sem_cons;

// Región de memoria compartida.
void * sh_mem;
int * datos;

void Impares( void ){
  int i;

  for(i=1; i<=PROD; i+=2){
    sem_wait( sem_impares ); 
    *datos = i;
    sem_post( sem_cons );
  }
}

void main(void){

  // Descriptor de fichero de respaldo.
  int shd;

  // Apertura de fichero de respaldo.
  shd = open( "DATO", O_RDWR );
  if( shd == -1 ) {
    perror( "Error abriendo fichero compartido\n" );
    exit( -1 );
  }
  ftruncate( shd, sizeof(int) );

  // Mapeado de zona de memoria compartida.
  sh_mem = mmap(NULL, sizeof(int), PROT_WRITE, MAP_SHARED, shd, 0 );
  if( sh_mem == NULL ) {
    perror( "Error mapeando memoria\n" );
    exit( -1 );
  }
  datos = (int*)sh_mem;

  // Apertura de semáforos.
  sem_impares = sem_open( "IMPARES", 0 );
  if( sem_impares == NULL ) {
      perror("Error abriendo sem_impares\n");
      exit(-1);
  }
  sem_cons = sem_open( "CONS", 0 );
  if( sem_cons == NULL ) {
      perror("Error abriendo sem_cons\n");
      exit(-1);
  }

  Impares();

  // Cierre de recursos.
  sem_close( sem_impares );
  sem_close( sem_cons );

  close( shd );
}


