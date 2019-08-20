#ifndef BUFFER_H
#define BUFFER_H

#include<stddef.h>
#include<unistd.h>
#include<stdlib.h>
#include<stdio.h>

typedef struct 
{
    char* buffer;
    size_t buffer_length;
    ssize_t input_length;
} InputBuffer;

InputBuffer* new_input_buffer();
void read_input(InputBuffer* input_buffer);
void close_input_buffer(InputBuffer* buffer);
#endif