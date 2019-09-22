#ifndef BTREE_H
#define BTREE_H

#include <stdint.h>
#include <unistd.h>
#include "row.h"
#include "pager.h"
#include "table.h"

typedef enum {
    NODE_INTERNAL, NODE_LEAF
} NodeType;

//NODE HEADER LAYOUT
#define NODE_TYPE_SIZE sizeof(uint8_t)
#define NODE_TYPE_OFFSET 0
#define IS_ROOT_SIZE sizeof(uint8_t)
#define IS_ROOT_OFFSET 0
#define PARENT_POINTER_SIZE sizeof(uint32_t)
#define PARENT_POINTER_OFFSET (uint32_t) (NODE_TYPE_OFFSET + IS_ROOT_OFFSET)
#define COMMON_NODE_HEADER_SIZE (uint8_t) (NODE_TYPE_SIZE + IS_ROOT_SIZE + PARENT_POINTER_SIZE)

//LEAF NODE HEADER LAYOUT
#define LEAF_NODE_NUM_CELLS_SIZE sizeof(uint32_t)
#define LEAF_NODE_NUM_CELLS_OFFSET COMMON_NODE_HEADER_SIZE
#define LEAF_NODE_HEADER_SIZE (uint32_t)(COMMON_NODE_HEADER_SIZE + LEAF_NODE_NUM_CELLS_SIZE)

//LEAF NODE BODY LAYOUT
#define LEAF_NODE_KEY_SIZE sizeof(uint32_t)
#define LEAF_NODE_KEY_OFFSET 0
#define LEAF_NODE_VALUE_SIZE ROW_SIZE
#define LEAF_NODE_VALUE_OFFSET (uint32_t)(LEAF_NODE_KEY_OFFSET + LEAF_NODE_KEY_SIZE)
#define LEAF_NODE_CELL_SIZE (uint32_t)(LEAF_NODE_KEY_SIZE + LEAF_NODE_VALUE_SIZE)
#define LEAF_NODE_SPACE_FOR_CELLS  (uint32_t)(PAGE_SIZE - LEAF_NODE_HEADER_SIZE)
#define LEAF_NODE_MAX_CELLS (uint32_t)(LEAF_NODE_SPACE_FOR_CELLS / LEAF_NODE_CELL_SIZE)

uint32_t* leaf_node_num_cells(void* node);
void* leaf_node_cell(void* node, uint32_t cell_num);
uint32_t* leaf_node_key(void* node, uint32_t cell_num);
void* leaf_node_value(void* node, uint32_t cell_num);
void init_leaf_node(void* node);

#endif