
SOURCES=OBJ_TEST.c PARENT_OBJ.c CHILD_OBJ.c DECEN_OBJ.c 
OBJECTS :=$(SOURCES:.c=.o)
OBJECTS := $(addprefix ../$(OBJ_FILE_DIR)/, $(OBJECTS))
EXECUTABLE=../$(EXE_BIN_DIR)/example


CFLAGS=-c -Wall -I../CxOOP_lib

all: $(SOURCES) $(EXECUTABLE)
    
$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

../$(OBJ_FILE_DIR)/%.o : %.c
	@echo $< 
	$(CC) $(LDFLAGS) $(CFLAGS) -c $< -o $@
	

clean:
	rm -r ../$(EXE_BIN_DIR) ../$(OBJ_FILE_DIR)