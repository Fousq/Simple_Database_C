#ifndef TABLE_H
#define TABLE_H
#include "row.h"
#include "pager.h"

#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct
{
    uint32_t root_page_num;
    Pager* pager;
} Table;

typedef struct
{
    Table* table;
    uint32_t row_num;
    bool end_of_table;
} Cursor;

Table* db_open(const char* filename);
Cursor* table_start(Table* table);
void* cursor_value(Cursor* cursor);
void next(Cursor* cursor);
Cursor* table_end(Table* table);
void db_close(Table* table);

#endif