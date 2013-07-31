it: it.o
CLEANFILES+=it

it.o: it.c
CLEANFILES+=it.o

clean:
	rm -f $(CLEANFILES)
