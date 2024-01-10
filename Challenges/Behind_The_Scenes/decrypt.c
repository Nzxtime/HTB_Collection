#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <string.h>
#include <ctype.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>




int main() {
    char *path = "flag.enc";
    FILE *input_file = fopen(path, "rb");
    unsigned int time;
    void *buffer_address;
    int random_1;
    unsigned int random_2;

    fseek(input_file, 0, 2);
    size_t file_size = ftell(input_file);
    buffer_address = malloc(file_size);
    fseek(input_file, 0, 0);
    fread(&time, 1, 4, input_file);
    fprintf(stdout, "time: %i\n", time);
    fread(buffer_address, file_size, 1, input_file);
    fclose(input_file);
    fprintf(stdout, "Data encrypted: %ld\n!", (long) buffer_address);
    srand(time);

    for (int i = 0; i < (long) file_size; i++) {
        random_1 = rand();
        *(unsigned char *)((long)buffer_address + i) = *(unsigned char *)((long)buffer_address + i) ^ (char)random_1;
        random_2 = rand();
        random_2 = random_2 & 7;
        *(unsigned char *)((long)buffer_address + i) = *(unsigned char *)((long)buffer_address + i) >> (char)random_1 &
            *(unsigned char *)((long)buffer_address + i) << 8 + (char)random_1;
        fprintf(stdout, "%x", (unsigned char) random_2);
    }
    
    fprintf(stdout, "!\nData decrypted: %ld\n", (long) buffer_address);


    return EXIT_SUCCESS;
}