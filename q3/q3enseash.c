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
    char *enseash = "enseash% ";

    write(STDOUT_FILENO, enseash, strlen(enseash));
//Question 2 **** Ajout de la fonctionalité : exécution de la commande et retour au prompt ****
    pid_t pid;
    while (1)
    {

        int end = read(STDIN_FILENO, buf, READNUMER);
//Question 3 **** Ajout de la fonctionalité : sortie du prompt avec la commande exit ****
        if (strncmp(buf,"exit",4)==0 || (end == 0) ) //strncmp retourne 0 si les chaînes de caractères sont identiques : on sort de la console
        {
            write(STDOUT_FILENO, "Bye bye...\n", strlen("Bye bye...\n"));
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

    // exit(1);
}
