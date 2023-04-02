CC = clang
OUTPUT = build
NAME = gbtime
EXE = $(OUTPUT)/$(NAME)

BACKEND-SRC = $(basename $(wildcard source/*.m))
BACKEND-OBJ = $(addprefix $(OUTPUT)/,$(addsuffix .o,$(notdir $(BACKEND-SRC))))
BACKEND = $(OUTPUT)/libESGL.a

SRC = main.c
FLAGS = -O2 -std=c99
LIBS = $(BACKEND) -framework AppKit -framework Foundation -framework OpenGL -framework CoreVideo
INCLUDE = -I"include" -I"source"


all: $(OUTPUT) $(BACKEND) $(EXE) run

run:
	./$(EXE)

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