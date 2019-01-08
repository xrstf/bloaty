all: bloaty.c
	$(CC) -o bloaty bloaty.c

clean:
	rm -rf *o bloaty
