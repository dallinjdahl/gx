#define TABLE \
	X("https?://.+") \
	Y("firefox \\0") \
	X("#include \"([a-zA-Z0-9]+\\.h)\"") \
	Y("E \\1")
