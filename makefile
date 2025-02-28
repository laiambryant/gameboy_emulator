CC := gcc
CFLAGS := -Wall -Iinclude -ISDL/include
LDFLAGS := -LSDL/build -lSDL3

SRC := $(wildcard src/*.c)
OBJ := $(SRC:.c=.o)
TARGET := gameboy_emulator

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(OBJ) -o $@ $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(TARGET)

run: $(TARGET)
	export LD_LIBRARY_PATH=SDL/build && ./$(TARGET)