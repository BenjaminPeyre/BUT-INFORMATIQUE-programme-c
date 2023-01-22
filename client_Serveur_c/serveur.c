#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/wait.h>
#include <ctype.h>
#include <signal.h>
 
/** Environnement pour le client */
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
int main(){

    struct sockaddr_in adresse;
    int support, supportClient;
    int port = 64100;

    support = socket(AF_INET, SOCK_STREAM, 0);
    if(support < 0){
        printf("Erreur lors de la création du socket\n");
        exit(1);
    } 

    adresse.sin_family = AF_INET;
    adresse.sin_port = htons(port);
    adresse.sin_addr.s_addr = INADDR_ANY;
    if(bind(support, (struct sockaddr *) &adresse, sizeof(adresse)) <0){
        printf("Erreur lors du lien du socket \n ");
        exit(1);
    }  
    listen(support, 5);
    int tailleAdresse = sizeof(adresse);
    while(1)
   {
    supportClient = accept(support, (struct sockaddr * ) &adresse, &tailleAdresse);
    if(supportClient < 0){
        printf("Erreur lors de l'acceptation de la connexion \n ");
        exit(1);
    } 
    int message;
    read(supportClient, &message, sizeof(int));
    printf("%d\n", message);
    message = message*2;
    write(supportClient, &message, sizeof(int));
    close(supportClient);
   } 
   //Fermer le socket d'ecoute
   close(support);
   return 0;
} 