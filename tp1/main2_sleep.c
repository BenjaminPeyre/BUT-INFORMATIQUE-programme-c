#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main() {
  pid_t child_pid = fork();

  if (child_pid == 0) {
    // Code exécuté par le processus fils
    for (int i = 0; i < 10; i++) {
      printf("Fils: %d\n", i * 2);
      sleep(1);
  }
  } else {
    // Code exécuté par le processus père
    for (int i = 0; i < 10; i++) {
      printf("Père: %d\n", i * 2 + 1);
//      sleep(1); // Pause de 1 seconde avant de passer à la prochaine itération de la boucle
    }
  }

  return 0;
}

