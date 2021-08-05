OBJ=gcc -c $< -o $@ -ggdb3
B=build/

chat: clean folders client


client: build/client.o build/sig_winch.o build/interface.o build/window_chat.o build/window_input.o build/size_window.o build/term.o build/init_color.o build/registration.o build/message.o build/receive_message_system_v.o build/receive_message_posix.o build/send_message_system_v.o build/send_message_posix.o build/send_message_shmem_system_v.o build/receive_message_shmem_system_v.o build/send_message_shmem_posix.o build/receive_message_shmem_posix.o
	gcc build/client.o  build/sig_winch.o build/interface.o build/window_chat.o build/window_input.o build/size_window.o build/term.o build/init_color.o build/registration.o  build/message.o build/receive_message_system_v.o build/receive_message_posix.o build/send_message_system_v.o build/send_message_posix.o build/send_message_shmem_system_v.o build/receive_message_shmem_system_v.o build/send_message_shmem_posix.o build/receive_message_shmem_posix.o -lncurses -lpthread -lrt -o client -ggdb3

build/client.o: client.c
	$(OBJ)


build/window.o: ./window/window.c
	$(OBJ)

build/sig_winch.o: ./terminal/sig_winch.c
	$(OBJ)

build/size_window.o: ./terminal/size_window.c
	$(OBJ)

build/term.o: ./terminal/term.c
	$(OBJ)

build/interface.o: ./interface/interface.c
	$(OBJ)

build/window_chat.o: ./interface/chat/window_chat.c
	$(OBJ)

build/window_input.o: ./interface/input/window_input.c
	$(OBJ)

build/init_color.o: ./interface/color/init_color.c
	$(OBJ)

build/registration.o: ./interface/registration/registration.c
	$(OBJ)

build/message.o: ./message/message.c
	$(OBJ)

build/receive_message_system_v.o: ./message/receive_message_system_v.c
	$(OBJ)

build/receive_message_posix.o: ./message/receive_message_posix.c
	$(OBJ)

build/send_message_system_v.o: ./message/send_message_system_v.c
	$(OBJ)

build/send_message_posix.o: ./message/send_message_posix.c
	$(OBJ)

build/send_message_shmem_system_v.o: ./message/send_message_shmem_system_v.c
	$(OBJ)

build/receive_message_shmem_system_v.o: ./message/receive_message_shmem_system_v.c
	$(OBJ)

build/send_message_shmem_posix.o: ./message/send_message_shmem_posix.c
	$(OBJ)

build/receive_message_shmem_posix.o: ./message/receive_message_shmem_posix.c
	$(OBJ)

clean:
	rm -rf bin
	rm -rf build
	rm -rf *.a 
	rm -rf client
	rm -rf *.so
#	rm -rf *.txt
	rm -rf *.o

folders:
#	mkdir bin
	mkdir build