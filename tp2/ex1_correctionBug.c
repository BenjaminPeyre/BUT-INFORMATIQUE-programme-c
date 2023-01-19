#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

void *thread_function_1(void *arg) {
  // Configuration de l'affichage sans bufferisation
  setbuf(stdout, NULL);

  while (1) {
    printf(".");
    fflush(stdout); // Vide le buffer de l'affichage
    sleep(1);
  }

  return NULL;
}

void *thread_function_2(void *arg) {
  printf("Tapez un caractère:\n");
  getchar();

  return NULL;
}

int main() {
  pthread_t thread_1, thread_2;

  // Création des threads
  pthread_create(&thread_1, NULL, thread_function_1, NULL);
  pthread_create(&thread_2, NULL, thread_function_2, NULL);

  printf("Les 2 threads sont lancés\n");

  // Attente de la fin de l'exécution du second thread
  pthread_join(thread_2, NULL);

  printf("On va s'arrêter là\n");

  // Attente de la fin de l'exécution du premier thread
  pthread_join(thread_1, NULL);

  return 0;
}

