OBJ=gcc -c $< -o $@ -ggdb3
OBJ_CURSES=gcc -c $<  -o $@ -ggdb3

text_editor: clean folders main


 main: build/main.o build/sig_winch.o build/window.o build/size_window.o build/dir_list.o build/print_dir_list.o build/subwindow.o build/color_string.o build/clear_subwindow.o build/start_process.o
	gcc build/main.o  build/sig_winch.o build/window.o build/size_window.o build/dir_list.o build/print_dir_list.o build/subwindow.o build/color_string.o build/clear_subwindow.o build/start_process.o -lncurses -o main -ggdb3

build/main.o: main.c
	$(OBJ)


build/window.o: window.c
	$(OBJ)

build/sig_winch.o: sig_winch.c
	$(OBJ)

build/size_window.o: size_window.c
	$(OBJ)

build/dir_list.o: dir_list.c
	$(OBJ)

build/print_dir_list.o: print_dir_list.c
	$(OBJ)

build/color_string.o: color_string.c
	$(OBJ)

build/subwindow.o: subwindow.c
	$(OBJ)

build/clear_subwindow.o: clear_subwindow.c
	$(OBJ)

build/start_process.o: start_process.c
	$(OBJ)


clean:
	rm -rf bin
	rm -rf build
	rm -rf *.a 
	rm -rf main
	rm -rf *.so
	rm -rf *.txt
	rm -rf *.o

folders:
	mkdir bin
	mkdir build