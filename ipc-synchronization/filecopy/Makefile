CC=gcc
CFLAGS=-lpthread

copier:
	@rm -f 2ndfile.txt
	@$(CC) -o copier.o copier.c $(CFLAGS)
	@./copier.o
	@md5sum 1stfile.txt 2ndfile.txt

test:
	@cp 1stfile.txt tmp.txt
	@rm -f 2ndfile.txt
	@echo "----------------------------------------------------------------------------------------------------" > 1stfile.txt
	@echo "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" >> 1stfile.txt
	@$(CC) -o copier.o copier.c $(CFLAGS)
	@./copier.o
	@md5sum 1stfile.txt 2ndfile.txt
	cat 1stfile.txt
	cat 2ndfile.txt
	@cp tmp.txt 1stfile.txt
