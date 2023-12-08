#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <wait.h>
#include <time.h>


#define READNUMER 300
#define NANOSECOND 1000000000.

char buf[READNUMER];
ssize_t nread;
size_t len = 0;

int status;
int end;
char *enseash = "enseash % ";
char *welcome = "Bienvenue dans le Shell ENSEA.\nPour quitter, tapez 'exit'.\nenseash % ";



int status_number = 1;
char status_buf[READNUMER] = {0};
char enseash2[READNUMER] = "enseash ";
char string_status_number[READNUMER];

struct timespec start, stop;
double accum;
char string_accum[READNUMER];





pid_t pid, wpid;

void printWelcomeMessage() {
    char *welcome = "Bienvenue dans le Shell ENSEA.\nPour quitter, tapez 'exit'.\nenseash % ";
    write(STDOUT_FILENO, welcome, strlen(welcome));
}


void q1(){
    
    
    char *line = NULL;
    size_t len = 0;
    printWelcomeMessage();

}

void q5()
{

    while (1)
    {

        end = read(STDIN_FILENO, buf, 300);

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
            

            sprintf(enseash2, "enseash");
            strcat(enseash2, string_status_number);
            strcat(enseash2, string_accum);

            write(STDOUT_FILENO, enseash2, strlen(enseash2));
            sprintf(enseash2, " ");
        }
    }
 

}


int main ()
{
    q1();
    q5();

}