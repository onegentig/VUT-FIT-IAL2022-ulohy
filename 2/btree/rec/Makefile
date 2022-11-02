CC=gcc
CFLAGS=-Wall -std=c11 -pedantic -lm
FILES=btree.c ../btree.c ../test_util.c ../test.c

.PHONY: test clean

test: $(FILES)
	@echo "======== rec/btree ========"
	@rm -f current-test.output
	@$(CC) $(CFLAGS) -o $@ $(FILES)
	@./test > current-test.output
	@echo "Test output differences:"
	@tr -d '\r' <../btree-test.output | diff -su - current-test.output | cat

clean:
	rm -f test
