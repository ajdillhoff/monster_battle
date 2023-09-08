CC = gcc
CFLAGS = -Wall -Wextra -pedantic -std=c11
SRC_DIR = src
BUILD_DIR = build
TARGET = monster_battle

LDPATH = -L/usr/local/lib
LDLIBS = -lraylib

SRCS = $(wildcard $(SRC_DIR)/*.c)
OBJS = $(SRCS:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.o)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@ $(LDPATH) $(LDLIBS)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR):
	mkdir $(BUILD_DIR)

.PHONY: clean
clean:
	rm -rf $(BUILD_DIR) $(TARGET)
