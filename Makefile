.POSIX=
.SUFFIXES=

CC = cc
CFLAGS = -Wall -Wextra -Werror -pedantic -O2
LDLIBS = -lm
PREFIX = ${HOME}/.local

all: sqfactors factors isprime primefact make_prime_table

factors: factors.o lazy.o lazy.h lazyfuncs.o
	${CC} ${LDFLAGS} -o $@ factors.o lazy.o lazyfuncs.o ${LDLIBS}

sqfactors: sqfactors.o lazy.o lazy.h lazyfuncs.o
	${CC} ${LDFLAGS} -o $@ sqfactors.o lazy.o lazyfuncs.o ${LDLIBS}

isprime: isprime.o lazy.o lazy.h lazyfuncs.o
	${CC} ${LDFLAGS} -o $@ isprime.o lazy.o lazyfuncs.o ${LDLIBS}

primefact: primefact.o lazy.o lazyfuncs.o lazy.h
	${CC} ${LDFLAGS} -o $@ primefact.o lazy.o lazyfuncs.o ${LDLIBS}

make_prime_table: make_prime_table.o lazy.o lazy.h
	${CC} ${LDFLAGS} -o $@ make_prime_table.o lazy.o ${LDLIBS}

prime_table.h: make_prime_table
	./make_prime_table > prime_table.h

lazyfuncs.o: lazyfuncs.c lazyfuncs.h prime_table.h
	${CC} -c ${CFLAGS} $<

clean:
	rm sqfactors factors isprime primefact make_prime_table *.o prime_table.h

install: all
	mkdir -p ${DESTDIR}${PREFIX}/bin
	cp -i -t ${DESTDIR}${PREFIX}/bin factors sqfactors isprime primefact
	chmod u+x ${DESTDIR}${PREFIX}/bin/{factors,sqfactors,isprime,primefact}

uninstall:
	rm -i ${DESTDIR}${PREFIX}/bin/{factors,sqfactors,isprime,primefact}

.SUFFIXES=.c .o

.c.o:
	${CC} -c ${CFLAGS} $<

.PHONY: all clean install uninstall
