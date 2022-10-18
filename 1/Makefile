CC = gcc
CFLAGS = -std=c99 -Wall -Wextra -pedantic -lm -fcommon

all:
	@make -s c201
	@sleep 1s
	@make -s c203
	@sleep 1s
	@make -s c206
	@rm -f current-test.output

c201:
	@echo "======== c201 ========"
	@rm -f current-test.output
	@wget -qO c201.h https://pastebin.com/raw/9wEfSiRX
	@wget -qO c201-test-utils.h https://pastebin.com/raw/Z20CnMBn
	@wget -qO c201-test-utils.c https://pastebin.com/raw/vrHtUyLE
	@wget -qO c201-test.c https://pastebin.com/raw/ixd7rfzL
	@wget -qO c201-test.output https://pastebin.com/raw/rruFmuK9
	@$(CC) $(CFLAGS) -o c201-test c201.c c201-test.c c201-test-utils.c
	@./c201-test > current-test.output
	@echo "Test output differences:"
	@tr -d '\r' <c201-test.output | diff -su - current-test.output | cat
	@rm -f c201-test c201.h c201-test-utils.h c201-test-utils.c c201-test.c c201-test.output

c203:
	@echo "======== c203 ========"
	@rm -f current-test.output
	@wget -qO c203.h https://www.pastery.net/haesgq/raw
	@wget -qO c203-test-utils.h https://www.pastery.net/sedfxx/raw
	@wget -qO c203-test-utils.c https://www.pastery.net/cygwzc/raw
	@wget -qO c203-test.c https://www.pastery.net/wyjvez/raw
	@wget -qO c203-test.output https://www.pastery.net/ndddka/raw
	@$(CC) $(CFLAGS) -o c203-test c203.c c203-test.c c203-test-utils.c
	@./c203-test > current-test.output
	@echo "Test output differences:"
	@tr -d '\r' <c203-test.output | diff -su - current-test.output | cat
	@rm -f c203-test c203.h c203-test-utils.h c203-test-utils.c c203-test.c c203-test.output

c206:
	@echo "======== c206 ========"
	@rm -f current-test.output
	@wget -qO c206.h https://www.pastery.net/acnruk/raw
	@wget -qO c206-test-utils.h https://www.pastery.net/pgxtud/raw
	@wget -qO c206-test-utils.c https://www.pastery.net/ctajnr/raw
	@wget -qO c206-test.c https://www.pastery.net/fhhfup/raw
	@wget -qO c206-test.output https://www.pastery.net/gkwbbe/raw
	@$(CC) $(CFLAGS) -o c206-test c206.c c206-test.c c206-test-utils.c
	@./c206-test > current-test.output
	@echo "Test output differences:"
	@tr -d '\r' <c206-test.output | diff -su - current-test.output | cat
	@rm -f c206-test c206.h c206-test-utils.h c206-test-utils.c c206-test.c c206-test.output