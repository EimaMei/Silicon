LIBS = -framework Cocoa

example:
	make opengl
	make mac-load
	make hello-world
	make save-file
	make button
	make checkbox
	make combobox
	make menu
	make trackbar
	make basic

debug:
	gcc -g -Wall examples/general/basic.c -I./ -framework Cocoa -o basic
	./basic

button:
	gcc examples/controls/button.c -I./ -framework Cocoa -o button
checkbox:
	gcc examples/controls/checkbox.c -I./ -framework Cocoa -o checkbox
combobox:	
	gcc examples/controls/combobox.c -I./ -framework Cocoa -o combobox
menu:	
	gcc examples/controls/menu.c -I./ -framework Cocoa -o menu
trackbar:
	gcc examples/controls/trackbar.c -I./ -framework Cocoa -o trackbar

save-file:
	gcc examples/dialogs/save-file.c -I./ -framework Cocoa -o save-file

basic:
	gcc examples/general/basic.c -I./ -framework Cocoa -o basic
mac-load:
	gcc examples/general/mac-load.c -I./ -framework Cocoa -o mac-load
hello-world:
	gcc examples/general/hello-world.c -I./ -framework Cocoa -o hello-world
events:
	gcc examples/general/events.c -I./ -framework Cocoa -o events

opengl:
	gcc examples/graphics/opengl.c -I./ -framework Cocoa -framework OpenGL -framework CoreVideo -o opengl

runExamples:
	./opengl
	./mac-load
	./hello-world
	./save-file
	./button
	./checkbox
	./combobox
	./menu
	./trackbar
	./basic

clean:
	rm -f main.m opengl mac-load basic events menu trackbar checkbox combobox button save-file hello-world 