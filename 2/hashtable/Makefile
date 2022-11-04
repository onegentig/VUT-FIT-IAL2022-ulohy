CC=gcc
CFLAGS=-Wall -std=c11 -pedantic
FILES=hashtable.c test.c test_util.c

.PHONY: test clean

test:
	@echo "======== hashtable ========"
	@rm -f current-test.output
	@wget -qO hashtable.h https://www.pastery.net/zdvrep/raw
	@wget -qO test_util.h https://www.pastery.net/cepfuz/raw
	@wget -qO test_util.c https://www.pastery.net/pkcfhb/raw
	@wget -qO test.c https://www.pastery.net/dqgfvb/raw
	@wget -qO hashtable-test.output https://www.pastery.net/pdebdh/raw
	@$(CC) $(CFLAGS) -o $@ $(FILES)
	@./test > current-test.output
	@echo "Test output differences:"
	@tr -d '\r' <hashtable-test.output | diff -su - current-test.output | cat
	@rm -f test hashtable.h test_util.h test_util.c test.c hashtable-test.output

clean:
	rm -f test
