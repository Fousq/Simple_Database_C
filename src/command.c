#include "command.h"

CommandResult exec_command(InputBuffer* input_buffer) {
    if (strcmp(input_buffer->buffer, ".exit") == 0) {
        return COMMAND_SUCCESS;
    } else {
        return UNRECOGNIZED_COMMAND;
    }
}
