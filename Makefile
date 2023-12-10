CC = g++
CFLAGS = -g -O2
PROJECT = doprava
FILES = main.cpp arg_parse.cpp
CLASSES = Classes/*.cpp
FLAGS = -lsimlib -lm -std=c++1z -Wall -Wextra -Wpedantic

all:
	$(CC) $(CFLAGS) -o $(PROJECT) $(FILES) $(CLASSES) $(FLAGS)

run:
	./$(PROJECT)
	./$(PROJECT) $(ARGS)

clean:
	rm $(PROJECT) $(PROJECT).o arg_parse.o
