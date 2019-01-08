all: bloaty.c
	$(CC) -O2 -Wall -o bloaty bloaty.c

clean:
	rm -rf *o bloaty
