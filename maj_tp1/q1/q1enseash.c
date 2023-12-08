#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>



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

int main(){
   q1();

}

