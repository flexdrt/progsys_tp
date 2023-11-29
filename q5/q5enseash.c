#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <wait.h>
#include <time.h>
#define READNUMER 300
#define NANOSECOND 1000000000.
char *enseash = "enseash% ";
char * welcome  = "Bienvenue dans le Shell ENSEA.\n Pour quitter, tapez 'exit'.\n enseash % ";

void q1(){
    
    write(STDOUT_FILENO, welcome, strlen(welcome));

}

//Question 2 **** Ajout de la fonctionalité : exécution de la commande et retour au prompt ****
void q2(){

    ssize_t nread;
    char buf[READNUMER];
    size_t len = 0;
    int status;
      
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
        write(STDOUT_FILENO, enseash, strlen(enseash));
        
    }

    exit(1);

}

void q3 (){
    
    ssize_t nread;
    char buf[READNUMER];
    size_t len = 0;
    int status;
      
    pid_t pid;
     while (1)
    {

        int end = read(STDIN_FILENO, buf, READNUMER);
//Question 3 **** Ajout de la fonctionalité : sortie du prompt avec la commande exit
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
    
}

void q4(){

    ssize_t nread;
    char buf[READNUMER];
    size_t len = 0;
    int status;
    int status_number = 1;
    char status_buf[READNUMER] = {0};
    char enseash2[READNUMER] = "enseash ";
    char string_status_number[READNUMER];

    

    pid_t pid, wpid;
    while (1)
    {

        int end = read(STDIN_FILENO, buf, 300);

        if (strncmp(buf, "exit", 4) == 0)
        {
            write(STDOUT_FILENO, "Bye bye...", strlen("Bye bye..."));
            exit(0);
        }
        buf[end - 1] = '\0';
        pid = fork();
        if (pid < 0)
        {
            wait(&status);
        }
        else if (pid == 0)
        {                        // child

            execlp(buf, buf, NULL);
            exit(EXIT_FAILURE);
        }
        else if (pid > 0)         //father
        {
            wpid = wait(&status);
            if (wpid == -1)
            {
                perror("wait error:");
                exit(1);
            }
            if (WIFEXITED(status)) // normal exit
            {
                status_number = WEXITSTATUS(status);
                sprintf(string_status_number, "[exit:%i] %%  ", status_number);
            }
            else // signal exit
            {
                status_number = WTERMSIG(status);
                sprintf(string_status_number, "[sign:%i] %% ", status_number);
            }
            sprintf(enseash2,"enseash");
            strcat(enseash2, string_status_number);
            
            write(STDOUT_FILENO, enseash2, strlen(enseash2));
            sprintf(enseash2," ");
        }

    }

    
}

void q5(){


#define READNUMER 40


    ssize_t nread;
    char buf[READNUMER];
    size_t len = 0;
    int status;
    int status_number = 1;
    char status_buf[READNUMER] = {0};
    char enseash2[READNUMER] = "enseash ";
    char string_status_number[READNUMER];
    char *enseash = "enseash% ";
    struct timespec start, stop;
    double accum;
    char string_accum[READNUMER];
   

    pid_t pid, wpid;
    while (1)
    {

        int end = read(STDIN_FILENO, buf, 300);

        if (strncmp(buf, "exit", 4) == 0 || (end == 0))
        {
            write(STDOUT_FILENO, "Bye bye...", strlen("Bye bye..."));
            exit(0);
        }
        buf[end - 1] = '\0';

        if (clock_gettime(CLOCK_REALTIME, &start) == -1) // start time
        {
            perror("clock_gettime");
            exit(EXIT_FAILURE);
        }
        pid = fork();
        if (pid < 0)
        {
            wait(&status);
        }
        else if (pid == 0)
        { // child

            
            execlp(buf, buf, NULL);

            exit(EXIT_FAILURE);
        }
        else if (pid > 0)
        {
            wpid = wait(&status);
            if (wpid == -1)
            {
                perror("wait error:");
                exit(1);
            }

            if (clock_gettime(CLOCK_REALTIME, &stop) == -1) // end of time
            {
                perror("clock_gettime");
                exit(EXIT_FAILURE);
            }
            accum = (stop.tv_sec-start.tv_sec)+((stop.tv_nsec - start.tv_nsec)/NANOSECOND);


            if (WIFEXITED(status)) // normal exit
            {
                status_number = WEXITSTATUS(status);
                sprintf(string_status_number, "[exit:%i", status_number);
            }
            else // signal exit
            {
                status_number = WTERMSIG(status);
                sprintf(string_status_number, "[sign:%i ", status_number);
            }

            sprintf(string_accum, "|%lfs] %% ", accum);
            //write(STDOUT_FILENO, string_accum, strlen(string_accum));

            sprintf(enseash2, "enseash");
            strcat(enseash2, string_status_number);
            strcat(enseash2, string_accum);

            write(STDOUT_FILENO, enseash2, strlen(enseash2));
            sprintf(enseash2, " ");
        }
    }

    



}


int main()
{
    
    q1();
    //q2();
    //q3();
    //q4();
    q5();
    
}



