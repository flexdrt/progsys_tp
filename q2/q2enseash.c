#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <wait.h>

#define READNUMER 300

int main()
{
    ssize_t nread;
    char buf[READNUMER];
    size_t len = 0;
    int status;
    char *welcome = "enseash% ";
    
    write(STDOUT_FILENO, welcome, strlen(welcome));
//Ajout de la fonctionalité : exécution de la commande et retour au prompt
    pid_t pid;
    while (1)
    {

       int end =  read(STDIN_FILENO, buf, READNUMER);
       buf[end-1] = '\0';
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
        write(STDOUT_FILENO, welcome, strlen(welcome));
    }

    exit(1);
}
