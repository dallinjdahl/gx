# gx
gx is a utility inspired by the
[plan9 plumber](http://doc.cat-v.org/plan_9/4th_edition/papers/plumb)
and [suckless utilities](https://suckless.org).

## Building
gx depends on the unix version of plan9's
[regex library](https://9fans.github.io/plan9port/unix/).  Other than that:
```
make && sudo make install
```

## port
port is a script that dissassociates interfaces from implementations.
This allows you to register multiple implementations for a given interface,
and makes it easier to use in a multi-user environment.
```
#!/bin/sh
op="$1"
shift 1
case "$op" in
	web)
		firefox "$@" &
		;;
	edit)
		st vim $@ &
		;;
esac
```
This routes web actions to firefox, and edits to vim running in st.

## config.h
gx uses [X macros](https://en.wikipedia.org/wiki/X_Macro) to simplify
the development, so each line but the last must have a `\` as the
last character.  X lines define regular expressions that must match the
input on stdin, then the following Y line specifies the command to run.
Note that the X lines must match the input in it's entirety, or it
doesn't count as a match.  Also, if a backslash is needed to escape
a character, it must be doubled so as to escape the c string parsing.
The Y line can use `\\n` where `n` is a digit to specify a sub match to
be interpolated.  `\\0` matches the entire regex (so the entire input),
while `\\1` matches from the leftmost parenthese to it's closing pair.

Example:
```
#define TABLE \
	X("https?://.+") \
	Y("port web \\0") \
	X("#include \"([a-zA-Z0-9]+\\.h)\"") \
	Y("port edit \\1")
```
When presented with a http or https url, it runs the web port to open it,
and when presented with an include directive, it will open the edit port on the file.
This is meant to be run, among other ways,
inside vim or [vis](https://github.com/martanne/vis) to better utilize
linux and [dwm](https://dwm.suckless.org) as an ide.

## Features
Note that if the last character in the input is a newline, it doesn't
have to be matched.  There are limits to the number of matches (8) and
the length of the input (1023 bytes) and the regex-interpolated command to
run (4095 bytes). If you don't like them, you can edit them in the source.

## dwm
To aid in incorporating this with dwm, there is a script, `dwmgx` that
pipes the primary selection to gx.  It can be added to your dwm config.h
