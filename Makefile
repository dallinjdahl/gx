.POSIX:

include config.mk

all: gx port std_inc

gx: gx.c config.h
	gcc $< -lregexp9 -lutf -o $@

config.h:
	cp config.def.h config.h

port:
	cp port.def port

clean:
	rm -rfv gx

install: all
	mkdir -p $(DESTDIR)$(PREFIX)/bin
	cp -f gx port std_inc $(DESTDIR)$(PREFIX)/bin
	chmod 755 $(DESTDIR)$(PREFIX)/bin/gx 
	chmod 755 $(DESTDIR)$(PREFIX)/bin/port 
	chmod 755 $(DESTDIR)$(PREFIX)/bin/std_inc 

uninstall:
	rm -f $(DESTDIR)$(PREFIX)/bin/gx

.PHONY: all clean install uninstall

