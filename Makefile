exec = faye.out
OBJDIR = out
sources = $(wildcard src/*.c)
objects = $(sources:.c=.o)
flags = -g
move = mv $(objects) out/
OUTPROG = /usr/local/bin/


$(exec): $(objects)
	gcc $(objects) $(flags) -o $(exec)

%.o: %.c include/%.h
	gcc -c $(flags) $< -o $@

install:
	make
	test -d $(OUTPROG) || mkdir $(OUTPROG)
	cp ./faye.out $(OUTPROG)faye
	$(move)

clean:
	-rm *.out
	-rm *.o
	-rm src/*.o

