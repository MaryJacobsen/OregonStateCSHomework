CC=gcc
exe=a.out

$(exe): list.o test_list.o
	$(CC) list.o test_list.o -o $(exe)
list.o: list.c
	$(CC) -c list.c
test_list.o: test_list.c
	$(CC) -c test_list.c

