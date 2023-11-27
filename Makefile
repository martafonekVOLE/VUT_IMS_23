CC = g++
CFLAGS = -g -O2
PROJECT = doprava
OBJECTS = main.cpp arg_parse.cpp
CLASSES = Classes

$(PROJECT): $(OBJECTS)
	$(CC) $(CFLAGS) -o $(PROJECT) $(OBJECTS) $(CLASSES)/*.cpp -lsimlib -lm

clean:
	rm $(PROJECT) $(PROJECT).o arg_parse.o
