OBJ=gcc -c $< -o $@ -ggdb3

text_editor: clean folders main

 
main: build/main.o build/loader.o build/fill_magazine.o build/buyer.o
	gcc build/main.o build/loader.o build/fill_magazine.o build/buyer.o -lpthread -o main -ggdb3

build/main.o: main.c
	$(OBJ)

build/loader.o: loader.c
	$(OBJ)

build/fill_magazine.o: fill_magazine.c
	$(OBJ)

build/buyer.o: buyer.c
	$(OBJ)


clean:
	rm -rf build
	rm -rf *.a 
	rm -rf main
	rm -rf *.so
	rm -rf *.txt
	rm -rf *.o

folders:
	mkdir build