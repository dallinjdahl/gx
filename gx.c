#include <utf.h>
#include <fmt.h>
#include <regexp9.h>

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <ctype.h>
#include <fcntl.h>
#include <unistd.h>

#include "config.h"

struct match {
	char *re;
	Reprog *prog;
};


#define X(s) {s, 0},
#define Y(s) {0, 0},
struct match matches[] = {
	TABLE
	{(char *)-1, (Reprog *)-1},
};
#undef X
#undef Y


#define X(s)
#define Y(s) s,
char *commands[] = {
	TABLE
	0,
};
#undef X
#undef Y


char buf[1024] = {0};
char *in;

Resub results[8];
char run[4096] = {0};

uint8_t VERBOSE = 0;
uint8_t MESSAGE = 0;

void fill() {
	int devnull = open("/dev/null", O_RDONLY);
	fgets(buf, 1024, stdin);
	dup2(devnull, fileno(stdin));
	dup2(devnull, fileno(stdout));
	VERBOSE ? 0 : dup2(devnull, fileno(stderr));
	close(devnull);
}

void init() {
	for(struct match *i = matches; i->re != (char *)-1; i++) {
		if(i->re == 0) {
			continue;
		}
		i->prog = regcomp(i->re);
	}
}

void doplumb() {
	uint8_t found = 1;
	uint16_t j = 0;
	for(struct match *i = matches; i->re != (char *)-1; i++) {
		if(!found && i->re == 0) {
			found = 1;
			j++;
			continue;
		}
		if(!found) {
			continue;
		}
		if(i->re == 0) {
			regsub(commands[j], run, 4096, results, 8);
			VERBOSE ? fprintf(stderr, "running: %s\n", run) : 0;
			if(fork() == 0) {
				execl("/bin/sh", "sh", "-c", run, NULL);
			}
			exit(0);
		}
		VERBOSE ? fprintf(stderr, "checking %s against %s for %s\n", in, i->re, commands[j]) : 0;
		results->s.sp = 0;
		results->e.ep = 0;
		found = regexec(i->prog, in, results, 8) == 1;
		if(found) {
			VERBOSE ? fprintf(stderr, "found for %s\n", commands[j]) : 0;
			found = results->s.sp == in && !*(results->e.ep);
		}
	}
}

uint8_t streq(char *s, char *t) {
	while(*s && *s == *t) {
		s++;
		t++;
	}
	return *s == *t;
}

char *trim(char *s) {
	while(*s && isspace(*s)) s++;
	if(!*s) return s;
	char *e = s;
	while(*e) e++;
	e--;
	while(isspace(*e)) *(e--) = 0;
	return s;
}

int main(int argc, char ** argv) {
	for(int i = 1; i < argc; i++) {
		if(streq(argv[i], "-h")) {
			printf("Usage: gx [--verbose] [-m \"message\"]\n");
			exit(0);
		}
		if(streq(argv[i], "--verbose")) {
			VERBOSE=1;
		}
		if(streq(argv[i], "-m")) {
			MESSAGE=1;
			i++;
			in = argv[i];
		}
	}

	if(!MESSAGE) {
		fill();
		in = buf;
	}

	in = trim(in);
	init();
	doplumb();
	exit(1);
}

