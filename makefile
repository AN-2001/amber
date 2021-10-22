cc := gcc
flags := -Wall -Werror -pedantic-errors
libs := -lgd -lm
obj := colour.o boilerplate.o vec.o
proj := amber

all: $(proj)


$(proj): $(proj).c $(obj)
	$(cc) $< $(obj) $(flags) $(libs) -o $@

%.o : %.c %.h
	$(cc) -c $< -o $@ $(flags) $(libs)

clean:
	rm $(proj) $(obj)
	
