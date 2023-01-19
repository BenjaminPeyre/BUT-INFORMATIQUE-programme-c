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
 
/** Outils logiciels */
// struct sockaddr_in{
//     short sin_family;           /* domaine internet */
//     u_short sin_port;           /* numéro du port */
//     struct in_addr sin_addr;    /*adresse internet*/
//     char sin_zero[8];
// };
 
// struct in_addr {
//     u_long s_addr;              /** adresse internet */
// };
 
 
int main(){
   struct sockaddr_in adresse;
   struct hostent *serveur; // COntient l'adresse du serveur distant
   char *nom = "iparla.iutbayonne.univ-pau.fr";
 
   serveur = gethostbyname(nom);
   adresse.sin_family = AF_INET;
   adresse.sin_port = htons(64100);
   //adresse.sin_port = htons(46789);
   adresse.sin_addr.s_addr = ((struct in_addr *)(serveur->h_addr))->s_addr;
   /* Rq : ici ça se corse, mais c'est pas si dur que ça en fait.
   serveur->h_addr est un des membres de la structure hostent,
   il contient l'adresse IP du serveur, convertie au format réseau et récupéré par la fonction gethostbuname*/
 
   int support = socket(AF_INET, SOCK_STREAM, 0);
 
   if(connect(support, (struct sockaddr *)&adresse, sizeof(adresse)) < 0){
       printf("Connexion impossible !\n");
   }
   else{
       printf("COnnexion OK\n");
   }
   int message = 8;
 
   write(support, &message, sizeof(message));
 
   read(support, &message, sizeof(int));
   printf("%d\n",  message);
 
   close(support);
  
}

