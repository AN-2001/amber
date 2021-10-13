cc := gcc
flags := -Wall -Werror -pedantic-errors
libs := -lgd -lm
obj := colour.o vec.o

all: amber


amber: amber.c config.h $(obj)
	gcc amber.c $(obj) $(libs) $(flags) -o $@

%.o: %.c %.h config.h
	gcc -c $< $(flags) $(libs) -o $@
clean:
	rm amber $(obj)
