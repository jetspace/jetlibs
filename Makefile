export CFLAGS_BASE =
export LDFLAGS_BASE =

ifdef TRAVIS
CFLAGS_BASE += -coverage -fprofile-arcs -ftest-coverage
LDFLAGS_BASE += -fprofile-arcs
endif

build:
	mkdir libs header -p
	$(MAKE) -C logkit
	$(MAKE) -C configkit
	$(MAKE) -C commandkit
	$(MAKE) -C processkit

install:
	sudo mkdir -p /usr/include/jetspace/
	sudo cp header/* /usr/include/jetspace/
	sudo cp libs/* /usr/lib/

test:
	make runtests -C tests
