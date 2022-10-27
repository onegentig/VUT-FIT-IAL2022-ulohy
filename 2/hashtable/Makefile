CC=gcc
CFLAGS=-Wall -std=c11 -pedantic
FILES=hashtable.c test.c test_util.c

.PHONY: test clean

test: $(FILES)
	@echo "======== hashtable ========"
	@rm -f current-test.output
	@wget -qO hashtable-test.output https://www.pastery.net/pdebdh/raw
	@$(CC) $(CFLAGS) -o $@ $(FILES)
	@./test > current-test.output
	@echo "Test output differences:"
	@tr -d '\r' <hashtable-test.output | diff -su - current-test.output | cat
	@valgrind -s --leak-check=full --show-leak-kinds=all --track-origins=yes --log-file="valgrind.output" test

clean:
	rm -f test
