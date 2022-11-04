CC=gcc
CFLAGS=-Wall -std=c11 -pedantic -lm
FILES=btree.c ../btree.c ../test_util.c ../test.c

.PHONY: test clean

test:
	@echo "======== rec/btree ========"
	@rm -f current-test.output
	@wget -qO ../btree.h https://www.pastery.net/ncbdfu/raw
	@wget -qO ../btree.c https://www.pastery.net/znebzw/raw
	@wget -qO ../test_util.h https://www.pastery.net/hqtsxc/raw
	@wget -qO ../test_util.c https://www.pastery.net/ysmbjj/raw
	@wget -qO ../test.c https://www.pastery.net/qyfpdh/raw
	@wget -qO ../btree-test.output https://www.pastery.net/mtkxmb/raw
	@$(CC) $(CFLAGS) -o $@ $(FILES)
	@./test > current-test.output
	@echo "Test output differences:"
	@tr -d '\r' <../btree-test.output | diff -su - current-test.output | cat
	@rm -f test ../btree.h ../btree.c ../test_util.h ../test_util.c ../test.c ../btree-test.output

clean:
	rm -f test
