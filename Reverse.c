#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_BUFFER_SIZE 1024

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Error: Exefile, inputfile , outputfile");
        return 1;
    }

    char *input_file_name = argv[1];
    char *output_file_name = argv[2];

    FILE *input_file = fopen(input_file_name, "r");
    if (input_file == NULL) {
        perror("Error opening input file");
        return 1;
    }

    FILE *output_file = fopen(output_file_name, "w");
    if (output_file == NULL) {
        perror("Error opening output file");
        fclose(input_file);
        return 1;
    }

    char buffer[MAX_BUFFER_SIZE];
    size_t read_bytes, write_bytes;
    long int position;
    fseek(input_file, 0, SEEK_END);
    position = ftell(input_file);

    while (position) {
        size_t read_size = (position < MAX_BUFFER_SIZE) ? position : MAX_BUFFER_SIZE;
        position -= read_size;
        fseek(input_file, position, SEEK_SET);
        read_bytes = fread(buffer, 1, read_size, input_file);

        for (size_t i = read_bytes; i > 0; i--) {
            fputc(buffer[i - 1], output_file);
        }
    }

    fclose(input_file);
    fclose(output_file);

    printf("Content from '%s' has been reversed and written to '%s'.\n", input_file_name, output_file_name);

    return 0;
}

