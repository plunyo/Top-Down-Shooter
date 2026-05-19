CC = clang

DEBUG ?= 1
TARGET = game

OBJ_DIR = build
SRC = $(shell find src -name "*.c")
OBJ = $(patsubst src/%.c, $(OBJ_DIR)/%.o, $(SRC))

CFLAGS = -g -Wall -Werror -Isrc

ifeq ($(DEBUG),1)
CFLAGS += -DDEBUG=1
endif

# -------------------------
# OS detection
# -------------------------
UNAME_S := $(shell uname -s)

# -------------------------
# pkg-config (raylib if available)
# -------------------------
PKG_CFLAGS := $(shell pkg-config --cflags raylib 2>/dev/null)
PKG_LIBS   := $(shell pkg-config --libs raylib 2>/dev/null)

ifneq ($(PKG_CFLAGS),)
CFLAGS += $(PKG_CFLAGS)
endif

# -------------------------
# linker flags
# IMPORTANT: split correctly
# -------------------------
LDFLAGS =
LDLIBS  =

ifeq ($(PKG_LIBS),)
# fallback manual linking

ifeq ($(UNAME_S),Darwin)
LDLIBS += -lraylib -lm
LDFLAGS += -L/usr/local/lib -L/opt/homebrew/lib
LDFLAGS += -framework OpenGL -framework Cocoa -framework IOKit -framework CoreVideo
else
LDLIBS += -lraylib -lm -lGL -lpthread -ldl -lrt -lX11
endif

else
LDLIBS += $(PKG_LIBS) -lm
endif

# -------------------------
# build rules
# -------------------------
all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(OBJ) -o $(TARGET) $(LDFLAGS) $(LDLIBS)

$(OBJ_DIR)/%.o: src/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR) $(TARGET) compile_commands.json

run: $(TARGET)
	./$(TARGET)

compile_commands: clean
	bear -- make

compile_commands_debug: clean
	bear -- make DEBUG=1

compile_debug: clean
	$(MAKE) DEBUG=1 all

.PHONY: all clean run compile_commands compile_commands_debug compile_debug