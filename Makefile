.POSIX:

include config.mk

all: gx

gx: gx.c
	gcc $< -lregexp9 -lutf -o $@

clean:
	rm -rfv gx

install: all
	mkdir -p $(DESTDIR)$(PREFIX)/bin
	cp -f gx $(DESTDIR)$(PREFIX)/bin
	chmod 755 $(DESTDIR)$(PREFIX)/bin/gx 

uninstall:
	rm -f $(DESTDIR)$(PREFIX)/bin/gx

.PHONY: all clean install uninstall

