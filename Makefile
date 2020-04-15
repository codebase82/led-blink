all: led-blink

display-daemon: led-blink.c 
	arm-linux-gnueabihf-gcc led-blink.c -g -Wall -o led-blink

install: led-blink
	cp $< $(DESTDIR)$(PREFIX)/led-blink

clean:
	rm led-blink
