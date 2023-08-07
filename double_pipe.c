#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    int pipefd1[2]; //parent to child communication
    int pipefd2[2]; //child to parent communication
    int pid;
    char buf[100];

    if (pipe(pipefd1) == -1 || pipe(pipefd2) == -1)
    {
        perror("pipe");
        exit(1);
    }

    pid = fork();

    if (pid < 0)
    {
        perror("fork");
        exit(1);
    }

    if (pid == 0) // Child process
    {
        close(pipefd1[1]); // Close the write end of Pipe 1 in the child process
        close(pipefd2[0]); // Close the read end of Pipe 2 in the child process

        char *message_to_child = "Hello from Parent!";
        if (write(pipefd2[1], message_to_child, strlen(message_to_child) + 1) == -1)
        {
            perror("write");
            exit(1);
        }

        char message_from_parent[100];
        if (read(pipefd1[0], message_from_parent, sizeof(message_from_parent)) == -1)
        {
            perror("read");
            exit(1);
        }

        printf("Child received from Parent: %s\n", message_from_parent);
    }
    else // Parent process
    {
        close(pipefd1[0]); // Close the read end of Pipe 1 in the parent process
        close(pipefd2[1]); // Close the write end of Pipe 2 in the parent process

        char *message_to_parent = "Hello from Child!";
        if (write(pipefd1[1], message_to_parent, strlen(message_to_parent) + 1) == -1)
        {
            perror("write");
            exit(1);
        }

        char message_from_child[100];
        if (read(pipefd2[0], message_from_child, sizeof(message_from_child)) == -1)
        {
            perror("read");
            exit(1);
        }

        printf("Parent received from Child: %s\n", message_from_child);
    }

    return 0;
}



/*
           out put
--------------------------------------
Child received from Parent: Hello from Child!
Parent received from Child: Hello from Parent!


*/
