LIBS = -framework Cocoa
all:
	gcc main.c $(LIBS) -Wall

debug:
	gcc main.c $(LIBS) -Wall
	./a.out

objc:
	cp main.c main.m
	gcc main.m $(LIBS) -Wall
	./a.out