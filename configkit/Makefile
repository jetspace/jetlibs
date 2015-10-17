build:
	gcc -c -std=c99 -Wall -Werror -fPIC  config.c -o config.o
	gcc -shared -o ../libs/libjetspace-configkit.so config.o
	cp config.h ../header/configkit.h
	rm config.o
tester:
	gcc -std=c99 test.c -o test -ljetspace-configkit
clean:
	rm test

python:
	swig -python config.i
	gcc -c -fPIC config.c config_wrap.c -I /usr/include/python3.4
	ld -shared config.o config_wrap.o -o _configkit.so
	rm *.o
	rm config_wrap.c

pythonclear:
	rm _configkit.so
	rm *.py
