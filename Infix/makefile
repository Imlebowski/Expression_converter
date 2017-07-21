TARGET := ../lib/libInfix.so
SRC := $(wildcard *.c)
Cflag := -I ../include
LFLAG := -L ../lib 

all: ${TARGET}

${TARGET} : ${SRC}
		gcc -fPIC -shared $^ ${LFLAG} ${Cflag} -o $@

clean:
		rm ${TARGET}
