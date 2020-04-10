# gx
gx is a utility inspired by the [plan9 plumber](http://doc.cat-v.org/plan_9/4th_edition/papers/plumb) and [suckless utilities](https://suckless.org).

## config.h
gx uses [X macros](https://en.wikipedia.org/wiki/X_Macro) to simplify the development, so each line but the
last must have a `\` as the last character.
X lines define regular expressions that must match the input on stdin, then the following Y line specifies the command
to run.  Note that the X lines must match the input in it's entirety, or it doesn't count as a match.
The Y line can use `\n` where `n` is a digit to specify a sub match to be interpolated.
`\0` matches the entire regex (so the entire input), while `\1` matches from the leftmost parenthese to it's closing pair.

Example:
```
#define TABLE \
	X("https?://.+") \
	Y("firefox \\0") \
	X("#include \"([a-zA-Z0-9]+\\.h)\"") \
	Y("st vim \\1")
```
so when presented with a http or https url, it runs firefox to open it, and when presented with an include directive, it will open a terminal running vim and the file.  This is meant to be run, among other ways, inside vim or [vis](https://github.com/martanne/vis) to better utilize linux and [dwm](https://dwm.suckless.org) as an ide.

## features
Note that if the last character in the input is a newline, it doesn't have to be matched.  There are limits to the number of matches (8) and the length of the input (1023 bytes) and the regex-interpolated command to run (4095 bytes). If you don't like them, you can edit them in the source.
