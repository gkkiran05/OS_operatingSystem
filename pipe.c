#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    int pipefd[2];
    int pid;
    char buf[100];
    
    if(pipe(pipefd)== -1)
    {
        perror("pipe");
        exit(0);
    }
    
    char *message = "hello pipe !\n";
    
    if(write(pipefd[1],message , strlen(message) + 1) == -1)
    {
        perror("write");
        exit(0);
    }
    close(pipefd[1]);
    
    if(read(pipefd[0], buf, sizeof(buf)) == -1)
    {
        perror("read");
        exit(0);
    }
    
    printf("Read From Pipe : %s\n", buf);
    
    return 0;
}



/*
           out put
---------------------------------
Read From Pipe : hello pipe !


*/
