build:
	gcc -c -Wall -Werror -fPIC log.c -o log.o -std=c99 -g `pkg-config --libs --cflags glib-2.0`
	gcc -shared -o ../libs/libjetspace-logkit.so log.o
	rm log.o
	cp log.h ../header/logkit.h

clean:
	rm test
tester:
	gcc -std=c99 -Wall test.c -o test -ljetspace-logkit `pkg-config --libs --cflags glib-2.0`

python:
	swig -python log.i
	gcc -c -fPIC log.c log_wrap.c -I /usr/include/python3.4
	ld -shared log.o log_wrap.o -o _logkit.so
	rm *.o
	rm log_wrap.c

pythonclear:
	rm _logkit.so
	rm *.py
