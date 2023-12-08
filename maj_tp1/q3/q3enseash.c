#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <wait.h>

#define READNUMER 300

char buf[READNUMER];
ssize_t nread;
size_t len = 0;

int status;
int end;
char *enseash = "enseash % ";
char *welcome = "Bienvenue dans le Shell ENSEA.\nPour quitter, tapez 'exit'.\nenseash % ";

pid_t pid;

void printWelcomeMessage() {
    char *welcome = "Bienvenue dans le Shell ENSEA.\nPour quitter, tapez 'exit'.\nenseash % ";
    write(STDOUT_FILENO, welcome, strlen(welcome));
}


void q1(){
    
    
    char *line = NULL;
    size_t len = 0;
    printWelcomeMessage();

}

void q3()
{
 
     while (1)
    {

        end = read(STDIN_FILENO, buf, READNUMER);
//Question 3 **** Ajout de la fonctionalité : sortie du prompt avec la commande exit
        if (strncmp(buf,"exit",4)==0 || (end == 0) ) //strncmp retourne 0 si les chaînes de caractères sont identiques : on sort de la console
        {
            write(STDOUT_FILENO, "\nBye bye...\n", strlen("Bye bye...\n"));
            exit(0);
        }
        buf[end - 1] = '\0';
        pid = fork();
        if (pid < 0)
        {
            wait(&status);
        }
        else if (pid == 0)
        { // child

            execlp(buf, buf, NULL);
            exit(EXIT_SUCCESS);
        }
        wait(&status);
        write(STDOUT_FILENO, enseash, strlen(enseash));
    }
    
}

int main(){
    q1();
    q3();
}

