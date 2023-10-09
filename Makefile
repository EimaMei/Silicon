LIBS = -framework Cocoa
all:
	gcc main.c $(LIBS) -Wall
	make opengl

debug:
	gcc main.c $(LIBS) -Wall
	./a.out

opengl:
	gcc examples/graphics/opengl.c -I./ -framework Cocoa -framework OpenGL -framework CoreVideo -o opengl

objc:
	cp main.c main.m
	gcc main.m $(LIBS) -Wall
	./a.out

clean:
	rm -f main.m opengl ./a.out