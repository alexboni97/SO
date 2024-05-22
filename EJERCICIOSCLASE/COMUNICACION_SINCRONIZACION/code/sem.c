#include <pthread.h>

typedef struct {
  int val;

  pthread_mutex_t mutex;
  pthread_cond_t cond;
} sem_t;

void sem_init( sem_t* s, int val ) {
    s->val = val;

    pthread_mutex_init( &(s->mutex), NULL );
    pthread_cond_init( &(s->cond), NULL );
}

void sem_destroy( sem_t* s ) {
    pthread_mutex_destroy( &(s->mutex) );
    pthread_cond_destroy( &(s->cond) );
}

void sem_wait( sem_t * s  ) {

    pthread_mutex_lock( &(s->mutex ) );

    if( s->val < 0 ) // while
      pthread_cond_wait( &(s->cond), &(s->mutex) );
  
    s->val--;

    pthread_mutex_unlock( &(s->mutex ) );
    
}

void sem_signal( sem_t * s  ) {

    pthread_mutex_lock( &(s->mutex ) );

    s->val++;

    if( s->val <= 0 )
        pthread_cond_signal( &(s->cond) );

    pthread_mutex_unlock( &(s->mutex ) );
    
}

#if 0
sem_t misemaforo;

int main( void ) {

    sem_init( &misemaforo, 1 );

    sem_destroy( &misemaforo );

    return 0;

}
#endif
