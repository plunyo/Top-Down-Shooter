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
# raylib flags (pkg-config first)
# -------------------------
PKG_CFLAGS := $(shell pkg-config --cflags raylib 2>/dev/null)
PKG_LIBS := $(shell pkg-config --libs raylib 2>/dev/null)

ifeq ($(PKG_CFLAGS),)
	# fallback include paths
	CFLAGS += -I/usr/local/include -I/opt/homebrew/include
else
	CFLAGS += $(PKG_CFLAGS)
endif

ifeq ($(PKG_LIBS),)
	# fallback libs per OS
	ifeq ($(UNAME_S),Darwin)
		LDFLAGS = -L/usr/local/lib -L/opt/homebrew/lib -lraylib \
		          -framework OpenGL -framework Cocoa -framework IOKit -framework CoreVideo -lm
	else
		LDFLAGS = -lraylib -lm -lGL -lm -lpthread -ldl -lrt -lX11
	endif
else
	LDFLAGS = $(PKG_LIBS)
endif

# -------------------------
# build rules
# -------------------------
all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(OBJ) -o $(TARGET) $(LDFLAGS)

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