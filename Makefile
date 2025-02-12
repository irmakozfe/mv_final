CC = gcc
CFLAGS = -Wall -Wextra -std=c11

TARGET = mv

SRC_DIR = src
SOURCES = $(SRC_DIR)/main.c $(SRC_DIR)/file_utils.c $(SRC_DIR)/linked_list.c $(SRC_DIR)/move_utils.c $(SRC_DIR)/globals.c

OBJECTS = $(SOURCES:.c=.o)

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(TARGET) $(OBJECTS)

.PHONY: all clean