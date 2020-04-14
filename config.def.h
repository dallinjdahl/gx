#define TABLE \
	 /*web addresses*/\
	X("https?://.+") \
	Y("port web \\0") \
	/*man files*/\
	X("([a-zA-Z0-9\\-_]+)\\(([0-9a-zA-Z]+)\\),?") \
	Y("port man \\2 \\1") \
	 /*local include files*/\
	X("#include \"([a-zA-Z0-9]+\\.h)\"") \
	Y("port edit \\1") \
	 /*standard include files*/\
	X("#include <([a-zA-Z0-9]+\\.h)>") \
	Y("port edit $(std_inc \\1)") \
	 /*addressed files: should work with gcc error output*/\
	X("(.+):([0-9]+):([0-9]+):.*") \
	Y("port 2a_edit \\1 \\2 \\3") \
	 /*addressed files: should work with grep -n */\
	X("(.+):([0-9]+|(/|\\?).+).*") \
	Y("port a_edit \\1 \\2")
