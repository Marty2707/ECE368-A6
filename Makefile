WARNING = -Wall -Wshadow --pedantic
ERROR = -Wvla -Werror
GCC = gcc -std=c99 -g $(WARNING) $(ERROR)

a5: a6.o
	$(GCC) a6.o -o a6

a5.o: a6.c
	$(GCC) -c a6.c -o a6.o

clean:
	rm -f *.o a6
