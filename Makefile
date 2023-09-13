TARGET_EXEC := MonsterBattle

CC = gcc
CFLAGS = -Wall -Wextra -pedantic -std=c11
SRC_DIR = src
BUILD_DIR = build
RELEASE = $(BUILD_DIR)/$(TARGET_EXEC)

LDPATH = -Llibs/raylib
LDLIBS = -lraylib
INCLUDES = -Ilibs

ifeq ($(OS),Windows_NT)
	LDLIBS += -lopengl32 -lgdi32 -lwinmm
endif

ifeq ($(shell uname),Darwin)
	LDFLAGS += -Wl,-rpath,libs/raylib
endif

SRCS = $(wildcard $(SRC_DIR)/*.c)
OBJS = $(SRCS:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.o)

$(RELEASE): $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@ $(LDPATH) $(LDLIBS) $(LDFLAGS)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(BUILD_DIR):
	mkdir $(BUILD_DIR)

.PHONY: clean
clean:
	rm -rf $(BUILD_DIR)
