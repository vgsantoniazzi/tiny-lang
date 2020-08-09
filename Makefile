CC=g++
DOXYGEN=doxygen
CFLAGS=-std=c++11 -DLOGLEVEL=WARNING -pthread
LDFLAGS=
SOURCE_PATH=src
BIN_PATH=bin
DEPENDENCIES=src/**/*.cpp
SOURCE=src/Interpreter.cpp
EXECUTABLE=$(BIN_PATH)/tiny
SYSTEM_PATH=/usr/local/bin
FILE=examples/english.tl
FORMAT_EXECUTABLE=bin/format
TOKENS=tokens/english.yml

all: clean
	$(CC) $(CFLAGS) $(DEPENDENCIES) $(SOURCE) -o $(EXECUTABLE)

run:
	$(EXECUTABLE) $(FILE) $(TOKENS)

docs: docs.delete docs.generate

docs.delete:
	@rm -Rf docs

docs.generate:
	@$(DOXYGEN)

format:
	$(FORMAT_EXECUTABLE)

install:
	cp $(EXECUTABLE) $(SYSTEM_PATH)

clean:
	rm -f $(EXECUTABLE)
