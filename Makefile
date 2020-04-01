CC=gcc

check: map_test list_test
	./map_test
	./list_test

map_test: ./map_test.c
	$(CC) map_test.c map.c -o $@

list_test: ./list_test.c
	$(CC) list_test.c list.c -o $@

clean:
	rm -f map_test list_test

.PHONY: clean check map_test list_test
