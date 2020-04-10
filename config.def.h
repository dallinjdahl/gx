#define TABLE \
	 /*web addresses*/\
	X("https?://.+") \
	Y("port web \\0") \
	 /*local include files*/\
	X("#include \"([a-zA-Z0-9]+\\.h)\"") \
	Y("port edit \\1") \
	 /*standard include files*/\
	X("#include <([a-zA-Z0-9]+\\.h)>") \
	Y("port edit $(std_inc \\1)") \
	 /*addressed files: should work with grep -n */\
	X("(.+):([0-9]+|(/|\\?).+).*") \
	Y("port a_edit \\1 \\2")

