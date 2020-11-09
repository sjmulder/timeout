DESTDIR?=
PREFIX?=	/usr/local
MANPREFIX?=	${PREFIX}/man

CFLAGS+=	-Wall -Werror

all: timeout

clean:
	rm -f timeout

install: all
	install -d ${DESTDIR}${PREFIX}/bin \
	           ${DESTDIR}${MANPREFIX}/man1
	install -m755 timeout   ${DESTDIR}${PREFIX}/bin/
	install -m644 timeout.1 ${DESTDIR}${MANPREFIX}/man1/

uninstall:
	rm -f ${DESTDIR}${PREFIX}/bin/timeout \
	      ${DESTDIR}${MANPREFIX}/man1/timeout.1

.PHONY: all clean install uninstall
