#ifndef COMMAND_H
#define COMMAND_H
#include "buffer.h"
#include <string.h>

typedef enum {
    COMMAND_SUCCESS,
    UNRECOGNIZED_COMMAND
} CommandResult;

CommandResult exec_command(InputBuffer* input_buffer);
#endif