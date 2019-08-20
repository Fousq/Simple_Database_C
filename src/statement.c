#include "statement.h"

StatementResult prepared_insert(InputBuffer* input_buffer, Statement* statement) {
    statement->type = INSERT;
    
    char* keywords = strtok(input_buffer->buffer, " ");
    char* id_string = strtok(NULL, " ");
    char* username = strtok(NULL, " ");
    char* email = strtok(NULL, " ");

    if (id_string == NULL || username == NULL || email == NULL) {
        return STATEMENT_SYNTAX_ERROR;
    }

    if (strlen(email) > EMAIL_COLUMN_SIZE || strlen(username) > USERNAME_COLUMN_SIZE) {
        return STATEMENT_TOO_LONG_STR;
    }

    int id = atoi(id_string);
    if (id < 0) {
        return STATEMENT_NEGATIVE_VALUE_ERROR;
    }
    statement->row_to_insert.id = id;
    strcpy(statement->row_to_insert.username, username);
    strcpy(statement->row_to_insert.email, email);

    return PREPARED_SUCCESS;
}

StatementResult prepared_statement(InputBuffer* input_buffer, Statement* statement) {
    if (strncmp(input_buffer->buffer, "select", 6) == 0) {
        statement->type = SELECT;
        return PREPARED_SUCCESS;
    } else if (strncmp(input_buffer->buffer, "insert", 6) == 0) {
        return prepared_insert(input_buffer, statement);
    }

    return UNRECOGNIZED_STATEMENT;
}

ExecuteResult exec_select(Statement* statement, Table* table) {
    Row row;
    
    Cursor* cursor = table_start(table);
    while(!(cursor->end_of_table)) {
        deserialize_row(cursor_value(cursor), &row);
        printf("(%d, %s, %s)\n", row.id, row.username, row.email);
        next(cursor);
    }

    free(cursor);

    return EXECUTE_SUCCESS;
}

ExecuteResult exec_insert(Statement* statement, Table* table) {
    if (table->num_rows > TABLE_MAX_ROWS) {
        return EXECUTE_FAIL;
    }

    Row* row = &(statement->row_to_insert);

    Cursor* cursor = table_end(table);
    serialize_row(row, cursor_value(cursor));
    table->num_rows++;

    free(cursor);

    return EXECUTE_SUCCESS;
}

ExecuteResult exec_statement(Statement* statement, Table* table) {
    switch (statement->type)
    {
    case SELECT:
        return exec_select(statement, table);
    case INSERT:
        return exec_insert(statement, table);
    default:
        break;
    }
}
