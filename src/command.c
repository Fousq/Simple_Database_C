#include "command.h"

void print_constants() {
    printf("ROW SIZE: %d\n", ROW_SIZE);
    printf("COMMON_NODE_HEADER_SIZE: %d\n",COMMON_NODE_HEADER_SIZE);
    printf("LEAF_NODE_HEADER_SIZE: %d\n", LEAF_NODE_HEADER_SIZE);
    printf("LEAF_NODE_CELL_SIZE: %d\n", LEAF_NODE_CELL_SIZE);
    printf("LEAF_NODE_SPACE_FOR_CELLS: %d\n", LEAF_NODE_SPACE_FOR_CELLS);
    printf("LEAF_NODE_MAX_CELLS: %d\n", LEAF_NODE_MAX_CELLS);
}

void print_leaf_node(void* node) {
    uint32_t num_cells = *leaf_node_num_cells(node);
    printf("leaf (size %d)\n", num_cells);
    for (uint32_t i = 0; i < num_cells; i++) {
        uint32_t key = *leaf_node_key(node, i);
        printf(" - %d : %d\n", i, key);
    }
}

CommandResult exec_command(InputBuffer* input_buffer, Table* table) {
    if (strcmp(input_buffer->buffer, ".exit") == 0) {
        return EXIT_COMMAND;
    } else if (strcmp(input_buffer->buffer, ".constants") == 0) {
        print_constants();
        return COMMAND_SUCCESS;
    } else if (strcmp(input_buffer->buffer, ".btree") == 0) {
        print_leaf_node(get_page(table->pager, 0));
        return COMMAND_SUCCESS;
    } else {
        return UNRECOGNIZED_COMMAND;
    }
}
