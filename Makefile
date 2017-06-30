# File to compile
#OBJS = 01_hello_SDL.cpp
NAME = basic_window

# Extension
EXT = .c

# Compiler to use
#CC = g++
CC = gcc

# Compiler flags
COMPILER_FLAGS = -w

# Linker flags
LINKER_FLAGS = -lSDL2

# Output filename
OBJ_NAME = 01_hello_SDL

all : $(OBJS)
	$(CC) $(NAME)$(EXT) $(LINKER_FLAGS) -o $(NAME)
