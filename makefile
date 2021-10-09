cc := gcc
flags := -Wall -Werror -pedantic-errors -g
libs := -lgd -lm
obj := colour.o vec.o

all: amber


amber: amber.c $(obj)
	gcc amber.c $(obj) $(libs) $(flags) -o $@

%.o: %.c %.h
	gcc -c $< $(flags) $(libs) -o $@
clean:
	rm amber $(obj)
