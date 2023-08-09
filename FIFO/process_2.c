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

    // Open pipe for reading
    fd = open("FIFO_1", O_RDONLY);
    if (fd == -1) {
        perror("open");
        exit(0);
    }
    //Reading The Message
    while (1) {
        read(fd, buff, sizeof(buff));
        printf("Message Recieved: %s", buff);
    }

    close(fd);

    return 0;
}



/*
  
            out put
-----------------------------------
Message Recieved: hi
Message Recieved: how are you


*/
