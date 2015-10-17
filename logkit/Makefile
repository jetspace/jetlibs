build:
	gcc -c -Wall -Werror -fPIC log.c -o log.o -std=c99 -g
	gcc -shared -o ../libs/libjetspace-logkit.so log.o
	rm log.o
	cp log.h ../header/logkit.h

clean:
	rm test
tester:
	gcc -std=c99 -Wall test.c -o test -ljetspace-logkit
