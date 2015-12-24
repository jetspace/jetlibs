build:
	gcc -c -Wall -Werror -fPIC command.c -o command.o -std=c99 -g
	gcc -shared -o ../libs/libjetspace-commandkit.so command.o
	rm command.o
	cp command.h ../header/commandkit.h
clean:
	rm test
tester:
	gcc --std=c99 -rdynamic  -Wall test.c -o test -ljetspace-commandkit `pkg-config --libs --cflags glib-2.0` -g
