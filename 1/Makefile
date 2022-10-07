CC = gcc
CFLAGS = -std=c99 -Wall -Wextra -pedantic -lm -fcommon

c201:
	@rm -f current-test.output
	@curl -so c201.h https://pastebin.com/raw/9wEfSiRX
	@curl -so c201-test-utils.h https://pastebin.com/raw/Z20CnMBn
	@curl -so c201-test-utils.c https://pastebin.com/raw/vrHtUyLE
	@curl -so c201-test.c https://pastebin.com/raw/ixd7rfzL
	@curl -so c201-test.output https://pastebin.com/raw/rruFmuK9
	@$(CC) $(CFLAGS) -o c201-test c201.c c201-test.c c201-test-utils.c
	@./c201-test > current-test.output
	@echo "\nTest output differences:"
	@tr -d '\r' <c201-test.output | diff -su - current-test.output | cat
	@rm -f c201-test c201.h c201-test-utils.h c201-test-utils.c c201-test.c c201-test.output

c203:
	@rm -f current-test.output
	@curl -so c203.h https://www.pastery.net/haesgq/raw
	@curl -so c203-test-utils.h https://www.pastery.net/sedfxx/raw
	@curl -so c203-test-utils.c https://www.pastery.net/cygwzc/raw
	@curl -so c203-test.c https://www.pastery.net/wyjvez/raw
	@curl -so c203-test.output https://www.pastery.net/ndddka/raw
	@$(CC) $(CFLAGS) -o c203-test c203.c c203-test.c c203-test-utils.c
	@./c203-test > current-test.output
	@echo "\nTest output differences:"
	@tr -d '\r' <c203-test.output | diff -su - current-test.output | cat
	@rm -f c203-test c203.h c203-test-utils.h c203-test-utils.c c203-test.c c203-test.output

c206:
	@rm -f current-test.output
	@curl -so c206.h https://www.pastery.net/acnruk/raw
	@curl -so c206-test-utils.h https://www.pastery.net/pgxtud/raw
	@curl -so c206-test-utils.c https://www.pastery.net/ctajnr/raw
	@curl -so c206-test.c https://www.pastery.net/fhhfup/raw
	@curl -so c206-test.output https://www.pastery.net/gkwbbe/raw
	@$(CC) $(CFLAGS) -o c206-test c206.c c206-test.c c206-test-utils.c
	@./c206-test > current-test.output
	@echo "\nTest output differences:"
	@tr -d '\r' <c206-test.output | diff -su - current-test.output | cat
	@rm -f c206-test c206.h c206-test-utils.h c206-test-utils.c c206-test.c c206-test.output
