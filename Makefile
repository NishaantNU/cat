cat:
	gcc src/main.c -o out/cat

debug:
	gcc src/main.c -o out/cat_debug -g -Wall -Wextra -O0
clean:
	rm out/cat out/cat_debug
