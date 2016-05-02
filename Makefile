OBJ=denman
CC=gcc
SOURCES=*.c
OBJCT=$(SOURCES:.c=.o)
INSTD=/usr/bin/

all:
	@echo "Start make [$(OBJ)]"
	$(CC) $(SOURCES) -o $(OBJ)
	@echo "Make finished"

clean :
	rm -f *.o $(OBJ)

install: $(OBJ)
	@echo "Start installing [$(OBJ)] to [$(INSTD)]"
	cp $(OBJ) $(INSTD)
	@echo "Installing finished"

uninstall:
	@echo "Uninstall [$(OBJ)] from [$(INSTD)]"
	rm -f $(INSTD)$(OBJ)

