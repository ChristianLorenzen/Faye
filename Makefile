exec = faye.out
OBJDIR = out
sources = $(wildcard src/*.c)
objects = $(sources:.c=.o)
flags = -g
OUTDIR = out/
echomv = echo $(objects)
echoOUT = echo $(OUTDIR)
move = mv $(objects) $(OUTDIR)
OUTPROG = /usr/local/bin/
PROGDIR = src/

$(exec): $(objects)
	gcc $(objects) $(flags) -o $(exec)

%.o: %.c include/%.h
	gcc -c $(flags) $< -o $@

test:
	$(echomv)
	$(echoOUT)

install:
	make
	test -d $(OUTPROG) || mkdir $(OUTPROG)
	cp ./faye.out $(OUTPROG)faye
	test -d $(OUTDIR) || mkdir $(OUTDIR)
	$(move)

clean:
	-rm *.out
	-rm *.o
	test -d $(PROGDIR) || -rm $(PROGDIR)*.o


