runtests:
	gcc test.c -Wall -Wextra -std=c99 -g -O0 -coverage -fprofile-arcs -ftest-coverage `pkg-config --libs check` -ljetspace-configkit -o test
	./test
