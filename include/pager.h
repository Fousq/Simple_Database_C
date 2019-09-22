#ifndef PAGER_H
#define PAGER_H
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>

#define PAGE_SIZE 4096
#define TABLE_MAX_PAGES 100
#define ROWS_PRE_PAGE (uint32_t)(PAGE_SIZE / ROW_SIZE)
#define TABLE_MAX_ROWS TABLE_MAX_PAGES * ROWS_PRE_PAGE


typedef struct
{
    int file_descriptor;
    uint32_t file_length;
    void* pages[TABLE_MAX_PAGES];
    uint32_t num_pages;
} Pager;

Pager* pager_fopen(const char* filename);
void* get_page(Pager* pager, uint32_t page_num);
void pager_flush(Pager* pager, uint32_t page_num);

#endif