# Makefile for SFML program

# Compiler
CC = g++

# Compiler flags
CFLAGS = -Wall -Wextra

# SFML libraries
SFML_LIBS = -lsfml-graphics -lsfml-window -lsfml-system

# Source file
SOURCE = sfml.cpp

# Output executable
OUTPUT = prog

all: $(OUTPUT)

$(OUTPUT): $(SOURCE)
	$(CC) $(CFLAGS) $(SOURCE) -o $(OUTPUT) $(SFML_LIBS)

clean:
	rm -f $(OUTPUT)
