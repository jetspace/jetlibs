build:
	gcc -c -std=c99 -Wall -Werror -fPIC  process.c -o process.o -g
	gcc -shared -o ../libs/libjetspace-processkit.so process.o -g
	cp process.h ../header/processkit.h
	rm process.o
tester:
	gcc -std=c99 test.c -o test -ljetspace-processkit -g
clean:
	rm test
