CC = clang
OUTPUT = build
NAME = app
EXE = $(OUTPUT)/$(NAME)

BACKEND-SRC = $(basename $(wildcard source/*.m))
BACKEND-OBJ = $(addprefix $(OUTPUT)/,$(addsuffix .o,$(notdir $(BACKEND-SRC))))
BACKEND = $(OUTPUT)/libSilicon.a

SRC = main.c
FLAGS = -O2 -std=c99 -ferror-limit=3
LIBS = $(BACKEND) -framework AppKit -framework Foundation -framework OpenGL -framework CoreVideo
INCLUDE = -I"include" -I"source"


all: $(OUTPUT) $(BACKEND) $(EXE) run

run:
	./$(EXE)

runExamples:
	@for f in $(shell ls examples/*.c); do make SRC=$${f}; rm -rf $(EXE); done

clean:
	rm $(BACKEND) $(EXE) $(BACKEND-OBJ)

$(EXE): $(SRC)
	$(CC) $(FLAGS) $(INCLUDE) $(SRC) $(LIBS) -o $@

$(BACKEND): $(BACKEND-OBJ)
	$(AR) -rcs $@ $^

$(OUTPUT)/%.o: source/%.m
	$(CC) $(FLAGS) $(INCLUDE) $^ -c -o $@

$(OUTPUT):
	mkdir $(OUTPUT)


install: $(BACKEND)
	sudo cp -r include/Silicon /usr/local/include/Silicon
	sudo cp -r $(BACKEND) /usr/local/lib/libSilicon.a

ICON=
generateApp:
	mkdir -p $(NAME).app $(NAME).app/Contents/MacOS $(NAME).app/Contents/Resources app.iconset
	cp $(EXE) $(NAME).app/Contents/MacOS/$(NAME)

ifeq ($(ICON),) # Makefile is dum with tabs.
else
	@cp $(ICON) app.iconset/icon.png
	iconutil -c icns -o $(NAME).app/Contents/Resources/app.icns app.iconset
	@rm -rf app.iconset
endif

	printf '\
	<?xml version="1.0" encoding="UTF-8"?>									\n\
	<!DOCTYPE plist PUBLIC "-//Apple//DTD PLIST 1.0//EN" "http://www.apple.com/DTDs/PropertyList-1.0.dtd">	\n\
	<plist version="1.0">											\n\
	<dict>													\n\
		<key>CFBundleExecutable</key>									\n\
		<string>$(NAME)</string>									\n\
														\n\
		<key>CFBundleIconFile</key>									\n\
		<string>app</string>										\n\
	</dict>													\n\
	</plist>' > $(NAME).app/Contents/Info.plist

	touch $(NAME).app