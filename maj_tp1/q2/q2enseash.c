#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <wait.h>

#define READNUMER 300

char buf[READNUMER];
size_t len = 0;
int status;
char *enseash = "enseash% ";
char *welcome = "Bienvenue dans le Shell ENSEA.\nPour quitter, tapez 'exit'.\nenseash % ";

void printWelcomeMessage() {
    char *welcome = "Bienvenue dans le Shell ENSEA.\nPour quitter, tapez 'exit'.\nenseash % ";
    write(STDOUT_FILENO, welcome, strlen(welcome));
}


void q1(){
    
    ssize_t nread;
    char *line = NULL;
    size_t len = 0;
    printWelcomeMessage();

}
void q2(){
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



int main(){
   q1();
   q2();

}

