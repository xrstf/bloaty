# Do not compile with -O2 or else gcc will remove the
# seemingly bogus memory allocations done by bloaty.

all: bloaty.c
	$(CC) -Wall -o bloaty bloaty.c

clean:
	rm -rf *o bloaty
