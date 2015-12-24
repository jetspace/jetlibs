build:
	mkdir libs header -p
	make -C logkit
	make -C configkit
	make -C commandkit

install:
	sudo mkdir -p /usr/include/jetspace/
	sudo cp header/* /usr/include/jetspace/
	sudo cp libs/* /usr/lib/
