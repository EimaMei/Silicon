LIBS = -framework Cocoa
ARGS = -g -o0 -Wall

example:
	make opengl
	make mac-load
	make hello-world
	make gamepad
	make save-file
	make button
	make checkbox
	make combobox
	make menu
	make trackbar
	make basic
	make iphone

debug:
	gcc $(ARGS) examples/general/basic.c -I./ -framework Cocoa -o basic
	./basic

button:
	gcc $(ARGS) examples/controls/button.c -I./ -framework Cocoa -o button
checkbox:
	gcc $(ARGS) examples/controls/checkbox.c -I./ -framework Cocoa -o checkbox
combobox:	
	gcc $(ARGS) examples/controls/combobox.c -I./ -framework Cocoa -o combobox
menu:	
	gcc $(ARGS) examples/controls/menu.c -I./ -framework Cocoa -o menu
trackbar:
	gcc $(ARGS) examples/controls/trackbar.c -I./ -framework Cocoa -o trackbar

save-file:
	gcc $(ARGS) examples/dialogs/save-file.c -I./ -framework Cocoa -o save-file

basic:
	gcc $(ARGS) examples/general/basic.c -I./ -framework Cocoa -o basic
mac-load:
	gcc $(ARGS) examples/general/mac-load.c -I./ -framework Cocoa -o mac-load
hello-world:
	gcc $(ARGS) examples/general/hello-world.c -I./ -framework Cocoa -o hello-world
gamepad:
	gcc $(ARGS) examples/general/gamepad.c -I./ -framework Cocoa -framework IOKit -o gamepad
events:
	gcc $(ARGS) examples/general/events.c -I./ -framework Cocoa -o events

opengl:
	gcc $(ARGS) examples/graphics/opengl.c -I./ -framework Cocoa -framework OpenGL -framework CoreVideo -o opengl

iphone:
	gcc $(ARGS) examples/iphone/print.c -I./ -framework Cocoa -o iphone_print

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
	./iphone_print

clean:
	rm -r -f main.m opengl mac-load basic events menu trackbar checkbox combobox button save-file hello-world iphone_print *.dSYM