LIBS = -framework Foundation
all:
	gcc main.c $(LIBS)
	./a.out

objc:
	cp main.c main.m
	gcc main.m $(LIBS)
	./a.out
	rm main.m