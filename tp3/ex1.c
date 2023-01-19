#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/wait.h>
#include <pthread.h>

// Déclaration du mutex
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void thread(unsigned long int *cpt){
    unsigned long int tmp;
    for(unsigned long int i = 0; i<10000000; i++){
        // Verrouillage du mutex
        pthread_mutex_lock(&mutex);
        tmp = *cpt;
        tmp = tmp + 1;
        *cpt = tmp;
        // Déverrouillage du mutex
        pthread_mutex_unlock(&mutex);
    }
    printf("Cpt = %ld\n ", *cpt);
    pthread_exit(NULL);
}

int main(){
    pthread_attr_t attr;
    pthread_t id1, id2;
    unsigned long int cpt;
    cpt=0;

    pthread_attr_init(&attr);
    pthread_create(&id1, &attr, (void *)thread, &cpt);
    pthread_create(&id2, &attr, (void *)thread, &cpt);

    printf("les 2 threads sont lancés\n");
    pthread_join(id1, NULL);
    pthread_join(id2, NULL);

    exit(EXIT_SUCCESS);
}
