.PHONY: all clean install

all: xls

clean:
	@rm -f *.o xls
	@echo all clean

install:
	@sudo cp xls /usr/bin
	@echo installed successfully
uninstall:
	@sudo rm /usr/bin/xls
	@echo uninstalled successfully
%.o: %.c
	@gcc -o $@ -c $<

main.o: main.c functions.h structures.h parser.h main.h
	@gcc -o main.o -c main.c

xls: main.o functions.o parser.o
	@gcc -o xls main.o functions.o parser.o -g