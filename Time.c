#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void wait_one_second() {
    // Function to wait for one second.
    time_t start_time = time(NULL);
    while (time(NULL) == start_time) {}
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Error:give exefile , file , time in minute");
        return 1;
    }

    char *file_name = argv[1];
    int time_in_minutes = atoi(argv[2]);
    
    FILE *file = fopen(file_name, "w");
    if (file == NULL) {
        perror("Error opening file");
        return 1;
    }

    time_t start_time = time(NULL);
    time_t end_time = start_time + (time_in_minutes * 60);

    while (time(NULL) < end_time) {
        time_t current_time = time(NULL);
        fprintf(file, "%s", ctime(&current_time));
        fflush(file);
        wait_one_second();
    }

    fclose(file);
    printf("Data written to %s for %d minutes.\n", file_name, time_in_minutes);

    return 0;
}

