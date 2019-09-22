#ifndef STATEMENT_H
#define STATEMENT_H
#include "buffer.h"
#include "row.h"
#include "table.h"
#include "b-tree.h"

#include<string.h>
#include <stdio.h>

typedef enum {
    PREPARED_SUCCESS,
    STATEMENT_SYNTAX_ERROR,
    STATEMENT_TOO_LONG_STR,
    STATEMENT_NEGATIVE_VALUE_ERROR,
    UNRECOGNIZED_STATEMENT
} StatementResult;

typedef enum {
    SELECT,
    INSERT
} StatementType;

typedef enum {
    EXECUTE_SUCCESS,
    EXECUTE_FAIL
} ExecuteResult;

typedef struct 
{
    StatementType type;
    Row row_to_insert;
} Statement;

StatementResult prepared_statement(InputBuffer* input_buffer, Statement* statement);
ExecuteResult exec_select(Statement* statement, Table* table);
ExecuteResult exec_insert(Statement* statement, Table* table);
ExecuteResult exec_statement(Statement* statement, Table* table);

#endif