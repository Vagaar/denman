OBJ=mkdeskli
CC=gcc
SOURCES=*.c
OBJCT=$(SOURCES:.c=.o)
INSTD=/usr/bin/

all:
	@echo "Start make [$(OBJ)]"
	$(CC) $(SOURCES) -o $(OBJ)
	@echo "Make finish"

clean :
	rm -f *.o $(OBJ)

install: $(OBJ)
	@echo "Start installing [$(OBJ)] to [$(INSTD)]"
	cp $(OBJ) $(INSTD)
	@echo "Installing finish"

uninstall:
	@echo "Uninstall [$(OBJ)] from [$(INSTD)]"
	rm -f $(INSTD)$(OBJ)

