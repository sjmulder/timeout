DESTDIR?=
PREFIX?=	/usr/local

CFLAGS+=	-Wall -Werror

all: timeout

clean:
	rm -f timeout

install: all
	install -d ${DESTDIR}${PREFIX}/bin
	install -m755 timeout ${DESTDIR}${PREFIX}/bin/

uninstall:
	rm -f ${DESTDIR}${PREFIX}/bin/timeout

.PHONY: all clean install uninstall
