#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>

int main() {
    int fd;
    char buff[100];

    //create Fifo with name FIFO_1
    if (mkfifo("FIFO_1", 0666) == -1) {
        perror("mkfifo");
        exit(0);
    }

    //open pipe for writing
    fd = open("FIFO_1", O_WRONLY);
    if (fd == -1) {
        perror("open");
        exit(0);
    }

    while (1) {
        printf("Enter Message to send: ");
        fgets(buff, sizeof(buff), stdin);
        write(fd, buff, strlen(buff));
    }

    close(fd);
    unlink("FIFO_1");

    return 0;
}


/*
 *
 *
       out put
------------------------------
Enter Message to send: hi
Enter Message to send: how are you


*/
