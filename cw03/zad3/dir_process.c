#include "dir_process.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <errno.h>

void list_all_files_by_content(char *path, const char *contains) {
    if (fork() == 0) {
        DIR *dir = opendir(path);
        if (dir == NULL) {
            char b[BUFFER_SIZE];
            snprintf(b, BUFFER_SIZE, "Failed to open %s", path);
            perror(b);
            exit(-1);
        }

        struct dirent *dirt;
        while ((dirt = readdir(dir)) != NULL) {
            const unsigned int size = strlen(path) + strlen(dirt->d_name) + 2;
            char *new_path = malloc(sizeof(char) * size);
            new_path = strcpy(new_path, path);
            new_path = strcat(new_path, "/");
            new_path = strcat(new_path, dirt->d_name);
            new_path[size - 1] = '\0';

            struct stat st;
            if (stat(new_path, &st) == -1) {
                char b[BUFFER_SIZE];
                snprintf(b, BUFFER_SIZE, "%d stat() error %s", errno, new_path);
                perror(b);
                exit(errno);
            }

            if (!S_ISDIR(st.st_mode) && S_ISREG(st.st_mode)) {
                if (file_contains(new_path, contains)) {
                    printf("%s\t%d\n", new_path, getpid());
                }
            }
            else if (strcmp(dirt->d_name, ".") != 0 && strcmp(dirt->d_name, "..") != 0 && S_ISDIR(st.st_mode)) {
                list_all_files_by_content(new_path, contains);
            }

            free(new_path);
        }
        
        closedir(dir);
        while (wait(NULL) > 0);
        fflush(stdout);
        exit(0);
    }  
}

bool file_contains(char *path, const char *str) {
    const int size = strlen(str);
    FILE *fp = fopen(path, "r");

    if (fp == NULL) {
        fprintf(stderr, "%s cannot be open (file_contains())\n", path);
        return false;
    }
    
    char *buffer = malloc(sizeof(char) * (size + 1));
    bool r = false;
    if (fread(buffer, sizeof(char), size, fp) > 0) {
        buffer[size] = '\0';
        r = strcmp(str, buffer) == 0 ? true : false;
    }

    free(buffer);
    fclose(fp);

    return r;
}