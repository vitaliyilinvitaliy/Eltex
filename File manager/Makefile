OBJ=gcc -c $< -o $@ -ggdb3
OBJ_CURSES=gcc -c $<  -o $@ -ggdb3

text_editor: clean folders main


main: build/main.o build/sig_winch.o build/window.o build/size_window.o
	gcc build/main.o  build/sig_winch.o build/window.o build/size_window.o -lncurses -o main -ggdb3

build/main.o: main.c
	$(OBJ)

build/window.o: window.c
	$(OBJ)

build/sig_winch.o: sig_winch.c
	$(OBJ)

build/size_window.o: size_window.c
	$(OBJ)


clean:
	rm -rf bin
	rm -rf build
	rm -rf *.a 
	rm -rf main
	rm -rf *.so
	rm -rf *.txt

folders:
	mkdir bin
	mkdir build