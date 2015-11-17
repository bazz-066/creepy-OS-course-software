CC=gcc
CFLAGS=-lpthread

writer:
	@rm -f dstfile.txt
	@$(CC) -o write.o write.c $(CFLAGS)
	@./write.o
	@cat dstfile.txt

