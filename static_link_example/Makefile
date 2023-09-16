CC=gcc

LIBDIR=/opt/homebrew/opt/libarchive/lib
INCLUDEDIR=/opt/homebrew/opt/libarchive/include

all:
	$(CC) *.c -o test -I$(INCLUDEDIR) $(LIBDIR)/libarchive.a

clean:
	rm -f *.o test

