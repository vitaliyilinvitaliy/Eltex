OBJ=gcc -c $< -o $@ -ggdb3

OBJ_DYN=gcc $< -fPIC -c -o $@ -ggdb3

LIBSO=gcc -shared $< -o $@ 

.PHONY: clean


calculator_dynamic: clean folder_dynamic operation_dynamic main_dynamic

folder_dynamic:
	mkdir -p build
	mkdir -p libs_static	
	mkdir -p libs_dynamic

main_dynamic: build/main.o interface build/add.o build/minus.o build/mult.o build/div.o
	gcc build/main.o -o main_dynamic -L./libs_static/ -linterface  -L./libs_dynamic/ -ladd -lmult -lminus -ldiv  -ggdb3

interface: build/interface.o build/clearscreen.o build/gotoxy.o build/box.o build/getscreensize.o build/button.o build/color.o build/keyboard.o build/display.o build/terminal.o build/displaylogic.o build/operations.o
	ar cr libs_static/libinterface.a build/interface.o build/clearscreen.o build/gotoxy.o build/box.o build/getscreensize.o build/button.o build/color.o build/keyboard.o build/display.o build/terminal.o build/displaylogic.o build/operations.o

operation_dynamic: build/add.o build/minus.o build/mult.o build/div.o libs_dynamic/libadd.so libs_dynamic/libminus.so libs_dynamic/libmult.so libs_dynamic/libdiv.so


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


libs_dynamic/libadd.so: build/add.o
	$(LIBSO)

libs_dynamic/libminus.so: build/minus.o
	$(LIBSO)

libs_dynamic/libmult.so: build/mult.o
	$(LIBSO)

libs_dynamic/libdiv.so: build/div.o
	$(LIBSO)

build/add.o: operations/add.c
	$(OBJ_DYN)

build/minus.o: operations/minus.c
	$(OBJ_DYN)

build/mult.o: operations/mult.c
	$(OBJ_DYN)

build/div.o: operations/div.c
	$(OBJ_DYN)





clean:
	rm -rf build
	rm -rf *.a 
	rm -rf main_dynamic
	rm -rf main
	rm -rf libs_dynamic
	rm -rf libs_static
	rm -rf *.so


#all: library.cpp main.cpp
#В таком случае:

#$@ оценивает all
#$< оценивает library.cpp
#$^ оценивает library.cpp main.cpp
