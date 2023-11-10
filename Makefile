CC=x86_64-w64-mingw32-gcc
CFLAGS=-Wall -s -shared

Str8.asi: dllmain.c memory.c
	$(CC) $(CFLAGS) $^ -o $@

.PHONY: clean

clean:
	rm -f Str8.asi
