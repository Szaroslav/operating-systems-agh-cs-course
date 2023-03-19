#ifndef _REVERSE_H
#define _REVERSE_H

#define BLOCK_SIZE 1024

void reverse_file_by_byte(char *, char *);
void reverse_file_by_block(char *, char *);

#endif // _REVERSE_H