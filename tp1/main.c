#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main() {
  printf("Je suis le processus numéro %d\n", getpid());

  pid_t child_pid = fork();
  printf("Fork m'a renvoyé la valeur : %d\n", child_pid);

  if (child_pid == 0) {
    printf("Je suis le processus numéro %d et mon père est le processus numéro %d\n", getpid(), getppid());
  }

  return 0;
}

