CC = gcc
SRC_DIR = src
INCLUDE_DIR = include
BIN_DIR = bin

CFLAGS = -I${INCLUDE_DIR}/
COMPILE = ${CC} ${CFLAGS} -c $^ -o $@

SRC_FILES = $(wildcard ${SRC_DIR}/*.c)
SRC_OBJS = $(patsubst $(SRC_DIR)/%.c, $(BIN_DIR)/%.o, $(SRC_FILES))

$(BIN_DIR)/%.o: $(SRC_DIR)/%.c
	$(COMPILE)

.phony: all src linking clean

all: src linking

src: $(SRC_OBJS)
	@echo "Object files created."

clean:
	@echo "Cleaning up..."
	@rm -rf ${BIN_DIR}/*

OBJS = ${BIN_DIR}/buffer.o \
		${BIN_DIR}/command.o \
		${BIN_DIR}/pager.o \
		${BIN_DIR}/row.o \
		${BIN_DIR}/statement.o \
		${BIN_DIR}/table.o \
		${BIN_DIR}/main.o

LINK_EXE = ${CC} -o db ${OBJS}

linking: 
	@echo "Linking the objects file..."
	$(LINK_EXE)
