OBJ=mkdeskli
CC=gcc
SOURCES=*.c
OBJCT=$(SOURCES:.c=.o)
INSTD=/usr/bin/
BUILD=build/

all:
	@echo "Start make [$(OBJ)]"
	$(CC) $(SOURCES) -o $(BUILD)$(OBJ)
	#mv $(OBJ) $(BUILD)
	@echo "Make finished"

clean :
	rm -f *.o $(BUILD)$(OBJ)

install: $(OBJ)
	@echo "Start installing [$(OBJ)] to [$(INSTD)]"
	cp $(BUILD)$(OBJ) $(INSTD)
	@echo "Installing finished"

uninstall:
	@echo "Uninstall [$(OBJ)] from [$(INSTD)]"
	rm -f $(INSTD)$(OBJ)

