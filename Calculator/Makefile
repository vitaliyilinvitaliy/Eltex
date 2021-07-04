OBJ=gcc -c $< -o $@ -ggdb3

.PHONY: clean

calculator: folder calc main

folder:
	mkdir -p build
	mkdir -p libs

main: build/main.o
	gcc build/main.o -L./libs/ -lcalc  -o main -ggdb3

calc: libinterface.a liboperations.a
	ar crT libs/libcalc.a libs/liboperations.a libs/libinterface.a 

libinterface.a: build/interface.o build/clearscreen.o build/gotoxy.o build/box.o build/getscreensize.o build/button.o build/color.o build/keyboard.o build/display.o build/terminal.o build/displaylogic.o
	ar cr libs/libinterface.a build/interface.o build/clearscreen.o build/gotoxy.o build/box.o build/getscreensize.o build/button.o build/color.o build/keyboard.o build/display.o build/terminal.o build/displaylogic.o
	
liboperations.a: build/operations.o build/add.o build/minus.o build/mult.o build/div.o
	ar cr libs/liboperations.a build/add.o build/minus.o build/mult.o build/div.o build/operations.o

build/main.o: main.c
	$(OBJ)

build/interface.o: interface/interface.c
	$(OBJ)

build/clearscreen.o: interface/clearscreen.c
	$(OBJ)
	
build/gotoxy.o: interface/gotoxy.c
	$(OBJ)

build/box.o: interface/box.c
	$(OBJ)

build/getscreensize.o: interface/getscreensize.c
	$(OBJ)

build/button.o: interface/button.c
	$(OBJ)

build/color.o: interface/color.c
	$(OBJ)

build/keyboard.o: interface/keyboard.c
	$(OBJ)

build/display.o: interface/display.c
	$(OBJ)

build/terminal.o: interface/terminal.c
	$(OBJ)

build/displaylogic.o: interface/displaylogic.c
	$(OBJ)



build/operations.o: operations/operation.c 
	$(OBJ)

build/add.o: operations/add.c
	$(OBJ)

build/minus.o: operations/minus.c
	$(OBJ)

build/mult.o: operations/mult.c
	$(OBJ)

build/div.o: operations/div.c
	$(OBJ)

clean:
	rm -rf build
	rm -rf *.a 
	rm -rf main
	rm -rf libs