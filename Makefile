DEPS = gtk+-2.0 webkit-1.0
CFLAGS = `pkg-config --cflags ${DEPS}` -Wall -Wextra -g
LDFLAGS = `pkg-config --libs ${DEPS}`
OBJ = docarchive.o directory_view.o directory_selection.o browser.o
CONF = config.c config.h

all: docarchive ${CONF}

docarchive: ${OBJ}

%.o: %.h

clean:
	rm -f docarchive *.o
