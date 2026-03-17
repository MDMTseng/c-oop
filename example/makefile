
SOURCES=main.c Shape.c Circle.c Sphere.c
OBJECTS :=$(SOURCES:.c=.o)
OBJECTS := $(addprefix ../$(OBJ_FILE_DIR)/, $(OBJECTS))
EXECUTABLE=../$(EXE_BIN_DIR)/example


CFLAGS=-c -Wall -std=c99 -I../CxOOP_lib

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@ -lm

../$(OBJ_FILE_DIR)/%.o : %.c
	@echo $<
	$(CC) $(LDFLAGS) $(CFLAGS) -c $< -o $@


clean:
	rm -r ../$(EXE_BIN_DIR) ../$(OBJ_FILE_DIR)
