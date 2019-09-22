#include "buffer.h"
#include "command.h"
#include "statement.h"
#include "table.h"

#include<stdio.h>
#include<stdbool.h>
#include<string.h>

void print_prompt();

int main(int argc, char* argv[]) {
    InputBuffer* input_buffer = new_input_buffer();
    if (argc < 2) {
        printf("Usage: ./db [filename]\n");
        exit(EXIT_FAILURE);
    }
    char* filename = argv[1];
    Table* table = db_open(filename);
    while(true) {
        print_prompt();
        read_input(input_buffer);

        if (input_buffer->buffer[0] == '.') {
            switch (exec_command(input_buffer, table))
            {
            case COMMAND_SUCCESS:
                continue;
            case EXIT_COMMAND:
                db_close(table);
                close_input_buffer(input_buffer);
                exit(EXIT_SUCCESS);
                continue;
            case UNRECOGNIZED_COMMAND:
                printf("Unrecognized command %s\n", input_buffer->buffer);
                continue;
            default:
                continue;
            }
        }
        
        Statement statement;
        switch (prepared_statement(input_buffer, &statement))
        {
        case PREPARED_SUCCESS:
            break;
        case STATEMENT_SYNTAX_ERROR:
            printf("Syntax error on the quiery, cannot parse\n");
            continue;
        case STATEMENT_TOO_LONG_STR:
            printf("One of the string is too long to parse.\n");
            continue;
        case STATEMENT_NEGATIVE_VALUE_ERROR:
            printf("The value of id field must not be negative.\n");
            continue;
        case UNRECOGNIZED_STATEMENT:
            printf("Unrecognized statement %s\n", input_buffer->buffer);
            continue;
        default:
            break;
        }

        switch(exec_statement(&statement, table)) {
            case EXECUTE_SUCCESS:
                printf("Executed.\n");
                break;
            case EXECUTE_FAIL:
                printf("Execution of the quiery has failed.\n");
                break;
        }
    }
}

void print_prompt() {
    printf("db > ");
}
