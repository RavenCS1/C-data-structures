BINARY=Red_black_tree
CODEDIRS=. ./src/
INCDIRS=. ./include/

CC=gcc
OPT=-O3

DEPFLAGS=-MP -MD
CFLAGS=-Wall -Wextra -g -std=c2x $(foreach D, $(INCDIRS), -I$(D)) $(OPT) $(DEPFLAGS)

CFILES=$(foreach D, $(CODEDIRS), $(wildcard $(D)/*.c))
OBJECTS=$(patsubst %.c,%.o,$(CFILES))
DEPFILES=$(patsubst %.c,%.d,$(CFILES))

# Domyślny target - buduje i czyści .o pliki
all: $(BINARY)

# Linkowanie binarki
$(BINARY): $(OBJECTS)
	$(CC) -o $@ $^

# Kompilacja .o plików
%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

# NOWY TARGET: buduje + kasuje .o (zostawia binarkę)
build-clean: $(BINARY)
	rm -f $(OBJECTS) $(DEPFILES)

# Pełny clean (z binarką)
clean:
	rm -f $(OBJECTS) $(DEPFILES) $(BINARY)

distribute: clean
	tar zcvf dist.tgz *

diff:
	$(info The status of the repository)
	@git status
	@git diff --stat

-include $(DEPFILES)
