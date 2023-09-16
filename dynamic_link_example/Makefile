CC=gcc

INCLUDEDIR=/opt/homebrew/opt/libarchive/include
LIBDIR=/opt/homebrew/opt/libarchive/lib

all:
	$(CC) *.c -o test -I$(INCLUDEDIR) #$(LIBDIR)/liblzma.a
	tar cvf archive.tar test

clean:
	rm -f *.o test
	rm -f archive.tar
