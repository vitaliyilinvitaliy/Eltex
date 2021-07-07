OBJ=gcc -c $< -o $@ -ggdb3

.PHONY: clean

calculator_static: clean folder_static calc_static main_static

folder_static:
	mkdir -p build
	mkdir -p libs_static

main_static: build/main.o
	gcc build/main.o -L./libs_static/ -lcalc  -o main_static -ggdb3


calc_static: libinterface.a liboperations.a
	ar crT libs_static/libcalc.a libs_static/liboperations.a libs_static/libinterface.a 



libinterface.a: build/interface.o build/clearscreen.o build/gotoxy.o build/box.o build/getscreensize.o build/button.o build/color.o build/keyboard.o build/display.o build/terminal.o build/displaylogic.o
	ar cr libs_static/libinterface.a build/interface.o build/clearscreen.o build/gotoxy.o build/box.o build/getscreensize.o build/button.o build/color.o build/keyboard.o build/display.o build/terminal.o build/displaylogic.o
	
liboperations.a: build/operations.o build/add.o build/minus.o build/mult.o build/div.o
	ar cr libs_static/liboperations.a build/add.o build/minus.o build/mult.o build/div.o build/operations.o

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
	rm -rf main_static
	rm -rf main
	rm -rf libs_static