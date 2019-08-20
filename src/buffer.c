#include "buffer.h"

InputBuffer* new_input_buffer() {
    InputBuffer* input_buffer = (InputBuffer*) malloc(sizeof(InputBuffer));
    input_buffer->buffer = NULL;
    input_buffer->buffer_length = 0;
    input_buffer->input_length = 0;

    return input_buffer;
}

void read_input(InputBuffer* input_buffer) {
    ssize_t byte_reads = getline(&(input_buffer->buffer),&(input_buffer->buffer_length), stdin);

    if (byte_reads <= 0) {
        printf("ERROR on reading");
        exit(EXIT_FAILURE);
    }

    input_buffer->buffer_length = byte_reads - 1;
    input_buffer->buffer[byte_reads - 1] = 0;
}

void close_input_buffer(InputBuffer* input_buffer) {
    free(input_buffer->buffer);
    free(input_buffer);
}
