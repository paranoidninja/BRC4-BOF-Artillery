CC = x86_64-w64-mingw32-gcc
CFLAGS = -m64 -Os -s -pedantic -nostdlib -fno-jump-tables -fdiagnostics-color=always -fno-ident -Wshadow -Wconversion -Wall
INCLUDES = -I includes
SRC_DIR = src
OBJ_DIR = bofs

SRC_FILES = $(wildcard $(SRC_DIR)/*.c)
OBJ_FILES = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC_FILES))

all: $(OBJ_FILES)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $(INCLUDES) -o $@ $<

clean:
	rm -f $(OBJ_DIR)/*.o
