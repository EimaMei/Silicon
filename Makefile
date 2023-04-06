CC = clang
OUTPUT = build
NAME = gbtime
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

$(EXE): $(SRC) $(BACKEND)
	$(CC) $(FLAGS) $(INCLUDE) $(SRC) $(LIBS) -o $@

$(BACKEND): $(BACKEND-OBJ)
	$(AR) -rcs $@ $^

$(OUTPUT)/%.o: source/%.m
	$(CC) $(FLAGS) $(INCLUDE) $^ -c -o $@

$(OUTPUT):
	mkdir $(OUTPUT)

debug: $(EXE)
	lldb ./$(EXE)