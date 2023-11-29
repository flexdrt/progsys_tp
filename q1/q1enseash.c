#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>

int main(){
    ssize_t nread;
    char *line =NULL;
    size_t len = 0;
    char * welcome  = "Bienvenue dans le Shell ENSEA.\n Pour quitter, tapez 'exit'.\n enseash % ";
    write(STDOUT_FILENO,welcome,strlen(welcome)); 

}

