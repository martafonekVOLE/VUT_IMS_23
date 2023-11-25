CC = g++
CFLAGS = -g -O2
PROJECT = main
OBJECTS = main.o arg_parse.o
CLASSES = Classes

$(PROJECT): $(OBJECTS)
	$(CC) $(CFLAGS) -o $(PROJECT) $(PROJECT).o arg_parse.o -lsimlib -lm

$(PROJECT).o: $(PROJECT).cpp
	$(CC) $(CFLAGS) -c $(PROJECT).cpp -lsimlib -lm

arg_parse.o: arg_parse.cpp
	$(CC) $(CFLAGS) -c arg_parse.cpp -lsimlib -lm

classes: $(CLASSES)
	$(CC) $(CFLAGS) -c $(CLASSES)

clean:
	rm $(PROJECT) $(PROJECT).o arg_parse.o
