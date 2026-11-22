all: main

main: main.cb
	gcc -Wall -Wextra -o main main.c

clean:
	rm -f main
