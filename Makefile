.POSIX:

include config.mk

all: gx port std_inc dwmgx

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
	cp -f gx port std_inc dwmgx $(DESTDIR)$(PREFIX)/bin
	chmod 755 $(DESTDIR)$(PREFIX)/bin/gx 
	chmod 755 $(DESTDIR)$(PREFIX)/bin/port 
	chmod 755 $(DESTDIR)$(PREFIX)/bin/std_inc 
	chmod 755 $(DESTDIR)$(PREFIX)/bin/dwmgx 

uninstall:
	rm -f $(DESTDIR)$(PREFIX)/bin/gx
	rm -f $(DESTDIR)$(PREFIX)/bin/port
	rm -f $(DESTDIR)$(PREFIX)/bin/std_inc
	rm -f $(DESTDIR)$(PREFIX)/bin/dwmgx

.PHONY: all clean install uninstall

