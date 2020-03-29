CC=gcc

check: map_test
	./map_test

map_test: ./map_test.c
	$(CC) map_test.c map.c -o $@

clean:
	rm -f map_test

.PHONY: clean check map_test
