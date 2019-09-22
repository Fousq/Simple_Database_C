#ifndef COMMAND_H
#define COMMAND_H
#include "buffer.h"
#include <string.h>
#include "row.h"
#include "b-tree.h"

typedef enum {
    COMMAND_SUCCESS,
    UNRECOGNIZED_COMMAND
} CommandResult;

CommandResult exec_command(InputBuffer* input_buffer);
#endif