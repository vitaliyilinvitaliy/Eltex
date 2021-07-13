OBJ=gcc -c $< -o $@ -ggdb3
OBJ_CURSES=gcc -c $<  -o $@ -ggdb3



text_editor: clean folders main

folders:
	mkdir bin
	mkdir build

main: build/main.o build/sig_winch.o build/window.o build/edit_text.o build/print_parameters.o build/open_file.o build/save_text.o build/get_file_name.o build/message.o build/clear_screen.o
	gcc build/main.o build/sig_winch.o build/window.o build/edit_text.o build/print_parameters.o  build/open_file.o build/save_text.o build/get_file_name.o build/message.o build/clear_screen.o -lncurses -o main -ggdb3 


build/main.o: main.c
	$(OBJ) 

build/sig_winch.o: sig_winch.c
	$(OBJ)

build/window.o: window.c
	$(OBJ)

build/edit_text.o: edit_text.c
	$(OBJ)

build/print_parameters.o: print_parameters.c
	$(OBJ)

build/open_file.o: open_file.c 
	$(OBJ)

build/save_text.o: save_text.c 
	$(OBJ)

build/get_file_name.o: get_file_name.c 
	$(OBJ)

build/message.o: message.c 
	$(OBJ)

build/clear_screen.o: clear_screen.c 
	$(OBJ)


clean:
	rm -rf bin
	rm -rf build
	rm -rf *.a 
	rm -rf main
	rm -rf *.so
	rm -rf *.txt
