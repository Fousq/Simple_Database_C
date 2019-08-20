#ifndef ROW_H
#define ROW_H
#include <stdint.h>
#include <string.h>
#define EMAIL_COLUMN_SIZE 255
#define USERNAME_COLUMN_SIZE 32
#define size_of_attr(Struct, Attribute) sizeof(((Struct*)0)->Attribute)

typedef struct
{
    uint32_t id;
    char username[USERNAME_COLUMN_SIZE + 1];
    char email[EMAIL_COLUMN_SIZE + 1];
} Row;

#define ID_SIZE size_of_attr(Row, id)
#define USERNAME_SIZE size_of_attr(Row, username)
#define EMAIL_SIZE size_of_attr(Row, email)
#define ID_OFFSET 0
#define USERNAME_OFFSET (uint32_t)(ID_OFFSET + ID_SIZE)
#define EMAIL_OFFSET (uint32_t)(USERNAME_OFFSET + USERNAME_SIZE)
#define ROW_SIZE (uint32_t)(EMAIL_SIZE + USERNAME_SIZE + ID_SIZE)

void serialize_row(Row* source, void* destination);
void deserialize_row(void* source, Row* destination);

#endif