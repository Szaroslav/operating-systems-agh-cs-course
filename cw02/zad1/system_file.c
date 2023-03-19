#include "system_file.h"
#include <string.h>
#include <fcntl.h>
#include <unistd.h>

void sf_replace_chars(char *input_file, char *output_file, char from, char to) {
    int input_fd = open(input_file, O_RDONLY);
    int output_fd = open(output_file, O_WRONLY | O_CREAT | O_TRUNC, S_IRWXU);
    char buffer;

    while (read(input_fd, &buffer, sizeof(char)) != 0) {
        if (buffer == from) {
            buffer = to;
        }
        write(output_fd, &buffer, sizeof(char));
    }

    close(input_fd);
    close(output_fd);
}