build:
	gcc -c -std=c99 -Wall -Werror -fPIC  config.c -o config.o
	gcc -shared -o ../libs/libjetspace-configkit.so config.o
	cp config.h ../header/configkit.h
	rm config.o
tester:
	gcc -std=c99 test.c -o test -ljetspace-configkit
clean:
	rm test
