SRC_FILES=test.c melodies.c

LDLIBS=-lportaudio -lm
CFLAGS=-DSLIPS_TEST
test: test.o melodies.o

# Magic to build Makefile.depend if it does not exist
ifndef DEPEND_RECURSE
ifeq ($(shell test -e Makefile.depend && echo yes),yes)
include Makefile.depend
else
# Do not want to try to do this again when we get called from here, hence the
# recurse block
$(info $(shell make depend DEPEND_RECURSE=1))
include Makefile.depend
endif
endif

depend: Makefile.depend

Makefile.depend: $(SRC_FILES)
	$(CC) $(CFLAGS) -MM $^ > $@

clean:
	rm -rf *.o
