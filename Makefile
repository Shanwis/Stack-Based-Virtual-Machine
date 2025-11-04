SRC = src/virtualMachine.c src/main.c src/assembler.c
CC = gcc
CFLAG = -Iinclude
OBJ = $(SRC:.c=.o)
TARGET = virtualMachine

FILE ?= program.asm

.PHONY: all clean run

all:$(TARGET)

$(TARGET):$(OBJ)
	$(CC) $(OBJ) -o $(TARGET)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

run:$(TARGET)
	./$(TARGET) $(FILE)

clean:
	rm -f $(OBJ) $(TARGET)