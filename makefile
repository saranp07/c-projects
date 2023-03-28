mypreprocessor:header.o macro.o comments.o
	cc header.o macro.o comments.o -o mypreprocessor
header.o:header.c
	cc -c header.c
macro.o:macro.c
	cc -c macro.c
comments.o:comments.c
	cc -c comments.c
